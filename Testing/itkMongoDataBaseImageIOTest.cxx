/*    Copyright 2010  Kitware Inc.
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


// Define a test structure
struct somedata
{
    int a;
    double b,c,d;
    char name[12];
};


int main( int argc, const char **argv )
{
    itkMongoInterface mongoint;

    mongoint.connect();
    //mongoint.connect("192.168.32.4");
    mongoint.insert("DJ" , 125 );


    // test BSON Creation
    mongo::BSONObjBuilder b;
    b.append("name", "Joe");
    b.append("age", 33);
    mongo::BSONObj p = b.obj();

    // test BSON insertion
    mongoint.insert("DJ", p);

    // Create a structure
    somedata myData;
    myData.a = 54;
    myData.b = 3.1415616;
    myData.c = 0.99;
    myData.d = 1.1;
    strcpy(myData.name , "Dhanannjay");

    // Insert struct in BSON

    mongo::BSONObjBuilder bin;
    bin.appendBinData("somedata",sizeof(somedata),  mongo::BinDataGeneral, (char *) &myData );
    //cout << bin.len()<< ", " << sizeof(somedata) ;

    mongoint.insert("DJ.objs", bin.obj());

    auto_ptr<mongo::DBClientCursor> cur = mongoint.query("brainbow.0", "{level : {'$lt' : 2 } }");

    while(cur->more())
      {
        mongo::BSONObj b = cur->next();
        cout << b.getStringField("name") << endl;
        cout << b.getIntField("xs") << endl;

      }


}
