#include "mpi.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
#include <complex.h>
#elif defined(__APPLE__) || defined(__linux__)
#include <time.h>
#endif

int fbmpi_memcpy(void* dest, const void* src, size_t count)
{
  memcpy(dest, src, count);
  return MPI_SUCCESS;
}

enum fbmpi_request_type {
  FBMPI_SEND,
  FBMPI_RECEIVE,
  FBMPI_REDUCE,
  FBMPI_GATHER,
  FBMPI_BARRIER
};

struct fbmpi_request {
  enum fbmpi_request_type type;
  const void* const_buf;
  void* non_const_buf;
  int count;
  MPI_Datatype datatype;
  int tag;
  int is_complete;
};

struct fbmpi_op {
  char msvc_hates_empty_structs;
};

struct fbmpi_comm_attribute_key {
  int keyval;
  MPI_Comm_copy_attr_function* copy_function;
  MPI_Comm_delete_attr_function* delete_function;
  void* extra_state;
  int freed;
  int reference_count;
};

struct fbmpi_comm_attribute_keys_s {
  struct fbmpi_comm_attribute_key* array;
  int size;
};

struct fbmpi_attribute_value {
  int keyval;
  void* value;
};

struct fbmpi_attribute_values {
  struct fbmpi_attribute_value* array;
  int size;
};

struct fbmpi_requests {
  MPI_Request* array;
  int size;
};

struct fbmpi_comm {
  int id;
  struct fbmpi_attribute_values attribute_values;
  struct fbmpi_requests incomplete_requests;
  int cart_ndims;
  int* cart_periods;
};

struct fbmpi_comms_s {
  MPI_Comm* array;
  int size;
};

struct fbmpi_comms_s fbmpi_comms;

struct fbmpi_comm fbmpi_comm_self;
struct fbmpi_comm fbmpi_comm_world;

int fbmpi_next_comm_id = 1;
MPI_Comm MPI_COMM_SELF = &fbmpi_comm_self;
MPI_Comm MPI_COMM_WORLD = &fbmpi_comm_world;

MPI_Errhandler MPI_ERRORS_ARE_FATAL;
MPI_Errhandler MPI_ERRORS_RETURN;

struct fbmpi_datatype {
  MPI_Count size;
};

MPI_Datatype fbmpi_byte;
MPI_Datatype fbmpi_packed;
MPI_Datatype fbmpi_char;
MPI_Datatype fbmpi_signed_char;
MPI_Datatype fbmpi_unsigned_char;
MPI_Datatype fbmpi_c_bool;
MPI_Datatype fbmpi_unsigned_short;
MPI_Datatype fbmpi_unsigned;
MPI_Datatype fbmpi_unsigned_long;
MPI_Datatype fbmpi_unsigned_long_long;
MPI_Datatype fbmpi_short;
MPI_Datatype fbmpi_int;
MPI_Datatype fbmpi_long;
MPI_Datatype fbmpi_long_long;
MPI_Datatype fbmpi_float;
MPI_Datatype fbmpi_double;
MPI_Datatype fbmpi_long_double;
MPI_Datatype fbmpi_int8_t;
MPI_Datatype fbmpi_int16_t;
MPI_Datatype fbmpi_int32_t;
MPI_Datatype fbmpi_int64_t;
MPI_Datatype fbmpi_uint8_t;
MPI_Datatype fbmpi_uint16_t;
MPI_Datatype fbmpi_uint32_t;
MPI_Datatype fbmpi_uint64_t;
MPI_Datatype fbmpi_c_float_complex;
MPI_Datatype fbmpi_c_double_complex;
MPI_Datatype fbmpi_short_int;
MPI_Datatype fbmpi_2int;
MPI_Datatype fbmpi_long_int;
MPI_Datatype fbmpi_float_int;
MPI_Datatype fbmpi_double_int;
MPI_Datatype fbmpi_count;

MPI_Op MPI_SUM;
MPI_Op MPI_PROD;
MPI_Op MPI_MIN;
MPI_Op MPI_MAX;
MPI_Op MPI_BOR;
MPI_Op MPI_LOR;
MPI_Op MPI_LAND;
MPI_Op MPI_MINLOC;
MPI_Op MPI_MAXLOC;

MPI_Message MPI_MESSAGE_NO_PROC;

static int fbmpi_is_initialized = 0;
static int fbmpi_is_finalized = 0;

static struct fbmpi_comm_attribute_keys_s fbmpi_comm_attribute_keys;

static void fbmpi_construct_comm(MPI_Comm comm)
{
  comm->id = fbmpi_next_comm_id;
  ++fbmpi_next_comm_id;
  comm->attribute_values.array = NULL;
  comm->attribute_values.size = 0;
  comm->incomplete_requests.array = NULL;
  comm->incomplete_requests.size = 0;
  comm->cart_ndims = 0;
  comm->cart_periods = NULL;
  int new_size = fbmpi_comms.size + 1;
  MPI_Comm* new_array = (MPI_Comm*)malloc(sizeof(MPI_Comm) * new_size);
  memcpy(new_array, fbmpi_comms.array, sizeof(MPI_Comm) * fbmpi_comms.size);
  new_array[fbmpi_comms.size] = comm;
  free(fbmpi_comms.array);
  fbmpi_comms.array = new_array;
  fbmpi_comms.size = new_size;
}

static void fbmpi_destroy_comm(MPI_Comm comm)
{
  int new_size = fbmpi_comms.size - 1;
  MPI_Comm* new_array = (MPI_Comm*)malloc(sizeof(MPI_Comm) * new_size);
  int new_i = 0;
  for (int old_i = 0; old_i < fbmpi_comms.size; ++old_i) {
    if (fbmpi_comms.array[old_i] != comm) {
      new_array[new_i] = fbmpi_comms.array[old_i];
      ++new_i;
    }
  }
  free(fbmpi_comms.array);
  fbmpi_comms.array = new_array;
  fbmpi_comms.size = new_size;
  while (comm->attribute_values.size) {
    MPI_Comm_delete_attr(comm, comm->attribute_values.array[0].keyval);
  }
  free(comm->cart_periods);
  comm->cart_periods = NULL;
}

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64)
typedef _Fcomplex fbmpi_native_float_complex;
typedef _Dcomplex fbmpi_native_double_complex;
#else
typedef float _Complex fbmpi_native_float_complex;
typedef double _Complex fbmpi_native_double_complex;
#endif

