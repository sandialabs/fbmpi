FBMPI
=====

FallBack MPI (FBMPI) is a partial implementation of the MPI standard that only supports a single rank.
The purpose of FBMPI is to act as a fallback MPI implementation in situations where
a full-fledged MPI implementation is not desired.
One important situation like this is on Windows, where OpenMPI has dropped support and
the alternative (before FBMPI) was to compile Microsoft MPI, which is costly.

By ensuring that there can always be an MPI implementation, FBMPI alleviates the need
for downstream libraries and applications to have "no MPI" build options and associated
preprocessor logic in their own code, including many custom implementations
of single-rank communication functionality.

FBMPI is written in standard C and compiles with modern CMake, ensuring portability across systems.

Downstream packages should use CMake to find their MPI implementation like this:

```cmake
find_package(MPI)
```

To use FBMPI with downstream packages, those packages can be configured using the following
CMake variable definitions:

```
-DMPI_HOME=$INTALL_LOCATION"
-DMPI_C_LIB_NAMES=mpi
-DMPI_CXX_LIB_NAMES=mpi
-DMPI_mpi_LIBRARY=$INSTALL_LOCATION/lib/libfbmpi.a
-DMPI_C_HEADER_DIR=$INSTALL_LOCATION/include
-DMPI_CXX_HEADER_DIR=$INSTALL_LOCATION/include
```

Where `$INSTALL_LOCATION` is the directory where FBMPI was installed.

FBMPI defines the majority of MPI functions used in popular software
such as [HDF5](https://www.hdfgroup.org/solutions/hdf5/), although many functions are not implemented yet.
Sufficient functionality exists to run many applications successfully
including point-to-point communication and reductions.

FBMPI supports the `PMPI` profiling interface and works with profiling
tools such as [Caliper](https://software.llnl.gov/Caliper/).

FBMPI also supports CUDA-aware MPI through its CMake option:

```
-Dfbmpi_ENABLE_CUDA=ON
```

At Sandia, FBMPI is SCR# 2756
