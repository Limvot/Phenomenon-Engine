#ifndef LIGHT_H
#define LIGHT_H

#include "Node.h"
#include "DataTypes.h"

namespace phen {

class Light: public Node
{
    public:
        Light(std::string);
        virtual ~Light();
        int draw();
        int setAmbient(float,float,float);
        int setDiffuse(float,float,float);

        GLfloat LightAmbient[4];    //Light settings
        GLfloat LightDiffuse[4];

    protected:
    private:
};

} //End Namespace

#endif // LIGHT_H
