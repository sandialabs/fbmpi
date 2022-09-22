#include "mpi.h"

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
