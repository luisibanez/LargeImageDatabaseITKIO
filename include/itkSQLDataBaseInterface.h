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
#ifndef __itkSQLDataBaseInterface_h
#define __itkSQLDataBaseInterface_h

#include <iostream>

#include "itkDataBaseInterfaceBase.h"


namespace itk
{

class SQLDataBaseInterface : public DataBaseInterfaceBase
{
public:
  /** Standard class typedefs. */
  typedef SQLDataBaseInterface      Self;
  typedef DataBaseInterfaceBase       Superclass;
  typedef SmartPointer<Self>          Pointer;
  typedef SmartPointer<const Self>    ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(SQLDataBaseInterface, DataBaseInterfaceBase);

  bool Connect( const std::string & server,
                const std::string & port,
                const std::string & username,
                const std::string & password );

  // Operations possible
  // FIXME check itkSetMacro with std::string
  void SetUsername( const std::string & username );

  void SetPassword( const std::string & password );

protected:

    // Constructor
    SQLDataBaseInterface();
    virtual ~SQLDataBaseInterface();

    void PrintSelf(std::ostream& os, Indent indent) const;

    std::string m_User;
    std::string m_Password;

    template<typename RT, typename T, typename Trait, typename Alloc>
    RT ss_atoi( const std::basic_string<T, Trait, Alloc>& the_string )
    {
        std::basic_istringstream< T, Trait, Alloc> temp_ss(the_string);
        RT num;
        temp_ss >> num;
        return num;
    }


private:
    SQLDataBaseInterface(const Self&); //purposely not implemented
    void operator=(const Self&); //purposely not implemented

};

} // end namespace itk

#endif
