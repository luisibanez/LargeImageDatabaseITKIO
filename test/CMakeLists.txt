#
#
#
set(KIT LargeImageDataBase)

create_test_sourcelist(Tests ${KIT}TestDriver.cxx
  itkDataBaseImageIOTest.cxx
  itkMongoDataBaseImageIOTest.cxx
  itkMongoDataBaseInterfaceTest.cxx
  itkMySQLDataBaseInterfaceTest.cxx
  itkSQLDataBaseInterfaceTest.cxx
  )

add_executable(${KIT}TestDriver ${KIT}TestDriver.cxx ${Tests})
target_link_libraries(${KIT}TestDriver DataBaseImageIO)


add_test(NAME itkMongoDataBaseInterfaceTest
      COMMAND ${KIT}TestDriver itkMongoDataBaseInterfaceTest)

add_test(NAME itkMongoDataBaseImageIOTest1
      COMMAND ${KIT}TestDriver itkMongoDataBaseImageIOTest1)
