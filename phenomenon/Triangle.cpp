#include "Triangle.h"

Triangle::Triangle(string tmp_name)                                                        //Please note that the Triangle inherets the Node class, and all of its node releated functions.
{
    name = tmp_name;                    //The rest of the init is taken care of by the Node constructor.
}

Triangle::~Triangle()
{
    for (int i = 0; i < numChildren;)
    {
        delete children.getArrayMember(i);
        i += 1;
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

    glLoadIdentity();

    if (numChildren > 0)                            //If we have children, iliterate through and draw them
    {
        for (int i = 0; i < numChildren;)
        {
            children.getArrayMember(i)->draw();
            i += 1;
        }
    }

    return 0;
}
