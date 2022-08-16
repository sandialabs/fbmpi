#ifndef MPI_H
#define MPI_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#define MPI_VERSION 3
#define MPI_SUBVERSION 1

#ifdef __cplusplus
extern "C" {
#endif

#define MPI_THREAD_SINGLE 0
#define MPI_THREAD_FUNNELED 1
#define MPI_THREAD_SERIALIZED 2
#define MPI_THREAD_MULTIPLE 3

enum fbmpi_error_code {
  MPI_SUCCESS = 0,
  MPI_ERR_BUFFER,
  MPI_ERR_COUNT,
  MPI_ERR_TYPE,
  MPI_ERR_TAG,
  MPI_ERR_COMM,
  MPI_ERR_RANK,
  MPI_ERR_REQUEST,
  MPI_ERR_ROOT,
  MPI_ERR_GROUP,
  MPI_ERR_OP,
  MPI_ERR_TOPOLOGY,
  MPI_ERR_DIMS,
  MPI_ERR_ARG,
  MPI_ERR_UNKNOWN,
  MPI_ERR_TRUNCATE,
  MPI_ERR_OTHER,
  MPI_ERR_INTERN,
  MPI_ERR_IN_STATUS,
  MPI_ERR_PENDING,
  MPI_ERR_KEYVAL,
  MPI_ERR_NO_MEM,
  MPI_ERR_BASE,
  MPI_ERR_INFO_KEY,
  MPI_ERR_INFO_VALUE,
  MPI_ERR_INFO_NOKEY,
  MPI_ERR_SPAWN,
  MPI_ERR_PORT,
  MPI_ERR_SERVICE,
  MPI_ERR_NAME,
  MPI_ERR_WIN,
  MPI_ERR_SIZE,
  MPI_ERR_DISP,
  MPI_ERR_INFO,
  MPI_ERR_LOCKTYPE,
  MPI_ERR_ASSERT,
  MPI_ERR_LASTCODE
};

#define MPI_IN_PLACE ((char*)0x1)

enum fbmpi_special_rank {
  MPI_ANY_SOURCE = -2,
  MPI_PROC_NULL = -1
};

enum fbmpi_special_tag {
  MPI_ANY_TAG = -2
};

enum fbmpi_special_keyval {
  MPI_KEYVAL_INVALID = -1
};

#define MPI_UNDEFINED -10

enum fbmpi_comparison_result {
  MPI_IDENT,
  MPI_CONGRUENT,
  MPI_SIMILAR,
  MPI_UNEQUAL
};

enum fbmpi_file_mode {
  MPI_MODE_RDONLY           =   1,
  MPI_MODE_RDWR             =   2,
  MPI_MODE_WRONLY           =   4,
  MPI_MODE_CREATE           =   8,
  MPI_MODE_EXCL             =  16,
  MPI_MODE_DELETE_ON_CLOSE  =  32,
  MPI_MODE_UNIQUE_OPEN      =  64,
  MPI_MODE_SEQUENTIAL       = 128,
  MPI_MODE_APPEND           = 256
};

enum fbmpi_comm_type {
  MPI_COMM_TYPE_SHARED,
  MPI_COMM_TYPE_HW_GUIDED,
  MPI_COMM_TYPE_HW_UNGUIDED
};

#define MPI_UNWEIGHTED (((int*)NULL) + 1)
#define MPI_WEIGHTS_EMPTY (((int*)NULL) + 2)

typedef FILE* fbmpi_file_ptr;
typedef fbmpi_file_ptr MPI_File;

#define MPI_FILE_NULL ((MPI_File)NULL)

struct fbmpi_comm;
typedef struct fbmpi_comm* fbmpi_comm_ptr;
typedef fbmpi_comm_ptr MPI_Comm;

#define MPI_COMM_NULL ((MPI_Comm)NULL)

extern MPI_Comm MPI_COMM_SELF;
extern MPI_Comm MPI_COMM_WORLD;

struct fbmpi_group;
typedef struct fbmpi_group* fbmpi_group_ptr;
typedef fbmpi_group_ptr MPI_Group;

struct fbmpi_info;
typedef struct fbmpi_info* fbmpi_info_ptr;
typedef fbmpi_info_ptr MPI_Info;

#define MPI_INFO_NULL ((MPI_Info)NULL)

struct fbmpi_datatype;
typedef struct fbmpi_datatype* fbmpi_datatype_ptr;
typedef fbmpi_datatype_ptr MPI_Datatype;

#define MPI_DATATYPE_NULL ((MPI_Datatype)NULL)

typedef int MPI_Fint;
typedef ptrdiff_t MPI_Aint;
typedef int64_t MPI_Offset;
typedef int64_t MPI_Count;

#define MPI_MAX_ERROR_STRING 512
#define MPI_MAX_PROCESSOR_NAME 128
#define MPI_MAX_LIBRARY_VERSION_STRING 8192

typedef int MPI_Type_copy_attr_function(
    MPI_Datatype oldtype,
    int type_keyval,
    void* extra_state,
    void* attribute_val_in,
    void* attribute_val_out,
    int* flag);

typedef int MPI_Type_delete_attr_function(
    MPI_Datatype datatype,
    int type_keyval,
    void* attribute_val,
    void* extra_state);

typedef int MPI_Comm_copy_attr_function(
    MPI_Comm oldcomm,
    int type_keyval,
    void* extra_state,
    void* attribute_val_in,
    void* attribute_val_out,
    int* flag);

typedef int MPI_Comm_delete_attr_function(
    MPI_Comm datacomm,
    int type_keyval,
    void* attribute_val,
    void* extra_state);

typedef void MPI_Comm_errhandler_function(MPI_Comm*, int*, ...);

typedef void MPI_User_function(void* invec, void* inoutvec, int* len, MPI_Datatype* datatype);

struct fbmpi_errhandler;
typedef struct fbmpi_errhandler* fbmpi_errhandler_ptr;
typedef fbmpi_errhandler_ptr MPI_Errhandler;

extern MPI_Errhandler MPI_ERRORS_ARE_FATAL;
extern MPI_Errhandler MPI_ERRORS_RETURN;

#define MPI_MAX_INFO_KEY 255
#define MPI_MAX_INFO_VAL 1024

extern MPI_Datatype fbmpi_byte;
extern MPI_Datatype fbmpi_packed;
extern MPI_Datatype fbmpi_char;
extern MPI_Datatype fbmpi_signed_char;
extern MPI_Datatype fbmpi_unsigned_char;
extern MPI_Datatype fbmpi_c_bool;
extern MPI_Datatype fbmpi_unsigned_short;
extern MPI_Datatype fbmpi_unsigned;
extern MPI_Datatype fbmpi_unsigned_long;
extern MPI_Datatype fbmpi_unsigned_long_long;
extern MPI_Datatype fbmpi_short;
extern MPI_Datatype fbmpi_int;
extern MPI_Datatype fbmpi_long;
extern MPI_Datatype fbmpi_long_long;
extern MPI_Datatype fbmpi_float;
extern MPI_Datatype fbmpi_double;
extern MPI_Datatype fbmpi_long_double;
extern MPI_Datatype fbmpi_int8_t;
extern MPI_Datatype fbmpi_int16_t;
extern MPI_Datatype fbmpi_int32_t;
extern MPI_Datatype fbmpi_int64_t;
extern MPI_Datatype fbmpi_uint8_t;
extern MPI_Datatype fbmpi_uint16_t;
extern MPI_Datatype fbmpi_uint32_t;
extern MPI_Datatype fbmpi_uint64_t;
extern MPI_Datatype fbmpi_c_float_complex;
extern MPI_Datatype fbmpi_c_double_complex;
extern MPI_Datatype fbmpi_short_int;
extern MPI_Datatype fbmpi_2int;
extern MPI_Datatype fbmpi_long_int;
extern MPI_Datatype fbmpi_float_int;
extern MPI_Datatype fbmpi_double_int;

/* there are codes that assume these to be macros */
#define MPI_BYTE fbmpi_byte
#define MPI_PACKED fbmpi_packed
#define MPI_CHAR fbmpi_char
#define MPI_SIGNED_CHAR fbmpi_signed_char
#define MPI_UNSIGNED_CHAR fbmpi_unsigned_char
#define MPI_C_BOOL fbmpi_c_bool
#define MPI_UNSIGNED_SHORT fbmpi_unsigned_short
#define MPI_UNSIGNED fbmpi_unsigned
#define MPI_UNSIGNED_LONG fbmpi_unsigned_long
#define MPI_UNSIGNED_LONG_LONG fbmpi_unsigned_long_long
#define MPI_SHORT fbmpi_short
#define MPI_INT fbmpi_int
#define MPI_LONG fbmpi_long
#define MPI_LONG_LONG_INT fbmpi_long_long
#define MPI_LONG_LONG fbmpi_long_long
#define MPI_FLOAT fbmpi_float
#define MPI_DOUBLE fbmpi_double
#define MPI_LONG_DOUBLE fbmpi_long_double
#define MPI_INT8_T fbmpi_int8_t
#define MPI_INT16_T fbmpi_int16_t
#define MPI_INT32_T fbmpi_int32_t
#define MPI_INT64_T fbmpi_int64_t
#define MPI_UINT8_T fbmpi_uint8_t
#define MPI_UINT16_T fbmpi_uint16_t
#define MPI_UINT32_T fbmpi_uint32_t
#define MPI_UINT64_T fbmpi_uint64_t
#define MPI_C_FLOAT_COMPLEX fbmpi_c_float_complex
#define MPI_C_DOUBLE_COMPLEX fbmpi_c_double_complex
#define MPI_SHORT_INT fbmpi_short_int
#define MPI_2INT fbmpi_2int
#define MPI_LONG_INT fbmpi_long_int
#define MPI_FLOAT_INT fbmpi_float_int
#define MPI_DOUBLE_INT fbmpi_double_int

struct fbmpi_status {
  int MPI_SOURCE;
  int MPI_TAG;
  int MPI_ERROR;
  size_t fbmpi_bytes;
};
typedef struct fbmpi_status MPI_Status;

#define MPI_STATUS_IGNORE ((MPI_Status*)NULL)
#define MPI_STATUSES_IGNORE ((MPI_Status*)NULL)

struct fbmpi_request;
typedef struct fbmpi_request* fbmpi_request_ptr;
typedef fbmpi_request_ptr MPI_Request;

#define MPI_REQUEST_NULL ((MPI_Request)NULL)

struct fbmpi_op;
typedef struct fbmpi_op* fbmpi_op_ptr;
typedef fbmpi_op_ptr MPI_Op;

#define MPI_OP_NULL ((MPI_Op)NULL)

extern MPI_Op MPI_SUM;
extern MPI_Op MPI_MIN;
extern MPI_Op MPI_MAX;
extern MPI_Op MPI_BOR;
extern MPI_Op MPI_LOR;
extern MPI_Op MPI_LAND;
extern MPI_Op MPI_MINLOC;
extern MPI_Op MPI_MAXLOC;

struct fbmpi_message;
typedef struct fbmpi_message* fbmpi_message_ptr;
typedef fbmpi_message_ptr MPI_Message;

extern MPI_Message MPI_MESSAGE_NO_PROC;
#define MPI_MESSAGE_NULL ((MPI_Message)NULL)

#define MPI_BOTTOM ((void*)NULL)

int MPI_Init(int* argc, char*** argv);
int PMPI_Init(int* argc, char*** argv);
int MPI_Init_thread(
    int* argc,
    char*** argv,
    int required,
    int* provided);
int PMPI_Init_thread(
    int* argc,
    char*** argv,
    int required,
    int* provided);
int MPI_Finalize(void);
int PMPI_Finalize(void);
int MPI_Initialized(int* flag);
int PMPI_Initialized(int* flag);
int MPI_Finalized(int* flag);
int PMPI_Finalized(int* flag);
int MPI_Abort(MPI_Comm comm, int errorcode);
int PMPI_Abort(MPI_Comm comm, int errorcode);
double MPI_Wtime(void);
double PMPI_Wtime(void);
double MPI_Wtick(void);
double PMPI_Wtick(void);

int MPI_Pcontrol(const int level, ...);
int PMPI_Pcontrol(const int level, ...);

int MPI_Error_string(int errorcode, char* string, int* resultlen);
int PMPI_Error_string(int errorcode, char* string, int* resultlen);
int MPI_Error_class(int errorcode, int* errorclass);
int PMPI_Error_class(int errorcode, int* errorclass);

int MPI_Get_processor_name(char *name, int *resultlen);
int PMPI_Get_processor_name(char *name, int *resultlen);
int MPI_Get_library_version(char *version, int *resultlen);
int PMPI_Get_library_version(char *version, int *resultlen);

int PMPI_Comm_size(MPI_Comm comm, int *size);
int MPI_Comm_size(MPI_Comm comm, int *size);
int PMPI_Comm_rank(MPI_Comm comm, int *rank);
int MPI_Comm_rank(MPI_Comm comm, int *rank);
int MPI_Comm_dup(MPI_Comm comm, MPI_Comm* newcomm);
int PMPI_Comm_dup(MPI_Comm comm, MPI_Comm* newcomm);
int MPI_Comm_free(MPI_Comm* comm);
int PMPI_Comm_free(MPI_Comm* comm);
int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int* result);
int PMPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int* result);
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm* newcomm);
int PMPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm* newcomm);
int MPI_Comm_split_type(
    MPI_Comm comm,
    int split_type,
    int key,
    MPI_Info info,
    MPI_Comm *newcomm);
