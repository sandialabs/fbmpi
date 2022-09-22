#include "mpi.h"

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
