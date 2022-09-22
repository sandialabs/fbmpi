#include "mpi.h"

int MPI_Group_free(MPI_Group* group)
{
  return PMPI_Group_free(group);
}
