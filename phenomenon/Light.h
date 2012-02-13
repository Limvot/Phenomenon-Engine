#ifndef LIGHT_H
#define LIGHT_H

#include "Node.h"
#include "DataTypes.h"

class Light: public Node
{
    public:
        Light(string);
        virtual ~Light();
        int draw();
        int update();
        int enable();

        GLfloat LightAmbient[4];    //Light settings
        GLfloat LightDiffuse[4];
        GLfloat LightPosition[4];

        static int lightIndex;

    protected:
    private:
};

#endif // SQUARE_H