int PMPI_Comm_split_type(
    MPI_Comm comm,
    int split_type,
    int key,
    MPI_Info info,
    MPI_Comm *newcomm);
int MPI_Comm_test_inter(MPI_Comm comm, int *flag);
int PMPI_Comm_test_inter(MPI_Comm comm, int *flag);

int MPI_Comm_create_errhandler(
    MPI_Comm_errhandler_function* comm_errhandler_fn,
    MPI_Errhandler* errhandler);
int PMPI_Comm_create_errhandler(
    MPI_Comm_errhandler_function* comm_errhandler_fn,
    MPI_Errhandler* errhandler);
int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler);
int PMPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler);

int MPI_Comm_create_keyval(
    MPI_Comm_copy_attr_function* type_copy_attr_fn,
    MPI_Comm_delete_attr_function* type_delete_attr_fn,
    int* type_keyval,
    void* extra_state);
int PMPI_Comm_create_keyval(
    MPI_Comm_copy_attr_function* type_copy_attr_fn,
    MPI_Comm_delete_attr_function* type_delete_attr_fn,
    int* type_keyval,
    void* extra_state);
int MPI_Comm_set_attr(
    MPI_Comm comm,
    int type_keyval,
    void* attribute_val);
int PMPI_Comm_set_attr(
    MPI_Comm comm,
    int type_keyval,
    void* attribute_val);
