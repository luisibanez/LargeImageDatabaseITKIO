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

#include "itkMySQLDataBaseInterface.h"

namespace itk
{

MySQLDataBaseInterface
::MySQLDataBaseInterface() : Superclass(),
  m_Port( 0 ),
  m_Private( new MySQLDataBasePrivate )
  {}

MySQLDataBaseInterface
::~MySQLDataBaseInterface()
{
  // let's make sure the connection is closed
  this->Disconnect();
  delete this->m_Private;
}

void
MySQLDataBaseInterface
::PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf( os, indent );
  os << indent << "Server : " << m_Server <<std::endl;
  os << indent << "Port : " << m_Port <<std::endl;
  os << indent << "DataBaseName : " << m_DataBaseName <<std::endl;
}

void
MySQLDataBaseInterface
::SetDataBaseName( const std::string& iDataBaseName )
{
  if( ( !iDataBaseName.empty() ) &&
      ( m_DataBaseName.compare( iDataBaseName ) != 0 ) )
    {
    m_DataBaseName = iDataBaseName;
    this->Modified();
    }
}

bool
MySQLDataBaseInterface
::IsOpen() const
  {
  return ( this->m_Private->m_Connection != NULL );
  }

bool
MySQLDataBaseInterface
::Connect( const std::string & Server = std::string("127.0.0.1"),
           const std::string & Port = std::string( "27017" ) )
  {
  if( this->IsOpen() )
    {
    return true;
    }
  else
    {
    if( ( !Server.empty() ) && ( m_Server.compare( Server ) != 0 ) )
      {
      m_Server = Server;
      }
    unsigned int t_port = ss_atoi< unsigned int >( Port );

    if( m_Port != t_port )
      {
      m_Port = Port;
      }

    if( m_Reconnect )
      {
      // reconnect ?
      }

    this->m_Private->m_Connection =
      mysql_real_connect( &this->m_Private->NullConnection,
        m_Server.c_str(),
        this->m_User.c_str(),
        this->m_Password.c_str(),
        m_DatabaseName.c_str(),
        m_Port,
        0, // unix socket
        0  // client_flag
      );

    if( this->m_Private->m_Connection == NULL )
      {
      itkGenericExceptionMacro( << "Connect() failed with error: "
                                << mysql_error( &this->m_Private->NullConnection ) );
      return false;
      }
    return true;
    }
  }

void
MySQLDataBaseInterface
::SetQuery( const std::string & iQuery )
{
  if( !iQuery.empty() )
    {
    itkGenericExceptionMacro( << "Empty Query" );
    }

  if( m_Query.compare( iQuery ) == 0 )
    {
    // this query has already been processed
    return;
    }
  else
    {
    MYSQL* db = dbContainer->Private->Connection;
    st_mysql_stmt statement = mysql_stmt_init( db );

    if( statement == NULL )
      {
      itkGenericExceptionMacro( << "mysql_stmt_init returned out of memory error" );
      return;
      }

    int status = mysql_stmt_prepare( statement,
                                    iQuery.c_str(),
                                    iQuery.size() );

    if( status == 0 )
      {
      size_t nb_parameter =
          static_cast< size_t >( mysql_stmt_param_count( statement ) );

      m_UserParameters.resize( nb_parameter, NULL );
      }
    else
      {
      std::string error_message = std::string( mysql_stmt_error( statement ) );

      itkGenericExceptionMacro( << "MySQLDataBaseInterface::SetQuery error "
                                << error_message );
      }
    }
}

IdentifierType
MySQLDataBaseInterface
::ExecuteQuery(const std::string & collection)
{
  if( !this->IsOpen() )
    {
    itkGenericExceptionMacro( <<"Database is closed" );
    return 0;
    }

  if( !m_Query.empty() )
    {
    MYSQL *db = dbContainer->Private->Connection;
    assert(db != NULL);

    int result = mysql_query( db, m_Query.c_str() );

    if( result == 0 )
      {
      // The query probably succeeded.
      st_mysql_res temp_result = mysql_store_result( db );
      unsigned int field_count = mysql_field_count( db );

      if( temp_result || field_count == 0 )
        {
        this->m_Active = ( field_count == 0 );
        return;
        }
      else
        {
        this->m_Active = false;
        std::string error_message( mysql_error( db ) );
        itkGenericExceptionMacro( << "Query returned an error: "
                                  << error_message );
        return;
        }
      }
    else
      {
      // result != 0; the query failed
      this->m_Active = false;
      std::string error_message( mysql_error( db ) );
      itkGenericExceptionMacro( << "Query returned an error: "
                                << error_message );
      return;
      }
    }
  else
    {

    }
}

bool
MySQLDataBaseInterface
::ValidPreparedStatementSQL( const std::string& iQuery )
{
  if( iQuery.empty() )
    {
    return false;
    }


}

void
MySQLDataBaseInterface
::Disconnect()
  {
  if( !this->IsOpen() )
    {
    return;
    }
  else
    {
    mysql_close( this->m_Private->m_Connection );
    this->m_Private->m_Connection = NULL;
    }
  }

}
