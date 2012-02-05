#include "Camera.h"

Camera::Camera(string tmp_name)                                                        //Please note that the Square inherets the Node class, and all of its node releated functions.
{
    name = tmp_name;                            //Rest of init is taken care of by the Node constructor
}

Camera::~Camera()
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

int Camera::draw()
{
    getGlobalPosition();                                                    //Update our world-space varibles.
    getGlobalRotation();
    getGlobalScale();

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

int Camera::drawScene(Node *rootNode)
{
    getGlobalPosition();
    getGlobalRotation();
    getGlobalScale();

    //Doing this with matrix. The matrix is transformed, roatated, and scaled, and then nothing else modifies the matrix (permenantly) because they push and pop accordingly.


    glRotatef(-globalRotation.x, 1.0f, 0.0f, 0.0f);                          //Note that this time we rotate first.
    glRotatef(-globalRotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(-globalRotation.z, 0.0f, 0.0f, 1.0f);

    glTranslatef(-globalPosition.x, -globalPosition.y, -globalPosition.z);     //Translate to the approiate position. (the reverse of the camera position.)

    glScalef((1/globalScale.x), (1/globalScale.y), (1/globalScale.z));                  //Scale along each axis the proper ammount. NOTE: I'm not sure why, for expected results, you have to scale after translation and rotation, but it seems you do.

    rootNode->draw();                                                          //Draw from the root down. This may eventually reach the camera, in which case our draw function will draw our children.

    return 0;
}

int Camera::rotate(float rot_x, float rot_y, float rot_z)
{
    localRotation.x += rot_x;
    localRotation.y += rot_y;
    localRotation.z += rot_z;

    return 0;
}

int Camera::goForward(float)
{
    //To Do
    return 0;
}

int Camera::goBackward(float)
{
    //To Do
    return 0;
}

int Camera::goLeft(float)
{
    //To Do
    return 0;
}

int Camera::goRight(float)
{
    //To Do
    return 0;
}