int MPI_Comm_free_keyval(int* type_keyval);
int PMPI_Comm_free_keyval(int* type_keyval);
int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval);
int PMPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval);

int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm* newcomm);
int PMPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm* newcomm);
int MPI_Comm_group(MPI_Comm comm, MPI_Group* group);
int PMPI_Comm_group(MPI_Comm comm, MPI_Group* group);
int MPI_Group_incl(
    MPI_Group group,
    int n,
    const int ranks[],
    MPI_Group* newgroup);
int PMPI_Group_incl(
    MPI_Group group,
    int n,
    const int ranks[],
    MPI_Group* newgroup);
int MPI_Group_excl(
    MPI_Group group,
    int n,
    const int ranks[],
    MPI_Group* newgroup);
int PMPI_Group_excl(
    MPI_Group group,
    int n,
    const int ranks[],
    MPI_Group* newgroup);
int MPI_Group_rank(MPI_Group group, int *rank);
int PMPI_Group_rank(MPI_Group group, int *rank);
int MPI_Group_translate_ranks(
    MPI_Group group1,
    int n,
    const int ranks1[],
    MPI_Group group2,
    int ranks2[]);
int PMPI_Group_translate_ranks(
    MPI_Group group1,
    int n,
    const int ranks1[],
    MPI_Group group2,
    int ranks2[]);
