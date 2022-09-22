#include "mpi.h"

int MPI_Type_get_extent_x(
    MPI_Datatype datatype,
    MPI_Count* lb,
    MPI_Count* extent)
{
  return PMPI_Type_get_extent_x(datatype, lb, extent);
}
