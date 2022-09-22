#include "mpi.h"

int MPI_Type_create_hindexed(
    int count,
    const int array_of_blocklengths[],
    const MPI_Aint array_of_displacements[],
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  return PMPI_Type_create_hindexed(
      count,
      array_of_blocklengths,
      array_of_displacements,
      oldtype,
      newtype);
}
