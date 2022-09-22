#include "mpi.h"

int MPI_Init_thread(
    int* argc,
    char*** argv,
    int required,
    int* provided)
{
  return PMPI_Init_thread(argc, argv, required, provided);
}
