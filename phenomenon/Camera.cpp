#include "Camera.h"

Camera::Camera()
{
    name = "camera";
}

Camera::Camera(string tmp_name)                 //Please note that the Square inherets the Node class, and all of its node releated functions.
{
    name = tmp_name;                            //Rest of init is taken care of by the Node constructor
}

                                                //Inherit destructor as well.

int Camera::drawScene(Scene *scene)
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

    scene->render();                                                          //Render the scene. This may eventually reach the camera, in which case our draw function will draw our children.

    return 0;
}

int Camera::rotate(float rot_x, float rot_y, float rot_z)
{
    localRotation.x += rot_x;
    localRotation.y += rot_y;
    localRotation.z += rot_z;

    return 0;
}

int Camera::goForward(float movement_ammount)
{
    float x_rotation_radians, y_rotation_radians;
    x_rotation_radians = -((localRotation.x/180) * PI);                          //Change degrees to radians, and reverse sign.
    y_rotation_radians = -((localRotation.y/180) * PI);                         //This is necessary because the camera rotations are reversed compared to objects, and we store the rotations like an object.

    localPosition.x += float(movement_ammount * sin(y_rotation_radians));        //Fid the x component of the movement
    localPosition.y -= float(movement_ammount * sin(x_rotation_radians));        //Find the y component of the movement
    localPosition.z -= float(movement_ammount * cos(y_rotation_radians));        //Find the z component of the movemen

    return 0;
}

int Camera::goBackward(float movement_ammount)
{
    float x_rotation_radians, y_rotation_radians;
    x_rotation_radians = -((localRotation.x/180) * PI);                          //Change degrees to radians, and reverse sign.
    y_rotation_radians = -((localRotation.y/180) * PI);                         //This is necessary because the camera rotations are reversed compared to objects, and we store the rotations like an object.

    localPosition.x -= float(movement_ammount * sin(y_rotation_radians));        //Fid the x component of the movement
    localPosition.y += float(movement_ammount * sin(x_rotation_radians));        //Find the y component of the movement
    localPosition.z += float(movement_ammount * cos(y_rotation_radians));        //Find the z component of the movement

    return 0;
}

int Camera::goLeft(float movement_ammount)
{
    float y_rotation_radians;
                                                                                //Change degrees to radians, and reverse sign.
    y_rotation_radians = -((localRotation.y/180) * PI);                         //This is necessary because the camera rotations are reversed compared to objects, and we store the rotations like an object.

    localPosition.x -= float(movement_ammount * cos(y_rotation_radians));        //Fid the x component of the movement
    localPosition.z -= float(movement_ammount * sin(y_rotation_radians));        //Find the z component of the movement

    return 0;
}

int Camera::goRight(float movement_ammount)
{
    float y_rotation_radians;
                                                                                //Change degrees to radians, and reverse sign.
    y_rotation_radians = -((localRotation.y/180) * PI);                         //This is necessary because the camera rotations are reversed compared to objects, and we store the rotations like an object.

    localPosition.x += float(movement_ammount * cos(y_rotation_radians));        //Fid the x component of the movement
    localPosition.z += float(movement_ammount * sin(y_rotation_radians));        //Find the z component of the movement

    return 0;
}
