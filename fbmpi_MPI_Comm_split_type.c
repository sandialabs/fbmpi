#include "mpi.h"

int MPI_Comm_split_type(
    MPI_Comm comm,
    int split_type,
    int key,
    MPI_Info info,
    MPI_Comm *newcomm)
{
  return PMPI_Comm_split_type(comm, split_type, key, info, newcomm);
}
