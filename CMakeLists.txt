cmake_minimum_required(VERSION 2.8)
SET(CMAKE_C_FLAGS   "-g")

#Elasticity library
project(Blapp)
file(                  GLOB_RECURSE source_files src/*)
add_executable(        elastic      ${source_files})
target_link_libraries( elastic "-lm -lpthread")

#tests de la librairie d'élasticité
include(CTest)
enable_testing()
add_test(test_elastic elastic ${CMAKE_SOURCE_DIR}/demos/biel3d.mesh)

if(TRUE)

  project(Dependencies)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
  set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests")

  #Eigen3
  find_package(Eigen3 REQUIRED)
  if(${EIGEN3_FOUND})
    message("-- Found Eigen3: ${EIGEN3_INCLUDE_DIR}")
    include_directories(${EIGEN3_INCLUDE_DIR})
    add_executable(test_eigen_exe ${TEST_DIR}/eigen_example.cpp )
    add_test(test_eigen test_eigen_exe)
  endif()

  #Mumps
  find_package(MUMPS REQUIRED)
  if(${MUMPS_FOUND})
    find_package(MPI REQUIRED)
    include_directories(${MPI_INCLUDE_PATH})
    include_directories(${MUMPS_INCLUDE_DIR})
    add_executable(test_mumps_exe ${TEST_DIR}/mumps_example.c )
    target_link_libraries( test_mumps_exe ${MPI_C_LIBRARIES} ${MUMPS_LIBRARIES} "-lm")
    set(PROCS 4)
    add_test(test_mumps ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${PROCS} ${MPIEXEC_PREFLAGS} test_mumps_exe ${MPIEXEC_POSTFLAGS})
  endif()

  #Hypre
  find_package(Hypre REQUIRED)
  if(${HYPRE_FOUND})
    find_package(MPI REQUIRED)
    include_directories(${HYPRE_INCLUDE_DIR})
    add_executable(test_hypre_exe ${TEST_DIR}/hypre_example.c )
    target_link_libraries( test_hypre_exe ${MPI_C_LIBRARIES} ${HYPRE_LIBRARIES} "-lm")
    set(PROCS 4)
    add_test(test_hypre ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${PROCS} ${MPIEXEC_PREFLAGS} test_hypre_exe ${MPIEXEC_POSTFLAGS})
  endif()

  #MMGs (would work the same way for the different "colors" of mmg3d, mmg2d, mmg...)
  find_package(Mmgs REQUIRED)
  if(${MMGS_FOUND})
    find_package(Scotch REQUIRED)
    include_directories(${MMGS_INCLUDE_DIRS} ${SCOTCH_INCLUDE_DIRS})
    add_executable(test_mmgs_exe ${TEST_DIR}/mmgs_example.c )
    target_link_libraries( test_mmgs_exe ${MMGS_LIBRARIES} ${SCOTCH_LIBRARIES} "-lm")
    add_test(test_mmgs test_mmgs_exe ${CMAKE_SOURCE_DIR}/tests/cube.mesh ${CMAKE_SOURCE_DIR}/tests/output.mesh)
  endif()

  #LIS
  find_package(LIS)
  if(${LIS_FOUND})
    find_package(MPI REQUIRED)
    find_package(OpenMP REQUIRED)
    if(OPENMP_FOUND)
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif()
    include_directories(${MPI_INCLUDE_PATH})
    include_directories(${LIS_INCLUDE_DIR})
    add_executable(test_lis_exe ${TEST_DIR}/lis_example.c )
    target_link_libraries( test_lis_exe ${LIS_LIBRARIES} "-lm")
    target_link_libraries( test_lis_exe ${MPI_C_LIBRARIES})
    set(PROCS 4)
    add_test(test_lis ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${PROCS} ${MPIEXEC_PREFLAGS} test_lis_exe ${MPIEXEC_POSTFLAGS} 200 200 100)
  endif()

  #METIS
  find_package(Metis)
  if(${METIS_FOUND})
    include_directories(${METIS_INCLUDE_DIRS})
    add_executable(test_metis_exe ${TEST_DIR}/metis_example.c )
    target_link_libraries( test_metis_exe ${METIS_LIBRARIES})
    add_test(test_metis test_metis_exe)
  endif()

  #Lapack(e) , still have to fix the cblas trouble
  find_package(LAPACKE)
  if(${LAPACKE_FOUND})
    include_directories(${LAPACKE_INCLUDE_DIRS})
    add_executable(test_lapack_exe ${TEST_DIR}/lapack_example.c )
    target_link_libraries( test_lapack_exe ${LAPACKE_LIBRARIES})
    add_test(test_lapack test_lapack_exe)
  endif()
  find_package(Parmetis)
  find_package(MKL)

  find_package (PETSc)
  if(${PETSC_FOUND})
    include_directories(${PETSC_INCLUDES})
    add_definitions (${PETSC_DEFINITIONS})
    add_executable(test_petsc_exe ${TEST_DIR}/petsc_example.c )
    target_link_libraries(test_petsc_exe ${PETSC_LIBRARIES})
    add_test(test_petsc test_petsc_exe)
  endif()


endif()
