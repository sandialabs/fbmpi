#include "mpi.h"

int MPI_Comm_test_inter(MPI_Comm comm, int *flag)
{
  return PMPI_Comm_test_inter(comm, flag);
}
