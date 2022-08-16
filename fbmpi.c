#include "mpi.h"

#include <stdlib.h>

int MPI_Init(int* argc, char*** argv)
{
  return PMPI_Init(argc, argv);
}

int MPI_Init_thread(
    int* argc,
    char*** argv,
    int required,
    int* provided)
{
  return PMPI_Init_thread(argc, argv, required, provided);
}

int MPI_Finalize(void)
{
  return PMPI_Finalize();
}

int MPI_Initialized(int* flag)
{
  return PMPI_Initialized(flag);
}

int MPI_Finalized(int* flag)
{
  return PMPI_Finalized(flag);
}

int MPI_Abort(MPI_Comm comm, int errorcode)
{
  return PMPI_Abort(comm, errorcode);
}

double MPI_Wtime(void)
{
  return PMPI_Wtime();
}

double MPI_Wtick(void)
{
  return PMPI_Wtick();
}

int MPI_Pcontrol(const int level, ...)
{
  return MPI_SUCCESS;
}

int MPI_Error_string(int errorcode, char* string, int* resultlen)
{
  return PMPI_Error_string(errorcode, string, resultlen);
}

int MPI_Error_class(int errorcode, int* errorclass)
{
  return PMPI_Error_class(errorcode, errorclass);
}

int MPI_Get_processor_name(char *name, int *resultlen)
{
  return PMPI_Get_processor_name(name, resultlen);
}

int MPI_Get_library_version(char *version, int *resultlen)
{
  return PMPI_Get_library_version(version, resultlen);
}

int MPI_Comm_size(MPI_Comm comm, int *size)
{
  return PMPI_Comm_size(comm, size);
}

int MPI_Comm_rank(MPI_Comm comm, int *rank)
{
  return PMPI_Comm_rank(comm, rank);
}

int MPI_Comm_dup(MPI_Comm comm, MPI_Comm* newcomm)
{
  return PMPI_Comm_dup(comm, newcomm);
}

int MPI_Comm_free(MPI_Comm* comm)
{
  return PMPI_Comm_free(comm);
}

int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int* result)
{
  return PMPI_Comm_compare(comm1, comm2, result);
}

int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm* newcomm)
{
  return PMPI_Comm_split(comm, color, key, newcomm);
}

int MPI_Comm_split_type(
    MPI_Comm comm,
    int split_type,
    int key,
    MPI_Info info,
    MPI_Comm *newcomm)
{
  return PMPI_Comm_split_type(comm, split_type, key, info, newcomm);
}

int MPI_Comm_test_inter(MPI_Comm comm, int *flag)
{
  return PMPI_Comm_test_inter(comm, flag);
}

int MPI_Comm_create_errhandler(
    MPI_Comm_errhandler_function* comm_errhandler_fn,
    MPI_Errhandler* errhandler)
{
  return PMPI_Comm_create_errhandler(comm_errhandler_fn, errhandler);
}

int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler)
{
  return PMPI_Comm_set_errhandler(comm, errhandler);
}

int MPI_Comm_create_keyval(
    MPI_Comm_copy_attr_function* comm_copy_attr_fn,
    MPI_Comm_delete_attr_function* comm_delete_attr_fn,
    int* type_keyval,
    void* extra_state)
{
  return PMPI_Comm_create_keyval(
      comm_copy_attr_fn,
      comm_delete_attr_fn,
      type_keyval,
      extra_state);
}

int MPI_Comm_set_attr(
    MPI_Comm comm,
    int comm_keyval,
    void* attribute_val)
{
  return PMPI_Comm_set_attr(comm, comm_keyval, attribute_val);
}

int MPI_Comm_free_keyval(int* comm_keyval)
{
  return PMPI_Comm_free_keyval(comm_keyval);
}

int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval)
{
  return PMPI_Comm_delete_attr(comm, comm_keyval);
}

int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm* newcomm)
{
  return PMPI_Comm_create(comm, group, newcomm);
}

