#include "DataTypes.h"

Vertex::Vertex()                                                    //If no arguments, init to 0
{
    x = 0;
    y = 0;
    z = 0;
}

Vertex::Vertex(float tmp_in_x, float tmp_in_y, float tmp_in_z)      //If we do have arguments, init to them
{
    x = tmp_in_x;
    y = tmp_in_y;
    z = tmp_in_z;
}

Vertex::~Vertex()
{

}

Vertex Vertex::operator+ (Vertex tmp_in_vertex)                    //Overload + so we can add vertexes
{
    Vertex tmp_return;

    tmp_return.x = x + tmp_in_vertex.x;
    tmp_return.y = y + tmp_in_vertex.y;
    tmp_return.z = z + tmp_in_vertex.z;

    return (tmp_return);
}

Vertex Vertex::operator- (Vertex tmp_in_vertex)                    //Overload - so we can subtract vertexes
{
    Vertex tmp_return;

    tmp_return.x = x - tmp_in_vertex.x;
    tmp_return.y = y - tmp_in_vertex.y;
    tmp_return.z = z - tmp_in_vertex.z;

    return (tmp_return);
}

Vertex Vertex::operator* (Vertex tmp_in_vertex)
{
    Vertex tmp_return;

    tmp_return.x = x * tmp_in_vertex.x;
    tmp_return.y = y * tmp_in_vertex.y;
    tmp_return.z = z * tmp_in_vertex.z;

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
