#include "mpi.h"

int MPI_Get_address(void const* location, MPI_Aint* address)
{
  return PMPI_Get_address(location, address);
}
