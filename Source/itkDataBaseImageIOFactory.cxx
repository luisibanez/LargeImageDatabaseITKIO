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

#include "itkDataBaseImageIOFactory.h"
#include "itkCreateObjectFunction.h"
#include "itkDataBaseImageIO.h"
#include "itkVersion.h"


namespace itk
{
DataBaseImageIOFactory::DataBaseImageIOFactory()
{
  this->RegisterOverride("itkImageIOBase",
                         "itkDataBaseImageIO",
                         "DataBase Image IO",
                         1,
                         CreateObjectFunction<DataBaseImageIO>::New());
}

DataBaseImageIOFactory::~DataBaseImageIOFactory()
{
}

const char*
DataBaseImageIOFactory::GetITKSourceVersion() const
{
  return ITK_SOURCE_VERSION;
}

const char*
DataBaseImageIOFactory::GetDescription() const
{
  return "DataBase ImageIO Factory, allows the loading of DataBase images into insight";
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
  std::cout << "Calling DataBaseImageIO itkLoad()" << std::endl;
  return itk::DataBaseImageIOFactory::FactoryNew();
}


} // end namespace itk
