#include "mpi.h"

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
