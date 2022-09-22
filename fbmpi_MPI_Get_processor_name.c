#include "mpi.h"

int MPI_Get_processor_name(char *name, int *resultlen)
{
  return PMPI_Get_processor_name(name, resultlen);
}
