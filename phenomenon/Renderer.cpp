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
    screen_size.set(width_in, height_in);

    G_Buffer.init(screen_size.x, screen_size.y);                       //Init our GBuffer

    setGamma(gamma_in);

    FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);

    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

    glGenTextures(1, &renderedTexture);


    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, screen_size.x, screen_size.y, 0, GL_RGB, GL_FLOAT, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screen_size.x, screen_size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);


    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);

    DrawBuffers[0] = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return false;

    return true;
}

int Renderer::initQuad()
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

    return 0;
}

int Renderer::initLighting(Shader* shader_in)
{
    light_shader = shader_in;
    light_position_textureID = glGetUniformLocation(light_shader->getShader(), "position_worldspace");
    light_diffuse_textureID = glGetUniformLocation(light_shader->getShader(), "diffuse");
    light_normal_textureID = glGetUniformLocation(light_shader->getShader(), "normal_worldspace");
    light_screen_sizeID = glGetUniformLocation(light_shader->getShader(), "screenSize");
    light_colorID = glGetUniformLocation(light_shader->getShader(), "LightColor");
    light_powerID = glGetUniformLocation(light_shader->getShader(), "LightPower");
    light_positionID = glGetUniformLocation(light_shader->getShader(), "LightPosition");
    camera_positionID = glGetUniformLocation(light_shader->getShader(), "CameraPosition");

    return 0;
}

int Renderer::initPostProcess(Shader* shader_in)
{
    post_shader = shader_in;
    texID = glGetUniformLocation(post_shader->getShader(), "renderedTexture");
    gammaID = glGetUniformLocation(post_shader->getShader(), "gamma_divided");
    timeID = glGetUniformLocation(post_shader->getShader(), "time");

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

    glDepthMask(GL_TRUE);  //Only the geometry pass updates the depth buffer

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable(GL_DEPTH_TEST);    //Return to normal
    glDisable(GL_BLEND);        //Ditto

    scene->draw(this);

    glDepthMask(GL_FALSE);      //Light pass does not write to depth buffer
    glDisable(GL_DEPTH_TEST);   //Don't want to test for depth for lighting either

    return 0;
}

int Renderer::beginLightingPass()
{
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

    G_Buffer.bindForReading();
    glClear(GL_COLOR_BUFFER_BIT);

    return 0;
}

int Renderer::lightingPass(Camera* camera, Scene* scene)
{
//*
    G_Buffer.bindForReading();
    glBindFramebuffer(GL_DRAW_BUFFER, FramebufferName);
    glUseProgram(light_shader->getShader());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, G_Buffer.textures[GBuffer::GBUFFER_TEXTURE_TYPE_POSITION]);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, G_Buffer.textures[GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE]);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, G_Buffer.textures[GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL]);

    for (GLuint i = 0; i < scene->numLights; i++)
    {
        glUniform1i(light_position_textureID, GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
        glUniform1i(light_diffuse_textureID, GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
        glUniform1i(light_normal_textureID, GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
        glUniform2f(light_screen_sizeID, screen_size.x, screen_size.y);

        Vector light_position = scene->LightArray.getArrayMember(i)->getGlobalPosition();
        Color3f light_diffuse = scene->LightArray.getArrayMember(i)->getDiffuse();
        camera_position = camera->getGlobalPosition();

        glUniform3f(light_colorID, light_diffuse.r, light_diffuse.g, light_diffuse.b);
        glUniform1f(light_powerID, 1.0f);
        glUniform3f(light_positionID, light_position.x, light_position.y, light_position.z);
        glUniform3f(camera_positionID, camera_position.x, camera_position.y, camera_position.z);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, (void*)12);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    return 0;
}

int Renderer::preparePostProcess()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);     //Bind the framebuffer that is written to for post-processing
    glViewport(0, 0, screen_size.x, screen_size.y);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return 0;
}

int Renderer::postProcess()
{
    std::cout << "Here is renderedTexture: " << renderedTexture << "\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);                   //Render the post-processing to screen
    glViewport(0, 0, screen_size.x, screen_size.y);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(post_shader->getShader());
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
    preparePostProcess();
    //Now do the lighting
    beginLightingPass();
    lightingPass(camera, scene);
    //End deffered rendering
    postProcess();  //Do post-process

    return 0;
}

} //End namespace
