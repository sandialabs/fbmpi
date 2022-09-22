#include "mpi.h"

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
