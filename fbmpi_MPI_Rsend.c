#include "mpi.h"

int MPI_Rsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm)
{
  return PMPI_Rsend(
      buf,
      count,
      datatype,
      dest,
      tag,
      comm);
}
