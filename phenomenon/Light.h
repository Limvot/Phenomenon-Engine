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

        GLfloat LightAmbient[4];    //Light settings
        GLfloat LightDiffuse[4];

    protected:
    private:
};

#endif // LIGHT_H
