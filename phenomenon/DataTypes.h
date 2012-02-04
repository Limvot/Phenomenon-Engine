#ifndef DATATYPES_H
#define DATATYPES_H

#include "ExpandableArray.h"    //Include the ExpandableArray class template, which has to be in one file. Because of this, it gets its own file.

class Vertex           //Simple vertex class.
{
    public:
        Vertex();
        Vertex(float,float,float);
        ~Vertex();
        Vertex operator+ (Vertex);
        Vertex operator- (Vertex);
        float x,y,z;
};

class Color3f           //Simple rgb color class.
{
    public:
        Color3f();
        Color3f(float,float,float);
        ~Color3f();
        int setColor(float,float,float);
        Color3f operator+ (Color3f);
        Color3f operator- (Color3f);
        float r,g,b;
};
#endif // DATATYPES_H
