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

    int create(int,int,int);
    int resize(int,int,int,int);
    void handleEvent(SDL_Event*);
    int initGL();
    int clearScreen();
    int swapBuffers();
    int getSDLVideoFlags();
    int toggleFullScreen();
    int setCaption(std::string);

    SDL_Surface *surface;
    int bpp;
    int isActive;           //Whether or not the window is active (focus)

    private:
    int videoFlags;

};

} //End Namespace

#endif
