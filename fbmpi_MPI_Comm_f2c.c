#include "mpi.h"

MPI_Comm MPI_Comm_f2c(MPI_Fint comm)
{
  return PMPI_Comm_f2c(comm);
}
