/*    Copyright 2010 Kitware Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#ifndef __itkMongoDataBaseInterface_h
#define __itkMongoDataBaseInterface_h

// Include necessary headers for mongo \

#include <iostream>
#include <client/dbclient.h>

#include "itkDataBaseInterfaceBase.h"


namespace itk
{

class MongoDataBaseInterface : public DataBaseInterfaceBase
{
public:
  /** Standard class typedefs. */
  typedef MongoDataBaseInterface      Self;
  typedef DataBaseInterfaceBase       Superclass;
  typedef SmartPointer<Self>          Pointer;
  typedef SmartPointer<const Self>    Pointer;

  /** No NewMacro because this is an abstract class */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MongoDataBaseInterface, DataBaseInterfaceBase);


    // Constructor
    MongoDataBaseInterface()  {}

    typedef auto_ptr<mongo::DBClientCursor>  CursorPointer;

    // Operations possible
    int Connect(std::string server = std::string("127.0.0.1"), std::string port = std::string("27017"));
    int Insert(const char * name , int num );
    int Insert(const char * path, mongo::BSONObj  obj);
    CursorPointer Query(const char * collection, const char  * query);
    int Result(int i, mongo::BSONObj * r);

private:

    mongo::DBClientConnection conn;

};

} // end namespace itk

#endif
