#include "mpi.h"

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
