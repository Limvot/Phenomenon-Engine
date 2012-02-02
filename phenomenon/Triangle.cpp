#include "Triangle.h"

Triangle::Triangle()                                                        //Please note that the Triangle inherets the Node class, and all of its node releated functions.
{
    parent = NULL;
    children = NULL;
}

Triangle::~Triangle()
{
    if (children != NULL)
    {
        delete children;                                                    //Delete our children
        std::cout << "Deleted Children, deleting self\n";
    }
}

int Triangle::draw()
{
    getGlobalPosition();
    glTranslatef(globalPosition.x, globalPosition.y, globalPosition.z);

    glBegin( GL_TRIANGLES );
        glVertex3f( 0.0f,   1.0f,   0.0f    );
        glVertex3f( -1.0f,  -1.0f,  0.0f    );
        glVertex3f( 1.0f,   -1.0f,  0.0f    );
    glEnd();

    if (children != NULL)                                                   //Draw children, if we have any.
    {
        children->draw();
    }

    return 0;
}
