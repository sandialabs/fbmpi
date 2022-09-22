#include "mpi.h"

int MPI_Get_count(
    const MPI_Status* status,
    MPI_Datatype datatype,
    int* count)
{
  return PMPI_Get_count(status, datatype, count);
}