int MPI_Comm_group(MPI_Comm comm, MPI_Group* group)
{
  return PMPI_Comm_group(comm, group);
}

int MPI_Group_incl(
    MPI_Group group,
    int n,
    const int ranks[],
    MPI_Group* newgroup)
{
  return PMPI_Group_incl(group, n, ranks, newgroup);
}

int MPI_Group_excl(
    MPI_Group group,
    int n,
    const int ranks[],
    MPI_Group* newgroup)
{
  return PMPI_Group_excl(group, n, ranks, newgroup);
}

int MPI_Group_rank(MPI_Group group, int *rank)
{
  return PMPI_Group_rank(group, rank);
}

int MPI_Group_translate_ranks(
    MPI_Group group1,
    int n,
    const int ranks1[],
    MPI_Group group2,
    int ranks2[])
{
  return PMPI_Group_translate_ranks(
      group1, n, ranks1, group2, ranks2);
}

int MPI_Group_free(MPI_Group* group)
{
  return PMPI_Group_free(group);
}

int MPI_Cart_create(
    MPI_Comm comm_old,
    int ndims,
    const int dims[],
    const int periods[],
    int reorder,
    MPI_Comm* comm_cart)
{
  return PMPI_Cart_create(
      comm_old,
      ndims,
      dims,
      periods,
      reorder,
      comm_cart);
}

int MPI_Cartdim_get(
    MPI_Comm comm,
    int* ndims)
{
  return PMPI_Cartdim_get(comm, ndims);
}

int MPI_Cart_get(
    MPI_Comm comm,
    int maxdims,
    int dims[],
    int periods[],
    int coords[])
{
  return PMPI_Cart_get(
      comm,
      maxdims,
      dims,
      periods,
      coords);
}

int MPI_Cart_rank(
    MPI_Comm comm,
    const int coords[],
    int* rank)
{
  return PMPI_Cart_rank(comm, coords, rank);
}

int MPI_Cart_coords(
    MPI_Comm comm,
    int rank,
    int maxdims,
    int coords[])
{
  return PMPI_Cart_coords(comm, rank, maxdims, coords);
}

int MPI_Info_set(
    MPI_Info info,
    const char* key,
    const char* value)
{
  return PMPI_Info_set(
      info,
      key,
      value);
}

int MPI_Info_get(
    MPI_Info info,
    const char* key,
    int valuelen,
    char* value,
    int* flag)
{
  return PMPI_Info_get(
      info,
      key,
      valuelen,
      value,
      flag);
}

int MPI_Info_get_nkeys(MPI_Info info, int* nkeys)
{
  return PMPI_Info_get_nkeys(info, nkeys);
}

int MPI_Info_get_nthkey(MPI_Info info, int n, char* key)
{
  return PMPI_Info_get_nthkey(info, n, key);
}

int MPI_Info_get_valuelen(
    MPI_Info info,
    const char* key,
    int* valuelen,
    int* flag)
{
  return PMPI_Info_get_valuelen(info, key, valuelen, flag);
}

int MPI_Info_dup(MPI_Info info, MPI_Info* newinfo)
{
  return PMPI_Info_dup(info, newinfo);
}

int MPI_Info_free(MPI_Info* info)
{
  return PMPI_Info_free(info);
}

int MPI_Info_create(MPI_Info* info)
{
  return PMPI_Info_create(info);
}

int MPI_Type_commit(MPI_Datatype* datatype)
{
  return PMPI_Type_commit(datatype);
}

int MPI_Type_free(MPI_Datatype* datatype)
{
  return PMPI_Type_free(datatype);
}

int MPI_Type_get_extent(
    MPI_Datatype datatype,
    MPI_Aint* lb,
    MPI_Aint* extent)
{
  return PMPI_Type_get_extent(datatype, lb, extent);
}

int MPI_Type_get_extent_x(
    MPI_Datatype datatype,
    MPI_Count* lb,
    MPI_Count* extent)
{
  return PMPI_Type_get_extent_x(datatype, lb, extent);
}

