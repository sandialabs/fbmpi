#include "mpi.h"

int MPI_Type_commit(MPI_Datatype* datatype)
{
  return PMPI_Type_commit(datatype);
}
