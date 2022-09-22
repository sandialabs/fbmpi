#include "mpi.h"

double MPI_Wtime(void)
{
  return PMPI_Wtime();
}
