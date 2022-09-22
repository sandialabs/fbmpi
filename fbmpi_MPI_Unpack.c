#include "mpi.h"

int MPI_Unpack(
    const void *inbuf,
    int insize,
    int *position,
    void *outbuf,
    int outcount,
    MPI_Datatype datatype,
    MPI_Comm comm)
{
  return PMPI_Unpack(
      inbuf,
      insize,
      position,
      outbuf,
      outcount,
      datatype,
      comm);
}
