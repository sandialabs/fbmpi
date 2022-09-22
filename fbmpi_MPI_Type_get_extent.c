#include "mpi.h"

int MPI_Type_get_extent(
    MPI_Datatype datatype,
    MPI_Aint* lb,
    MPI_Aint* extent)
{
  return PMPI_Type_get_extent(datatype, lb, extent);
}
