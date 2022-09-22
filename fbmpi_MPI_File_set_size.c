#include "mpi.h"

int MPI_File_set_size(MPI_File fh, MPI_Offset size)
{
  return PMPI_File_set_size(fh, size);
}
