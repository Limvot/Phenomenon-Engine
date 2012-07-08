#include "GBuffer.h"

namespace phen {


GBuffer::GBuffer()
{
}

GBuffer::~GBuffer()
{
    glDeleteFramebuffers(1, &frameBuffer);
    glDeleteTextures(GBUFFER_NUM_TEXTURES, textures);

    glDeleteTextures(1, &depthTexture);
}

int GBuffer::init(GLuint width_in, GLuint height_in)
{
    width = width_in;
    height = height_in;

    frameBuffer = 0;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glGenTextures(GBUFFER_NUM_TEXTURES, textures);
    glGenTextures(1, &depthTexture);

    for (GLuint i = 0; i < GBUFFER_NUM_TEXTURES; i++)
    {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures[i], 0);
    }

    //Depth
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);


    GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };

    glDrawBuffers(sizeof(DrawBuffers)/sizeof(DrawBuffers[0]), DrawBuffers);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "FrameBuffer error, status: " << status << "\n";
        return false;
    }

    // restore default FBO
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

void GBuffer::bindForWriting()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
}

void GBuffer::bindForReading()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
}

void GBuffer::setReadBuffer(GBUFFER_TEXTURE_TYPE textureType)
{
    glReadBuffer(GL_COLOR_ATTACHMENT0 + textureType);
}


} //End namespace
