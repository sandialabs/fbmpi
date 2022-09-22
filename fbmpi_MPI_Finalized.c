#include "mpi.h"

int MPI_Finalized(int* flag)
{
  return PMPI_Finalized(flag);
}
