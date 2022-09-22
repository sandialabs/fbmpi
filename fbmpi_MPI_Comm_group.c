#include "mpi.h"

int MPI_Comm_group(MPI_Comm comm, MPI_Group* group)
{
  return PMPI_Comm_group(comm, group);
}
