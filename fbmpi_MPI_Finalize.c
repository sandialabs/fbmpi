#include "mpi.h"

int MPI_Finalize(void)
{
  return PMPI_Finalize();
}