int MPI_Type_contiguous(
    int count,
    MPI_Datatype oldtype,
    MPI_Datatype *newtype)
{
  return PMPI_Type_contiguous(count, oldtype, newtype);
}

int MPI_Type_create_hvector(
    int count,
    int blocklength,
    MPI_Aint stride,
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  return PMPI_Type_create_hvector(
      count,
      blocklength,
      stride,
      oldtype,
      newtype);
}

int MPI_Type_create_hindexed(
    int count,
    const int array_of_blocklengths[],
    const MPI_Aint array_of_displacements[],
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  return PMPI_Type_create_hindexed(
      count,
      array_of_blocklengths,
      array_of_displacements,
      oldtype,
      newtype);
}

int MPI_Type_create_hindexed_block(
    int count,
    int blocklength,
    const MPI_Aint array_of_displacements[],
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  return PMPI_Type_create_hindexed_block(
      count,
      blocklength,
      array_of_displacements,
      oldtype,
      newtype);
}

int MPI_Type_create_struct(
    int count,
    const int array_of_blocklengths[],
    const MPI_Aint array_of_displacements[],
    const MPI_Datatype array_of_types[],
    MPI_Datatype* newtype)
{
  return PMPI_Type_create_struct(
      count,
      array_of_blocklengths,
      array_of_displacements,
      array_of_types,
      newtype);
}

int MPI_Type_vector(
    int count,
    int blocklength,
    int stride,
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  return PMPI_Type_vector(
      count,
      blocklength,
      stride,
      oldtype,
      newtype);
}

int MPI_Type_create_resized(
    MPI_Datatype oldtype,
    MPI_Aint lb,
    MPI_Aint extent,
    MPI_Datatype* newtype)
{
  return PMPI_Type_create_resized(
      oldtype,
      lb,
      extent,
      newtype);
}

int MPI_Type_dup(
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  return PMPI_Type_dup(oldtype, newtype);
}

int MPI_Get_count(
    const MPI_Status* status,
    MPI_Datatype datatype,
    int* count)
{
  return PMPI_Get_count(status, datatype, count);
}

int MPI_Get_elements_x(
    const MPI_Status* status,
    MPI_Datatype datatype,
    MPI_Count* count)
{
  return PMPI_Get_elements_x(status, datatype, count);
}

int MPI_Type_size(MPI_Datatype datatype, int* size)
{
  return PMPI_Type_size(datatype, size);
}

int MPI_Type_size_x(MPI_Datatype datatype, MPI_Count* size)
{
  return PMPI_Type_size_x(datatype, size);
}

int MPI_Send(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm)
{
  return PMPI_Send(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm);
}

int MPI_Recv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status* status)
{
  return PMPI_Recv(
      buf,
      count,
      datatype,
      source,
      tag,
      comm,
      status);
}

int MPI_Bsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm)
{
  return PMPI_Bsend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm);
}

int MPI_Bsend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  return PMPI_Bsend_init(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm,
      request);
}

int MPI_Rsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm)
{
  return PMPI_Rsend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm);
}

int MPI_Rsend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  return PMPI_Rsend_init(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm,
      request);
}

int MPI_Ssend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm)
{
  return PMPI_Ssend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm);
}

int MPI_Ssend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  return PMPI_Ssend_init(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm,
      request);
}

int MPI_Isend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  return PMPI_Isend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm,
      request);
}

int MPI_Ibsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  return PMPI_Ibsend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm,
      request);
}

int MPI_Issend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  return PMPI_Issend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm,
      request);
}

int MPI_Irecv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Request *request)
{
  return PMPI_Irecv(
      buf,
      count,
      datatype,
      source,
      tag,
      comm,
      request);
}

int MPI_Iprobe(
    int source,
    int tag,
    MPI_Comm comm,
    int* flag,
    MPI_Status* status)
{
  return PMPI_Iprobe(
      source,
      tag,
      comm,
      flag,
      status);
}

int MPI_Probe(
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status *status)
{
  return PMPI_Probe(source, tag, comm, status);
}

