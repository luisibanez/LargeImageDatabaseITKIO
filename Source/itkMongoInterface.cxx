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

#include <iostream>
#include "itkMongoInterface.h"

namespace itk {

int MongoInterface::Connect(std::string server, std::string port)
{
    // Build the connection string
    std::string connstring(server);
    connstring.append(":");
    connstring.append(port);
    connstring.append("\n");

    std::cout << connstring << endl;

    try
      {
      std::cout << "Here" << endl;
      conn.connect(connstring);
      std::cout << "connected ok" << endl;
      return 0;
      }
    catch( mongo::DBException &e )
      {
      std::cout << "caught " << e.what() << endl;
      return 1;
      }
}

int vtkMongoInterface::Insert(const char * path, mongo::BSONObj  obj)
{
    try
      {
      conn.insert( path , obj);
      return 0;
      }
    catch( mongo::DBException &e )
      {
      std::cout << "caught " << e.what() << endl;
      return 1;
      }
}


int vtkMongoInterface::Insert(const char * name , int num )
{
    try
      {
      mongo::BSONObjBuilder obj;
      obj.append( "name" , name );
      obj.append( "num" , num );
      conn.insert( "test.people" , obj.obj() );
      return 0;
      }
    catch( mongo::DBException &e )
    {
        std::cout << "caught " << e.what() << endl;
        return 1;
    }
}


auto_ptr<mongo::DBClientCursor> vtkMongoInterface::Query(const char * col, const char *qry )
{     
  return this->conn.query(col, mongo::Query(qry));
}


int vtkMongoInterface::Result(int i, mongo::BSONObj * res)
{
  return 0;
}

} // end namespace itk
