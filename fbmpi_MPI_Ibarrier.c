#include "mpi.h"

int MPI_Ibarrier(
    MPI_Comm comm,
    MPI_Request* request)
{
  return PMPI_Ibarrier(comm, request);
}
