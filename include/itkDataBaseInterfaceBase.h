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
  virtual void SetUsername( const std::string & username );
  virtual void SetPassword( const std::string & password );
  virtual void Connect(const std::string & serverAndPort = std::string("127.0.0.1:27017")) = 0;
  virtual void Connect(const std::string & serverAndPort = std::string("127.0.0.1:27017"), const std::string & username, const std::string & password) = 0;
  virtual void Insert(const std::string & path, const char * data, size_t size) = 0;

  /** This method is intended to be overloaded in derived classes that
   * implement specific databases. */
  virtual int SetQuery(const std::string & query );

  /** You must call SetQuery() first...
   * This method will return the number of records matching the query.
   * The data from each record can the be extracted by calling
   * GetRecord() with an identifier number. */
  virtual IdentifierType ExecuteQuery(const std::string & collection)
= 0;

  /** The GetRecord() method will allocate the required memory, and IT
   * IS THE RESPONSIBILITY of the caller to release the memory. */
  // FIXME: Consider using SmartPointers, or AutoPointers here.
  virtual void GetRecord(IdentifierType id, char ** data ) = 0;

  virtual MetaDataDictionary GetRecordDescription(IdentifierType id ) = 0;

  typedef void (callback)(IdentifierType id) OneRecordCallbackType
  virtual void SetProcessRecordCallback( OneRecordCallbackType * callback );

  // These two functions call the callback function that was provided
  // in  SetProcessRecordCallback(). In the case of ProcessRecord(id)
  // the callback function will be invoked only for the record identified by Id.
  // In the case of ProcessAllRecords() the callback function will be invoked for
  // each one of the records selected by the Query.
  virtual void ProcessRecord(IdentifierType id);
  virtual void ProcessAllRecords();

  // BSON : Binary Serialized Object = Binary JSON
  // http://bsonspec.org/

  virtual void Disconnect() = 0;

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
