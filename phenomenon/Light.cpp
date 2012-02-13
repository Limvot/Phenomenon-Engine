#include "Light.h"

int Light::lightIndex = 0;

Light::Light(string tmp_name)                                                        //Please note that the Light inherets the Node class, and all of its node releated functions.
{
    lightIndex++;                               //Update our light index

    name = tmp_name;                            //Rest of init is taken care of by the Node constructor
    LightAmbient[0] = 0.5f;
    LightAmbient[1] = 0.5f;
    LightAmbient[2] = 0.5f;
    LightAmbient[3] = 1.0f;

    LightDiffuse[0] = 1.0f;
    LightDiffuse[1] = 1.0f;
    LightDiffuse[2] = 1.0f;
    LightDiffuse[3] = 1.0f;

    update();
    enable();
}

Light::~Light()
{

}

int Light::draw()
{

    if (numChildren > 0)                                                    //If we have children, go through and draw them
    {
        for (int i = 0; i < numChildren;)
        {
            children.getArrayMember(i)->draw();
            i += 1;
        }
    }

    return 0;
}

int Light::update()
{
    getGlobalPosition();
    LightPosition[0] = globalPosition.x;
    LightPosition[1] = globalPosition.y;
    LightPosition[2] = globalPosition.z;
    LightPosition[3] = 1.0f;

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);

    return 0;
}

int Light::enable()
{
    glEnable(GL_LIGHT1);

    return 0;
}
