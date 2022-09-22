#include "mpi.h"

int MPI_Op_free(MPI_Op* op)
{
  return PMPI_Op_free(op);
}
