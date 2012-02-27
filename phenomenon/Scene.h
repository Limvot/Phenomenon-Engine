#ifndef SCENE_H
#define SCENE_H
#include <string>
//#include <stdlib.h>
//#include "SDL.h"
//#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)

//Includes from with in engine
#include "Node.h"
#include "Light.h"
#include "DataTypes.h"      //Also includes ExpandableArray.h

using std::string;

class Scene
{
    public:
        Scene();
        virtual ~Scene();
        int render();
        Node* getRootNode();
        Light* newLight(string light_name);
        Light* findLight(string light_name);
        int deleteLight(string light_name);
        int enableLighting();
        int disableLighting();

    protected:
    private:
        Node rootNode;
        ExpandableArray<Light*> LightArray;
        Light* tmp_light;
        int numLights;
        Vertex tmpGlobalLightPosition;
        GLfloat tmpLightPosition[4];
};

#endif // SCENE_H
