#include "mpi.h"

int MPI_File_get_size(MPI_File fh, MPI_Offset* size)
{
  return PMPI_File_get_size(fh, size);
}
