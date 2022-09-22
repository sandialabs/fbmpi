#include "mpi.h"

int MPI_Info_get_valuelen(
    MPI_Info info,
    const char* key,
    int* valuelen,
    int* flag)
{
  return PMPI_Info_get_valuelen(info, key, valuelen, flag);
}
