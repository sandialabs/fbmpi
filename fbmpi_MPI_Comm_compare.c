#include "mpi.h"

int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int* result)
{
  return PMPI_Comm_compare(comm1, comm2, result);
}
