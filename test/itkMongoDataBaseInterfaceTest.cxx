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

#include "itkMongoDataBaseInterface.h"
#include "itkTestingMacros.h"

int iitkMongoDataBaseInterfaceTest( int argc, const char * argv [] )
{

  if( argc < 3 )
    {
    std::cerr << "Missing parameters" << std::endl;
    return EXIT_FAILURE;
    }

  typedef itk::MongoDataBaseInterface   InterfaceType;

  InterfaceType::Pointer interface = InterfaceType::New();

  //
  // FIXME: Figure out how to enable a server first...
  //

  std::string serverAndPort = "127.0.0.1:27017";

  try
    {
    interface->Connect( serverAndPort );
    }
  catch( itk::ExceptionObject & excep )
    {
    std::cerr << "Connect failed" << std::endl;
    std::cerr << excep << std::endl;
    return EXIT_FAILURE;
    }

  std::cout << "Connect succesful" << std::endl;
    

  const char * pathToData = argv[2];
  double gineaPigValue = 3.141592;


  // Method 1
  std::string username = "Linus Torvalds";
  std::string password = "Penguin";
  interface->Connect( serverAndPort, username, password );

  // Method 2
  interface->SetUsername( username );
  interface->SetPassword( password );
  interface->Connect( serverAndPort );

  try
    {
    interface->Insert( pathToData, (char *)(&gineaPigValue),sizeof(gineaPigValue) );
    }
  catch( itk::ExceptionObject & excep )
    {
    std::cerr << "Insert failed" << std::endl;
    std::cerr << excep << std::endl;
    return EXIT_FAILURE;
    }

  std::cout << "Insert succesful" << std::endl;

  // Expect Exception because no SetQuery() has been called yet. 
  TRY_EXPECT_EXCEPTION( interface->ExecuteQuery( pathToData ) );

  // read the value back...
  std::string query; // FIXME : populate this query.

  interface->SetQuery( query.c_str() )

  itk::IdentifierType numberOfMatchingRecords = itk::NumericTraits< itk::IdentifierType >::Zero;

  try
    {
    numberOfMatchingRecords = interface->ExecuteQuery( pathToData );
    }
  catch( itk::ExceptionObject & excep )
    {
    std::cerr << "Insert failed" << std::endl;
    std::cerr << excep << std::endl;
    return EXIT_FAILURE;
    }

  std::cout << "ExecuteQuery succesful" << std::endl;


  if( numberOfMatchingRecords == 0 )
    {
    std::cerr << "Insert failed" << std::endl;
    return EXIT_FAILURE;
    }

  char * dataBuffer;

  for( itk::IdentifierType ri = 0; i < numberOfMatchingRecords; i++ )
    {
    interface->GetRecord( ri, &dataBuffer );

    // It is our responsibility to delete this buffer here.
    // FIXME: Consider using SmartPointers, or AutoPointers here.
    delete [] dataBuffer;
    }

  std::cout << "Insert succesful" << std::endl;

  char * bufferAllocatedAndFilledFromDatabase;

  interface->Result( 0, bufferAllocatedAndFilledFromDatabase );

  double * gineaPigValueReturned =
    reinterpret_cast< double * >( bufferAllocatedAndFilledFromDatabase );

  if( *gineaPigValueReturned != gineaPigValueReturned )
    {
    std::cerr << "Double stored failed " << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
