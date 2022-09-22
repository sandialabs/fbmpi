#include "mpi.h"

int MPI_Error_class(int errorcode, int* errorclass)
{
  return PMPI_Error_class(errorcode, errorclass);
}
