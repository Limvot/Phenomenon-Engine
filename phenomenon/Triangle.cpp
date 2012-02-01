#include "Triangle.h"

Triangle::Triangle()
{
    parent = NULL;
    children = NULL;
}

Triangle::~Triangle()
{

}

int Triangle::draw()
{
    glTranslatef(   0.0f,    0.0f,    -6.0f   );
    glBegin( GL_TRIANGLES );
        glVertex3f( 0.0f,   1.0f,   0.0f    );
        glVertex3f( -1.0f,  -1.0f,  0.0f    );
        glVertex3f( 1.0f,   -1.0f,   0.0f    );
    glEnd();

    return 0;
}
