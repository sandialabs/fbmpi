#include "mpi.h"

int MPI_Recv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status* status)
{
  return PMPI_Recv(
      buf,
      count,
      datatype,
      source,
      tag,
      comm,
      status);
}
