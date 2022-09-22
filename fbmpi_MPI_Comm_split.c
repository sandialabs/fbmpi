#include "mpi.h"

int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm* newcomm)
{
  return PMPI_Comm_split(comm, color, key, newcomm);
}
