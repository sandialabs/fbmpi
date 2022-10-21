cmake_minimum_required(VERSION 3.15.0...3.21.0)

project(fbmpi VERSION 1.0.0 LANGUAGES C)

set(FBMPI_SOURCES
fbmpi_MPI_Abort.c
fbmpi_MPI_Aint_diff.c
fbmpi_MPI_Allgather.c
fbmpi_MPI_Allgatherv.c
fbmpi_MPI_Allreduce.c
fbmpi_MPI_Alltoall.c
fbmpi_MPI_Alltoallv.c
fbmpi_MPI_Barrier.c
fbmpi_MPI_Bcast.c
fbmpi_MPI_Bsend.c
fbmpi_MPI_Bsend_init.c
fbmpi_MPI_Cancel.c
fbmpi_MPI_Cart_coords.c
fbmpi_MPI_Cart_create.c
fbmpi_MPI_Cart_get.c
fbmpi_MPI_Cart_rank.c
fbmpi_MPI_Cartdim_get.c
fbmpi_MPI_Comm_c2f.c
fbmpi_MPI_Comm_compare.c
fbmpi_MPI_Comm_create.c
fbmpi_MPI_Comm_create_errhandler.c
fbmpi_MPI_Comm_create_keyval.c
fbmpi_MPI_Comm_delete_attr.c
fbmpi_MPI_Comm_dup.c
fbmpi_MPI_Comm_f2c.c
fbmpi_MPI_Comm_free.c
fbmpi_MPI_Comm_free_keyval.c
fbmpi_MPI_Comm_group.c
fbmpi_MPI_Comm_rank.c
fbmpi_MPI_Comm_set_attr.c
fbmpi_MPI_Comm_set_errhandler.c
fbmpi_MPI_Comm_size.c
fbmpi_MPI_Comm_split.c
fbmpi_MPI_Comm_split_type.c
fbmpi_MPI_Comm_test_inter.c
fbmpi_MPI_Dist_graph_create_adjacent.c
fbmpi_MPI_Error_class.c
fbmpi_MPI_Error_string.c
fbmpi_MPI_Exscan.c
fbmpi_MPI_File_close.c
fbmpi_MPI_File_delete.c
fbmpi_MPI_File_get_atomicity.c
fbmpi_MPI_File_get_info.c
fbmpi_MPI_File_get_size.c
fbmpi_MPI_File_open.c
fbmpi_MPI_File_read_at.c
fbmpi_MPI_File_read_at_all.c
fbmpi_MPI_File_set_atomicity.c
fbmpi_MPI_File_set_size.c
fbmpi_MPI_File_set_view.c
fbmpi_MPI_File_sync.c
fbmpi_MPI_File_write_at.c
fbmpi_MPI_File_write_at_all.c
fbmpi_MPI_Finalize.c
fbmpi_MPI_Finalized.c
fbmpi_MPI_Gather.c
fbmpi_MPI_Gatherv.c
fbmpi_MPI_Get_address.c
fbmpi_MPI_Get_count.c
fbmpi_MPI_Get_elements_x.c
fbmpi_MPI_Get_library_version.c
fbmpi_MPI_Get_processor_name.c
fbmpi_MPI_Get_version.c
fbmpi_MPI_Group_excl.c
fbmpi_MPI_Group_free.c
fbmpi_MPI_Group_incl.c
fbmpi_MPI_Group_rank.c
fbmpi_MPI_Group_translate_ranks.c
fbmpi_MPI_Iallgather.c
fbmpi_MPI_Iallreduce.c
fbmpi_MPI_Ibarrier.c
fbmpi_MPI_Ibsend.c
fbmpi_MPI_Imrecv.c
fbmpi_MPI_Info_create.c
fbmpi_MPI_Info_dup.c
fbmpi_MPI_Info_f2c.c
fbmpi_MPI_Info_free.c
fbmpi_MPI_Info_get.c
fbmpi_MPI_Info_get_nkeys.c
fbmpi_MPI_Info_get_nthkey.c
fbmpi_MPI_Info_get_valuelen.c
fbmpi_MPI_Info_set.c
fbmpi_MPI_Init.c
fbmpi_MPI_Init_thread.c
fbmpi_MPI_Initialized.c
fbmpi_MPI_Iprobe.c
fbmpi_MPI_Irecv.c
fbmpi_MPI_Irsend.c
fbmpi_MPI_Isend.c
fbmpi_MPI_Issend.c
fbmpi_MPI_Mprobe.c
fbmpi_MPI_Neighbor_alltoall.c
fbmpi_MPI_Neighbor_alltoallv.c
fbmpi_MPI_Op_create.c
fbmpi_MPI_Op_free.c
fbmpi_MPI_Pack.c
fbmpi_MPI_Pack_size.c
fbmpi_MPI_Pcontrol.c
fbmpi_MPI_Probe.c
fbmpi_MPI_Recv.c
fbmpi_MPI_Recv_init.c
fbmpi_MPI_Reduce.c
fbmpi_MPI_Reduce_scatter.c
fbmpi_MPI_Request_free.c
fbmpi_MPI_Rsend.c
fbmpi_MPI_Rsend_init.c
fbmpi_MPI_Scan.c
fbmpi_MPI_Scatter.c
fbmpi_MPI_Scatterv.c
fbmpi_MPI_Send.c
fbmpi_MPI_Send_init.c
fbmpi_MPI_Sendrecv.c
fbmpi_MPI_Sendrecv_replace.c
fbmpi_MPI_Ssend.c
fbmpi_MPI_Ssend_init.c
fbmpi_MPI_Start.c
fbmpi_MPI_Startall.c
fbmpi_MPI_Test.c
fbmpi_MPI_Test_cancelled.c
fbmpi_MPI_Testall.c
fbmpi_MPI_Testany.c
fbmpi_MPI_Testsome.c
fbmpi_MPI_Type_commit.c
fbmpi_MPI_Type_contiguous.c
fbmpi_MPI_Type_create_hindexed.c
fbmpi_MPI_Type_create_hindexed_block.c
fbmpi_MPI_Type_create_hvector.c
fbmpi_MPI_Type_create_resized.c
fbmpi_MPI_Type_create_struct.c
fbmpi_MPI_Type_dup.c
fbmpi_MPI_Type_free.c
fbmpi_MPI_Type_get_extent.c
fbmpi_MPI_Type_get_extent_x.c
fbmpi_MPI_Type_size.c
fbmpi_MPI_Type_size_x.c
fbmpi_MPI_Type_vector.c
fbmpi_MPI_Unpack.c
fbmpi_MPI_Wait.c
fbmpi_MPI_Waitall.c
fbmpi_MPI_Waitany.c
fbmpi_MPI_Waitsome.c
fbmpi_MPI_Wtick.c
fbmpi_MPI_Wtime.c
fbpmpi.c
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(fbmpi ${FBMPI_SOURCES})
target_compile_features(fbmpi PRIVATE c_std_99)
set_target_properties(fbmpi
  PROPERTIES
  PUBLIC_HEADER mpi.h)
target_include_directories(fbmpi
  PUBLIC
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
install(TARGETS fbmpi
  EXPORT fbmpi-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

configure_file(mpicc.c.mac.static.in "${CMAKE_CURRENT_BINARY_DIR}/mpicc.c" @ONLY)
add_executable(mpicc "${CMAKE_CURRENT_BINARY_DIR}/mpicc.c")
target_link_libraries(mpicc PRIVATE fbmpi)
install(TARGETS mpicc
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/fbmpi-config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fbmpi)
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/fbmpi-config.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fbmpi)
install(
  EXPORT fbmpi-targets
  NAMESPACE fbmpi::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fbmpi)
