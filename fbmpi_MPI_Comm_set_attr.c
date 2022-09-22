#include "mpi.h"

int MPI_Comm_set_attr(
    MPI_Comm comm,
    int comm_keyval,
    void* attribute_val)
{
  return PMPI_Comm_set_attr(comm, comm_keyval, attribute_val);
}
