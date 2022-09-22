#include "mpi.h"

int MPI_Group_excl(
    MPI_Group group,
    int n,
    const int ranks[],
    MPI_Group* newgroup)
{
  return PMPI_Group_excl(group, n, ranks, newgroup);
}
