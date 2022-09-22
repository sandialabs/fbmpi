#include "mpi.h"

int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm* newcomm)
{
  return PMPI_Comm_create(comm, group, newcomm);
}
