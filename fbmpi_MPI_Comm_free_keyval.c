#include "mpi.h"

int MPI_Comm_free_keyval(int* comm_keyval)
{
  return PMPI_Comm_free_keyval(comm_keyval);
}
