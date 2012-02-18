#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"
#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)
#include "stdlib.h"
#include <string>

using namespace std;

class Texture
{
    public:
        Texture();
        Texture(string tmp_name);
        virtual ~Texture();

        int load(string);

        string name;
        GLuint texture_id;
    protected:
    private:
};

#endif // TEXTURE_H