int MPI_Group_free(MPI_Group* group);
int PMPI_Group_free(MPI_Group* group);

int fbmpi_comm_null_copy_fn(
    MPI_Comm oldcomm,
    int type_keyval,
    void* extra_state,
    void* attribute_val_in,
    void* attribute_val_out,
    int* flag);
#define MPI_COMM_NULL_COPY_FN fbmpi_comm_null_copy_fn

int fbmpi_comm_dup_fn(
    MPI_Comm oldcomm,
    int type_keyval,
    void* extra_state,
    void* attribute_val_in,
    void* attribute_val_out,
    int* flag);
#define MPI_COMM_DUP_FN fbmpi_comm_dup_fn

int fbmpi_comm_null_delete_fn(
    MPI_Comm datacomm,
    int type_keyval,
    void* attribute_val,
    void* extra_state);
#define MPI_COMM_NULL_DELETE_FN fbmpi_comm_null_delete_fn

int MPI_Cart_create(
    MPI_Comm comm_old,
    int ndims,
    const int dims[],
    const int periods[],
    int reorder,
    MPI_Comm* comm_cart);
int PMPI_Cart_create(
    MPI_Comm comm_old,
    int ndims,
    const int dims[],
    const int periods[],
    int reorder,
    MPI_Comm* comm_cart);
int MPI_Cartdim_get(
    MPI_Comm comm,
    int* ndims);
int PMPI_Cartdim_get(
    MPI_Comm comm,
    int* ndims);
int MPI_Cart_get(
    MPI_Comm comm,
    int maxdims,
    int dims[],
    int periods[],
    int coords[]);
int PMPI_Cart_get(
    MPI_Comm comm,
    int maxdims,
    int dims[],
    int periods[],
    int coords[]);
int MPI_Cart_rank(
    MPI_Comm comm,
    const int coords[],
    int* rank);
int PMPI_Cart_rank(
    MPI_Comm comm,
    const int coords[],
    int* rank);
int MPI_Cart_coords(
    MPI_Comm comm,
    int rank,
    int maxdims,
    int coords[]);
