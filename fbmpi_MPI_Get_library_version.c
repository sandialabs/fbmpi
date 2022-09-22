#include "mpi.h"

int MPI_Get_library_version(char *version, int *resultlen)
{
  return PMPI_Get_library_version(version, resultlen);
}
