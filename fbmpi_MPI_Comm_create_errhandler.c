#include "mpi.h"

int MPI_Comm_create_errhandler(
    MPI_Comm_errhandler_function* comm_errhandler_fn,
    MPI_Errhandler* errhandler)
{
  return PMPI_Comm_create_errhandler(comm_errhandler_fn, errhandler);
}
