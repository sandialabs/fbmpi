#include "mpi.h"

int MPI_Bsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm)
{
  return PMPI_Bsend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm);
}
