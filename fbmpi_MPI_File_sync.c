#include "mpi.h"

int MPI_File_sync(MPI_File fh)
{
  return PMPI_File_sync(fh);
}
