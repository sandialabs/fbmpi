#include "mpi.h"

int MPI_Sendrecv(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    int dest,
    int sendtag,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int source,
    int recvtag,
    MPI_Comm comm,
    MPI_Status* status)
{
  return PMPI_Sendrecv(
      sendbuf,
      sendcount,
      sendtype,
      dest,
      sendtag,
      recvbuf,
      recvcount,
      recvtype,
      source,
      recvtag,
      comm,
      status);
}
