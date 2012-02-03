#ifndef DATATYPES_H
#define DATATYPES_H

#include "ExpandableArray.h"    //Include the ExpandableArray class template, which has to be in one file. Because of this, it gets its own file.

class Vertex           //Simple vertex class. May add more data types here.
{
    public:
        Vertex();
        Vertex(float,float,float);
        ~Vertex();
        Vertex operator+ (Vertex);
        Vertex operator- (Vertex);
        float x,y,z;
};

#endif // DATATYPES_H
