#include "mpi.h"

int MPI_Cart_create(
    MPI_Comm comm_old,
    int ndims,
    const int dims[],
    const int periods[],
    int reorder,
    MPI_Comm* comm_cart)
{
  return PMPI_Cart_create(
      comm_old,
      ndims,
      dims,
      periods,
      reorder,
      comm_cart);
}