int PMPI_Cart_coords(
    MPI_Comm comm,
    int rank,
    int maxdims,
    int coords[]);

int MPI_Info_get(
    MPI_Info info,
    const char* key,
    int valuelen,
    char* value,
    int* flag);
int PMPI_Info_get(
    MPI_Info info,
    const char* key,
    int valuelen,
    char* value,
    int* flag);
int MPI_Info_get_nkeys(MPI_Info info, int* nkeys);
int PMPI_Info_get_nkeys(MPI_Info info, int* nkeys);
int MPI_Info_get_nthkey(MPI_Info info, int n, char* key);
int PMPI_Info_get_nthkey(MPI_Info info, int n, char* key);
int MPI_Info_dup(MPI_Info info, MPI_Info* newinfo);
int PMPI_Info_dup(MPI_Info info, MPI_Info* newinfo);
int MPI_Info_free(MPI_Info* info);
int PMPI_Info_free(MPI_Info* info);
int MPI_Info_create(MPI_Info* info);
int PMPI_Info_create(MPI_Info* info);

int MPI_Type_commit(MPI_Datatype* datatype);
int PMPI_Type_commit(MPI_Datatype* datatype);
int MPI_Type_free(MPI_Datatype* datatype);
int PMPI_Type_free(MPI_Datatype* datatype);
int MPI_Type_get_extent(
    MPI_Datatype datatype,
    MPI_Aint* lb,
    MPI_Aint* extent);
int PMPI_Type_get_extent(
    MPI_Datatype datatype,
    MPI_Aint* lb,
    MPI_Aint* extent);
int MPI_Type_get_extent_x(
    MPI_Datatype datatype,
    MPI_Count* lb,
    MPI_Count* extent);
int PMPI_Type_get_extent_x(
    MPI_Datatype datatype,
    MPI_Count* lb,
    MPI_Count* extent);
int MPI_Type_contiguous(
    int count,
    MPI_Datatype oldtype,
    MPI_Datatype *newtype);
int PMPI_Type_contiguous(
    int count,
    MPI_Datatype oldtype,
    MPI_Datatype *newtype);
int MPI_Type_create_hvector(
    int count,
    int blocklength,
    MPI_Aint stride,
    MPI_Datatype oldtype,
    MPI_Datatype* newtype);
int PMPI_Type_create_hvector(
    int count,
    int blocklength,
    MPI_Aint stride,
    MPI_Datatype oldtype,
    MPI_Datatype* newtype);
int MPI_Type_create_hindexed(
    int count,
    const int array_of_blocklengths[],
    const MPI_Aint array_of_displacements[],
    MPI_Datatype oldtype,
    MPI_Datatype* newtype);
int PMPI_Type_create_hindexed(
    int count,
    const int array_of_blocklengths[],
    const MPI_Aint array_of_displacements[],
    MPI_Datatype oldtype,
    MPI_Datatype* newtype);
int MPI_Type_create_hindexed_block(
    int count,
    int blocklength,
    const MPI_Aint array_of_displacements[],
    MPI_Datatype oldtype,
    MPI_Datatype* newtype);
int PMPI_Type_create_hindexed_block(
    int count,
    int blocklength,
    const MPI_Aint array_of_displacements[],
    MPI_Datatype oldtype,
    MPI_Datatype* newtype);
int MPI_Type_create_struct(
    int count,
    const int array_of_blocklengths[],
    const MPI_Aint array_of_displacements[],
    const MPI_Datatype array_of_types[],
    MPI_Datatype* newtype);
int PMPI_Type_create_struct(
    int count,
    const int array_of_blocklengths[],
    const MPI_Aint array_of_displacements[],
    const MPI_Datatype array_of_types[],
    MPI_Datatype* newtype);
int MPI_Type_vector(
    int count,
    int blocklength,
    int stride,
    MPI_Datatype oldtype,
    MPI_Datatype* newtype);
int PMPI_Type_vector(
    int count,
    int blocklength,
    int stride,
    MPI_Datatype oldtype,
    MPI_Datatype* newtype);
int MPI_Type_create_resized(
    MPI_Datatype oldtype,
    MPI_Aint lb,
    MPI_Aint extent,
    MPI_Datatype* newtype);
int PMPI_Type_create_resized(
    MPI_Datatype oldtype,
    MPI_Aint lb,
    MPI_Aint extent,
    MPI_Datatype* newtype);
int MPI_Type_dup(
    MPI_Datatype oldtype,
    MPI_Datatype* newtype);
int PMPI_Type_dup(
    MPI_Datatype oldtype,
    MPI_Datatype* newtype);

