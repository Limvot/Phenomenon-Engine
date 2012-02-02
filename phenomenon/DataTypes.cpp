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
