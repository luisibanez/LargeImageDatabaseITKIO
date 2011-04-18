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


#include <iostream>

#include "itkSQLDataBaseInterface.h"
#include "mysql.h" // needed for MYSQL typedefs

#include "itkObjectFactory.h"

namespace itk
{

class MySQLDataBaseInterface : public SQLDataBaseInterface
{
public:
  /** Standard class typedefs. */
  typedef MySQLDataBaseInterface      Self;
  typedef SQLDataBaseInterface        Superclass;
  typedef SmartPointer<Self>          Pointer;
  typedef SmartPointer<const Self>    ConstPointer;

  /** No NewMacro because this is an abstract class */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MySQLDataBaseInterface, SQLDataBaseInterface );

  void SetDataBaseName( const std::string& iDataBaseName )
    {
    if( ( !iDataBaseName.empty() ) &&
        ( m_DataBaseName.compare( iDataBaseName ) != 0 ) )
      {
      m_DataBaseName = iDataBaseName;
      this->Modified();
      }
    }

  // Operations possible
  bool IsOpen() const
    {
    return ( this->m_Private->m_Connection != NULL );
    }

  bool Connect(const std::string & Server = std::string("127.0.0.1"),
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


  void Disconnect()
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


protected:

    // Constructor
    MySQLDataBaseInterface() : Superclass(), m_Private( new MySQLDataBasePrivate )
      {
      }
    ~MySQLDataBaseInterface()
      {
      // let's make sure the connection is closed
      this->Disconnect();
      delete this->m_Private;
      }

    void PrintSelf(std::ostream& os, Indent indent) const
    {
      Superclass::PrintSelf( os, indent );
    }

    std::string m_DataBaseName;
    unsigned int m_Port;

private:
    MySQLDataBaseInterface(const Self&); //purposely not implemented
    void operator=(const Self&); //purposely not implemented

    struct MySQLDataBasePrivate
      {
      MySQLDataBasePrivate() : m_Connection( NULL )
        {
        mysql_init( &this->m_NullConnection );
        }
      ~MySQLDataBasePrivate() {}

      MYSQL m_NullConnection;
      MYSQL *m_Connection;
      };

    MySQLDataBasePrivate* const m_Private;
};

} // end namespace itk

#endif
