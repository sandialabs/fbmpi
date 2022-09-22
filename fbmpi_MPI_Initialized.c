#include "mpi.h"

int MPI_Initialized(int* flag)
{
  return PMPI_Initialized(flag);
}
