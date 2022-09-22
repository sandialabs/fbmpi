#include "mpi.h"

int MPI_File_get_atomicity(MPI_File fh, int* flag)
{
  return PMPI_File_get_atomicity(fh, flag);
}
