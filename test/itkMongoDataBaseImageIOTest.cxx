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
#include "itkMongoDataBaseImageIO.h"
#include "itkTestingMacros.h"


int itkMongoDataBaseImageIOTest( int argc, const char * argv [] )
{

  if( argc < 2 )
    {
    std::cerr << "Missing parameters" << std::endl;
    return EXIT_FAILURE;
    }

  typedef itk::MongoDataBaseImageIO   ImageIOType;

  ImageIOType::Pointer imageIO = ImageIOType::New();

  TEST_SET_GET_VALUE( false, imageIO->CanReadFile("non-exiting-file") );

  TEST_SET_GET_VALUE( true, imageIO->CanReadFile( argv[1] ) );

  imageIO->ReadImageInformation();

  // FIXME, check here for right origin, spacing, orientation and size.

  itk::ImageIORegion region;

  // Request region from (0,0) to (100,100)
//  region.push_back(0);
//  region.push_back(100);
//  region.push_back(0);
//  region.push_back(100);

//  imageIO->ReadImageInformation( region );

//  TEST_SET_GET_VALUE( 1, imageIO->GetNumberOfResolutionLevels() );

  typedef std::vector<double> SpacingIOType;
  typedef std::vector<double> OriginIOType;

  SpacingIOType   spacing;
  OriginIOType    origin;


//  imageIO->SetResolutionLevel(0);

  spacing.push_back(  imageIO->GetSpacing(0) );
  spacing.push_back(  imageIO->GetSpacing(1) );

  origin.push_back(  imageIO->GetOrigin(0) );
  origin.push_back(  imageIO->GetOrigin(1) );

  TEST_SET_GET_VALUE( 1.5, spacing[0] );
  TEST_SET_GET_VALUE( 1.5, spacing[1] );

//  typedef ImageIOType::PointType     PointType;
//  typedef ImageIOType::VectorType    VectorType;

//  PointType corner1;
//  PointType corner2;

//  ImageIORegion requestedRegion;

//  imageIO->SetRequestedPhysicalRegion( corner1, corner2 );

//  requestedRegion = imageIO->GetRequestedRegion();

//  // FIXME add here comparison with correct values

//  VectorType diagonal;

//  imageIO->SetRequestedPhysicalRegion( corner1, diagonal );

//  requestedRegion = imageIO->GetRequestedRegion();

//  // FIXME add here comparison with correct values

  return EXIT_SUCCESS;
}
