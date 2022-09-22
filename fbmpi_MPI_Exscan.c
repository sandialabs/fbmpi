#include "mpi.h"

int MPI_Exscan(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm)
{
  return PMPI_Exscan(
      sendbuf,
      recvbuf,
      count,
      datatype,
      op,
      comm);
}
