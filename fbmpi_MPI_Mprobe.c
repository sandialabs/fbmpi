#include "mpi.h"

int MPI_Mprobe(
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Message* message,
    MPI_Status* status)
{
  return PMPI_Mprobe(
      source,
      tag,
      comm,
      message,
      status);
}
