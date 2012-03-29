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

namespace phen {

class Scene
{
    public:
        Scene();
        virtual ~Scene();
        int render();
        Node* getRootNode();
        Light* newLight(std::string light_name);
        Light* findLight(std::string light_name);
        int deleteLight(std::string light_name);
        int enableLighting();
        int disableLighting();

        Material* newMaterial(std::string mat_name);
        Material* findMaterial(std::string mat_name);
        int deleteMaterial(std::string mat_name);

        Texture* newTexture(std::string tex_name);
        Texture* findTexture(std::string tex_name);
        int deleteTexture(std::string tex_name);

    protected:
    private:
        Node rootNode;
        ExpandableArray<Light*> LightArray;
        Light* tmp_light;
        int numLights;
        Vector tmpGlobalLightPosition;
        GLfloat tmpLightPosition[4];

        ExpandableArray<Material*> MaterialArray;
        int numMaterials;

        ExpandableArray<Texture*> TextureArray;
        int numTextures;
};

} //End Namespace

#endif // SCENE_H
