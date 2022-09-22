#include "mpi.h"

int MPI_Ssend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm)
{
  return PMPI_Ssend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm);
}
