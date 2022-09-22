#include "mpi.h"

int MPI_Type_create_resized(
    MPI_Datatype oldtype,
    MPI_Aint lb,
    MPI_Aint extent,
    MPI_Datatype* newtype)
{
  return PMPI_Type_create_resized(
      oldtype,
      lb,
      extent,
      newtype);
}
