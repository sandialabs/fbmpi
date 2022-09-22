#include "mpi.h"

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
