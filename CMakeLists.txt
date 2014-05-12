CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(microblx_cartesiangen)

set(CMAKE_CXX_FLAGS "-Wall -Werror -fvisibility=hidden")
set( CMAKE_CXX_COMPILER clang++ )
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake") ## temporary resources, for UBX

# Global
set(INSTALL_LIB_TYPES_DIR lib/ubx/types CACHE PATH "Installation directory for types libraries")
set(INSTALL_LIB_BLOCKS_DIR lib/ubx/blocks CACHE PATH "Installation directory for blocks libraries")
set(INSTALL_INCLUDE_DIR include/ubx CACHE PATH "Installation directory for header files (types)")
set(INSTALL_CMAKE_DIR  share/ubx/cmake CACHE PATH  "Installation directory for CMake files") # default ${DEF_INSTALL_CMAKE_DIR}

# Local
SET(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib/ CACHE PATH "Configure the library output path.")
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/ CACHE PATH "Configure the executable output path.")


find_package(PkgConfig)
find_package(kdl-types REQUIRED)
pkg_check_modules(KDL orocos-kdl)

set (UBX_ROOT $ENV{UBX_ROOT} )
if (NOT UBX_ROOT)
 message( FATAL_ERROR "UBX_ROOT is not defined. CMake install willl abort." )
endif()

find_package(Ubx REQUIRED)


##
# Add uninstall target.
##
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
    
add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
)

link_directories(
    ${KDL_LIBRARY_DIRS}
)
include_directories(
    ${UBX_INCLUDE_DIR}
    ${KDL_INCLUDE_DIRS}
    ${KDL_TYPES_INCLUDE_DIRS}
)

 
add_library(cart_trajgen SHARED cart_trajgen.cpp)
set_target_properties(cart_trajgen PROPERTIES PREFIX "") 
target_link_libraries(cart_trajgen ${UBX_LIBRARIES} ${KDL_LIBRARIES})

install(TARGETS cart_trajgen DESTINATION ${INSTALL_LIB_BLOCKS_DIR} EXPORT cartesiangen-block)
set_property(TARGET cart_trajgen PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
install(EXPORT cartesiangen-block DESTINATION ${INSTALL_CMAKE_DIR})
