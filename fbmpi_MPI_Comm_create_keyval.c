#include "mpi.h"

int MPI_Comm_create_keyval(
    MPI_Comm_copy_attr_function* comm_copy_attr_fn,
    MPI_Comm_delete_attr_function* comm_delete_attr_fn,
    int* type_keyval,
    void* extra_state)
{
  return PMPI_Comm_create_keyval(
      comm_copy_attr_fn,
      comm_delete_attr_fn,
      type_keyval,
      extra_state);
}
