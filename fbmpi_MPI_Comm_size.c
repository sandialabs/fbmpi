#include "mpi.h"

int MPI_Comm_size(MPI_Comm comm, int *size)
{
  return PMPI_Comm_size(comm, size);
}
