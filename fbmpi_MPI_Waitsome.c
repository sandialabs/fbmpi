#include "mpi.h"

int MPI_Waitsome(
    int incount,
    MPI_Request array_of_requests[],
    int *outcount,
    int array_of_indices[],
    MPI_Status array_of_statuses[])
{
  return PMPI_Waitsome(
      incount,
      array_of_requests,
      outcount,
      array_of_indices,
      array_of_statuses);
}
