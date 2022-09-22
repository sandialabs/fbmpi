#include "mpi.h"

int MPI_Get_version(int *version, int *subversion)
{
  return PMPI_Get_version(version, subversion);
}
