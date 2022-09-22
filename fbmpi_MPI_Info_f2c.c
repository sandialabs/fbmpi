#include "mpi.h"

MPI_Info MPI_Info_f2c(MPI_Fint info)
{
  return PMPI_Info_f2c(info);
}
