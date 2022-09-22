#include "mpi.h"

int MPI_Type_create_hvector(
    int count,
    int blocklength,
    MPI_Aint stride,
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  return PMPI_Type_create_hvector(
      count,
      blocklength,
      stride,
      oldtype,
      newtype);
}
