#include "mpi.h"

int MPI_Info_get_nkeys(MPI_Info info, int* nkeys)
{
  return PMPI_Info_get_nkeys(info, nkeys);
}
