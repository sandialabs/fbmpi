#include "mpi.h"

int MPI_Type_vector(
    int count,
    int blocklength,
    int stride,
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  return PMPI_Type_vector(
      count,
      blocklength,
      stride,
      oldtype,
      newtype);
}
