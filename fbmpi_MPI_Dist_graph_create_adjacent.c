#include "mpi.h"

int MPI_Dist_graph_create_adjacent(
    MPI_Comm comm_old,
    int indegree,
    const int sources[],
    const int sourceweights[],
    int outdegree,
    const int destinations[],
    const int destweights[],
    MPI_Info info,
    int reorder,
    MPI_Comm *comm_dist_graph)
{
  return PMPI_Dist_graph_create_adjacent(
      comm_old,
      indegree,
      sources,
      sourceweights,
      outdegree,
      destinations,
      destweights,
      info,
      reorder,
      comm_dist_graph);
}
