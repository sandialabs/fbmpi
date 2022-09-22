#include "mpi.h"

int MPI_Ssend_init(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request)
{
  return PMPI_Ssend_init(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm,
      request);
}

