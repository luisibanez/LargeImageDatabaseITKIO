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

#include "itkSQLDataBaseInterface.h"

namespace itk
{
SQLDataBaseInterface
::SQLDataBaseInterface() : Superclass()
  {}

SQLDataBaseInterface
::~SQLDataBaseInterface()
  {}


bool
SQLDataBaseInterface
::Connect( const std::string & server,
          const std::string & port,
          const std::string & username,
          const std::string & password )
{
  this->SetUsername( username );
  this->SetPassword( password );

  return Superclass::Connect( server, port );
}

void
SQLDataBaseInterface
::PrintSelf(std::ostream &os, Indent indent) const
  {
  // FIXME do we really want to print the password?
  // security issue
  Superclass::PrintSelf( os, indent );
  os << "User: " << m_User << std::endl;
  os << "Password: " << m_Password << std::endl;
  }

void
SQLDataBaseInterface
::SetUsername( const std::string & username )
  {
  if( ( !username.empty() ) && ( m_User.compare( username ) != 0 ) )
    {
    m_User = username;
    this->Modified();
    }
  }

void
SQLDataBaseInterface
::SetPassword( const std::string & password )
  {
  if( ( !password.empty() ) && ( m_Password.compare( password ) != 0 ) )
    {
    m_Password = password;
    this->Modified();
    }
  }
}

