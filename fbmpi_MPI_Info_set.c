#include "mpi.h"

int MPI_Info_set(
    MPI_Info info,
    const char* key,
    const char* value)
{
  return PMPI_Info_set(
      info,
      key,
      value);
}
