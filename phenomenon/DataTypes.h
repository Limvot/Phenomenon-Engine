#ifndef DATATYPES_H
#define DATATYPES_H

#include "ExpandableArray.h"    //Include the ExpandableArray class template, which has to be in one file. Because of this, it gets its own file.

namespace phen {

class Vector           //Simple vector class.
{
    public:
        Vector();
        Vector(float,float,float);
        ~Vector();
        int set(float,float,float);
        Vector operator+ (Vector);
        Vector operator- (Vector);
        Vector operator* (Vector);
        float x,y,z;
};

class Vector4f           //Vector4f class.
{
    public:
        Vector4f();
        Vector4f(float,float,float,float);
        ~Vector4f();
        Vector4f operator+ (Vector4f);
        Vector4f operator- (Vector4f);
        Vector4f operator* (Vector4f);
        float x,y,z,w;
};

class Vector2f           //Simple vector class.
{
    public:
        Vector2f();
        Vector2f(float,float);
        ~Vector2f();
        int set(float,float);
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

class Matrix4f           //Matrix4f class.
{
    public:
        Matrix4f();
        Matrix4f(Vector4f,Vector4f,Vector4f,Vector4f);
        ~Matrix4f();
        Vector4f operator* (Vector4f);
        Matrix4f operator* (Matrix4f);
        float m[4][4];
};


class Vertex           //Vertex class.
{
    public:
        Vertex();
        Vertex(float x,float y, float z, float nx, float ny, float nz, float u, float v);
        ~Vertex();
        void set(float x, float y, float z, float nx, float ny, float nz, float u, float v);
        bool operator== (Vertex);
        Vertex operator+ (Vertex);
        Vertex operator- (Vertex);
        Vertex operator* (Vertex);
        float x,y,z;
        float nx,ny, nz;
        float u, v;
};

} //End Namespace

#endif // DATATYPES_H
