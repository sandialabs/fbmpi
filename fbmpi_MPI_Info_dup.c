#include "mpi.h"

int MPI_Info_dup(MPI_Info info, MPI_Info* newinfo)
{
  return PMPI_Info_dup(info, newinfo);
}
