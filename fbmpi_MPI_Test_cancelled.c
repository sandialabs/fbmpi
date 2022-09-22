#include "mpi.h"

int MPI_Test_cancelled(const MPI_Status *status, int *flag)
{
  return PMPI_Test_cancelled(status, flag);
}