int PMPI_Init(int* argc, char*** argv)
{
  int thread_support_provided;
  return MPI_Init_thread(argc, argv, MPI_THREAD_SINGLE,
      &thread_support_provided);
}

int PMPI_Init_thread(
    int* argc,
    char*** argv,
    int required,
    int* provided)
{
  *provided = MPI_THREAD_SINGLE;
  (void)argc;
  (void)argv;
  fbmpi_comms.array = NULL;
  fbmpi_comms.size = 0;
  fbmpi_comm_attribute_keys.array = NULL;
  fbmpi_comm_attribute_keys.size = 0;
  fbmpi_construct_comm(MPI_COMM_WORLD);
  fbmpi_construct_comm(MPI_COMM_SELF);
  typedef struct { short value; int rank; } short_int_t;
  typedef struct { int value; int rank; } int_int_t;
  typedef struct { long value; int rank; } long_int_t;
  typedef struct { float value; int rank; } float_int_t;
  typedef struct { double value; int rank; } double_int_t;
  fbmpi_byte = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_byte->size = 1;
  fbmpi_packed = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_packed->size = 1;
  fbmpi_char = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_char->size = 1;
  fbmpi_signed_char = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_signed_char->size = 1;
  fbmpi_unsigned_char = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_unsigned_char->size = 1;
  fbmpi_c_bool = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_c_bool->size = sizeof(_Bool);
  fbmpi_unsigned_short = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_unsigned_short->size = sizeof(unsigned short int);
  fbmpi_unsigned = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_unsigned->size = sizeof(unsigned);
  fbmpi_unsigned_long = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_unsigned_long->size = sizeof(unsigned long);
  fbmpi_unsigned_long_long = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_unsigned_long_long->size = sizeof(unsigned long long);
  fbmpi_short = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_short->size = sizeof(signed short int);
  fbmpi_int = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_int->size = sizeof(int);
  fbmpi_long = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_long->size = sizeof(long);
  fbmpi_long_long = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_long_long->size = sizeof(long long int);
  fbmpi_float = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_float->size = sizeof(float);
  fbmpi_double = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_double->size = sizeof(double);
  fbmpi_long_double = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_long_double->size = sizeof(long double);
  fbmpi_int8_t = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_int8_t->size = sizeof(int8_t);
  fbmpi_int16_t = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_int16_t->size = sizeof(int16_t);
  fbmpi_int32_t = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_int32_t->size = sizeof(int32_t);
  fbmpi_int64_t = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_int64_t->size = sizeof(int64_t);
  fbmpi_uint8_t = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_uint8_t->size = sizeof(uint8_t);
  fbmpi_uint16_t = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_uint16_t->size = sizeof(uint16_t);
  fbmpi_uint32_t = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_uint32_t->size = sizeof(uint32_t);
  fbmpi_uint64_t = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_uint64_t->size = sizeof(uint64_t);
  fbmpi_c_float_complex = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_c_float_complex->size = sizeof(fbmpi_native_float_complex);
  fbmpi_c_double_complex = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_c_double_complex->size = sizeof(fbmpi_native_double_complex);
  fbmpi_short_int = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_short_int->size = sizeof(short_int_t);
  fbmpi_2int = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_2int->size = sizeof(int_int_t);
  fbmpi_long_int = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_long_int->size = sizeof(long_int_t);
  fbmpi_float_int = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_float_int->size = sizeof(float_int_t);
  fbmpi_double_int = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_double_int->size = sizeof(double_int_t);
  fbmpi_count = (MPI_Datatype)malloc(sizeof(struct fbmpi_datatype));
  fbmpi_count->size = sizeof(MPI_Count);
  fbmpi_is_initialized = 1;
  return MPI_SUCCESS;
}

int PMPI_Finalize(void)
{
  MPI_Type_free(&fbmpi_byte);
  MPI_Type_free(&fbmpi_packed);
  MPI_Type_free(&fbmpi_char);
  MPI_Type_free(&fbmpi_signed_char);
  MPI_Type_free(&fbmpi_unsigned_char);
  MPI_Type_free(&fbmpi_c_bool);
  MPI_Type_free(&fbmpi_unsigned_short);
  MPI_Type_free(&fbmpi_unsigned);
  MPI_Type_free(&fbmpi_unsigned_long);
  MPI_Type_free(&fbmpi_unsigned_long_long);
  MPI_Type_free(&fbmpi_short);
  MPI_Type_free(&fbmpi_int);
  MPI_Type_free(&fbmpi_long);
  MPI_Type_free(&fbmpi_long_long);
  MPI_Type_free(&fbmpi_float);
  MPI_Type_free(&fbmpi_double);
  MPI_Type_free(&fbmpi_long_double);
  MPI_Type_free(&fbmpi_int8_t);
  MPI_Type_free(&fbmpi_int16_t);
  MPI_Type_free(&fbmpi_int32_t);
  MPI_Type_free(&fbmpi_int64_t);
  MPI_Type_free(&fbmpi_uint8_t);
  MPI_Type_free(&fbmpi_uint16_t);
  MPI_Type_free(&fbmpi_uint32_t);
  MPI_Type_free(&fbmpi_uint64_t);
  MPI_Type_free(&fbmpi_c_float_complex);
  MPI_Type_free(&fbmpi_c_double_complex);
  MPI_Type_free(&fbmpi_short_int);
  MPI_Type_free(&fbmpi_2int);
  MPI_Type_free(&fbmpi_long_int);
  MPI_Type_free(&fbmpi_float_int);
  MPI_Type_free(&fbmpi_double_int);
  MPI_Type_free(&fbmpi_count);
  fbmpi_destroy_comm(MPI_COMM_WORLD);
  fbmpi_destroy_comm(MPI_COMM_SELF);
  fbmpi_is_finalized = 1;
  return MPI_SUCCESS;
}

int PMPI_Initialized(int* flag)
{
  *flag = fbmpi_is_initialized;
  return MPI_SUCCESS;
}

int PMPI_Finalized(int* flag)
{
  *flag = fbmpi_is_finalized;
  return MPI_SUCCESS;
}

int PMPI_Abort(MPI_Comm comm, int errorcode)
{
  exit(errorcode);
  return MPI_SUCCESS;
}

