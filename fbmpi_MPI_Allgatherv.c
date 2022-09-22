#include "mpi.h"

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
