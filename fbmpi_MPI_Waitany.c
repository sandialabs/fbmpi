#include "mpi.h"

int MPI_Waitany(
    int count,
    MPI_Request array_of_requests[],
    int* index,
    MPI_Status* status)
{
  return PMPI_Waitany(count, array_of_requests, index, status);
}
