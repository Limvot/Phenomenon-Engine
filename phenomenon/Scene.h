#ifndef SCENE_H
#define SCENE_H
#include <string>
#include <stdlib.h>

#define NO_SDL_GLEXT

#include <GL/glew.h>
#include "SDL.h"
//#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)

//Includes from with in engine
#include "Node.h"
#include "PhysicsManager.h"
#include "Light.h"
#include "Material.h"
#include "Texture.h"
#include "DataTypes.h"      //Also includes ExpandableArray.h
#include "Renderer.h"

namespace phen {

class Scene
{
    public:
        Scene();
        virtual ~Scene();
        int draw(Renderer* renderer);
        Node* getRootNode();
        PhysicsManager* getPhysicsManager();
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

        Shader* newShader(std::string shader_name);
        Shader* findShader(std::string shader_name);
        int deleteShader(std::string shader_name);

    protected:
    private:
        Node rootNode;
        PhysicsManager physicsManager;

        ExpandableArray<Light*> LightArray;
        GLuint numLights;
        Light* tmp_light;
        Vector tmpGlobalLightPosition;
        GLfloat tmpLightPosition[4];

        ExpandableArray<Material*> MaterialArray;
        GLuint numMaterials;

        ExpandableArray<Texture*> TextureArray;
        GLuint numTextures;

        ExpandableArray<Shader*> ShaderArray;
        GLuint numShaders;
};

} //End Namespace

#endif // SCENE_H
