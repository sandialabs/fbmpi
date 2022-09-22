#include "mpi.h"

int MPI_Testany(
    int count,
    MPI_Request array_of_requests[],
    int *index,
    int *flag,
    MPI_Status *status)
{
  return PMPI_Testany(
      count,
      array_of_requests,
      index,
      flag,
      status);
}
