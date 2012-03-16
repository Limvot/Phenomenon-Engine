#include "DataTypes.h"

Vector::Vector()                                                    //If no arguments, init to 0
{
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(float tmp_in_x, float tmp_in_y, float tmp_in_z)      //If we do have arguments, init to them
{
    x = tmp_in_x;
    y = tmp_in_y;
    z = tmp_in_z;
}

Vector::~Vector()
{

}

Vector Vector::operator+ (Vector tmp_in_vector)                    //Overload + so we can add vertexes
{
    Vector tmp_return;

    tmp_return.x = x + tmp_in_vector.x;
    tmp_return.y = y + tmp_in_vector.y;
    tmp_return.z = z + tmp_in_vector.z;

    return (tmp_return);
}

Vector Vector::operator- (Vector tmp_in_vector)                    //Overload - so we can subtract vertexes
{
    Vector tmp_return;

    tmp_return.x = x - tmp_in_vector.x;
    tmp_return.y = y - tmp_in_vector.y;
    tmp_return.z = z - tmp_in_vector.z;

    return (tmp_return);
}

Vector Vector::operator* (Vector tmp_in_vector)
{
    Vector tmp_return;

    tmp_return.x = x * tmp_in_vector.x;
    tmp_return.y = y * tmp_in_vector.y;
    tmp_return.z = z * tmp_in_vector.z;

    return (tmp_return);
}

//////////////////
//Vector2f
//////////////////

Vector2f::Vector2f()                                                    //If no arguments, init to 0
{
    x = 0;
    y = 0;
}

Vector2f::Vector2f(float tmp_in_x, float tmp_in_y)      //If we do have arguments, init to them
{
    x = tmp_in_x;
    y = tmp_in_y;
}

Vector2f::~Vector2f()
{

}

Vector2f Vector2f::operator+ (Vector2f tmp_in_vector)                    //Overload + so we can add vertexes
{
    Vector2f tmp_return;

    tmp_return.x = x + tmp_in_vector.x;
    tmp_return.y = y + tmp_in_vector.y;

    return (tmp_return);
}

Vector2f Vector2f::operator- (Vector2f tmp_in_vector)                    //Overload - so we can subtract vertexes
{
    Vector2f tmp_return;

    tmp_return.x = x - tmp_in_vector.x;
    tmp_return.y = y - tmp_in_vector.y;

    return (tmp_return);
}

Vector2f Vector2f::operator* (Vector2f tmp_in_vector)
{
    Vector2f tmp_return;

    tmp_return.x = x * tmp_in_vector.x;
    tmp_return.y = y * tmp_in_vector.y;

    return (tmp_return);
}


//////////////////
//Color3f
//////////////////

Color3f::Color3f()                                                    //If no arguments, init to 0
{
    r = 1;
    g = 1;
    b = 1;
}

Color3f::Color3f(float tmp_in_r, float tmp_in_g, float tmp_in_b)      //If we do have arguments, init to them
{
    r = tmp_in_r;
    g = tmp_in_g;
    b = tmp_in_b;
}

Color3f::~Color3f()
{

}

Color3f Color3f::operator+ (Color3f tmp_in_color3f)                    //Overload + so we can add vertexes
{
    Color3f tmp_return;

    tmp_return.r = r + tmp_in_color3f.r;
    tmp_return.g = g + tmp_in_color3f.g;
    tmp_return.b = b + tmp_in_color3f.b;

    return (tmp_return);
}

Color3f Color3f::operator- (Color3f tmp_in_color3f)                    //Overload - so we can subtract vertexes
{
    Color3f tmp_return;

    tmp_return.r = r - tmp_in_color3f.r;
    tmp_return.g = g - tmp_in_color3f.g;
    tmp_return.b = b - tmp_in_color3f.b;

    return (tmp_return);
}

/////////////
//Vertex
/////////////

Vertex::Vertex()                                                    //If no arguments, init to 0
{
    x = 0;
    y = 0;
    z = 0;

    nx = 0;
    ny = 0;
    nz = 0;

    u = 0;
    v = 0;
}

Vertex::Vertex(float tmp_in_x, float tmp_in_y, float tmp_in_z, float tmp_in_nx, float tmp_in_ny, float tmp_in_nz, float tmp_in_u, float tmp_in_v)      //If we do have arguments, init to them
{
    x = tmp_in_x;
    y = tmp_in_y;
    z = tmp_in_z;

    nx = tmp_in_nx;
    ny = tmp_in_ny;
    nz = tmp_in_nz;

    u = tmp_in_u;
    v = tmp_in_v;
}

Vertex::~Vertex()
{

}

void Vertex::set(float tmp_in_x, float tmp_in_y, float tmp_in_z, float tmp_in_nx, float tmp_in_ny, float tmp_in_nz, float tmp_in_u, float tmp_in_v)      //Set our our properties
{
    x = tmp_in_x;
    y = tmp_in_y;
    z = tmp_in_z;

    nx = tmp_in_nx;
    ny = tmp_in_ny;
    nz = tmp_in_nz;

    u = tmp_in_u;
    v = tmp_in_v;
}

bool Vertex::operator== (Vertex tmp_in_vertex)                    //Overload == so we can check for equality
{

    if (    (x == tmp_in_vertex.x) &&
            (y == tmp_in_vertex.y) &&
            (z == tmp_in_vertex.z) &&
            (nx == tmp_in_vertex.nx) &&
            (ny == tmp_in_vertex.ny) &&
            (nz == tmp_in_vertex.nz) &&
            (u == tmp_in_vertex.u) &&
            (v == tmp_in_vertex.v)  )
        {
            return true;                                            //If everything is equal, return true. If not, return false.
        }
        return false;
}

Vertex Vertex::operator+ (Vertex tmp_in_vertex)                    //Overload + so we can add vertexes
{
    Vertex tmp_return;

    tmp_return.x = x + tmp_in_vertex.x;
    tmp_return.y = y + tmp_in_vertex.y;
    tmp_return.z = z + tmp_in_vertex.z;

    tmp_return.nx = nx + tmp_in_vertex.nx;
    tmp_return.ny = ny + tmp_in_vertex.ny;
    tmp_return.nz = nz + tmp_in_vertex.nz;

    tmp_return.u = u + tmp_in_vertex.u;
    tmp_return.v = v + tmp_in_vertex.v;

    return (tmp_return);
}

Vertex Vertex::operator- (Vertex tmp_in_vertex)                    //Overload - so we can subtract vertexes
{
    Vertex tmp_return;

    tmp_return.x = x - tmp_in_vertex.x;
    tmp_return.y = y - tmp_in_vertex.y;
    tmp_return.z = z - tmp_in_vertex.z;

    tmp_return.nx = nx - tmp_in_vertex.nx;
    tmp_return.ny = ny - tmp_in_vertex.ny;
    tmp_return.nz = nz - tmp_in_vertex.nz;

    tmp_return.u = u - tmp_in_vertex.u;
    tmp_return.v = v - tmp_in_vertex.v;

    return (tmp_return);
}

Vertex Vertex::operator* (Vertex tmp_in_vertex)
{
    Vertex tmp_return;

    tmp_return.x = x * tmp_in_vertex.x;
    tmp_return.y = y * tmp_in_vertex.y;
    tmp_return.z = z * tmp_in_vertex.z;

    tmp_return.nx = nx * tmp_in_vertex.nx;
    tmp_return.ny = ny * tmp_in_vertex.ny;
    tmp_return.nz = nz * tmp_in_vertex.nz;

    tmp_return.u = u * tmp_in_vertex.u;
    tmp_return.v = v * tmp_in_vertex.v;

    return (tmp_return);
}
