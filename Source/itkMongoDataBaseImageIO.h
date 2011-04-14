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

#ifndef __itkMongoDataBaseImageIO_h
#define __itkMongoDataBaseImageIO_h

#ifdef _MSC_VER
#pragma warning ( disable : 4786 )
#endif

#include <fstream>
#include "itkImageIOBase.h"
#include "itkMongoDataBaseInterface.h"

namespace itk
{

/** \class MongoDataBaseImageIO
 *
 *  \brief Read images from a MongoDataBase
 *
 * FIXME  Add documentation...
 *
 *  \ingroup IOFilters
 */
class ITK_EXPORT MongoDataBaseImageIO : public ImageIOBase
{
public:
  /** Standard class typedefs. */
  typedef MongoDataBaseImageIO      Self;
  typedef ImageIOBase               Superclass;
  typedef SmartPointer<Self>        Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** No NewMacro because this is an abstract class */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MongoDataBaseImageIO, ImageIOBase);

 /*-------- This part of the interfaces deals with reading data. ----- */

  /** Determine the file type. Returns true if this ImageIO can read the
   * file specified. */
  virtual bool CanReadFile(const char*);

  /** Set the spacing and dimension information for the set filename. */
  virtual void ReadImageInformation();

  /** Reads the data from disk into the memory buffer provided. */
  virtual void Read(void* buffer);

  /*-------- This part of the interfaces deals with writing data. ----- */

  /** Determine the file type. Returns true if this ImageIO can write the
   * file specified. */
  virtual bool CanWriteFile(const char*);

  /** Set the spacing and dimension information for the set filename. */
  virtual void WriteImageInformation();

  /** Writes the data to disk from the memory buffer provided. Make sure
   * that the IORegions has been set properly. */
  virtual void Write(const void* buffer);

  /** Method for supporting streaming.  Given a requested region, determine what
   * could be the region that we can read from the file. This is called the
   * streamable region, which will be smaller than the LargestPossibleRegion and
   * greater or equal to the RequestedRegion */
  virtual ImageIORegion
  GenerateStreamableReadRegionFromRequestedRegion( const ImageIORegion & requested ) const;

  /** Connect to Mongo Data Base interface object. */
  void SetDataBaseInterface( MongoDataBaseInterface * );

protected:
  MongoDataBaseImageIO();
  ~MongoDataBaseImageIO();
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  MongoDataBaseImageIO(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  MongoDataBaseInterface *  m_DataBaseInterface;
};

} // end namespace itk

#endif // __itkMongoDataBaseImageIO_h
