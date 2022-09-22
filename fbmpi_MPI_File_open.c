#include "mpi.h"

int MPI_File_open(
    MPI_Comm comm,
    const char* filename,
    int amode,
    MPI_Info info,
    MPI_File* fh)
{
  return PMPI_File_open(
      comm,
      filename,
      amode,
      info,
      fh);
}
