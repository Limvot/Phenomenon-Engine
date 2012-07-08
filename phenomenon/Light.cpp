#include "Light.h"

namespace phen {

Light::Light(std::string tmp_name)                                               //Please note that the Light inherets the Node class, and all of its node releated functions.
{

    name = tmp_name;                                                        //Rest of init is taken care of by the Node constructor
    LightAmbient[0] = 0.5f;
    LightAmbient[1] = 0.5f;
    LightAmbient[2] = 0.5f;
    LightAmbient[3] = 1.0f;

    LightDiffuse[0] = 1.0f;
    LightDiffuse[1] = 1.0f;
    LightDiffuse[2] = 1.0f;
    LightDiffuse[3] = 1.0f;
}

Light::~Light()
{

}

int Light::draw(Renderer* renderer)
{
    if (numChildren > 0)                                                    //If we have children, go through and draw them
    {
        for (int i = 0; i < numChildren;)
        {
            if (children.getArrayMember(i) != NULL)
                children.getArrayMember(i)->draw(renderer);
            i += 1;
        }
    }

    return 0;
}

int Light::setAmbient(float r, float g, float b)
{
    LightAmbient[0] = r;
    LightAmbient[1] = g;
    LightAmbient[2] = b;

    return 0;
}

int Light::setAmbient(Color3f ambient_in)
{
    LightAmbient[0] = ambient_in.r;
    LightAmbient[1] = ambient_in.g;
    LightAmbient[2] = ambient_in.b;

    return 0;
}

int Light::setDiffuse(float r, float g, float b)
{
    LightDiffuse[0] = r;
    LightDiffuse[1] = g;
    LightDiffuse[2] = b;

    return 0;
}

int Light::setDiffuse(Color3f diffuse_in)
{
    LightDiffuse[0] = diffuse_in.r;
    LightDiffuse[1] = diffuse_in.g;
    LightDiffuse[2] = diffuse_in.b;

    return 0;
}

Color3f Light::getAmbient()
{
    return Color3f(LightAmbient[0], LightAmbient[1], LightAmbient[2]);
}

Color3f Light::getDiffuse()
{
    return Color3f(LightDiffuse[0], LightDiffuse[1], LightDiffuse[2]);
}

} //End Namespace
