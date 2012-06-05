#ifndef PHEN_WINDOW_H
#define PHEN_WINDOW_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define NO_SDL_GLEXT

#include <GL/glew.h>
#include "SDL.h"
#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)

namespace phen {

class Window {

public:
    Window();

    ~Window();
    void quit();

    GLint create(GLint,GLint,GLint);
    GLint resize(GLint,GLint,GLint,GLint);
    GLint simpleResize(GLint,GLint);
    void handleEvent(SDL_Event*);
    GLint initGL();
    GLint clearScreen();
    GLint swapBuffers();
    GLint getSDLVideoFlags();
    GLint toggleFullScreen();
    GLint setCaption(std::string);
    GLint enableBackfaceCulling();
    GLint disableBackfaceCulling();

    SDL_Surface *surface;
    GLint bpp;
    GLint isActive;           //Whether or not the window is active (focus)

    private:
    GLint videoFlags;

};

} //End Namespace

#endif
