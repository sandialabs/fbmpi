#include "mpi.h"

int MPI_File_set_view(
    MPI_File fh,
    MPI_Offset disp,
    MPI_Datatype etype,
    MPI_Datatype filetype,
    const char* datarep,
    MPI_Info info)
{
  return PMPI_File_set_view(
      fh,
      disp,
      etype,
      filetype,
      datarep,
      info);
}
