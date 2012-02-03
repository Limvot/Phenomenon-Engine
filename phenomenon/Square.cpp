#include "Square.h"

Square::Square(string tmp_name)                                                        //Please note that the Square inherets the Node class, and all of its node releated functions.
{
    name = tmp_name;
    parent = NULL;
    tmp_return_child = NULL;
    numChildren = 0;
}

Square::~Square()
{
    for (int i = 0; i < numChildren;)
    {
        delete children.getArrayMember(i);
        i += 1;
    }
}

int Square::draw()
{
    getGlobalPosition();
    glTranslatef(globalPosition.x, globalPosition.y, globalPosition.z);

    glBegin( GL_QUADS );
        glVertex3f( -1.0f,  1.0f,   0.0f    );
        glVertex3f( -1.0f,  -1.0f,  0.0f    );
        glVertex3f( 1.0f,  -1.0f,   0.0f    );
        glVertex3f( 1.0f,   1.0f,   0.0f    );
    glEnd();

    glLoadIdentity();

    if (numChildren > 0)                            //If we have children, go through and draw them
    {
        for (int i = 0; i < numChildren;)
        {
            children.getArrayMember(i)->draw();
            i += 1;
        }
    }

    return 0;
}
