#include "mpi.h"

int MPI_Error_string(int errorcode, char* string, int* resultlen)
{
  return PMPI_Error_string(errorcode, string, resultlen);
}
