#include "mpi.h"

int MPI_Info_get(
    MPI_Info info,
    const char* key,
    int valuelen,
    char* value,
    int* flag)
{
  return PMPI_Info_get(
      info,
      key,
      valuelen,
      value,
      flag);
}
