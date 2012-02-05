#ifndef CAMERA_H
#define CAMERA_H

#include "Node.h"
#include "DataTypes.h"

class Camera: public Node
{
    public:
        Camera(string);
        virtual ~Camera();
        int draw();
        int drawScene(Node*);
        int rotate(float,float,float);
        int goForward(float);
        int goBackward(float);
        int goLeft(float);
        int goRight(float);
    protected:
    private:
};

#endif // CAMERA_H
