#include "mpi.h"

int MPI_Type_dup(
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  return PMPI_Type_dup(oldtype, newtype);
}
