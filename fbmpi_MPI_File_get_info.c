#include "mpi.h"

int MPI_File_get_info(MPI_File fh, MPI_Info* info_used)
{
  return PMPI_File_get_info(fh, info_used);
}
