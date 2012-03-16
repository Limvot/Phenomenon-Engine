#include "BasicShapes.h"

StaticObject* createTriangle(string name)
{
    GLuint num_vertices = 3;
    Vertex vertices[3];

    vertices[0].set( 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f );
    vertices[1].set( -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f );
    vertices[2].set( 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f );

    GLuint num_indices = 3;
    GLuint indices[3] = {0,1,2};                                                            //Remember, zero-indexed

    return new StaticObject(name, num_vertices, vertices, num_indices, indices);            //Return a pointer to the new object
}

StaticObject* createSquare(string name)
{
    GLuint num_vertices = 4;
    Vertex vertices[4];

    vertices[0].set( -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f );
    vertices[1].set( 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f );
    vertices[2].set( 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f );
    vertices[3].set( -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f );

    GLuint num_indices = 6;
    GLuint indices[6] = { 0, 1, 2, 0, 2, 3 };                                               //Remember, zero-indexed

    return new StaticObject(name, num_vertices, vertices, num_indices, indices);            //Return a pointer to the new object
}
