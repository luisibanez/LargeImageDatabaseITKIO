#
#
#
add_library(DataBaseImageIO
  itkDataBaseImageIO.cxx
  itkMongoDataBaseImageIO.cxx
  itkMongoDataBaseImageIOFactory.cxx
  itkMongoDataBaseInterface.cxx
  itkSQLDataBaseInterface.cxx
  itkMySQLDataBaseInterface.cxx
  )

set( THIRD_PART_LIBRARIES
  # FIXME See what to do with Boost dependencies
  # Maybe add them to the FindMongoDB.cmake file...
  ${MongoDB_LIBRARIES}
  ${MYSQL_LIBRARIES}
)

if( WIN32 )
  set( THIRD_PART_LIBRARIES
    ${THIRD_PART_LIBRARIES}
    ${MYSQL_EXTRA_LIBRARIES}
  )
endif()

target_link_libraries( DataBaseImageIO
  ${ITK_LIBRARIES}
  ${THIRD_PART_LIBRARIES}
  )
