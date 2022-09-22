#include "mpi.h"

int MPI_Type_free(MPI_Datatype* datatype)
{
  return PMPI_Type_free(datatype);
}
