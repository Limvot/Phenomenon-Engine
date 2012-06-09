#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <math.h>

#include "Scene.h"
#include "Node.h"
#include "DataTypes.h"

#ifndef PI
#define PI 3.141592654f
#endif

namespace phen {

class Camera: public Node
{
    public:
        Camera();
        Camera(std::string);
        //Destructor is inhereted
        int setProjectionMatrix(GLuint width, GLuint height, GLfloat FOV, GLfloat zNear, GLfloat zFar);
        int setProjectionMatrix(GLfloat aspectRatio, GLfloat FOV, GLfloat zNear, GLfloat zFar);
        Matrix4f getViewMatrix();
        Matrix4f getProjectionMatrix();
        int rotate(float,float,float);
        int goForward(float);
        int goBackward(float);
        int goLeft(float);
        int goRight(float);

        Matrix4f viewMatrix;
        Matrix4f projectionMatrix;
    protected:
    private:
};

} //End Namespace

#endif // CAMERA_H