int MPI_Test(
    MPI_Request* request,
    int* flag,
    MPI_Status* status)
{
  return PMPI_Test(request, flag, status);
}

int MPI_Send_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  return PMPI_Send_init(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm,
      request);
}

int MPI_Recv_init(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Request *request)
{
  return PMPI_Recv_init(
      buf,
      count,
      datatype,
      source,
      tag,
      comm,
      request);
}

int MPI_Irsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request *request)
{
  return PMPI_Irsend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm,
      request);
}

int MPI_Start(MPI_Request* request)
{
  return PMPI_Start(request);
}

int MPI_Startall(
    int count,
    MPI_Request array_of_requests[])
{
  return PMPI_Startall(count, array_of_requests);
}

int MPI_Request_free(MPI_Request *request)
{
  return PMPI_Request_free(request);
}

int MPI_Cancel(MPI_Request *request)
{
  return PMPI_Cancel(request);
}

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
    MPI_Status* status)
{
  return PMPI_Sendrecv(
      sendbuf,
      sendcount,
      sendtype,
      dest,
      sendtag,
      recvbuf,
      recvcount,
      recvtype,
      source,
      recvtag,
      comm,
      status);
}

int MPI_Sendrecv_replace(
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
  return PMPI_Sendrecv_replace(
      buf,
      count,
      datatype,
      dest,
      sendtag,
      source,
      recvtag,
      comm,
      status);
}

int MPI_Wait(
    MPI_Request* request,
    MPI_Status* status)
{
  return PMPI_Wait(request, status);
}

int MPI_Mprobe(
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Message* message,
    MPI_Status* status)
{
  return PMPI_Mprobe(
      source,
      tag,
      comm,
      message,
      status);
}

int MPI_Imrecv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Message* message,
    MPI_Request* request)
{
  return PMPI_Imrecv(
      buf,
      count,
      datatype,
      message,
      request);
}

int MPI_Waitall(
    int count,
    MPI_Request array_of_requests[],
    MPI_Status array_of_statuses[])
{
  return PMPI_Waitall(count, array_of_requests, array_of_statuses);
}

int MPI_Waitany(
    int count,
    MPI_Request array_of_requests[],
    int* index,
    MPI_Status* status)
{
  return PMPI_Waitany(count, array_of_requests, index, status);
}

int MPI_Waitsome(
    int incount,
    MPI_Request array_of_requests[],
    int *outcount,
    int array_of_indices[],
    MPI_Status array_of_statuses[])
{
  return PMPI_Waitsome(
      incount,
      array_of_requests,
      outcount,
      array_of_indices,
      array_of_statuses);
}

int MPI_Testall(
    int count,
    MPI_Request array_of_requests[],
    int* flag,
    MPI_Status array_of_statuses[])
{
  return PMPI_Testall(
      count,
      array_of_requests,
      flag,
      array_of_statuses);
}

int MPI_Testany(
    int count,
    MPI_Request array_of_requests[],
    int *index,
    int *flag,
    MPI_Status *status)
{
  return PMPI_Testany(
      count,
      array_of_requests,
      index,
      flag,
      status);
}

int MPI_Testsome(
    int incount,
    MPI_Request array_of_requests[],
    int* outcount,
    int array_of_indices[],
    MPI_Status array_of_statuses[])
{
  return PMPI_Testsome(
      incount,
      array_of_requests,
      outcount,
      array_of_indices,
      array_of_statuses);
}

int MPI_Barrier(MPI_Comm comm)
{
  return PMPI_Barrier(comm);
}

int MPI_Bcast(
    void* buffer,
    int count,
    MPI_Datatype datatype,
    int root,
    MPI_Comm comm)
{
  return PMPI_Bcast(buffer, count, datatype, root, comm);
}

int MPI_Reduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    int root,
    MPI_Comm comm)
{
  return PMPI_Reduce(
      sendbuf,
      recvbuf,
      count,
      datatype,
      op,
      root,
      comm);
}

