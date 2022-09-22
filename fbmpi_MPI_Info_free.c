#include "mpi.h"

int MPI_Info_free(MPI_Info* info)
{
  return PMPI_Info_free(info);
}
