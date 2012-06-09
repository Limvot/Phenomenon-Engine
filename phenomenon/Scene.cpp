#include "Scene.h"

namespace phen {

Scene::Scene()
{
    numLights = 0;
    numMaterials = 0;
    numTextures = 0;
    numShaders = 0;
    tmp_light = NULL;
}

Scene::~Scene()
{
    if (numMaterials > 0)
    {
        for (GLuint i = 0; i < numMaterials; i++)
        {
            if (MaterialArray.getArrayMember(i) != NULL)
            {
                delete MaterialArray.getArrayMember(i);
                MaterialArray.setArrayMember(i, NULL);
            }
        }
        numMaterials = 0;
    }

    if (numTextures > 0)
    {
        for (GLuint i = 0; i < numTextures; i++)
        {
            if (TextureArray.getArrayMember(i) != NULL)
            {
                delete TextureArray.getArrayMember(i);
                TextureArray.setArrayMember(i, NULL);
            }
        }
        numTextures = 0;
    }

    if (numShaders > 0)
    {
        for (GLuint i = 0; i < numShaders; i++)
        {
            if (ShaderArray.getArrayMember(i) != NULL)
            {
                delete ShaderArray.getArrayMember(i);
                ShaderArray.setArrayMember(i, NULL);
            }
        }
        numShaders = 0;
    }
}

int Scene::draw(Renderer* renderer)
{
    GLenum current_light;

    for (GLuint i = 0; i < numLights; i++)
    {
        if (LightArray.getArrayMember(i) != NULL)
        {
            tmpGlobalLightPosition = LightArray.getArrayMember(i)->getGlobalPosition();
            tmpLightPosition[0] = tmpGlobalLightPosition.x;
            tmpLightPosition[1] = tmpGlobalLightPosition.y;
            tmpLightPosition[2] = tmpGlobalLightPosition.z;
            tmpLightPosition[3] = 1.0f;                                                         //What does this do?

            current_light = GL_LIGHT0 + i;                                                      //Is a GLenum, so since we're zero indexed, just add our offset to the base GL_LIGHT
            glLightfv(current_light, GL_AMBIENT, LightArray.getArrayMember(i)->LightAmbient);
            glLightfv(current_light, GL_DIFFUSE, LightArray.getArrayMember(i)->LightDiffuse);
            glLightfv(current_light, GL_POSITION, tmpLightPosition);
            glEnable(current_light);
        }

    }
    rootNode.draw(renderer);
    return 0;
}

Node* Scene::getRootNode()
{
    return &rootNode;
}

PhysicsManager* Scene::getPhysicsManager()
{
    return &physicsManager;
}

Light* Scene::newLight(std::string light_name)
{
    if (numLights >= 8)
        return NULL;                                        //We can't have more than 8 OpenGL lights

    tmp_light = new Light(light_name);
    LightArray.addArrayMember(tmp_light);
    rootNode.addChild(dynamic_cast<Node*>(tmp_light));      //Add our new light to rootNode by default.
    numLights += 1;
    return tmp_light;
}

Light* Scene::findLight(std::string light_name)
{
    if (numLights > 0)
    {
        for (GLuint i = 0; i < numLights; i++)
        {
            if (LightArray.getArrayMember(i)->name == light_name)
                return LightArray.getArrayMember(i);
        }

        return NULL;   //We couldn't find the light, return NULL
    }

    return NULL;       //We have no lights, return NULL
}

int Scene::deleteLight(std::string light_name)
{
    if (numLights > 0)
    {
        for (GLuint i = 0; i < numLights; i++)
        {
            if (LightArray.getArrayMember(i)->name == light_name)
            {
                delete LightArray.getArrayMember(i);
                LightArray.setArrayMember(i, NULL);
                return 0;
            }
        }

        return 1;   //We couldn't find the light, return 1
    }
    return 1;       //No lights
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

Material* Scene::newMaterial(std::string mat_name)
{
    Material* new_mat = new Material(mat_name);
    MaterialArray.addArrayMember(new_mat);
    numMaterials += 1;
    return new_mat;
}

Material* Scene::findMaterial(std::string mat_name)
{
    if (numMaterials > 0)
    {
        for (GLuint i = 0; i < numMaterials; i++)
        {
            if (MaterialArray.getArrayMember(i)->name == mat_name)
                return MaterialArray.getArrayMember(i);
        }

        return NULL;
    }
    return NULL;
}

int Scene::deleteMaterial(std::string mat_name)
{
    if (numMaterials > 0)
    {
        for (GLuint i = 0; i < numMaterials; i++)
        {
            if (MaterialArray.getArrayMember(i)->name == mat_name)
            {
                delete MaterialArray.getArrayMember(i);
                MaterialArray.setArrayMember(i, NULL);
                return 0;
            }
        }
        return 1;               //Couldn't find material
    }
    return 1;                   //No materials
}


Texture* Scene::newTexture(std::string tex_name)
{
    Texture* new_tex = new Texture(tex_name);
    TextureArray.addArrayMember(new_tex);
    numTextures += 1;
    return new_tex;
}

Texture* Scene::findTexture(std::string tex_name)
{
    if (numTextures > 0)
    {
        for (GLuint i = 0; i < numTextures; i++)
        {
            if (TextureArray.getArrayMember(i)->name == tex_name)
                return TextureArray.getArrayMember(i);
        }

        return NULL;
    }
    return NULL;
}

int Scene::deleteTexture(std::string tex_name)
{
    if (numTextures > 0)
    {
        for (GLuint i = 0; i < numTextures; i++)
        {
            if (TextureArray.getArrayMember(i)->name == tex_name)
            {
                delete TextureArray.getArrayMember(i);
                TextureArray.setArrayMember(i, NULL);
                return 0;
            }
        }
        return 1;               //Couldn't find texture
    }
    return 1;                   //No textures
}

Shader* Scene::newShader(std::string shader_name)
{
    Shader* new_shader = new Shader(shader_name);
    ShaderArray.addArrayMember(new_shader);
    numShaders += 1;
    return new_shader;
}

Shader* Scene::findShader(std::string shader_name)
{
    if (numShaders > 0)
    {
        for (GLuint i = 0; i < numShaders; i++)
        {
            if (ShaderArray.getArrayMember(i)->name == shader_name)
                return ShaderArray.getArrayMember(i);
        }

        return NULL;
    }
    return NULL;
}

int Scene::deleteShader(std::string shader_name)
{
    if (numShaders > 0)
    {
        for (GLuint i = 0; i < numShaders; i++)
        {
            if (ShaderArray.getArrayMember(i)->name == shader_name)
            {
                delete ShaderArray.getArrayMember(i);
                ShaderArray.setArrayMember(i, NULL);
                return 0;
            }
        }
        return 1;               //Couldn't find shader
    }
    return 1;                   //No shaders
}

} //End Namespace


