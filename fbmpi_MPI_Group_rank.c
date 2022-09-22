#include "mpi.h"

int MPI_Group_rank(MPI_Group group, int *rank)
{
  return PMPI_Group_rank(group, rank);
}
