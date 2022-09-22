#include "mpi.h"

int MPI_File_close(MPI_File* fh)
{
  return PMPI_File_close(fh);
}
