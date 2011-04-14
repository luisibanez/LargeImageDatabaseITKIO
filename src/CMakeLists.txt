#
#
#
add_library(DataBaseImageIO
  itkDataBaseImageIO.cxx
  itkMongoDataBaseImageIO.cxx
  itkMongoDataBaseImageIOFactory.cxx
  itkMongoDataBaseInterface.cxx
  )

target_link_libraries( DataBaseImageIO
  ${ITK_LIBRARIES}
  ${MongoDB_LIBRARIES}
  # FIXME See what to do with Boost dependencies
  # Maybe add them to the FindMongoDB.cmake file...
  )
