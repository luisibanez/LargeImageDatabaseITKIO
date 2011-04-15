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

#ifndef __itkDataBaseImageIO_h
#define __itkDataBaseImageIO_h

#ifdef _MSC_VER
#pragma warning ( disable : 4786 )
#endif

#include <fstream>
#include "itkImageIOBase.h"

namespace itk
{

/** \class DataBaseImageIO
 *
 *  \brief Read images from a DataBase
 *
 * FIXME  Add documentation...
 *
 *  \ingroup IOFilters
 */
class ITK_EXPORT DataBaseImageIO : public ImageIOBase
{
public:
  /** Standard class typedefs. */
  typedef DataBaseImageIO    Self;
  typedef ImageIOBase        Superclass;
  typedef SmartPointer<Self> Pointer;

  /** No NewMacro because this is an abstract class */

  /** Run-time type information (and related methods). */
  itkTypeMacro(DataBaseImageIO, ImageIOBase);

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


  /** Specific DataBase API */

  typedef std::vector<double>   PointType;
  typedef std::vector<double>   VectorType;

  /** Get how many resolution levels there are in this collection. FIXME: This
   * method is a candidate to be moved to the ImageIOBase class. */
  unsigned int GetNumberOfResolutionLevels() const;

  /** Focus the reader in a specific resolution level. Throws exception if
   * resolutionLevel doesn't exist. You must call this only after checking with
   * GetNumberOfResolutionLevels(). Subsequent call to query methods such as
   * GetSpacing(), GetOrigin() and GetOrigin(). */
  void SelectResolutionLevel( unsigned int resolutionLevel );

  /** Helper method to compute the requested region by giving to it physical coordinates. */
  void SetRequestedPhysicalRegion( const PointType & cornerPoint1, const VectorType & diagonalVector );
  void SetRequestedPhysicalRegion( const PointType & cornerPoint1, const PointType  & cornerPoint2 );

  /** Report what region is currently being requested. */
  ImageIORegion GetRequestedRegion() const;

protected:
  DataBaseImageIO();
  ~DataBaseImageIO();
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  DataBaseImageIO(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk

#endif // __itkDataBaseImageIO_h
