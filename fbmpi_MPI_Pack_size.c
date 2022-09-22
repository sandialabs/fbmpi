#include "mpi.h"

int MPI_Pack_size(
    int incount,
    MPI_Datatype datatype,
    MPI_Comm comm,
    int *size)
{
  return PMPI_Pack_size(incount, datatype, comm, size);
}
