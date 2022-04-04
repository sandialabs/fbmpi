cmake_minimum_required(VERSION 3.15.0...3.21.0)

project(fbmpi VERSION 1.0.0 LANGUAGES C)

option(fbmpi_ENABLE_CUDA "Enable CUDA support" OFF)

set(FBMPI_SOURCES fbpmpi.c fbmpi.c)

if (fbmpi_ENABLE_CUDA)
  enable_language(CUDA)
  set_source_files_properties(${FBMPI_SOURCES} PROPERTIES LANGUAGE CUDA)
endif()

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
