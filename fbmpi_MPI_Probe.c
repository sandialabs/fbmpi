#include "mpi.h"

int MPI_Probe(
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status *status)
{
  return PMPI_Probe(source, tag, comm, status);
}
