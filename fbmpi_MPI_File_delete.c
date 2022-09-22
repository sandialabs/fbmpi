#include "mpi.h"

int MPI_File_delete(const char *filename, MPI_Info info)
{
  return PMPI_File_delete(filename, info);
}
