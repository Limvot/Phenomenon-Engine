#ifndef GBUFFER_H
#define GBUFFER_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define NO_SDL_GLEXT

#include <GL/glew.h>
#include "SDL.h"
//#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)


namespace phen {

class GBuffer
{
    public:

        enum GBUFFER_TEXTURE_TYPE {
            GBUFFER_TEXTURE_TYPE_POSITION,
            GBUFFER_TEXTURE_TYPE_DIFFUSE,
            GBUFFER_TEXTURE_TYPE_NORMAL,
            GBUFFER_TEXTURE_TYPE_TEXCOORD,
            GBUFFER_NUM_TEXTURES
            };

        GBuffer();
        virtual ~GBuffer();
        int init(GLuint width_in, GLuint height_in);
        void bindForWriting();
        void bindForReading();
        void setReadBuffer(GBUFFER_TEXTURE_TYPE textureType);

        GLuint frameBuffer;
        GLuint textures[GBUFFER_NUM_TEXTURES];
        GLuint depthTexture;
        //GLenum DrawBuffers[];

        GLuint width;
        GLuint height;
    protected:
};

} //End Namespace

#endif // GBUFFER_H
