#include "mpi.h"

int MPI_Get_elements_x(
    const MPI_Status* status,
    MPI_Datatype datatype,
    MPI_Count* count)
{
  return PMPI_Get_elements_x(status, datatype, count);
}
