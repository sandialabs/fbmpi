#include "mpi.h"

int MPI_Cart_coords(
    MPI_Comm comm,
    int rank,
    int maxdims,
    int coords[])
{
  return PMPI_Cart_coords(comm, rank, maxdims, coords);
}
