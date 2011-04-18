cmake_minimum_required( VERSION 2.8 )

project( LargeImageDatabaseITKIO )

find_package(ITK REQUIRED)

if( ITK_FOUND )
  include( ${ITK_USE_FILE} )
endif()

set( CMAKE_MODULE_PATH
  "${LargeImageDatabaseITKIO_SOURCE_DIR}/CMake"
  ${CMAKE_MODULE_PATH}
)

find_package(MongoDB REQUIRED)

find_package( MySQL REQUIRED )

include_directories( BEFORE
  ${LargeImageDatabaseITKIO_SOURCE_DIR}/include
  ${MongoDB_INCLUDE_DIR}
  ${MYSQL_INCLUDE_DIR}
)

add_subdirectory( src )
add_subdirectory( test )


option(BUILD_REPORTS "Build Reproducible Reports." OFF)

if( BUILD_REPORTS )
  add_subdirectory( documents )
endif()
