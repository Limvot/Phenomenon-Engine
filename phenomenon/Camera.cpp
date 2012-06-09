#include "Camera.h"

namespace phen {

Camera::Camera()
{
    name = "camera";
}

Camera::Camera(std::string tmp_name)                 //Please note that the Square inherets the Node class, and all of its node releated functions.
{
    name = tmp_name;                            //Rest of init is taken care of by the Node constructor
}

                                                //Inherit destructor as well.
int Camera::setProjectionMatrix(GLuint width, GLuint height, GLfloat FOV, GLfloat zNear, GLfloat zFar)
{
    return setProjectionMatrix(GLfloat(width) / GLfloat(height), FOV, zNear, zFar);
}

int Camera::setProjectionMatrix(GLfloat aspectRatio, GLfloat FOV, GLfloat zNear, GLfloat zFar)
{
    std::cout << "aspectRation is: " << aspectRatio << "\n";

    GLfloat cotanHalfFOV = 1/(tanf((FOV/360)*PI));                //FOV/2/180 * PI simplifies to FOV/360*PI
    GLfloat zRange = zNear-zFar;

    projectionMatrix.m[0][0] = cotanHalfFOV/aspectRatio;
    projectionMatrix.m[0][1] = 0;
    projectionMatrix.m[0][2] = 0;
    projectionMatrix.m[0][3] = 0;

    projectionMatrix.m[1][0] = 0;
    projectionMatrix.m[1][1] = cotanHalfFOV;
    projectionMatrix.m[1][2] = 0;
    projectionMatrix.m[1][3] = 0;

    projectionMatrix.m[2][0] = 0;
    projectionMatrix.m[2][1] = 0;
    projectionMatrix.m[2][2] = -(zFar+zNear)/zRange;
    projectionMatrix.m[2][3] = (2*zFar*zNear)/zRange;

    projectionMatrix.m[3][0] = 0;
    projectionMatrix.m[3][1] = 0;
    projectionMatrix.m[3][2] = 1;
    projectionMatrix.m[3][3] = 0;

    return 0;
}


Matrix4f Camera::getViewMatrix()
{
    Matrix4f invPosition, invRotation, invScale;

    getGlobalPosition();
    getGlobalRotation();
    getGlobalScale();

    //Calculate inverse rotation

    GLfloat tmp_x_rot_rad = (-globalRotation.x/180) * PI;                 //Rotate minus degrees
    GLfloat tmp_y_rot_rad = (-globalRotation.y/180) * PI;
    GLfloat tmp_z_rot_rad = (-globalRotation.z/180) * PI;

    Matrix4f tmp_mat_x, tmp_mat_y, tmp_mat_z;                           //Now it's a standard rotation calculation

    tmp_mat_x.m[0][0] = 1;                      //The x rotations
    tmp_mat_x.m[1][1] = cos(tmp_x_rot_rad);
    tmp_mat_x.m[1][2] = sin(tmp_x_rot_rad);
    tmp_mat_x.m[2][1] = -sin(tmp_x_rot_rad);
    tmp_mat_x.m[2][2] = cos(tmp_x_rot_rad);
    tmp_mat_x.m[3][3] = 1;

    tmp_mat_y.m[0][0] = cos(tmp_y_rot_rad);     //The y rotations
    tmp_mat_y.m[0][2] = -sin(tmp_y_rot_rad);
    tmp_mat_y.m[2][2] = 1;
    tmp_mat_y.m[2][0] = sin(tmp_y_rot_rad);
    tmp_mat_y.m[2][2] = cos(tmp_y_rot_rad);
    tmp_mat_y.m[3][3] = 1;

    tmp_mat_z.m[0][0] = cos(tmp_z_rot_rad);     //The y rotations
    tmp_mat_z.m[0][1] = sin(tmp_z_rot_rad);
    tmp_mat_z.m[1][0] = -sin(tmp_z_rot_rad);
    tmp_mat_z.m[1][1] = cos(tmp_z_rot_rad);
    tmp_mat_z.m[2][2] = 1;
    tmp_mat_z.m[3][3] = 1;

    invRotation = tmp_mat_x * tmp_mat_y * tmp_mat_z;                    //Compile to rotations

    invPosition.m[0][3] = -globalPosition.x;                            //Negative positions
    invPosition.m[1][3] = -globalPosition.y;
    invPosition.m[2][3] = globalPosition.z;

    invScale.m[0][0] = 1/globalScale.x;                                 //Inverse scales
    invScale.m[1][1] = 1/globalScale.y;
    invScale.m[2][2] = 1/globalScale.z;

    return invScale * invRotation * invPosition;                       //Return the resulting viewMatrix
}

Matrix4f Camera::getProjectionMatrix()
{
    return projectionMatrix;
}

int Camera::rotate(float rot_x, float rot_y, float rot_z)
{
    localRotation.x += rot_x;
    localRotation.y += rot_y;
    localRotation.z += rot_z;

    GLfloat tmp_x_rot_rad = (localRotation.x/180) * PI;
    GLfloat tmp_y_rot_rad = (localRotation.y/180) * PI;
    GLfloat tmp_z_rot_rad = (localRotation.z/180) * PI;


    Matrix4f tmp_mat_x, tmp_mat_y, tmp_mat_z;

    tmp_mat_x.m[0][0] = 1;                      //The x rotations
    tmp_mat_x.m[1][1] = cos(tmp_x_rot_rad);
    tmp_mat_x.m[1][2] = sin(tmp_x_rot_rad);
    tmp_mat_x.m[2][1] = -sin(tmp_x_rot_rad);
    tmp_mat_x.m[2][2] = cos(tmp_x_rot_rad);
    tmp_mat_x.m[3][3] = 1;

    tmp_mat_y.m[0][0] = cos(tmp_y_rot_rad);     //The y rotations
    tmp_mat_y.m[0][2] = -sin(tmp_y_rot_rad);
    tmp_mat_y.m[2][2] = 1;
    tmp_mat_y.m[2][0] = sin(tmp_y_rot_rad);
    tmp_mat_y.m[2][2] = cos(tmp_y_rot_rad);
    tmp_mat_y.m[3][3] = 1;

    tmp_mat_z.m[0][0] = cos(tmp_z_rot_rad);     //The y rotations
    tmp_mat_z.m[0][1] = sin(tmp_z_rot_rad);
    tmp_mat_z.m[1][0] = -sin(tmp_z_rot_rad);
    tmp_mat_z.m[1][1] = cos(tmp_z_rot_rad);
    tmp_mat_z.m[2][2] = 1;
    tmp_mat_z.m[3][3] = 1;

    mat_localRotation = tmp_mat_x * tmp_mat_y * tmp_mat_z;

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

    mat_localPosition.m[0][4] = localPosition.x;
    mat_localPosition.m[1][4] = localPosition.y;
    mat_localPosition.m[2][4] = localPosition.z;

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

    mat_localPosition.m[0][4] = localPosition.x;
    mat_localPosition.m[1][4] = localPosition.y;
    mat_localPosition.m[2][4] = localPosition.z;

    return 0;
}

int Camera::goLeft(float movement_ammount)
{
    float y_rotation_radians;
                                                                                //Change degrees to radians, and reverse sign.
    y_rotation_radians = -((localRotation.y/180) * PI);                         //This is necessary because the camera rotations are reversed compared to objects, and we store the rotations like an object.

    localPosition.x -= float(movement_ammount * cos(y_rotation_radians));        //Fid the x component of the movement
    localPosition.z -= float(movement_ammount * sin(y_rotation_radians));        //Find the z component of the movement

    mat_localPosition.m[0][4] = localPosition.x;
    mat_localPosition.m[1][4] = localPosition.y;

    return 0;
}

int Camera::goRight(float movement_ammount)
{
    float y_rotation_radians;
                                                                                //Change degrees to radians, and reverse sign.
    y_rotation_radians = -((localRotation.y/180) * PI);                         //This is necessary because the camera rotations are reversed compared to objects, and we store the rotations like an object.

    localPosition.x += float(movement_ammount * cos(y_rotation_radians));        //Fid the x component of the movement
    localPosition.z += float(movement_ammount * sin(y_rotation_radians));        //Find the z component of the movement

    mat_localPosition.m[0][4] = localPosition.x;
    mat_localPosition.m[1][4] = localPosition.y;

    return 0;
}

} //End Namespace
