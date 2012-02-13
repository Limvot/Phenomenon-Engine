#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

#include "Scene.h"
#include "Node.h"
#include "DataTypes.h"

#ifndef PI
#define PI 3.141592654f
#endif

class Camera: public Node
{
    public:
        Camera(string);
        virtual ~Camera();
        int draw();
        int drawScene(Scene*);
        int rotate(float,float,float);
        int goForward(float);
        int goBackward(float);
        int goLeft(float);
        int goRight(float);
    protected:
    private:
};

#endif // CAMERA_H
