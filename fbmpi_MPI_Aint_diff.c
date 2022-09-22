#include "mpi.h"

MPI_Aint MPI_Aint_diff(MPI_Aint addr1, MPI_Aint addr2)
{
  return PMPI_Aint_diff(addr1, addr2);
}
