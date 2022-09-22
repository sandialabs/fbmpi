#include "mpi.h"

int MPI_Op_create(
    MPI_User_function* user_fn,
    int commute,
    MPI_Op* op)
{
  return PMPI_Op_create(user_fn, commute, op);
}
