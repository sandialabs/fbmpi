#include "mpi.h"

int MPI_Type_contiguous(
    int count,
    MPI_Datatype oldtype,
    MPI_Datatype *newtype)
{
  return PMPI_Type_contiguous(count, oldtype, newtype);
}
