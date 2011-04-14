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

#include "itkObject.h"

#ifndef __itkDataBaseInterfaceBase_h
#define __itkDataBaseInterfaceBase_h

namespace itk
{

class DataBaseInterfaceBase : public Object
{
public:
  /** Standard class typedefs. */
  typedef DataBaseInterfaceBase       Self;
  typedef Object                      Superclass;
  typedef SmartPointer<Self>          Pointer;
  typedef SmartPointer<const Self>    Pointer;

  /** No NewMacro because this is an abstract class */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(DataBaseInterfaceBase, Object);

  // Operations possible
  virtual int Connect(const std::string & serverAndPort = std::string("127.0.0.1:27017")) = 0;
  virtual int Insert(const char * path, const char * data, size_t size) = 0;
  virtual int Query(const char * collection, const char * query) = 0;
  virtual int Result( int i, const char * data ) = 0;

protected:

  // Constructor
  DataBaseInterfaceBase()  {}
  ~DataBaseInterfaceBase()  {}

  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  DataBaseInterfaceBase(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk

#endif
