#include "Triangle.h"

Triangle::Triangle(string tmp_name)                                         //Please note that the Triangle inherets the Node class, and all of its node releated functions.
{
    name = tmp_name;                                                        //The rest of the init is taken care of by the Node constructor.
}

Triangle::~Triangle()
{                                                                           //Taken care of by the Node destructor
}

int Triangle::draw()
{
    getGlobalPosition();                                                    //Update all our global varibles.
    getGlobalRotation();
    getGlobalScale();

    glPushMatrix();                                                         //Save state before current object transformations, rotations, scale.

    glTranslatef(globalPosition.x, globalPosition.y, globalPosition.z);     //Translate to our position

    glRotatef(globalRotation.x, 1.0f, 0.0f, 0.0f);                          //Must be a better way to do this. (rotate each axis the proper ammount.
    glRotatef(globalRotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(globalRotation.z, 0.0f, 0.0f, 1.0f);

    glScalef(globalScale.x, globalScale.y, globalScale.z);                  //Scale along each axis the proper ammount. NOTE: I'm not sure why, for expected results, you have to scale after translation and rotation, but it seems you do.

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material->diffuse);         //Apply material
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material->specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material->specularHardness);

    material->bindTexture();                                                //Bind the texture, if we have one.

    glBegin( GL_TRIANGLES );
        glTexCoord2f(0.5f, 0.0f);
        glVertex3f( 0.0f,   1.0f,   0.0f    );

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f( -1.0f,  -1.0f,  0.0f    );

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 1.0f,   -1.0f,  0.0f    );
    glEnd();

    glPopMatrix();                                                          //Return to state before object's translations, rotations, scale.

    if (numChildren > 0)                                                    //If we have children, iliterate through and draw them
    {
        for (int i = 0; i < numChildren; i++)
        {
            if (children.getArrayMember(i) != NULL)
                children.getArrayMember(i)->draw();
        }
    }

    return 0;
}
