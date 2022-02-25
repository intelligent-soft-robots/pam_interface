cmake_minimum_required(VERSION 3.10.2)
project(pam_interface)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)


################
# Dependencies #
################

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(mpi_cmake_modules REQUIRED)
find_package(pybind11 REQUIRED)
find_package(shared_memory REQUIRED)
find_package(json_helper REQUIRED)
ament_export_dependencies(
  mpi_cmake_modules
  pybind11
  shared_memory
  json_helper)

# prepare to export all needed targets
set(all_targets)
set(all_target_exports)


#######################
# Configuration files #
#######################

# configuration files are copied to /opt/mpi-is/
# (for running on current machine)
# and install/pam_interface/opt/mpi-is/
# (for being included in any debian created from the
# install folder)

#
# PAMY 1
#
get_filename_component(BITFILE_PATH pamy1/bitfile ABSOLUTE)
get_filename_component(PAMY1_JSON_CONFIG_DIR pamy1/config ABSOLUTE)
get_filename_component(PAMY2_JSON_CONFIG_DIR pamy2/config ABSOLUTE)
# installing files in /opt/mpi-is/ if exists
if (EXISTS "/opt/mpi-is")
  install(FILES
    "${BITFILE_PATH}/pam_robot.lvbitx"
    "${PAMY1_JSON_CONFIG_DIR}/pam.json"
    "${PAMY1_JSON_CONFIG_DIR}/pam_sim.json"
    DESTINATION /opt/mpi-is/pam_interface/pamy1)
  install(FILES
    "${PAMY2_JSON_CONFIG_DIR}/pam.json"
    DESTINATION /opt/mpi-is/pam_interface/pamy2)
  set(PAMY1_JSON_DEFAULT_CONFIG_FILE "/opt/mpi-is/pam_interface/pamy1/pam.json")
  set(PAMY2_JSON_DEFAULT_CONFIG_FILE "/opt/mpi-is/pam_interface/pamy2/pam.json")
  set(PAM_BITFILE "/opt/mpi-is/pam_interface/pamy1/pam_robot.lvbitx")
else()
  set(PAMY1_JSON_DEFAULT_CONFIG_FILE "${CMAKE_INSTALL_PREFIX}/opt/mpi-is/pam_interface/pamy1/pam.json")
  set(PAMY2_JSON_DEFAULT_CONFIG_FILE "${CMAKE_INSTALL_PREFIX}/opt/mpi-is/pam_interface/pamy2/pam.json")
  set(PAM_BITFILE "${CMAKE_INSTALL_PREFIX}/opt/mpi-is/pam_interface/pamy1/pam_robot.lvbitx")
endif()
# also installing in the workspace/install folder  
install(FILES
  "${BITFILE_PATH}/pam_robot.lvbitx"
  "${PAMY1_JSON_CONFIG_DIR}/pam.json"
  DESTINATION ${CMAKE_INSTALL_PREFIX}/opt/mpi-is/pam_interface/pamy1)
install(FILES
  "${PAMY2_JSON_CONFIG_DIR}/pam.json"
  DESTINATION ${CMAKE_INSTALL_PREFIX}/opt/mpi-is/pam_interface/pamy2)




###########
# Library #
###########


add_library( ${PROJECT_NAME} SHARED
  src/NiFpga.c
  src/NiFpga_exception.cpp
  src/NiFpga_robot.cpp
  src/typedefs.cpp
  src/factories.cpp
  src/interface.cpp
  src/udp_communication.cpp
  src/pamy2_interface.cpp
  src/pamy2_driver.cpp
  src/pamy2_configuration.cpp
  src/robot.cpp
  src/sign.cpp
  src/rotation.cpp)
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(${PROJECT_NAME}
  shared_memory
  json_helper)
