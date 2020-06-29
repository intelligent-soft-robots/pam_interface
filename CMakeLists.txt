cmake_minimum_required(VERSION 2.8.7)

project(pam_interface)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(catkin REQUIRED COMPONENTS
  mpi_cmake_modules
  pybind11_catkin
  shared_memory
  json_helper
)

catkin_package(
 LIBRARIES pam_interface
 INCLUDE_DIRS include
 CATKIN_DEPENDS pybind11_catkin json_helper shared_memory mpi_cmake_modules
)

DEFINE_OS()

include_directories(include ${catkin_INCLUDE_DIRS})

# absolute path to the lvbitx file that configures connection between the control pc and
# the fpga.
get_filename_component(BITFILE_PATH bitfile ABSOLUTE)
set(PAM_BITFILE "${BITFILE_PATH}/pam_robot.lvbitx")

# absolute path to default json configuration file
get_filename_component(JSON_CONFIG_DIR config ABSOLUTE)
set(JSON_DEFAULT_CONFIG_FILE "${JSON_CONFIG_DIR}/pam.json")

# to be sure that linkage remains after install
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

###########
# Library #
###########

add_library(pam_interface
  src/NiFpga.c
  src/NiFpga_exception.cpp
  src/NiFpga_robot.cpp
  src/typedefs.cpp
  src/factories.cpp)
target_link_libraries(pam_interface dl ${catkin_LIBRARIES})
target_compile_definitions(pam_interface PRIVATE
  PAM_DEFAULT_CONFIG_FILE_PATH="${JSON_DEFAULT_CONFIG_FILE}"
  BITFILE_4DOFS_FILE_PATH="${PAM_BITFILE}")

########
# Demo #
########

add_executable(demo_dummy
  demos/demo_dummy.cpp)
target_link_libraries(demo_dummy pam_interface)
target_compile_definitions(demo_dummy PRIVATE
  PAM_DEFAULT_CONFIG_FILE_PATH="${JSON_DEFAULT_CONFIG_FILE}"
  BITFILE_4DOFS_FILE_PATH="${PAM_BITFILE}")

add_executable(demo_real
  demos/demo_real.cpp)
target_link_libraries(demo_real pam_interface)
target_compile_definitions(demo_real PRIVATE
  PAM_DEFAULT_CONFIG_FILE_PATH="${JSON_DEFAULT_CONFIG_FILE}"
  BITFILE_4DOFS_FILE_PATH="${PAM_BITFILE}")

###############
# Executables #
###############

# moving pam_check to bin folder
configure_file(${CMAKE_CURRENT_LIST_DIR}/bin/pam_check
               ${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_BIN_DESTINATION}/pam_check
               COPYONLY)

# moving pam_server to bin folder
configure_file(${CMAKE_CURRENT_LIST_DIR}/bin/pam_server
               ${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_BIN_DESTINATION}/pam_server
               COPYONLY)
	     
###################
# Python bindings #
###################

pybind11_add_module(pam_interface_py srcpy/wrappers.cpp)
target_link_libraries(pam_interface_py PRIVATE pam_interface ${catkin_LIBRARIES})
set_target_properties(pam_interface_py PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_PYTHON_DESTINATION}
  OUTPUT_NAME pam_interface)
target_compile_definitions(pam_interface_py PRIVATE
  PAM_DEFAULT_CONFIG_FILE_PATH="${JSON_DEFAULT_CONFIG_FILE}"
  BITFILE_4DOFS_FILE_PATH="${PAM_BITFILE}")
install(TARGETS pam_interface_py DESTINATION ${CATKIN_GLOBAL_PYTHON_DESTINATION})

##############
# Unit tests #
##############

catkin_add_gtest(pam_interface_unit_tests
  tests/main.cpp
  tests/unit_tests.cpp)
target_link_libraries(pam_interface_unit_tests pam_interface ${catkin_libraries})
target_compile_definitions(pam_interface_unit_tests PRIVATE
  PAM_DEFAULT_CONFIG_FILE_PATH="${JSON_DEFAULT_CONFIG_FILE}"
  BITFILE_4DOFS_FILE_PATH="${PAM_BITFILE}")

################
# CMake Export #
################

# so these can be used by dependend catkin packages
# (e.g. O8O_pam)

set(PAM_BITFILE "${BITFILE_PATH}/pam_robot.lvbitx" PARENT_SCOPE)
set(JSON_DEFAULT_CONFIG_FILE "${JSON_CONFIG_DIR}/pam.json" PARENT_SCOPE)
