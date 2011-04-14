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

#ifdef _MSC_VER
#pragma warning ( disable : 4786 )
#endif

#include "itkMacro.h"
#include "itkIOCommon.h"
#include "itkDataBaseImageIO.h"
#include "itksys/SystemTools.hxx"

namespace itk
{

DataBaseImageIO::DataBaseImageIO()
{
}

DataBaseImageIO::~DataBaseImageIO()
{
}

void DataBaseImageIO::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}

bool DataBaseImageIO::CanReadFile( const char* filename )
{
  // FIXME Implement
  return true;
}


void DataBaseImageIO::ReadImageInformation()
{
  // FIXME: Talk to the database, figure out what kind of image is this, and
  // then populate the information below.

  this->SetPixelType( SCALAR );
  this->SetComponentType( UCHAR );

  this->SetDimensions( 0, nx );
  this->SetDimensions( 1, ny );
  this->SetDimensions( 2, nz );

  this->SetSpacing( 0, dx );
  this->SetSpacing( 1, dy );
  this->SetSpacing( 2, dz );
}


void DataBaseImageIO::Read( void * buffer)
{
  // Get region from the streaming layer:
  //
  const unsigned int nx = this->GetDimensions( 0 );
  const unsigned int ny = this->GetDimensions( 1 );
  const unsigned int nz = this->GetDimensions( 2 );

  ImageIORegion regionToRead = this->GetIORegion();

  ImageIORegion::SizeType  size  = regionToRead.GetSize();
  ImageIORegion::IndexType start = regionToRead.GetIndex();

  const unsigned int mx = size[0];
  const unsigned int my = size[1];
  const unsigned int mz = size[2];

  const unsigned int sx = start[0];
  const unsigned int sy = start[1];
  const unsigned int sz = start[2];

  // FIXME: Talk to the database and get this region of extent "size", and
  // begining from the "start" index.

  // Put the data in this pointer below.
  // The memory for it, is already allocated.
  char * inptr = static_cast< char * >( buffer );
}


bool DataBaseImageIO::CanWriteFile( const char * name )
{
  //
  // DataBase is not implemented to write yet.
  // It will be soon...
  //
  return false;
}


void
DataBaseImageIO
::WriteImageInformation(void)
{
  // add writing here
}


/**
 *
 */
void
DataBaseImageIO
::Write( const void* buffer)
{
}

/** Given a requested region, determine what could be the region that we can
 * read from the file. This is called the streamable region, which will be
 * smaller than the LargestPossibleRegion and greater or equal to the
RequestedRegion */
ImageIORegion
DataBaseImageIO
::GenerateStreamableReadRegionFromRequestedRegion( const ImageIORegion & requested ) const
{
  // FIXME: talk to the database, figure out what is the smallest region that you can get from the database, and still fully contain the "requested" 


  // This will be the code if the database is a perfect streamer: meaning that it will deliver any subpiece that you ask for.
  ImageIORegion streamableRegion = requested;

  return streamableRegion;

  // On the other extreme, an IO that does not stream, will return the LargestPossibleRegion

}


} // end namespace itk
