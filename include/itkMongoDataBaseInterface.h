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

#ifndef __itkMongoDataBaseInterface_h
#define __itkMongoDataBaseInterface_h

// Include necessary headers for mongo

#include <mongo/client/dbclient.h>

#include "itkDataBaseInterfaceBase.h"
#include "itkObjectFactory.h"


namespace itk
{

class MongoDataBaseInterface : public DataBaseInterfaceBase
{
public:
  /** Standard class typedefs. */
  typedef MongoDataBaseInterface      Self;
  typedef DataBaseInterfaceBase       Superclass;
  typedef SmartPointer<Self>          Pointer;
  typedef SmartPointer<const Self>    ConstPointer;

  /** No NewMacro because this is an abstract class */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MongoDataBaseInterface, DataBaseInterfaceBase);

  // Operations possible
  virtual void SetUsername( const std::string & username );
  virtual void SetPassword( const std::string & password );
  virtual void Connect(const std::string & serverAndPort = std::string("127.0.0.1:27017"));
  virtual void Connect( const std::string & serverAndPort,
                       const std::string & username,
                       const std::string & password ) {}

  virtual void Insert(const std::string& path, const char * data, size_t size) {}
  virtual void SetQuery(const std::string & query);

  virtual MetaDataDictionary GetRecordDescription(IdentifierType id );

  virtual IdentifierType ExecuteQuery(const std::string & collection );

  // FIXME: Consider using SmartPointers, or AutoPointers here.
  virtual void GetRecord(IdentifierType id, char ** data );

  virtual IdentifierType GetNumberOfFieldsInRecord(IdentifierType id );

  // This function is intended to be connected via the SetProcessRecordCallback() method.
  // It should implement the translation of data from the DataBase underlying data structures
  // into some other data structure that is then exposed in this API.
  // In the case of MongoDB, we may decide to simply use BSON for both, and therefore avoid
  // copying the record fields.
  static void ProcessRecordCallback(void);


  virtual void Disconnect();


protected:

    // Constructor
    MongoDataBaseInterface()  {}
    ~MongoDataBaseInterface();
    void PrintSelf(std::ostream& os, Indent indent) const;


private:
    MongoDataBaseInterface(const Self&); //purposely not implemented
    void operator=(const Self&); //purposely not implemented

    typedef auto_ptr<mongo::DBClientCursor>  CursorPointer;

    mongo::DBClientConnection m_Connection;

};

} // end namespace itk

#endif
