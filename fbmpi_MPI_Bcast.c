#include "mpi.h"

int MPI_Bcast(
    void* buffer,
    int count,
    MPI_Datatype datatype,
    int root,
    MPI_Comm comm)
{
  return PMPI_Bcast(buffer, count, datatype, root, comm);
}
