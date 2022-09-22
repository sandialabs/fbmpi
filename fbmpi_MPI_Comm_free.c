#include "mpi.h"

int MPI_Comm_free(MPI_Comm* comm)
{
  return PMPI_Comm_free(comm);
}
