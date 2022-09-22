#include "mpi.h"

int MPI_File_write_at_all(
    MPI_File fh,
    MPI_Offset offset,
    const void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status)
{
  return PMPI_File_write_at_all(
      fh,
      offset,
      buf,
      count,
      datatype,
      status);
}
