#include "mpi.h"

MPI_Fint MPI_Comm_c2f(MPI_Comm comm)
{
  return PMPI_Comm_c2f(comm);
}