int MPI_Get_count(
    const MPI_Status* status,
    MPI_Datatype datatype,
    int* count);
int PMPI_Get_count(
    const MPI_Status* status,
    MPI_Datatype datatype,
    int* count);
int MPI_Get_elements_x(
    const MPI_Status* status,
    MPI_Datatype datatype,
    MPI_Count* count);
int PMPI_Get_elements_x(
    const MPI_Status* status,
    MPI_Datatype datatype,
    MPI_Count* count);
int MPI_Type_size(MPI_Datatype datatype, int* size);
int PMPI_Type_size(MPI_Datatype datatype, int* size);
int MPI_Type_size_x(MPI_Datatype datatype, MPI_Count *size);
int PMPI_Type_size_x(MPI_Datatype datatype, MPI_Count *size);

int MPI_Send(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm);
int PMPI_Send(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm);
int MPI_Recv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status* status);
int PMPI_Recv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status* status);
int MPI_Bsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm);
int PMPI_Bsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm);
int MPI_Bsend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int PMPI_Bsend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int MPI_Rsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm);
int PMPI_Rsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm);
int MPI_Rsend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int PMPI_Rsend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int MPI_Ssend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm);
int PMPI_Ssend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm);
int MPI_Ssend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int PMPI_Ssend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int MPI_Isend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int PMPI_Isend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int MPI_Ibsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int PMPI_Ibsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int MPI_Issend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int PMPI_Issend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int MPI_Irecv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Request *request);
int PMPI_Irecv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Request *request);
int MPI_Iprobe(
    int source,
    int tag,
    MPI_Comm comm,
    int* flag,
    MPI_Status* status);
int PMPI_Iprobe(
    int source,
    int tag,
    MPI_Comm comm,
    int* flag,
    MPI_Status* status);
int MPI_Probe(
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status *status);
int PMPI_Probe(
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status *status);
int MPI_Test(
    MPI_Request* request,
    int* flag,
    MPI_Status* status);
int PMPI_Test(
    MPI_Request* request,
    int* flag,
    MPI_Status* status);
int MPI_Send_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int PMPI_Send_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request);
int MPI_Recv_init(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Request *request);
int PMPI_Recv_init(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Request *request);
int MPI_Irsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request *request);
int PMPI_Irsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request *request);
int MPI_Start(MPI_Request* request);
int PMPI_Start(MPI_Request* request);
int MPI_Startall(
    int count,
    MPI_Request array_of_requests[]);
int PMPI_Startall(
    int count,
    MPI_Request array_of_requests[]);
int MPI_Request_free(MPI_Request *request);
int PMPI_Request_free(MPI_Request *request);
int MPI_Cancel(MPI_Request *request);
int PMPI_Cancel(MPI_Request *request);
int MPI_Sendrecv(
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
    MPI_Status* status);
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
    MPI_Status* status);
int MPI_Sendrecv_replace(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int sendtag,
    int source,
    int recvtag,
    MPI_Comm comm,
    MPI_Status *status);
int PMPI_Sendrecv_replace(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int sendtag,
    int source,
    int recvtag,
    MPI_Comm comm,
    MPI_Status *status);

int MPI_Mprobe(
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Message* message,
    MPI_Status* status);
int PMPI_Mprobe(
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Message* message,
    MPI_Status* status);
int MPI_Imrecv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Message* message,
    MPI_Request* request);
int PMPI_Imrecv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Message* message,
    MPI_Request* request);
int MPI_Wait(
    MPI_Request* request,
    MPI_Status* status);
int PMPI_Wait(
    MPI_Request* request,
    MPI_Status* status);
int MPI_Test(
    MPI_Request* request,
    int* flag,
    MPI_Status* status);
int MPI_Waitall(
    int count,
    MPI_Request array_of_requests[],
    MPI_Status array_of_statuses[]);
int PMPI_Waitall(
    int count,
    MPI_Request array_of_requests[],
    MPI_Status array_of_statuses[]);
int MPI_Waitany(
    int count,
    MPI_Request array_of_requests[],
    int* index,
    MPI_Status* status);
int PMPI_Waitany(
    int count,
    MPI_Request array_of_requests[],
    int* index,
    MPI_Status* status);
int MPI_Waitsome(
    int incount,
    MPI_Request array_of_requests[],
    int *outcount,
    int array_of_indices[],
    MPI_Status array_of_statuses[]);
int PMPI_Waitsome(
    int incount,
    MPI_Request array_of_requests[],
    int *outcount,
    int array_of_indices[],
    MPI_Status array_of_statuses[]);
int MPI_Testall(
    int count,
    MPI_Request array_of_requests[],
    int* flag,
    MPI_Status array_of_statuses[]);
