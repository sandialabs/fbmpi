#include "mpi.h"

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
