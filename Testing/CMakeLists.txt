#
#
#
set(KIT LargeImageDataBase)

create_test_sourcelist(Tests ${KIT}TestDriver.cxx
  itkDiscreteGaussianImageFilterTest2.cxx
  itkSmoothingRecursiveGaussianImageFilterTest.cxx
  itkMeanImageFilterTest.cxx
  itkDiscreteGaussianImageFilterTest.cxx
  itkMedianImageFilterTest.cxx
  itkSmoothingHeaderTest.cxx
  )

add_executable(${KIT}TestDriver ${KIT}TestDriver.cxx ${Tests})
target_link_libraries(${KIT}TestDriver DataBaseImageIO)


add_test(NAME itkMongoDataBaseInterfaceTest
      COMMAND ${KIT}TestDriver itkMongoDataBaseInterfaceTest)

add_test(NAME itkMongoDataBaseImageIOTest1
      COMMAND ${KIT}TestDriver itkMongoDataBaseImageIOTest1)