int MPI_Allreduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm)
{
  return PMPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Iallreduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm,
    MPI_Request* request)
{
  return PMPI_Iallreduce(
      sendbuf,
      recvbuf,
      count,
      datatype,
      op,
      comm,
      request);
}

int MPI_Allgather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm)
{
  return PMPI_Allgather(
      sendbuf,
      sendcount,
      sendtype,
      recvbuf,
      recvcount,
      recvtype,
      comm);
}

int MPI_Gather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm)
{
  return PMPI_Gather(
      sendbuf,
      sendcount,
      sendtype,
      recvbuf,
      recvcount,
      recvtype,
      root,
      comm);
}

int MPI_Iallgather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm,
    MPI_Request* request)
{
  return PMPI_Iallgather(
      sendbuf,
      sendcount,
      sendtype,
      recvbuf,
      recvcount,
      recvtype,
      comm,
      request);
}

int MPI_Scatter(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm)
{
  return PMPI_Scatter(
      sendbuf,
      sendcount,
      sendtype,
      recvbuf,
      recvcount,
      recvtype,
      root,
      comm);
}

int MPI_Allgatherv(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    const int recvcounts[],
    const int displs[],
    MPI_Datatype recvtype,
    MPI_Comm comm)
{
  return PMPI_Allgatherv(
      sendbuf,
      sendcount,
      sendtype,
      recvbuf,
      recvcounts,
      displs,
      recvtype,
      comm);
}

int MPI_Gatherv(
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
  return PMPI_Gatherv(
      sendbuf,
      sendcount,
      sendtype,
      recvbuf,
      recvcounts,
      displs,
      recvtype,
      root,
      comm);
}

int MPI_Scatterv(
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
  return PMPI_Scatterv(
      sendbuf,
      sendcounts,
      displs,
      sendtype,
      recvbuf,
      recvcount,
      recvtype,
      root,
      comm);
}

int MPI_Alltoall(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm)
{
  return PMPI_Alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Alltoallv(
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
  return PMPI_Alltoallv(
      sendbuf,
      sendcounts,
      sdispls,
      sendtype,
      recvbuf,
      recvcounts,
      rdispls,
      recvtype,
      comm);
}

int MPI_Neighbor_alltoall(
    const void *sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void *recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm)
{
  return PMPI_Neighbor_alltoall(
      sendbuf,
      sendcount,
      sendtype,
      recvbuf,
      recvcount,
      recvtype,
      comm);
}

int MPI_Neighbor_alltoallv(
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
  return PMPI_Neighbor_alltoallv(
      sendbuf,
      sendcounts,
      sdispls,
      sendtype,
      recvbuf,
      recvcounts,
      rdispls,
      recvtype,
      comm);
}

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
    MPI_Comm *comm_dist_graph)
{
  return PMPI_Dist_graph_create_adjacent(
      comm_old,
      indegree,
      sources,
      sourceweights,
      outdegree,
      destinations,
      destweights,
      info,
      reorder,
      comm_dist_graph);
}

int MPI_Ibarrier(
    MPI_Comm comm,
    MPI_Request* request)
{
  return PMPI_Ibarrier(comm, request);
}

int MPI_Scan(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm)
{
  return PMPI_Scan(
      sendbuf,
      recvbuf,
      count,
      datatype,
      op,
      comm);
}

int MPI_Exscan(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm)
{
  return PMPI_Exscan(
      sendbuf,
      recvbuf,
      count,
      datatype,
      op,
      comm);
}

int MPI_Reduce_scatter(
    const void *sendbuf,
    void *recvbuf,
    const int recvcounts[],
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm)
{
  return PMPI_Reduce_scatter(
      sendbuf,
      recvbuf,
      recvcounts,
      datatype,
      op,
      comm);
}

int MPI_Op_create(
    MPI_User_function* user_fn,
    int commute,
    MPI_Op* op)
{
  return PMPI_Op_create(user_fn, commute, op);
}

int MPI_Op_free(MPI_Op* op)
{
  return PMPI_Op_free(op);
}

