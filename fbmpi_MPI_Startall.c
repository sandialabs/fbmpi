#include "mpi.h"

int MPI_Startall(
    int count,
    MPI_Request array_of_requests[])
{
  return PMPI_Startall(count, array_of_requests);
}
