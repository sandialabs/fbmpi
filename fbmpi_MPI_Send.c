#include "mpi.h"

int MPI_Send(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm)
{
  return PMPI_Send(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm);
}
