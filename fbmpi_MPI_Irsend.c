#include "mpi.h"

int MPI_Irsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request *request)
{
  return PMPI_Irsend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm,
      request);
}