double PMPI_Wtime(void)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  LARGE_INTEGER windows_ticks;
  BOOL ok = QueryPerformanceCounter(&windows_ticks);
  if (!ok) {
    return MPI_ERR_UNKNOWN;
  }
  LARGE_INTEGER windows_frequency;
  ok = QueryPerformanceFrequency(&windows_frequency);
  if (!ok) {
    return MPI_ERR_UNKNOWN;
  }
  return ((double)windows_ticks.QuadPart) / ((double)windows_frequency.QuadPart);
#elif defined(__APPLE__) || defined(__linux__)
  struct timespec linux_time;
  int err = clock_gettime(CLOCK_MONOTONIC, &linux_time);
  if (err != 0) {
    return MPI_ERR_UNKNOWN;
  }
  return ((double)linux_time.tv_sec) + (((double)linux_time.tv_nsec) * 1.0e-9);
#else
  fprintf(stderr, "MPI_Wtime not implemented for this platform\n");
  abort();
  return MPI_SUCCESS;
#endif
}

double PMPI_Wtick(void)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  LARGE_INTEGER windows_frequency;
  BOOL ok = QueryPerformanceFrequency(&windows_frequency);
  if (!ok) {
    return MPI_ERR_UNKNOWN;
  }
  return 1.0 / ((double)windows_frequency.QuadPart);
#elif defined(__APPLE__) || defined(__linux__)
  struct timespec linux_resolution;
  int err = clock_getres(CLOCK_MONOTONIC, &linux_resolution);
  if (err != 0) {
    return MPI_ERR_UNKNOWN;
  }
  return ((double)linux_resolution.tv_sec) + (((double)linux_resolution.tv_nsec) * 1.0e-9);
#else
  fprintf(stderr, "MPI_Wtick not implemented for this platform\n");
  abort();
  return MPI_SUCCESS;
#endif
}

int PMPI_Get_version(int *version, int *subversion)
{
  *version = MPI_VERSION;
  *subversion = MPI_SUBVERSION;
  return MPI_SUCCESS;
}

int PMPI_Pcontrol(const int level, ...)
{
  return MPI_SUCCESS;
}

