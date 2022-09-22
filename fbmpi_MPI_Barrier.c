#include "mpi.h"

int MPI_Barrier(MPI_Comm comm)
{
  return PMPI_Barrier(comm);
}
