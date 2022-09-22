#include "mpi.h"

int MPI_Cart_get(
    MPI_Comm comm,
    int maxdims,
    int dims[],
    int periods[],
    int coords[])
{
  return PMPI_Cart_get(
      comm,
      maxdims,
      dims,
      periods,
      coords);
}
