#ifndef MATERIAL_H
#define MATERIAL_H

#define NO_SDL_GLEXT

#include <GL/glew.h>
#include "SDL.h"
#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)
#include "stdlib.h"
#include <string>

#include "DataTypes.h"      //For Color3f
#include "Texture.h"        //For textured materials
#include "Shader.h"         //For materials with shaders

namespace phen {

class Material
{
    public:
        Material();
        Material(std::string tmp_name);
        virtual ~Material();

        int setDiffuse(float r, float g, float b);
        int setDiffuse(Color3f* set_color);
        int setSpecular(float r, float g,float b);
        int setSpecular(Color3f* set_color);
        int setSpecularHardness(float hardness);
        int setTexture(Texture* set_tex);
        int bindTexture();
        int setShader(Shader* set_shader);

        std::string name;
        GLfloat diffuse[3];    //Material settings
        GLfloat specular[3];
        GLfloat specularHardness[1];
        Texture* material_texture;
        Shader* material_shader;

    protected:
    private:
};

} //End Namespace

#endif // MATERIAL_H
