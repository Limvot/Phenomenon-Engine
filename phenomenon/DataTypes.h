#ifndef DATATYPES_H
#define DATATYPES_H

#include "ExpandableArray.h"    //Include the ExpandableArray class template, which has to be in one file. Because of this, it gets its own file.

class Vector           //Simple vector class.
{
    public:
        Vector();
        Vector(float,float,float);
        ~Vector();
        Vector operator+ (Vector);
        Vector operator- (Vector);
        Vector operator* (Vector);
        float x,y,z;
};

class Vector2f           //Simple vector class.
{
    public:
        Vector2f();
        Vector2f(float,float);
        ~Vector2f();
        Vector2f operator+ (Vector2f);
        Vector2f operator- (Vector2f);
        Vector2f operator* (Vector2f);
        float x,y;
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


class Vertex           //Vertex class.
{
    public:
        Vertex();
        Vertex(float x,float y, float z, float nx, float ny, float nz, float u, float v);
        ~Vertex();
        bool operator== (Vertex);
        Vertex operator+ (Vertex);
        Vertex operator- (Vertex);
        Vertex operator* (Vertex);
        float x,y,z;
        float nx,ny, nz;
        float u, v;
};
#endif // DATATYPES_H
