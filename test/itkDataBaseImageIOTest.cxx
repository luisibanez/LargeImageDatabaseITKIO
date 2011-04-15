/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include <iostream>
#include "itkDataBaseImageIO.h"

namespace itk {
namespace DataBaseImageIOTest {

class FakeDataBaseImageIO : public DataBaseImageIO
{
public:
  /** Standard class typedefs. */
  typedef FakeDataBaseImageIO     Self;
  typedef ImageIOBase             Superclass;
  typedef SmartPointer<Self>      Pointer;

  /** Define the New method */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(FakeDataBaseImageIO, DataBaseImageIO);

protected:
  FakeDataBaseImageIO();
  ~FakeDataBaseImageIO();
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  FakeDataBaseImageIO(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
};

}
}

int itkDataBaseImageIOTest( int argc, const char * argv [] )
{

  if( argc < 2 )
    {
    std::cerr << "Missing parameters" << std::endl;
    return EXIT_FAILURE;
    }

  typedef itk::DataBaseImageIOTest::FakeDataBaseImageIO  ImageIOType;

  ImageIOType::Pointer imageIO = ImageIOType::New();

  TEST_SET_GET_VALUE( false, imageIO->CanReadFile("non-exiting-file") );

  TEST_SET_GET_VALUE( true, imageIO->CanReadFile( argv[1] ) );

  imageIO->ReadImageInformation();

  // FIXME, check here for right origin, spacing, orientation and size.

  itk::ImageIORegion region;

  // Request region from (0,0) to (100,100)
  region.push_back(0);
  region.push_back(100);
  region.push_back(0);
  region.push_back(100);

  imageIO->ReadImageInformation( region );

  TEST_SET_GET_VALUE( 1, imageIO->GetNumberOfResolutionLevels() );

  imageIO->SetResolutionLevel(0);

  typedef itk::DataBaseImageIOTest::PointType     PointType;
  typedef itk::DataBaseImageIOTest::VectorType    VectorType;

  PointType corner1;
  PointType corner2;

  ImageIORegion requestedRegion;

  imageIO->SetRequestedPhysicalRegion( corner1, corner2 );

  requestedRegion = imageIO->GetRequestedRegion();

  // FIXME add here comparison with correct values

  VectorType diagonal;

  imageIO->SetRequestedPhysicalRegion( corner1, diagonal );

  requestedRegion = imageIO->GetRequestedRegion();

  // FIXME add here comparison with correct values

  return EXIT_SUCCESS;
}
