#include "mpi.h"

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
