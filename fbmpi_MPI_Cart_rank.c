#include "mpi.h"

int MPI_Cart_rank(
    MPI_Comm comm,
    const int coords[],
    int* rank)
{
  return PMPI_Cart_rank(comm, coords, rank);
}
