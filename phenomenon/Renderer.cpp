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

int Renderer::init(GLuint width_in, GLuint height_in, GLfloat gamma_in)
{
    width = width_in;
    height = height_in;

    G_Buffer.init(width, height);                       //Init our GBuffer

    setGamma(gamma_in);

    FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);

    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

    glGenTextures(1, &renderedTexture);


    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, 0);

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
    gammaID = glGetUniformLocation(quad_shader->getShader(), "gamma_divided");
    timeID = glGetUniformLocation(quad_shader->getShader(), "time");

    return 0;
}

int Renderer::setGamma(GLfloat gamma_in)
{
    gamma_divided = 1/gamma_in;
    return 0;
}

int Renderer::geometryPass(Scene* scene)
{
    G_Buffer.bindForWriting();
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    scene->draw(this);

    return 0;
}

int Renderer::lightingPass()
{
    G_Buffer.bindForReading();

    GLsizei HalfWidth = (GLsizei)(width/2.0f);
    GLsizei HalfHeight = (GLsizei)(height/2.0f);

    G_Buffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
    glBlitFramebuffer(0, 0, width, height, 0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    G_Buffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
    glBlitFramebuffer(0, 0, width, height, 0, HalfHeight, HalfWidth, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    G_Buffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    glBlitFramebuffer(0, 0, width, height, HalfWidth, HalfHeight, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    G_Buffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_TEXCOORD);
    glBlitFramebuffer(0, 0, width, height, HalfWidth, 0, width, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

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

    //Here is the defferd rendering part
    geometryPass(scene);

    //Bind the framebuffer that the lighting pass will render into, used for post-processing
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);     //Bind the framebuffer that is written to for post-processing
    glViewport(0, 0, width, height);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Now do the lighting
    lightingPass();
    //End deffered rendering

    glBindFramebuffer(GL_FRAMEBUFFER, 0);                   //Render the post-processing to screen
    glViewport(0, 0, width, height);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(quad_shader->getShader());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);

    glUniform1i(texID, 0);
    glUniform1f(gammaID, gamma_divided);
    glUniform1f(timeID, float(SDL_GetTicks()/100));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, (void*)12);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindTexture(GL_TEXTURE_2D, 0);


    return 0;
}

} //End namespace
