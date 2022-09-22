#include "mpi.h"

int MPI_Comm_dup(MPI_Comm comm, MPI_Comm* newcomm)
{
  return PMPI_Comm_dup(comm, newcomm);
}