int PMPI_Testall(
    int count,
    MPI_Request array_of_requests[],
    int* flag,
    MPI_Status array_of_statuses[]);
int MPI_Testany(
    int count,
    MPI_Request array_of_requests[],
    int *index,
    int *flag,
    MPI_Status *status);
int PMPI_Testany(
    int count,
    MPI_Request array_of_requests[],
    int *index,
    int *flag,
    MPI_Status *status);
int MPI_Testsome(
    int incount,
    MPI_Request array_of_requests[],
    int* outcount,
    int array_of_indices[],
    MPI_Status array_of_statuses[]);
int PMPI_Testsome(
    int incount,
    MPI_Request array_of_requests[],
    int* outcount,
    int array_of_indices[],
    MPI_Status array_of_statuses[]);

int MPI_Barrier(MPI_Comm comm);
int PMPI_Barrier(MPI_Comm comm);
int MPI_Bcast(
    void* buffer,
    int count,
    MPI_Datatype datatype,
    int root,
    MPI_Comm comm);
int PMPI_Bcast(
    void* buffer,
    int count,
    MPI_Datatype datatype,
    int root,
    MPI_Comm comm);
int MPI_Reduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    int root,
    MPI_Comm comm);
int PMPI_Reduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    int root,
    MPI_Comm comm);
int MPI_Allreduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm);
int PMPI_Allreduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm);
int MPI_Iallreduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm,
    MPI_Request* request);
int PMPI_Iallreduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm,
    MPI_Request* request);
int MPI_Allgather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm);
int PMPI_Allgather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm);
int MPI_Gather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm);
int PMPI_Gather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm);
int MPI_Iallgather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm,
    MPI_Request* request);
int PMPI_Iallgather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm,
    MPI_Request* request);
int MPI_Scatter(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm);
int PMPI_Scatter(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm);
int MPI_Allgatherv(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    const int recvcounts[],
    const int displs[],
    MPI_Datatype recvtype,
    MPI_Comm comm);
int PMPI_Allgatherv(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    const int recvcounts[],
    const int displs[],
    MPI_Datatype recvtype,
    MPI_Comm comm);
int MPI_Gatherv(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    const int recvcounts[],
    const int displs[],
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm);
int PMPI_Gatherv(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    const int recvcounts[],
    const int displs[],
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm);
int MPI_Scatterv(
    const void* sendbuf,
    const int sendcounts[],
    const int displs[],
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm);
int PMPI_Scatterv(
    const void* sendbuf,
    const int sendcounts[],
    const int displs[],
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm);
int MPI_Alltoall(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm);
int PMPI_Alltoall(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm);
int MPI_Alltoallv(
    const void* sendbuf,
    const int sendcounts[],
    const int sdispls[],
    MPI_Datatype sendtype,
    void* recvbuf,
    const int recvcounts[],
    const int rdispls[],
    MPI_Datatype recvtype,
    MPI_Comm comm);
int PMPI_Alltoallv(
    const void* sendbuf,
    const int sendcounts[],
    const int sdispls[],
    MPI_Datatype sendtype,
    void* recvbuf,
    const int recvcounts[],
    const int rdispls[],
    MPI_Datatype recvtype,
    MPI_Comm comm);
int MPI_Neighbor_alltoall(
    const void *sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void *recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm);
int PMPI_Neighbor_alltoall(
    const void *sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void *recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm);
int MPI_Neighbor_alltoallv(
    const void *sendbuf,
    const int sendcounts[],
    const int sdispls[],
    MPI_Datatype sendtype,
    void *recvbuf,
    const int recvcounts[],
    const int rdispls[],
    MPI_Datatype recvtype,
    MPI_Comm comm);
int PMPI_Neighbor_alltoallv(
    const void *sendbuf,
    const int sendcounts[],
    const int sdispls[],
    MPI_Datatype sendtype,
    void *recvbuf,
    const int recvcounts[],
    const int rdispls[],
    MPI_Datatype recvtype,
    MPI_Comm comm);
int MPI_Dist_graph_create_adjacent(
    MPI_Comm comm_old,
    int indegree,
    const int sources[],
    const int sourceweights[],
    int outdegree,
    const int destinations[],
    const int destweights[],
    MPI_Info info,
    int reorder,
    MPI_Comm *comm_dist_graph);
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
    MPI_Comm *comm_dist_graph);
int MPI_Ibarrier(
    MPI_Comm comm,
    MPI_Request* request);
int PMPI_Ibarrier(
    MPI_Comm comm,
    MPI_Request* request);
