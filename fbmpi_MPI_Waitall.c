#include "mpi.h"

int MPI_Waitall(
    int count,
    MPI_Request array_of_requests[],
    MPI_Status array_of_statuses[])
{
  return PMPI_Waitall(count, array_of_requests, array_of_statuses);
}
