#include "Square.h"

Square::Square(string tmp_name)                                                        //Please note that the Square inherets the Node class, and all of its node releated functions.
{
    name = tmp_name;                            //Rest of init is taken care of by the Node constructor
}

Square::~Square()
{
    if (numChildren > 0)
    {
        for (int i = 0; i < numChildren;)
        {
            delete children.getArrayMember(i);
            i += 1;
        }
    }
    numChildren = 0;
}

int Square::draw()
{
    getGlobalPosition();                                                    //Update our world-space varibles.
    getGlobalRotation();
    getGlobalScale();

    glPushMatrix();                                                         //Save state before current object transformations, rotations, scale.

    glTranslatef(globalPosition.x, globalPosition.y, globalPosition.z);     //Translate to our position

    glRotatef(globalRotation.x, 1.0f, 0.0f, 0.0f);                          //Must be a better way to do this. (rotate each axis the proper ammount.
    glRotatef(globalRotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(globalRotation.z, 0.0f, 0.0f, 1.0f);

    glScalef(globalScale.x, globalScale.y, globalScale.z);                  //Scale along each axis the proper ammount. NOTE: I'm not sure why, for expected results, you have to scale after translation and rotation, but it seems you do.

    glColor3f(color.r, color.g, color.b);

    glBegin( GL_QUADS );
        glVertex3f( -1.0f,  1.0f,   0.0f    );
        glVertex3f( -1.0f,  -1.0f,  0.0f    );
        glVertex3f( 1.0f,  -1.0f,   0.0f    );
        glVertex3f( 1.0f,   1.0f,   0.0f    );
    glEnd();

    glPopMatrix();                                                          //Return to state before object's translations, rotations, scale.

    if (numChildren > 0)                                                    //If we have children, go through and draw them
    {
        for (int i = 0; i < numChildren;)
        {
            children.getArrayMember(i)->draw();
            i += 1;
        }
    }

    return 0;
}