int MPI_Scan(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm);
int PMPI_Scan(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm);
int MPI_Exscan(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm);
int PMPI_Exscan(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm);
int MPI_Reduce_scatter(
    const void *sendbuf,
    void *recvbuf,
    const int recvcounts[],
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm);
int PMPI_Reduce_scatter(
    const void *sendbuf,
    void *recvbuf,
    const int recvcounts[],
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm);

int MPI_Op_create(
    MPI_User_function* user_fn,
    int commute,
    MPI_Op* op);
int PMPI_Op_create(
    MPI_User_function* user_fn,
    int commute,
    MPI_Op* op);
int MPI_Op_free(MPI_Op* op);
int PMPI_Op_free(MPI_Op* op);

int MPI_File_open(
    MPI_Comm comm,
    const char* filename,
    int amode,
    MPI_Info info,
    MPI_File* fh);
int PMPI_File_open(
    MPI_Comm comm,
    const char* filename,
    int amode,
    MPI_Info info,
    MPI_File* fh);
int MPI_File_close(MPI_File* fh);
int PMPI_File_close(MPI_File* fh);
int MPI_File_delete(const char *filename, MPI_Info info);
int PMPI_File_delete(const char *filename, MPI_Info info);
int MPI_File_get_size(MPI_File fh, MPI_Offset* size);
int PMPI_File_get_size(MPI_File fh, MPI_Offset* size);
int MPI_File_set_size(MPI_File fh, MPI_Offset size);
int PMPI_File_set_size(MPI_File fh, MPI_Offset size);
int MPI_File_set_atomicity(MPI_File fh, int flag);
int PMPI_File_set_atomicity(MPI_File fh, int flag);
int MPI_File_get_atomicity(MPI_File fh, int* flag);
int PMPI_File_get_atomicity(MPI_File fh, int* flag);
int MPI_File_set_view(
    MPI_File fh,
    MPI_Offset disp,
    MPI_Datatype etype,
    MPI_Datatype filetype,
    const char* datarep,
    MPI_Info info);
int PMPI_File_set_view(
    MPI_File fh,
    MPI_Offset disp,
    MPI_Datatype etype,
    MPI_Datatype filetype,
    const char* datarep,
    MPI_Info info);
int MPI_File_write_at_all(
    MPI_File fh,
    MPI_Offset offset,
    const void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status);
int PMPI_File_write_at_all(
    MPI_File fh,
    MPI_Offset offset,
    const void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status);
int MPI_File_read_at(
    MPI_File fh,
    MPI_Offset offset,
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status);
int PMPI_File_read_at(
    MPI_File fh,
    MPI_Offset offset,
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status);
int MPI_File_read_at_all(
    MPI_File fh,
    MPI_Offset offset,
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status);
int PMPI_File_read_at_all(
    MPI_File fh,
    MPI_Offset offset,
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status);
int MPI_File_write_at(
    MPI_File fh,
    MPI_Offset offset,
    const void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status);
int PMPI_File_write_at(
    MPI_File fh,
    MPI_Offset offset,
    const void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status);
int MPI_File_sync(MPI_File fh);
int PMPI_File_sync(MPI_File fh);

MPI_Aint MPI_Aint_diff(MPI_Aint addr1, MPI_Aint addr2);
MPI_Aint PMPI_Aint_diff(MPI_Aint addr1, MPI_Aint addr2);
int MPI_Get_address(const void* location, MPI_Aint* address);
int PMPI_Get_address(const void* location, MPI_Aint* address);

MPI_Comm MPI_Comm_f2c(MPI_Fint comm);
MPI_Info MPI_Info_f2c(MPI_Fint comm);

int MPI_Pack_size(
    int incount,
    MPI_Datatype datatype,
    MPI_Comm comm,
    int *size);
int PMPI_Pack_size(
    int incount,
    MPI_Datatype datatype,
    MPI_Comm comm,
    int *size);
int MPI_Pack(
    const void* inbuf,
    int incount,
    MPI_Datatype datatype,
    void* outbuf,
    int outsize,
    int* position,
    MPI_Comm comm);
int PMPI_Pack(
    const void* inbuf,
    int incount,
    MPI_Datatype datatype,
    void* outbuf,
    int outsize,
    int* position,
    MPI_Comm comm);
int MPI_Unpack(
    const void *inbuf,
    int insize,
    int *position,
    void *outbuf,
    int outcount,
    MPI_Datatype datatype,
    MPI_Comm comm);
int PMPI_Unpack(
    const void *inbuf,
    int insize,
    int *position,
    void *outbuf,
    int outcount,
    MPI_Datatype datatype,
    MPI_Comm comm);

#ifdef __cplusplus
}
#endif

#endif
