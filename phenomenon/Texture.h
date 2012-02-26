#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"
#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)
#include "stdlib.h"
#include <iostream>
#include <string>

using namespace std;

class Texture
{
    public:
        Texture();
        Texture(string tmp_name);
        virtual ~Texture();

        int load(string);
        int bind();

        string name;
        SDL_Surface* texture_image[1];
        GLuint texture_id[1];
    protected:
    private:
};

#endif // TEXTURE_H
