#include "mpi.h"

int MPI_Cartdim_get(
    MPI_Comm comm,
    int* ndims)
{
  return PMPI_Cartdim_get(comm, ndims);
}
