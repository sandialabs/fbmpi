#include "mpi.h"

int MPI_Test(
    MPI_Request* request,
    int* flag,
    MPI_Status* status)
{
  return PMPI_Test(request, flag, status);
}
