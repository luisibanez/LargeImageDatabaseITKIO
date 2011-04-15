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
#ifndef __itkMySQLDataBaseInterface_h
#define __itkMySQLDataBaseInterface_h

// Include necessary headers for mongo

#include <iostream>
#include <client/dbclient.h>

#include "itkDataBaseInterfaceBase.h"


namespace itk
{

class MySQLDataBaseInterface : public DataBaseInterfaceBase
{
public:
  /** Standard class typedefs. */
  typedef MySQLDataBaseInterface      Self;
  typedef DataBaseInterfaceBase       Superclass;
  typedef SmartPointer<Self>          Pointer;
  typedef SmartPointer<const Self>    Pointer;

  /** No NewMacro because this is an abstract class */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MySQLDataBaseInterface, DataBaseInterfaceBase);

  // Operations possible
  virtual void SetUsername( const std::string & username );
  virtual void SetPassword( const std::string & password );
  virtual void Connect(const std::string & serverAndPort = std::string("127.0.0.1:27017"));
  virtual void Connect(const std::string & serverAndPort = std::string("127.0.0.1:27017"), const std::string & username, const std::string & password);
  virtual void Insert(const std::string path, const char * data, size_t size);
  virtual void SetQuery(const std::string & query);
  virtual IdentifierType ExecuteQuery(const std::string & collection );

  // FIXME: Consider using SmartPointers, or AutoPointers here.
  virtual void GetRecord(IdentifierType id, char ** data );

  virtual IdentifierType GetNumberOfFieldsInRecord(IdentifierType id ) = 0;

  // This function is intended to be connected via the SetProcessRecordCallback() method.
  // It should implement the translation of data from the DataBase underlying data structures
  // into some other data structure that is then exposed in this API.
  // In the case of MySQLDB, we may decide to simply use BSON for both, and therefore avoid
  // copying the record fields.
  static void ProcessRecordCallback(void);


  virtual void Disconnect();


protected:

    // Constructor
    MySQLDataBaseInterface()  {}
    ~MySQLDataBaseInterface();
    void PrintSelf(std::ostream& os, Indent indent) const;


private:
    MySQLDataBaseInterface(const Self&); //purposely not implemented
    void operator=(const Self&); //purposely not implemented

    typedef auto_ptr<mongo::DBClientCursor>  CursorPointer;

    mongo::DBClientConnection m_Connection;

};

} // end namespace itk

#endif
