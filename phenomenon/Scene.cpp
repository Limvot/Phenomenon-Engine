#include "Scene.h"

Scene::Scene()
{
    numLights = 0;
    tmp_light = NULL;
}

Scene::~Scene()
{
    if (numLights > 0)
    {
        for (int i = 0; i< numLights;)
        {
            delete LightArray.getArrayMember(i);
            i += 1;
        }
        numLights = 0;
    }
}

int Scene::render()
{
    GLenum current_light;

    for (int i = 0; i < numLights; i +=1)
    {
        tmpGlobalLightPosition = LightArray.getArrayMember(i)->getGlobalPosition();
        tmpLightPosition[0] = tmpGlobalLightPosition.x;
        tmpLightPosition[1] = tmpGlobalLightPosition.y;
        tmpLightPosition[2] = tmpGlobalLightPosition.z;
        tmpLightPosition[3] = 1.0f;                         //What does this do?


                                ///////////ADD MULTIPLE LIGHT SUPPORT
        current_light = GL_LIGHT0 + i;
        glLightfv(current_light, GL_AMBIENT, LightArray.getArrayMember(i)->LightAmbient);
        glLightfv(current_light, GL_DIFFUSE, LightArray.getArrayMember(i)->LightDiffuse);
        glLightfv(current_light, GL_POSITION, tmpLightPosition);
        glEnable(current_light);

    }
    rootNode.draw();
    return 0;
}

Node* Scene::getRootNode()
{
    return &rootNode;
}

Light* Scene::newLight(string light_name)
{
    if (numLights >= 8)
        return NULL;                        //We can't have more than 8 OpenGL lights


    tmp_light = new Light(light_name);
    LightArray.addArrayMember(tmp_light);
    numLights += 1;
    return tmp_light;
}

Light* Scene::findLight(string light_name)
{
    if (numLights > 0)
    {
        for (int i = 0; i < numLights; i++)
        {
            if (LightArray.getArrayMember(i)->name == light_name)
                return LightArray.getArrayMember(i);
        }

        return NULL;   //We couldn't find the light, return NULL
    }

    return NULL;       //We have no lights, return NULL
}

int Scene::deleteLight(string light_name)
{
    tmp_light = findLight(light_name);

    if (tmp_light != NULL)
    {
        delete tmp_light;
        tmp_light = NULL;
        return 0;               //Sucess
    }
    return 1;                   //Failure
}

int Scene::enableLighting()
{
    glEnable(GL_LIGHTING);
    return 0;
}

int Scene::disableLighting()
{
    glDisable(GL_LIGHTING);
    return 0;
}

