#include "mpi.h"

int MPI_Info_create(MPI_Info* info)
{
  return PMPI_Info_create(info);
}
