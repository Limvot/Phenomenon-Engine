#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"
namespace phen {

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
    glDeleteFramebuffers(1, &FramebufferName);
    glDeleteTextures(1, &renderedTexture);
    glDeleteRenderbuffers(1, &depthrenderbuffer);
    glDeleteBuffers(1, &quad_vertexbuffer);
    glDeleteVertexArrays(1, &quad_VertexArrayID);
}

int Renderer::init(GLuint width_in, GLuint height_in)
{
    width = width_in;
    height = height_in;

    FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);

    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

    glGenTextures(1, &renderedTexture);


    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);


    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);

    DrawBuffers[0] = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return false;

    return true;
}

int Renderer::initQuad(Shader* shader_in)
{
    static const GLfloat g_quad_vertex_buffer_data[] = {
         1.0f, -1.0f, 0.0f,     1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,     0.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,     0.0f, 1.0f,
         1.0f, -1.0f, 0.0f,     1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,     0.0f, 1.0f,
         1.0f,  1.0f, 0.0f,     1.0f, 1.0f
    };

    glGenVertexArrays(1, &quad_VertexArrayID);
    glBindVertexArray(quad_VertexArrayID);

    glGenBuffers(1, &quad_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

    quad_shader = shader_in;
    texID = glGetUniformLocation(quad_shader->getShader(), "renderedTexture");
    timeID = glGetUniformLocation(quad_shader->getShader(), "time");

    return 0;
}

int Renderer::render(Camera* camera, Scene* scene)
{
    light_position[0][0] = 0;
    light_position[0][1] = 1;
    light_position[0][2] = 1;

    light_color[0][0] = 1;
    light_color[0][1] = 1;
    light_color[0][2] = 1;

    light_power[0] = 10;

    Vmatrix = camera->getViewMatrix();
    VPmatrix = camera->getProjectionMatrix() * Vmatrix;

    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);     //Bind the framebuffer
    glViewport(0, 0, width, height);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->draw(this);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);                   //Render to screen
    glViewport(0, 0, width, height);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(quad_shader->getShader());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);

    glUniform1i(texID, 0);
    glUniform1f(timeID, float(SDL_GetTicks()/100));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, (void*)12);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);


    return 0;
}

} //End namespace