int MPI_File_open(
    MPI_Comm comm,
    const char* filename,
    int amode,
    MPI_Info info,
    MPI_File* fh)
{
  return PMPI_File_open(
      comm,
      filename,
      amode,
      info,
      fh);
}

int MPI_File_close(MPI_File* fh)
{
  return PMPI_File_close(fh);
}

int MPI_File_delete(const char *filename, MPI_Info info)
{
  return PMPI_File_delete(filename, info);
}

int MPI_File_get_size(MPI_File fh, MPI_Offset* size)
{
  return PMPI_File_get_size(fh, size);
}

int MPI_File_set_size(MPI_File fh, MPI_Offset size)
{
  return PMPI_File_set_size(fh, size);
}

int MPI_File_set_atomicity(MPI_File fh, int flag)
{
  return PMPI_File_set_atomicity(fh, flag);
}

int MPI_File_get_atomicity(MPI_File fh, int* flag)
{
  return PMPI_File_get_atomicity(fh, flag);
}

int MPI_File_set_view(
    MPI_File fh,
    MPI_Offset disp,
    MPI_Datatype etype,
    MPI_Datatype filetype,
    const char* datarep,
    MPI_Info info)
{
  return PMPI_File_set_view(
      fh,
      disp,
      etype,
      filetype,
      datarep,
      info);
}

int MPI_File_write_at_all(
    MPI_File fh,
    MPI_Offset offset,
    const void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status)
{
  return PMPI_File_write_at_all(
      fh,
      offset,
      buf,
      count,
      datatype,
      status);
}

int MPI_File_read_at(
    MPI_File fh,
    MPI_Offset offset,
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status)
{
  return PMPI_File_read_at(
      fh,
      offset,
      buf,
      count,
      datatype,
      status);
}

int MPI_File_read_at_all(
    MPI_File fh,
    MPI_Offset offset,
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status)
{
  return PMPI_File_read_at_all(
      fh,
      offset,
      buf,
      count,
      datatype,
      status);
}

int MPI_File_write_at(
    MPI_File fh,
    MPI_Offset offset,
    const void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status)
{
  return PMPI_File_write_at(
      fh,
      offset,
      buf,
      count,
      datatype,
      status);
}

int MPI_File_sync(MPI_File fh)
{
  return PMPI_File_sync(fh);
}

int MPI_File_get_info(MPI_File fh, MPI_Info* info_used)
{
  return PMPI_File_get_info(fh, info_used);
}

MPI_Aint MPI_Aint_diff(MPI_Aint addr1, MPI_Aint addr2)
{
  return PMPI_Aint_diff(addr1, addr2);
}

int MPI_Get_address(void const* location, MPI_Aint* address)
{
  return PMPI_Get_address(location, address);
}

MPI_Comm MPI_Comm_f2c(MPI_Fint comm)
{
  fprintf(stderr, "MPI_Comm_f2c not implemented\n");
  abort();
  return MPI_COMM_NULL;
}

MPI_Info MPI_Info_f2c(MPI_Fint comm)
{
  fprintf(stderr, "MPI_Info_f2c not implemented\n");
  abort();
  return MPI_INFO_NULL;
}

int MPI_Pack_size(
    int incount,
    MPI_Datatype datatype,
    MPI_Comm comm,
    int *size)
{
  return PMPI_Pack_size(incount, datatype, comm, size);
}

int MPI_Pack(
    const void* inbuf,
    int incount,
    MPI_Datatype datatype,
    void* outbuf,
    int outsize,
    int* position,
    MPI_Comm comm)
{
  return PMPI_Pack(
      inbuf,
      incount,
      datatype,
      outbuf,
      outsize,
      position,
      comm);
}

int MPI_Unpack(
    const void *inbuf,
    int insize,
    int *position,
    void *outbuf,
    int outcount,
    MPI_Datatype datatype,
    MPI_Comm comm)
{
  return PMPI_Unpack(
      inbuf,
      insize,
      position,
      outbuf,
      outcount,
      datatype,
      comm);
}
