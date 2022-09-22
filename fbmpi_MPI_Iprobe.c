#include "mpi.h"

int MPI_Iprobe(
    int source,
    int tag,
    MPI_Comm comm,
    int* flag,
    MPI_Status* status)
{
  return PMPI_Iprobe(
      source,
      tag,
      comm,
      flag,
      status);
}
