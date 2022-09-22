#include "mpi.h"

int MPI_File_read_at_all(
    MPI_File fh,
    MPI_Offset offset,
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Status* status)
{
  return PMPI_File_read_at_all(
      fh,
      offset,
      buf,
      count,
      datatype,
      status);
}
