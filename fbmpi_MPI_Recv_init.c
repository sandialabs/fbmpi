#include "mpi.h"

int MPI_Recv_init(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Request *request)
{
  return PMPI_Recv_init(
      buf,
      count,
      datatype,
      source,
      tag,
      comm,
      request);
}
