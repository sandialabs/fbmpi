#include "mpi.h"

int MPI_Type_create_hindexed_block(
    int count,
    int blocklength,
    const MPI_Aint array_of_displacements[],
    MPI_Datatype oldtype,
    MPI_Datatype* newtype)
{
  return PMPI_Type_create_hindexed_block(
      count,
      blocklength,
      array_of_displacements,
      oldtype,
      newtype);
}
