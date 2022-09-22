#include "mpi.h"

int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler)
{
  return PMPI_Comm_set_errhandler(comm, errhandler);
}
