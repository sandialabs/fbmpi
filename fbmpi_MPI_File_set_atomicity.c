#include "mpi.h"

int MPI_File_set_atomicity(MPI_File fh, int flag)
{
  return PMPI_File_set_atomicity(fh, flag);
}
