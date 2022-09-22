#include "mpi.h"

int MPI_Testall(
    int count,
    MPI_Request array_of_requests[],
    int* flag,
    MPI_Status array_of_statuses[])
{
  return PMPI_Testall(
      count,
      array_of_requests,
      flag,
      array_of_statuses);
}
