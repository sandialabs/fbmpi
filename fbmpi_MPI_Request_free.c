#include "mpi.h"

int MPI_Request_free(MPI_Request *request)
{
  return PMPI_Request_free(request);
}
