#include "mpi.h"

int MPI_Wait(
    MPI_Request* request,
    MPI_Status* status)
{
  return PMPI_Wait(request, status);
}
