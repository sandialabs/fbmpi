#include "mpi.h"

int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval)
{
  return PMPI_Comm_delete_attr(comm, comm_keyval);
}
