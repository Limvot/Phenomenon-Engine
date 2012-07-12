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
        int setSpecular(float,float,float);
        int setSpecular(Color3f specular_in);
        int setPower(GLfloat power_in);
        Color3f getAmbient();
        Color3f getDiffuse();
        Color3f getSpecular();
        GLfloat getPower();

        GLfloat LightAmbient[4];    //Light settings
        GLfloat LightDiffuse[4];
        GLfloat LightSpecular[4];
        GLfloat LightPower;

    protected:
    private:
};

} //End Namespace

#endif // LIGHT_H
