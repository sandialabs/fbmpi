#include "mpi.h"

int MPI_Start(MPI_Request* request)
{
  return PMPI_Start(request);
}
