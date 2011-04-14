cmake_minimum_required( VERSION 2.8 )

project( LargeImageDatabaseITKIO )

find_package(ITK REQUIRED)

set( CMAKE_MODULE_PATH
  "${LargeImageDatabaseITKIO_SOURCE_DIR}/CMake"
  ${CMAKE_MODULE_PATH}
)

find_package(MongoDB REQUIRED)

include_directories( BEFORE
  ${LargeImageDatabaseITKIO_SOURCE_DIR}/include
)

add_subdirectory( src )
add_subdirectory( test )
# add_subdirectory( Documents )
