#include "mpi.h"

int MPI_Group_incl(
    MPI_Group group,
    int n,
    const int ranks[],
    MPI_Group* newgroup)
{
  return PMPI_Group_incl(group, n, ranks, newgroup);
}
