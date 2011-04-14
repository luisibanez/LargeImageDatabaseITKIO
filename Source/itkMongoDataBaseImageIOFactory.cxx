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

#include "itkMongoDataBaseImageIOFactory.h"
#include "itkCreateObjectFunction.h"
#include "itkMongoDataBaseImageIO.h"
#include "itkVersion.h"


namespace itk
{
MongoDataBaseImageIOFactory::MongoDataBaseImageIOFactory()
{
  this->RegisterOverride("itkImageIOBase",
                         "itkMongoDataBaseImageIO",
                         "MongoDataBase Image IO",
                         1,
                         CreateObjectFunction<MongoDataBaseImageIO>::New());
}

MongoDataBaseImageIOFactory::~MongoDataBaseImageIOFactory()
{
}

const char*
MongoDataBaseImageIOFactory::GetITKSourceVersion() const
{
  return ITK_SOURCE_VERSION;
}

const char*
MongoDataBaseImageIOFactory::GetDescription() const
{
  return "MongoDataBase ImageIO Factory, allows the loading of MongoDataBase images into insight";
}

//
// Entry point function for ITK to invoke, in order to create a new instance of
// a factory.
//
extern "C"
#ifdef _WIN32
__declspec( dllexport )
#endif
  itk::ObjectFactoryBase* itkLoad()
{
  std::cout << "Calling MongoDataBaseImageIO itkLoad()" << std::endl;
  return itk::MongoDataBaseImageIOFactory::FactoryNew();
}


} // end namespace itk
