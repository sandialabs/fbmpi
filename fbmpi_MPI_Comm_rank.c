#include "mpi.h"

int MPI_Comm_rank(MPI_Comm comm, int *rank)
{
  return PMPI_Comm_rank(comm, rank);
}
