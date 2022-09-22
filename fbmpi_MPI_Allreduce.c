#include "mpi.h"

int MPI_Allreduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm)
{
  return PMPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
}
