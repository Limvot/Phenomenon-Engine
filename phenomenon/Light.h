#ifndef LIGHT_H
#define LIGHT_H

#include "Node.h"
#include "DataTypes.h"
#include "Renderer.h"

namespace phen {

class Light: public Node
{
    public:
        Light(std::string);
        virtual ~Light();
        int draw(Renderer* renderer);
        int setAmbient(float,float,float);
        int setAmbient(Color3f ambient_in);
        int setDiffuse(float,float,float);
        int setDiffuse(Color3f diffuse_in);

        GLfloat LightAmbient[4];    //Light settings
        GLfloat LightDiffuse[4];

    protected:
    private:
};

} //End Namespace

#endif // LIGHT_H
