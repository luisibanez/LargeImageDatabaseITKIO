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

  int outcome = interface->Connect( serverAndPort );

  if( outcome == 0 )
    {
    std::cout << "Connect succesful" << std::endl;
    }
  else
    {
    std::cerr << "Connect failed" << std::endl;
    return EXIT_FAILURE;
    }

  const char * pathToData = argv[2];
  double gineaPigValue = 3.141592;

  outcome = interface->Insert( pathToData, (char *)(&gineaPigValue),sizeof(gineaPigValue) );

  if( outcome == 0 )  // FIXME : make it consistent with the doc.
    {
    std::cout << "Insert succesful" << std::endl;
    }
  else
    {
    std::cerr << "Insert failed" << std::endl;
    return EXIT_FAILURE;
    }

  // read the value back...
  std::string query; // FIXME : populate this query.

  outcome = interface->Query( pathToData, query.c_str() )

  if( outcome == 0 )
    {
    std::cerr << "Insert failed" << std::endl;
    return EXIT_FAILURE;
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
