#include "mpi.h"

int MPI_Cancel(MPI_Request *request)
{
  return PMPI_Cancel(request);
}