int PMPI_Error_string(int errorcode, char* string, int* resultlen)
{
  fprintf(stderr, "PMPI_Error_string not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Error_class(int errorcode, int* errorclass)
{
  fprintf(stderr, "PMPI_Error_class not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Get_processor_name(char *name, int *resultlen)
{
  fprintf(stderr, "PMPI_Get_processor_name not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Get_library_version(char *version, int *resultlen)
{
  fprintf(stderr, "PMPI_Get_library_version not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Comm_size(MPI_Comm comm, int *size)
{
  *size = 1;
  return MPI_SUCCESS;
}

int PMPI_Comm_rank(MPI_Comm comm, int *rank)
{
  *rank = 0;
  return MPI_SUCCESS;
}

static struct fbmpi_comm_attribute_key*
fbmpi_find_comm_attribute_key(int keyval)
{
  int size = fbmpi_comm_attribute_keys.size;
  struct fbmpi_comm_attribute_key* array =
    fbmpi_comm_attribute_keys.array;
  for (int i = 0; i < size; ++i) {
    if (array[i].keyval == keyval) {
      return array + i;
    }
  }
  return NULL;
}

int PMPI_Comm_dup(MPI_Comm comm, MPI_Comm* newcomm)
{
  *newcomm = (MPI_Comm) malloc(sizeof(struct fbmpi_comm));
  fbmpi_construct_comm(*newcomm);
  for (int i = 0; i < comm->attribute_values.size; ++i) {
    int keyval = comm->attribute_values.array[i].keyval;
    void* attr_val_in = comm->attribute_values.array[i].value;
    struct fbmpi_comm_attribute_key* key =
      fbmpi_find_comm_attribute_key(keyval);
    void* attr_val_out;
    int flag;
    key->copy_function(
        comm,
        keyval,
        key->extra_state,
        attr_val_in,
        &attr_val_out,
        &flag);
    if (flag) {
      int err = MPI_Comm_set_attr(
          *newcomm, keyval, attr_val_out);
      if (err != MPI_SUCCESS) {
        MPI_Comm_free(newcomm);
        return err;
      }
    }
  }
  return MPI_SUCCESS;
}

int PMPI_Comm_free(MPI_Comm* comm)
{
  fbmpi_destroy_comm(*comm);
  free(*comm);
  *comm = MPI_COMM_NULL;
  return MPI_SUCCESS;
}

int PMPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int* result)
{
  fprintf(stderr, "PMPI_Comm_compare not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm* newcomm)
{
  return MPI_Comm_dup(comm, newcomm);
}

int PMPI_Comm_split_type(
    MPI_Comm comm,
    int split_type,
    int key,
    MPI_Info info,
    MPI_Comm *newcomm)
{
  return MPI_Comm_dup(comm, newcomm);
}

int PMPI_Comm_test_inter(MPI_Comm comm, int *flag)
{
  *flag = 0;
  return MPI_SUCCESS;
}

int PMPI_Comm_create_errhandler(
    MPI_Comm_errhandler_function* comm_errhandler_fn,
    MPI_Errhandler* errhandler)
{
  fprintf(stderr, "PMPI_Comm_create_errhandler not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler)
{
  fprintf(stderr, "PMPI_Comm_set_errhandler not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Comm_create_keyval(
    MPI_Comm_copy_attr_function* comm_copy_attr_fn,
    MPI_Comm_delete_attr_function* comm_delete_attr_fn,
    int* type_keyval,
    void* extra_state)
{
  int old_size = fbmpi_comm_attribute_keys.size;
  struct fbmpi_comm_attribute_key* old_array =
    fbmpi_comm_attribute_keys.array;
  int new_keyval = 0;
  for (; 1; ++new_keyval) {
    int is_taken = 0;
    for (int i = 0; i < old_size; ++i) {
      if (old_array[i].keyval == new_keyval) {
        is_taken = 1;
      }
    }
    if (!is_taken) break;
  }
  int new_index = old_size;
  int new_size = old_size + 1;
  struct fbmpi_comm_attribute_key* new_array = 
    (struct fbmpi_comm_attribute_key*) 
    malloc(new_size * sizeof(struct fbmpi_comm_attribute_key));
  memcpy(new_array, old_array, old_size * sizeof(struct fbmpi_comm_attribute_key));
  free(old_array);
  new_array[new_index].keyval = new_keyval;
  new_array[new_index].copy_function = comm_copy_attr_fn;
  new_array[new_index].delete_function = comm_delete_attr_fn;
  new_array[new_index].extra_state = extra_state;
  new_array[new_index].freed = 0;
  new_array[new_index].reference_count = 0;
  fbmpi_comm_attribute_keys.size = new_size;
  fbmpi_comm_attribute_keys.array = new_array;
  *type_keyval = new_keyval;
  return MPI_SUCCESS;
}

int PMPI_Comm_set_attr(
    MPI_Comm comm,
    int comm_keyval,
    void* attribute_val)
{
  for (int i = 0; i < comm->attribute_values.size; ++i) {
    if (comm->attribute_values.array[i].keyval == comm_keyval) {
      comm->attribute_values.array[i].value = attribute_val;
      return MPI_SUCCESS;
    }
  }
  int old_size = comm->attribute_values.size;
  int new_index = old_size;
  int new_size = old_size + 1;
  struct fbmpi_attribute_value* old_array =
    comm->attribute_values.array;
  struct fbmpi_attribute_value* new_array =
    (struct fbmpi_attribute_value*)
    malloc(new_size * sizeof(struct fbmpi_attribute_value));
  memcpy(new_array, old_array,
     old_size * sizeof(struct fbmpi_attribute_value)); 
  free(old_array);
  new_array[new_index].keyval = comm_keyval;
  new_array[new_index].value = attribute_val;
  comm->attribute_values.array = new_array;
  comm->attribute_values.size = new_size;
  struct fbmpi_comm_attribute_key* key =
    fbmpi_find_comm_attribute_key(comm_keyval);
  key->reference_count += 1;
  return MPI_SUCCESS;
}

int PMPI_Comm_free_keyval(int* comm_keyval)
{
  struct fbmpi_comm_attribute_key* key =
    fbmpi_find_comm_attribute_key(*comm_keyval);
  key->freed = 1;
  *comm_keyval = MPI_KEYVAL_INVALID;
  return MPI_SUCCESS;
}

int PMPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval)
{
  for (int i = 0; i < comm->attribute_values.size; ++i) {
    if (comm->attribute_values.array[i].keyval == comm_keyval) {
      struct fbmpi_comm_attribute_key* key =
        fbmpi_find_comm_attribute_key(comm_keyval);
      void* attr_val = comm->attribute_values.array[i].value;
      key->delete_function(
          comm,
          comm_keyval,
          attr_val,
          key->extra_state);
      {
        int old_size = comm->attribute_values.size;
        int new_size = old_size - 1;
        struct fbmpi_attribute_value* old_array =
          comm->attribute_values.array;
        struct fbmpi_attribute_value* new_array =
          (new_size == 0 ?
           NULL :
           ((struct fbmpi_attribute_value*)
           malloc(new_size * sizeof(struct fbmpi_attribute_value))));
        memcpy(new_array, old_array,
            i * sizeof(struct fbmpi_attribute_value));
        memcpy(new_array + i, old_array + i + 1,
            (old_size - i - 1) * sizeof(struct fbmpi_attribute_value));
        comm->attribute_values.array = new_array;
        comm->attribute_values.size = new_size;
      }
      key->reference_count -= 1;
      if (key->reference_count == 0) {
        struct fbmpi_comm_attribute_key* old_array =
          fbmpi_comm_attribute_keys.array;
        int index = (int)(key - old_array);
        int old_size = fbmpi_comm_attribute_keys.size;
        int new_size = old_size - 1;
        struct fbmpi_comm_attribute_key* new_array =
          (new_size == 0 ?
           NULL :
           ((struct fbmpi_comm_attribute_key*)
           malloc(new_size * sizeof(struct fbmpi_comm_attribute_key))));
        memcpy(new_array, old_array,
            index * sizeof(struct fbmpi_comm_attribute_key));
        memcpy(new_array + index, old_array + index + 1,
            (old_size - index - 1) * sizeof(struct fbmpi_comm_attribute_key));
        free(old_array);
        fbmpi_comm_attribute_keys.array = new_array;
        fbmpi_comm_attribute_keys.size = new_size;
      }
    }
  }
  return MPI_SUCCESS;
}

int PMPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm* newcomm)
{
  fprintf(stderr, "PMPI_Comm_create not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Comm_group(MPI_Comm comm, MPI_Group* group)
{
  fprintf(stderr, "PMPI_Comm_group not implemented\n");
  abort();
  return MPI_SUCCESS;
}

MPI_Fint PMPI_Comm_c2f(MPI_Comm comm)
{
  return comm->id;
}

MPI_Comm PMPI_Comm_f2c(MPI_Fint comm)
{
  for (int i = 0; i < fbmpi_comms.size; ++i) {
    if (fbmpi_comms.array[i]->id == comm) {
      return fbmpi_comms.array[i];
    }
  }
  fprintf(stderr, "MPI_Comm_f2c could not find ID %d\n", comm);
  abort();
  return MPI_COMM_NULL;
}

int PMPI_Group_incl(
    MPI_Group group,
    int n,
    const int ranks[],
    MPI_Group* newgroup)
{
  fprintf(stderr, "PMPI_Group_incl not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Group_excl(
    MPI_Group group,
    int n,
    const int ranks[],
    MPI_Group* newgroup)
{
  fprintf(stderr, "PMPI_Group_excl not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Group_rank(MPI_Group group, int *rank)
{
  fprintf(stderr, "PMPI_Group_rank not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Group_translate_ranks(
    MPI_Group group1,
    int n,
    const int ranks1[],
    MPI_Group group2,
    int ranks2[])
{
  fprintf(stderr, "MPI_Group_translate_ranks not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Group_free(MPI_Group* group)
{
  fprintf(stderr, "PMPI_Group_free not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int fbmpi_comm_null_copy_fn(
    MPI_Comm oldcomm,
    int type_keyval,
    void* extra_state,
    void* attribute_val_in,
    void* attribute_val_out,
    int* flag)
{
  (void)oldcomm;
  (void)type_keyval;
  (void)extra_state;
  (void)attribute_val_in;
  (void)attribute_val_out;
  *flag = 0;
  return MPI_SUCCESS;
}

int fbmpi_comm_dup_fn(
    MPI_Comm oldcomm,
    int type_keyval,
    void* extra_state,
    void* attribute_val_in,
    void* attribute_val_out,
    int* flag)
{
  (void)oldcomm;
  (void)type_keyval;
  (void)extra_state;
  void** actual_out = (void**)attribute_val_out;
  *actual_out = attribute_val_in;
  *flag = 1;
  return MPI_SUCCESS;
}

int fbmpi_comm_null_delete_fn(
    MPI_Comm datacomm,
    int type_keyval,
    void* attribute_val,
    void* extra_state)
{
  (void)datacomm;
  (void)type_keyval;
  (void)attribute_val;
  (void)extra_state;
  return MPI_SUCCESS;
}

int PMPI_Cart_create(
    MPI_Comm comm_old,
    int ndims,
    const int dims[],
    const int periods[],
    int reorder,
    MPI_Comm* comm_cart)
{
  int error = MPI_Comm_dup(
      comm_old,
      comm_cart);
  if (error != MPI_SUCCESS) return error;
  (*comm_cart)->cart_ndims = ndims;
  (*comm_cart)->cart_periods = (int*)malloc(sizeof(int) * ndims);
  for (int i = 0; i < ndims; ++i) {
    (*comm_cart)->cart_periods[i] = periods[i];
  }
  return MPI_SUCCESS;
}

int PMPI_Cartdim_get(
    MPI_Comm comm,
    int* ndims)
{
  fprintf(stderr, "PMPI_Cartdim_get not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Cart_get(
    MPI_Comm comm,
    int maxdims,
    int dims[],
    int periods[],
    int coords[])
{
  if (maxdims > comm->cart_ndims) maxdims = comm->cart_ndims;
  for (int i = 0; i < maxdims; ++i) {
    dims[i] = 1;
    periods[i] = comm->cart_periods[i];
    coords[i] = 0;
  }
  return MPI_SUCCESS;
}

int PMPI_Cart_rank(
    MPI_Comm comm,
    const int coords[],
    int* rank)
{
  fprintf(stderr, "PMPI_Cart_rank not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Cart_coords(
    MPI_Comm comm,
    int rank,
    int maxdims,
    int coords[])
{
  fprintf(stderr, "PMPI_Cart_coords not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Info_set(
    MPI_Info info,
    const char* key,
    const char* value)
{
  fprintf(stderr, "PMPI_Info_set not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Info_get(
    MPI_Info info,
    const char* key,
    int valuelen,
    char* value,
    int* flag)
{
  fprintf(stderr, "PMPI_Info_get not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Info_get_nkeys(MPI_Info info, int* nkeys)
{
  fprintf(stderr, "PMPI_Info_get_nkeys not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Info_get_nthkey(MPI_Info info, int n, char* key)
{
  fprintf(stderr, "PMPI_Info_get_nthkey not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Info_get_valuelen(
    MPI_Info info,
    const char* key,
    int* valuelen,
    int* flag)
{
  fprintf(stderr, "PMPI_Info_get_valuelen not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Info_dup(MPI_Info info, MPI_Info* newinfo)
{
  fprintf(stderr, "PMPI_Info_dup not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Info_free(MPI_Info* info)
{
  fprintf(stderr, "PMPI_Info_free not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Info_create(MPI_Info* info)
{
  fprintf(stderr, "PMPI_Info_create not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Type_commit(MPI_Datatype* datatype)
{
  fprintf(stderr, "PMPI_Type_commit not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Type_free(MPI_Datatype* datatype)
{
  free(*datatype);
  *datatype = MPI_DATATYPE_NULL;
  return MPI_SUCCESS;
}

int PMPI_Type_get_extent(
    MPI_Datatype datatype,
    MPI_Aint* lb,
    MPI_Aint* extent)
{
  fprintf(stderr, "PMPI_Type_get_extent not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Type_get_extent_x(
    MPI_Datatype datatype,
    MPI_Count* lb,
    MPI_Count* extent)
{
  fprintf(stderr, "PMPI_Type_get_extent_x not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Type_contiguous(
    int count,
    MPI_Datatype oldtype,
    MPI_Datatype *newtype)
{
  fprintf(stderr, "PMPI_Type_contiguous not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Type_create_hvector(
    int count,
    int blocklength,
    MPI_Aint stride,
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  fprintf(stderr, "PMPI_Type_create_hvector not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Type_create_hindexed(
    int count,
    const int array_of_blocklengths[],
    const MPI_Aint array_of_displacements[],
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  fprintf(stderr, "PMPI_Type_create_hindexed not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Type_create_hindexed_block(
    int count,
    int blocklength,
    const MPI_Aint array_of_displacements[],
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  fprintf(stderr, "PMPI_Type_create_hindexed_block not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Type_create_struct(
    int count,
    const int array_of_blocklengths[],
    const MPI_Aint array_of_displacements[],
    const MPI_Datatype array_of_types[],
    MPI_Datatype* newtype)
{
  fprintf(stderr, "PMPI_Type_create_struct not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Type_vector(
    int count,
    int blocklength,
    int stride,
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  fprintf(stderr, "PMPI_Type_vector not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Type_create_resized(
    MPI_Datatype oldtype,
    MPI_Aint lb,
    MPI_Aint extent,
    MPI_Datatype* newtype)
{
  fprintf(stderr, "PMPI_Type_create_resized not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Type_dup(
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  fprintf(stderr, "PMPI_Type_dup not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Get_count(
    const MPI_Status* status,
    MPI_Datatype datatype,
    int* count)
{
  MPI_Count count_x;
  int err = MPI_Get_elements_x(status, datatype, &count_x);
  if (err != MPI_SUCCESS) return err;
  *count = (int)count_x;
  return MPI_SUCCESS;
}

int PMPI_Get_elements_x(
    const MPI_Status* status,
    MPI_Datatype datatype,
    MPI_Count* count)
{
  MPI_Count datatype_size;
  int err = MPI_Type_size_x(datatype, &datatype_size);
  if (err != MPI_SUCCESS) return err;
  *count = status->fbmpi_bytes / datatype_size;
  return MPI_SUCCESS;
}

int PMPI_Type_size(MPI_Datatype datatype, int* size)
{
  MPI_Count size_x;
  int err = MPI_Type_size_x(datatype, &size_x);
  if (err != MPI_SUCCESS) return err;
  *size = (int)size_x;
  return MPI_SUCCESS;
}

int PMPI_Type_size_x(MPI_Datatype datatype, MPI_Count* size)
{
  *size = datatype->size;
  return MPI_SUCCESS;
}

int PMPI_Send(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm)
{
  MPI_Request request;
  int err = MPI_Isend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm,
      &request);
  if (err != MPI_SUCCESS) return err;
  return MPI_Wait(&request, MPI_STATUS_IGNORE);
}

int PMPI_Recv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status* status)
{
  MPI_Request request;
  int err = MPI_Irecv(
      buf,
      count,
      datatype,
      source,
      tag,
      comm,
      &request);
  if (err != MPI_SUCCESS) return err;
  return MPI_Wait(&request, status);
}

int PMPI_Bsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Bsend not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Bsend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  fprintf(stderr, "PMPI_Bsend_init not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Rsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Rsend not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Rsend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  fprintf(stderr, "PMPI_Rsend_init not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Ssend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Ssend not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Ssend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  fprintf(stderr, "PMPI_Ssend_init not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int fbmpi_try_match(MPI_Request a, MPI_Request b, int* flag)
{
  *flag = 0;
  if (a->type == FBMPI_SEND &&
      b->type == FBMPI_RECEIVE)
  {
    if (b->tag != MPI_ANY_TAG && a->tag != b->tag) return MPI_SUCCESS;
    if (a->datatype != b->datatype) return MPI_SUCCESS;
    if (a->count != b->count) return MPI_SUCCESS;
    MPI_Count datatype_size;
    int err = MPI_Type_size_x(a->datatype, &datatype_size);
    if (err != MPI_SUCCESS) return err;
    err = fbmpi_memcpy(
        b->non_const_buf, a->const_buf,
        datatype_size * a->count);
    if (err != MPI_SUCCESS) return err;
    a->is_complete = 1; 
    b->is_complete = 1;
    *flag = 1;
    return MPI_SUCCESS;
  }
  else if (a->type == FBMPI_RECEIVE &&
             b->type == FBMPI_SEND)
  {
    return fbmpi_try_match(b, a, flag);
  }
  return MPI_SUCCESS;
}

int fbmpi_add_request(
    MPI_Request new_request,
    struct fbmpi_requests* incomplete_requests)
{
  MPI_Request* old_array = incomplete_requests->array;
  int old_size = incomplete_requests->size;
  for (int i = 0; i < old_size; ++i) {
    int flag;
    int err = fbmpi_try_match(
        new_request,
        incomplete_requests->array[i],
        &flag);
    if (err != MPI_SUCCESS) return err;
    if (flag) {
      int new_size = old_size - 1;
      MPI_Request* new_array = 
        new_size == 0 ?
        NULL :
        (MPI_Request*)
        malloc(new_size * sizeof(MPI_Request));
      memcpy(new_array, old_array, i * sizeof(MPI_Request));
      memcpy(new_array + i, old_array + i + 1,
          (old_size - i - 1) * sizeof(MPI_Request));
      incomplete_requests->array = new_array;
      incomplete_requests->size = new_size;
      return MPI_SUCCESS;
    }
  }
  int new_size = old_size + 1;
  MPI_Request* new_array = (MPI_Request*)malloc(new_size * sizeof(MPI_Request));
  memcpy(new_array, old_array, old_size * sizeof(MPI_Request));
  free(old_array);
  new_array[new_size - 1] = new_request;
  incomplete_requests->array = new_array;
  incomplete_requests->size = new_size;
  return MPI_SUCCESS;
}

int PMPI_Isend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  *request = (MPI_Request)malloc(sizeof(struct fbmpi_request));
  (*request)->type = FBMPI_SEND;
  (*request)->const_buf = buf;
  (*request)->non_const_buf = NULL;
  (*request)->count = count;
  (*request)->datatype = datatype;
  (*request)->tag = tag;
  if (dest == MPI_PROC_NULL) {
    (*request)->is_complete = 1;
    return MPI_SUCCESS;
  } else {
    (*request)->is_complete = 0;
    return fbmpi_add_request(*request,
        &(comm->incomplete_requests));
  }
}

int PMPI_Ibsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  fprintf(stderr, "PMPI_Ibsend not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Issend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  return MPI_Isend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm,
      request);
}

int PMPI_Irecv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Request *request)
{
  *request = (MPI_Request)malloc(sizeof(struct fbmpi_request));
  (*request)->type = FBMPI_RECEIVE;
  (*request)->const_buf = NULL;
  (*request)->non_const_buf = buf;
  (*request)->count = count;
  (*request)->datatype = datatype;
  (*request)->tag = tag;
  if (source == MPI_PROC_NULL) {
    (*request)->is_complete = 1;
    return MPI_SUCCESS;
  } else {
    (*request)->is_complete = 0;
    return fbmpi_add_request(*request,
        &(comm->incomplete_requests));
  }
}

int PMPI_Iprobe(
    int source,
    int tag,
    MPI_Comm comm,
    int* flag,
    MPI_Status* status)
{
  if (source == MPI_PROC_NULL) {
    *flag = 1;
    status->MPI_SOURCE = MPI_PROC_NULL;
    status->MPI_TAG = MPI_ANY_TAG;
    status->fbmpi_bytes = 0;
    return MPI_SUCCESS;
  }
  for (int i = 0; i < comm->incomplete_requests.size; ++i) {
    MPI_Request request = comm->incomplete_requests.array[i];
    if (request->type != FBMPI_SEND) continue;
    if (tag != MPI_ANY_TAG && request->tag != tag) continue;
    status->MPI_SOURCE = 0;
    status->MPI_TAG = request->tag;
    MPI_Count datatype_size;
    int err = MPI_Type_size_x(request->datatype, &datatype_size);
    if (err != MPI_SUCCESS) return err;
    status->fbmpi_bytes = datatype_size * request->count;
    *flag = 1;
    return MPI_SUCCESS;
  }
  *flag = 0;
  return MPI_SUCCESS;
}

int PMPI_Probe(
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status *status)
{
  int flag;
  int err = MPI_Iprobe(source, tag, comm, &flag, status);
  if (err != MPI_SUCCESS) return err;
  if (!flag) return MPI_ERR_OTHER;
  return MPI_SUCCESS;
}

int PMPI_Test(
    MPI_Request* request,
    int* flag,
    MPI_Status* status)
{
  *flag = 1;
  if (*request == MPI_REQUEST_NULL) {
    return MPI_SUCCESS;
  }
  if (!((*request)->is_complete)) {
    *flag = 0;
    return MPI_SUCCESS;
  }
  if ((status != MPI_STATUS_IGNORE) &&
      ((*request)->type == FBMPI_RECEIVE)) {
    status->MPI_SOURCE = 0;
    status->MPI_TAG = (*request)->tag;
    MPI_Count datatype_size;
    int err = MPI_Type_size_x((*request)->datatype, &datatype_size);
    if (err != MPI_SUCCESS) return err;
    status->fbmpi_bytes = datatype_size * (*request)->count;
  }
  free(*request);
  *request = MPI_REQUEST_NULL;
  return MPI_SUCCESS;
}

int PMPI_Send_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  fprintf(stderr, "PMPI_Send_init not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Recv_init(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Request *request)
{
  fprintf(stderr, "PMPI_Recv_init not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Irsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request *request)
{
  fprintf(stderr, "PMPI_Irsend not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Start(MPI_Request* request)
{
  fprintf(stderr, "PMPI_Start not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Startall(
    int count,
    MPI_Request array_of_requests[])
{
  fprintf(stderr, "PMPI_Startall not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Request_free(MPI_Request *request)
{
  fprintf(stderr, "PMPI_Request_free not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Cancel(MPI_Request *request)
{
  fprintf(stderr, "PMPI_Cancel not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Sendrecv(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    int dest,
    int sendtag,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int source,
    int recvtag,
    MPI_Comm comm,
    MPI_Status* status)
{
  fprintf(stderr, "PMPI_Sendrecv not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Sendrecv_replace(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int sendtag,
    int source,
    int recvtag,
    MPI_Comm comm,
    MPI_Status *status)
{
  fprintf(stderr, "PMPI_Sendrecv_replace not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Wait(
    MPI_Request* request,
    MPI_Status* status)
{
  int flag;
  int err = MPI_Test(request, &flag, status);
  if (err != MPI_SUCCESS) return err;
  if (!flag) return MPI_ERR_REQUEST;
  return MPI_SUCCESS;
}

int PMPI_Mprobe(
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Message* message,
    MPI_Status* status)
{
  fprintf(stderr, "PMPI_Mprobe not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Imrecv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Message* message,
    MPI_Request* request)
{
  fprintf(stderr, "PMPI_Imrecv not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Waitall(
    int count,
    MPI_Request array_of_requests[],
    MPI_Status array_of_statuses[])
{
  int had_errors = 0;
  for (int i = 0; i < count; ++i) {
    MPI_Status* status_ptr =
      array_of_statuses == MPI_STATUSES_IGNORE ?
      MPI_STATUS_IGNORE :
      array_of_statuses + i;
    int error = MPI_Wait(
        array_of_requests + i,
        status_ptr);
    if (status_ptr != MPI_STATUS_IGNORE) {
      status_ptr->MPI_ERROR = error;
    }
    if (error != MPI_SUCCESS) {
      had_errors = 1;
    }
  }
  if (had_errors) {
    return MPI_ERR_IN_STATUS;
  }
  return MPI_SUCCESS;
}

int PMPI_Waitany(
    int count,
    MPI_Request array_of_requests[],
    int* index,
    MPI_Status* status)
{
  fprintf(stderr, "PMPI_Waitany not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Waitsome(
    int incount,
    MPI_Request array_of_requests[],
    int *outcount,
    int array_of_indices[],
    MPI_Status array_of_statuses[])
{
  fprintf(stderr, "PMPI_Waitsome not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Testall(
    int count,
    MPI_Request array_of_requests[],
    int* flag,
    MPI_Status array_of_statuses[])
{
  int had_errors = 0;
  *flag = 1;
  for (int i = 0; i < count; ++i) {
    MPI_Status* status_ptr =
      array_of_statuses == MPI_STATUSES_IGNORE ?
      MPI_STATUS_IGNORE :
      array_of_statuses + i;
    int single_flag;
    int error = MPI_Test(
        array_of_requests + i,
        &single_flag,
        status_ptr);
    if (status_ptr != MPI_STATUS_IGNORE) {
      status_ptr->MPI_ERROR = error;
    }
    if (error == MPI_SUCCESS) {
      *flag = *flag && single_flag;
    } else {
      had_errors = 1;
    }
  }
  if (had_errors) {
    return MPI_ERR_IN_STATUS;
  }
  return MPI_SUCCESS;
}

int PMPI_Testany(
    int count,
    MPI_Request array_of_requests[],
    int *index,
    int *flag,
    MPI_Status *status)
{
  fprintf(stderr, "PMPI_Testany not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Testsome(
    int incount,
    MPI_Request array_of_requests[],
    int* outcount,
    int array_of_indices[],
    MPI_Status array_of_statuses[])
{
  fprintf(stderr, "PMPI_Testsome not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Test_cancelled(const MPI_Status *status, int *flag)
{
  fprintf(stderr, "PMPI_Test_cancelled not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Barrier(MPI_Comm comm)
{
  return MPI_SUCCESS;
}

int PMPI_Bcast(
    void* buffer,
    int count,
    MPI_Datatype datatype,
    int root,
    MPI_Comm comm)
{
  return MPI_SUCCESS;
}

int PMPI_Reduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    int root,
    MPI_Comm comm)
{
  return MPI_Allreduce(
      sendbuf,
      recvbuf,
      count,
      datatype,
      op,
      comm);
}

int PMPI_Allreduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm)
{
  if (sendbuf == MPI_IN_PLACE) return MPI_SUCCESS;
  MPI_Count datatype_size;
  MPI_Type_size_x(datatype, &datatype_size);
  return fbmpi_memcpy(
      recvbuf, sendbuf, count * datatype_size);
}

int PMPI_Iallreduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm,
    MPI_Request* request)
{
  int error = MPI_Allreduce(
      sendbuf,
      recvbuf,
      count,
      datatype,
      op,
      comm);
  if (error != MPI_SUCCESS) {
    return error;
  }
  *request = (MPI_Request)malloc(sizeof(struct fbmpi_request));
  (*request)->type = FBMPI_REDUCE;
  (*request)->is_complete = 1;
  return MPI_SUCCESS;
}

int PMPI_Allgather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm)
{
  if (sendbuf == MPI_IN_PLACE) return MPI_SUCCESS;
  MPI_Count datatype_size;
  MPI_Type_size_x(sendtype, &datatype_size);
  return fbmpi_memcpy(
      recvbuf, sendbuf, sendcount * datatype_size);
}

int PMPI_Gather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Gather not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Iallgather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm,
    MPI_Request* request)
{
  int error = MPI_Allgather(
      sendbuf,
      sendcount,
      sendtype,
      recvbuf,
      recvcount,
      recvtype,
      comm);
  if (error != MPI_SUCCESS) return error;
  *request = (MPI_Request)malloc(sizeof(struct fbmpi_request));
  (*request)->type = FBMPI_GATHER;
  (*request)->is_complete = 1;
  return MPI_SUCCESS;
}

int PMPI_Scatter(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Scatter not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Allgatherv(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    const int recvcounts[],
    const int displs[],
    MPI_Datatype recvtype,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Allgatherv not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Gatherv(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    const int recvcounts[],
    const int displs[],
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Gatherv not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Scatterv(
    const void* sendbuf,
    const int sendcounts[],
    const int displs[],
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Scatterv not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Alltoall(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Alltoall not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Alltoallv(
    const void* sendbuf,
    const int sendcounts[],
    const int sdispls[],
    MPI_Datatype sendtype,
    void* recvbuf,
    const int recvcounts[],
    const int rdispls[],
    MPI_Datatype recvtype,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Alltoallv not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Neighbor_alltoall(
    const void *sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void *recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Neighbor_alltoall not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Neighbor_alltoallv(
    const void *sendbuf,
    const int sendcounts[],
    const int sdispls[],
    MPI_Datatype sendtype,
    void *recvbuf,
    const int recvcounts[],
    const int rdispls[],
    MPI_Datatype recvtype,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Neighbor_alltoallv not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Dist_graph_create_adjacent(
    MPI_Comm comm_old,
    int indegree,
    const int sources[],
    const int sourceweights[],
    int outdegree,
    const int destinations[],
    const int destweights[],
    MPI_Info info,
    int reorder,
    MPI_Comm *comm_dist_graph)
{
  fprintf(stderr, "PMPI_Dist_graph_create_adjacent not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Ibarrier(
    MPI_Comm comm,
    MPI_Request* request)
{
  *request = (MPI_Request)malloc(sizeof(struct fbmpi_request));
  (*request)->type = FBMPI_BARRIER;
  (*request)->is_complete = 1;
  return MPI_SUCCESS;
}

int PMPI_Scan(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm)
{
  return MPI_Allreduce(
      sendbuf,
      recvbuf,
      count,
      datatype,
      op,
      comm);
}

int PMPI_Exscan(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm)
{
  return MPI_SUCCESS;
}

int PMPI_Reduce_scatter(
    const void *sendbuf,
    void *recvbuf,
    const int recvcounts[],
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Reduce_scatter not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Op_create(
    MPI_User_function* user_fn,
    int commute,
    MPI_Op* op)
{
  *op = (MPI_Op)malloc(sizeof(struct fbmpi_op));
  return MPI_SUCCESS;
}

int PMPI_Op_free(MPI_Op* op)
{
  free(*op);
  *op = NULL;
  return MPI_SUCCESS;
}

int PMPI_File_open(
    MPI_Comm comm,
    const char* filename,
    int amode,
    MPI_Info info,
    MPI_File* fh)
{
  fprintf(stderr, "PMPI_File_open not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_close(MPI_File* fh)
{
  fprintf(stderr, "PMPI_File_close not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_delete(const char *filename, MPI_Info info)
{
  fprintf(stderr, "PMPI_File_delete not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_get_size(MPI_File fh, MPI_Offset* size)
{
  fprintf(stderr, "PMPI_File_get_size not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_set_size(MPI_File fh, MPI_Offset size)
{
  fprintf(stderr, "PMPI_File_set_size not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_set_atomicity(MPI_File fh, int flag)
{
  fprintf(stderr, "PMPI_File_set_atomicity not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_get_atomicity(MPI_File fh, int* flag)
{
  fprintf(stderr, "PMPI_File_get_atomicity not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_set_view(
    MPI_File fh,
    MPI_Offset disp,
    MPI_Datatype etype,
    MPI_Datatype filetype,
    const char* datarep,
    MPI_Info info)
{
  fprintf(stderr, "PMPI_File_set_view not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_write_at_all(
    MPI_File fh,
    MPI_Offset offset,
    const void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status)
{
  fprintf(stderr, "PMPI_File_write_at_all not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_read_at(
    MPI_File fh,
    MPI_Offset offset,
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status)
{
  fprintf(stderr, "PMPI_File_read_at not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_read_at_all(
    MPI_File fh,
    MPI_Offset offset,
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status)
{
  fprintf(stderr, "PMPI_File_write_at_all not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_write_at(
    MPI_File fh,
    MPI_Offset offset,
    const void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status)
{
  fprintf(stderr, "PMPI_File_write_at not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_sync(MPI_File fh)
{
  fprintf(stderr, "PMPI_File_sync not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_File_get_info(MPI_File fh, MPI_Info* info_used)
{
  fprintf(stderr, "PMPI_File_get_info not implemented\n");
  abort();
  return MPI_SUCCESS;
}

MPI_Aint PMPI_Aint_diff(MPI_Aint addr1, MPI_Aint addr2)
{
  fprintf(stderr, "PMPI_Aint_diff not implemented\n");
  abort();
  return 0;
}

int PMPI_Get_address(void const* location, MPI_Aint* address)
{
  fprintf(stderr, "PMPI_Get_address not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Pack_size(
    int incount,
    MPI_Datatype datatype,
    MPI_Comm comm,
    int *size)
{
  fprintf(stderr, "PMPI_Pack_size not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Pack(
    const void* inbuf,
    int incount,
    MPI_Datatype datatype,
    void* outbuf,
    int outsize,
    int* position,
    MPI_Comm comm)
{
  fprintf(stderr, "MPI_Pack not implemented\n");
  abort();
  return MPI_SUCCESS;
}

int PMPI_Unpack(
    const void *inbuf,
    int insize,
    int *position,
    void *outbuf,
    int outcount,
    MPI_Datatype datatype,
    MPI_Comm comm)
{
  fprintf(stderr, "PMPI_Unpack not implemented\n");
  abort();
  return MPI_SUCCESS;
}

MPI_Info PMPI_Info_f2c(MPI_Fint info)
{
  fprintf(stderr, "PMPI_Info_f2c not implemented\n");
  abort();
  return MPI_INFO_NULL;
}
