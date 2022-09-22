#include "mpi.h"

int MPI_Pack(
    const void* inbuf,
    int incount,
    MPI_Datatype datatype,
    void* outbuf,
    int outsize,
    int* position,
    MPI_Comm comm)
{
  return PMPI_Pack(
      inbuf,
      incount,
      datatype,
      outbuf,
      outsize,
      position,
      comm);
}
