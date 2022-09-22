#include "mpi.h"

int MPI_Type_size_x(MPI_Datatype datatype, MPI_Count* size)
{
  return PMPI_Type_size_x(datatype, size);
}
