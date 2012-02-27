#ifndef MATERIAL_H
#define MATERIAL_H

#include "SDL.h"
#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)
#include "stdlib.h"
#include <string>

#include "Texture.h"        //For textured materials

using namespace std;

class Material
{
    public:
        Material();
        Material(string tmp_name);
        virtual ~Material();

        int setDiffuse(float,float,float);
        int setSpecular(float,float,float);
        int setSpecularHardness(float);
        int setTexture(Texture*);
        int bindTexture();

        string name;
        GLfloat diffuse[3];    //Material settings
        GLfloat specular[3];
        GLfloat specularHardness[1];
        Texture* material_texture;

    protected:
    private:
};

#endif // MATERIAL_H
