#include "mpi.h"

int MPI_Sendrecv_replace(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int sendtag,
    int source,
    int recvtag,
    MPI_Comm comm,
    MPI_Status *status)
{
  return PMPI_Sendrecv_replace(
      buf,
      count,
      datatype,
      dest,
      sendtag,
      source,
      recvtag,
      comm,
      status);
}
