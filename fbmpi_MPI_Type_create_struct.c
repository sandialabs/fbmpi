#include "mpi.h"

int MPI_Type_create_struct(
    int count,
    const int array_of_blocklengths[],
    const MPI_Aint array_of_displacements[],
    const MPI_Datatype array_of_types[],
    MPI_Datatype* newtype)
{
  return PMPI_Type_create_struct(
      count,
      array_of_blocklengths,
      array_of_displacements,
      array_of_types,
      newtype);
}
