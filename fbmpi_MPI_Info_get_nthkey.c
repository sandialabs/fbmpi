#include "mpi.h"

int MPI_Info_get_nthkey(MPI_Info info, int n, char* key)
{
  return PMPI_Info_get_nthkey(info, n, key);
}
