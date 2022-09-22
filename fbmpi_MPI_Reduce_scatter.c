#include "mpi.h"

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
