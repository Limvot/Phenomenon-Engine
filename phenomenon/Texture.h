#ifndef TEXTURE_H
#define TEXTURE_H

#define NO_SDL_GLEXT

#include <GL/glew.h>
#include "SDL.h"
#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)
#include "stdlib.h"
#include <iostream>
#include <string>

#include "../extern/stb_image.h"

namespace phen {

class Texture
{
    public:
        Texture();
        Texture(std::string tmp_name);
        virtual ~Texture();

        int assignGLid(GLuint);             //Used if not using the load function- the texture has already been loaded by user/library/some other part of phenomenon.
        int load(std::string file_path, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_LINEAR);
        int bind();

        std::string name;
        GLuint texture_id[1];
    protected:
    private:
};

} //End Namespace

#endif // TEXTURE_H
