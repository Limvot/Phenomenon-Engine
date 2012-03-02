#ifndef SCENE_H
#define SCENE_H
#include <string>
#include <stdlib.h>

#define NO_SDL_GLEXT

#include <GL/glew.h>
#include "SDL.h"
#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)

//Includes from with in engine
#include "Node.h"
#include "Light.h"
#include "Material.h"
#include "Texture.h"
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

        Material* newMaterial(string mat_name);
        Material* findMaterial(string mat_name);
        int deleteMaterial(string mat_name);

        Texture* newTexture(string tex_name);
        Texture* findTexture(string tex_name);
        int deleteTexture(string tex_name);

    protected:
    private:
        Node rootNode;
        ExpandableArray<Light*> LightArray;
        Light* tmp_light;
        int numLights;
        Vertex tmpGlobalLightPosition;
        GLfloat tmpLightPosition[4];

        ExpandableArray<Material*> MaterialArray;
        int numMaterials;

        ExpandableArray<Texture*> TextureArray;
        int numTextures;
};

#endif // SCENE_H
