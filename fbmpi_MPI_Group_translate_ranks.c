#include "mpi.h"

int MPI_Group_translate_ranks(
    MPI_Group group1,
    int n,
    const int ranks1[],
    MPI_Group group2,
    int ranks2[])
{
  return PMPI_Group_translate_ranks(
      group1, n, ranks1, group2, ranks2);
}
