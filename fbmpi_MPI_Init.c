#include "mpi.h"

int MPI_Init(int* argc, char*** argv)
{
  return PMPI_Init(argc, argv);
}
