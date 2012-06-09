#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define NO_SDL_GLEXT

#include <GL/glew.h>
#include "SDL.h"
#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)

//Includes from with in engine
#include "DataTypes.h"      //Also includes ExpandableArray.h
#include "Shader.h"
//#include "Camera.h"
//#include "Scene.h"

namespace phen {

class Scene;
class Camera;

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();
        int init(GLuint width_in, GLuint height_in);
        int initQuad(Shader* shader_in);
        int render(Camera* camera, Scene* scene);

        Matrix4f Vmatrix, VPmatrix;

        GLfloat light_position[1][3];
        GLfloat light_color[1][3];
        GLfloat light_power[1];

        GLuint FramebufferName;
        GLuint renderedTexture;
        GLuint depthrenderbuffer;
        GLenum DrawBuffers[2];

        GLuint quad_VertexArrayID;

        GLuint quad_vertexbuffer;
        Shader* quad_shader;
        GLuint texID;
        GLuint timeID;

        GLuint width;
        GLuint height;
    protected:
};

} //End Namespace

#endif // RENDERER_H