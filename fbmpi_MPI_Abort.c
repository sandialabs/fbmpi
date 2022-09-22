#include "mpi.h"

int MPI_Abort(MPI_Comm comm, int errorcode)
{
  return PMPI_Abort(comm, errorcode);
}