target_link_libraries(${PROJECT_NAME} shared_memory::shared_memory)
target_link_libraries(${PROJECT_NAME} json_helper::json_helper)
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
ament_export_interfaces(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
target_compile_definitions(pam_interface PRIVATE
  PAMY1_DEFAULT_CONFIG_FILE_PATH="${PAMY1_JSON_DEFAULT_CONFIG_FILE}"
  PAMY2_DEFAULT_CONFIG_FILE_PATH="${PAMY2_JSON_DEFAULT_CONFIG_FILE}"
  BITFILE_4DOFS_FILE_PATH="${PAM_BITFILE}")

list(APPEND all_targets ${PROJECT_NAME})
list(APPEND all_target_exports export_${PROJECT_NAME})


#########
# Demos #
#########

add_executable(pam_interface_demo_dummy
  demos/demo_dummy.cpp)
target_link_libraries(pam_interface_demo_dummy pam_interface)
target_compile_definitions(pam_interface_demo_dummy PRIVATE
  PAMY1_DEFAULT_CONFIG_FILE_PATH="${PAMY1_JSON_DEFAULT_CONFIG_FILE}"
  PAMY2_DEFAULT_CONFIG_FILE_PATH="${PAMY2_JSON_DEFAULT_CONFIG_FILE}"
  BITFILE_4DOFS_FILE_PATH="${PAM_BITFILE}")
list(APPEND all_targets pam_interface_demo_dummy)

add_executable(pam_interface_demo_real
  demos/demo_real.cpp)
target_link_libraries(pam_interface_demo_real pam_interface)
target_compile_definitions(pam_interface_demo_real PRIVATE
  PAMY1_DEFAULT_CONFIG_FILE_PATH="${PAMY1_JSON_DEFAULT_CONFIG_FILE}"
  PAMY2_DEFAULT_CONFIG_FILE_PATH="${PAMY2_JSON_DEFAULT_CONFIG_FILE}"
  BITFILE_4DOFS_FILE_PATH="${PAM_BITFILE}")
list(APPEND all_targets pam_interface_demo_real)

add_executable(pam_interface_demo_serialize_robot_state
  demos/serialize_robot_state.cpp)
target_link_libraries(pam_interface_demo_serialize_robot_state pam_interface)
target_compile_definitions(pam_interface_demo_serialize_robot_state PRIVATE
  PAMY1_DEFAULT_CONFIG_FILE_PATH="${PAMY1_JSON_DEFAULT_CONFIG_FILE}"
  PAMY2_DEFAULT_CONFIG_FILE_PATH="${PAMY2_JSON_DEFAULT_CONFIG_FILE}"
  BITFILE_4DOFS_FILE_PATH="${PAM_BITFILE}")
list(APPEND all_targets pam_interface_demo_serialize_robot_state)

add_executable(pam_interface_demo_pamy2_udp_communication
  demos/pamy2_udp_communication.cpp)
target_link_libraries(pam_interface_demo_pamy2_udp_communication pam_interface)
target_compile_definitions(pam_interface_demo_pamy2_udp_communication PRIVATE
  PAMY1_DEFAULT_CONFIG_FILE_PATH="${PAMY1_JSON_DEFAULT_CONFIG_FILE}"
  PAMY2_DEFAULT_CONFIG_FILE_PATH="${PAMY2_JSON_DEFAULT_CONFIG_FILE}")
list(APPEND all_targets pam_interface_demo_pamy2_udp_communication)


###############
# Executables #
###############

# moving pam_check to bin folder
configure_file(${CMAKE_CURRENT_LIST_DIR}/bin/pam_check
               ${CMAKE_INSTALL_PREFIX}/bin/pam_check
               COPYONLY)

# moving pam_server to bin folder
configure_file(${CMAKE_CURRENT_LIST_DIR}/bin/pamy1_server
               ${CMAKE_INSTALL_PREFIX}/bin/pamy1_server
               COPYONLY)

# moving pam_reset to bin folder
configure_file(${CMAKE_CURRENT_LIST_DIR}/bin/pamy1_reset
               ${CMAKE_INSTALL_PREFIX}/bin/pamy1_reset
               COPYONLY)
	     
###################
# Python wrappers #
###################

add_library(${PROJECT_NAME}_py MODULE srcpy/wrappers.cpp)
target_link_libraries(${PROJECT_NAME}_py PRIVATE pybind11::module)
target_link_libraries(${PROJECT_NAME}_py PRIVATE ${PYTHON_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_py PRIVATE ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}_py
  PROPERTIES PREFIX "" SUFFIX "${PYTHON_MODULE_EXTENSION}"
  OUTPUT_NAME ${PROJECT_NAME})
target_include_directories(
  ${PROJECT_NAME}_py
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include> SYSTEM
	 PUBLIC ${PYTHON_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME}_py PRIVATE
  PAMY1_DEFAULT_CONFIG_FILE_PATH="${PAMY1_JSON_DEFAULT_CONFIG_FILE}"
  PAMY2_DEFAULT_CONFIG_FILE_PATH="${PAMY2_JSON_DEFAULT_CONFIG_FILE}"
  BITFILE_4DOFS_FILE_PATH="${PAM_BITFILE}")
_ament_cmake_python_get_python_install_dir()
install(TARGETS ${PROJECT_NAME}_py DESTINATION ${PYTHON_INSTALL_DIR})


######################
# Install and export #
######################

install(DIRECTORY include/ DESTINATION include)
install(
  TARGETS ${all_targets}
  EXPORT ${all_target_exports}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include)
ament_package()


##############
# Unit tests #
##############

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_${PROJECT_NAME}_cpp tests/main.cpp tests/unit_tests.cpp)
  target_link_libraries(test_${PROJECT_NAME}_cpp ${PROJECT_NAME})
  target_compile_definitions(test_${PROJECT_NAME}_cpp PRIVATE
  PAMY1_DEFAULT_CONFIG_FILE_PATH="${PAMY1_JSON_DEFAULT_CONFIG_FILE}"
  PAMY2_DEFAULT_CONFIG_FILE_PATH="${PAMY2_JSON_DEFAULT_CONFIG_FILE}"
  BITFILE_4DOFS_FILE_PATH="${PAM_BITFILE}")
endif()

