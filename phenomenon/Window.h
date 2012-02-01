#ifndef PHEN_WINDOW_H
#define PHEN_WINDOW_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)

using namespace std;




class Window {

public:
    Window();

    ~Window();

    int start(int,int,int);
    int resize(int,int,int,int);
    void handleEvent(SDL_Event*);
    int initGL();
    int drawGLScene();
    int getSDLVideoFlags();
    int toggleFullScreen();

    SDL_Surface *surface;
    int bpp;
    int isActive;           //Whether or not the window is active (focus)

    private:
    int videoFlags;

};

#endif
