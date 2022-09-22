#include "mpi.h"

int MPI_Type_size(MPI_Datatype datatype, int* size)
{
  return PMPI_Type_size(datatype, size);
}
