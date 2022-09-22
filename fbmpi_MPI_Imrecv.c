#include "mpi.h"

int MPI_Imrecv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    MPI_Message* message,
    MPI_Request* request)
{
  return PMPI_Imrecv(
      buf,
      count,
      datatype,
      message,
      request);
}
