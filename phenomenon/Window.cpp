#include "Window.h"


Window::Window() {
//Constructor

}

Window::~Window() {
//Destructor
    quit();
}

void Window::quit()
{
    SDL_Quit();
    exit(0);
}
int Window::start(int width, int height, int inputBPP)
{
    bpp = inputBPP;
    isActive = true;    //Set to true when starting, since we should have focus. (Whether or not the window is active (focus))

    videoFlags = 0; //Init varible from Window.h

    if (SDL_Init( SDL_INIT_VIDEO) < 0)
    {
        cout<< "SDL video init failed: " << SDL_GetError() << endl;
        delete this;
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);        //Set up double buffering

    surface = SDL_SetVideoMode(width, height, bpp, getSDLVideoFlags()); //Get a surface

    if (!surface)               //Make sure we have a surface
    {
        cout << "SDL surface set video mode failed: " << SDL_GetError() << endl;
        delete this;
    }

    if (initGL() == false)      //Init OpenGL
    {
        cout << "OpenGL initilazation failed" << endl;
        delete this;
    }

    resize(width, height, bpp, getSDLVideoFlags());   //Resize the inital window

    return (0);                                       //Done starting up
}

int Window::getSDLVideoFlags()
{
    //Note that videoFlags already exists from Window.h
    if (videoFlags != 0)
    {
        return videoFlags; //If we've already done this once, just return what we did
    }
    const SDL_VideoInfo *videoInfo;      //Holds info about display

    videoInfo = SDL_GetVideoInfo();

    if (!videoInfo)
    {
        cout << "SDL video info query failed: " << SDL_GetError() << endl;
        delete this;
    }

    //Get all the flags to pass to SDL_SetVideoMode/resize
    videoFlags = SDL_OPENGL;                //Enable OpenGL in SDL
    videoFlags |= SDL_GL_DOUBLEBUFFER;      //Enable double buffering
    videoFlags |= SDL_HWPALETTE;            //Store palette in hardware
    videoFlags |= SDL_RESIZABLE;            //Enable window resizing

    if (videoInfo->hw_available)            //Store surfaces in memory if we can
        videoFlags |= SDL_HWSURFACE;
    else
        videoFlags |= SDL_SWSURFACE;

    if (videoInfo->blit_hw)                 //If hardware blits can be done, do them
        videoFlags |= SDL_HWACCEL;

    return videoFlags;

}


int Window::resize(int width, int height, int bpp, int videoFlags) {

    surface = SDL_SetVideoMode(width, height, bpp, videoFlags);    //Change SDL window

    if (!surface)                                                 //Make sure we still have a surface
    {
        cout << "Could not get a surface after resize: " << SDL_GetError();
        delete this;
    }

    GLfloat ratio;

    if (height == 0) {height = 1;}                                 //no devide by zero

    ratio = (GLfloat)width / (GLint)height;             // Find ratio

    glViewport( 0, 0, (GLint)width, (GLint)height );    //Setup viewport

    glMatrixMode(GL_PROJECTION);                        //Change to the projection matrix and set our viewing volume.
    glLoadIdentity();


    gluPerspective(45.0f, ratio, 0.1f, 100.0f);         //Set up perspective

    glMatrixMode(GL_MODELVIEW);                         //Make sure changing model view, not projection

    glLoadIdentity();

    return(true);
}


void Window::handleEvent(SDL_Event* event) {

    switch(event->type)
    {
        case SDL_ACTIVEEVENT:
            //Somthing has happend to the focus.
            //If we lose focus or are iconified, we shouldn't draw the screen
            //Thus, we set the isActive varible to false, and the draw function won't draw.
            if (event->active.gain == 0)
                isActive = false;
            else
                isActive = true;
            break;

        case SDL_VIDEORESIZE:
            //Handle resize
            resize(event->resize.w, event->resize.h, bpp, getSDLVideoFlags());
            break;

        case SDL_QUIT:          //If the sdl/operating system/window manager wants us to quit, quit. (ie, (X) button on window pressed)
            delete this;
            break;

        default:
            break;
    }

    return;
}


int Window::initGL()
{
    glShadeModel (GL_SMOOTH);                           //Smooth Shadeing

    glClearColor(0, 0, 0, 0);                           //Set background black

    glClearDepth(1.0f);                                 //Depth buffer setup

    glEnable(GL_DEPTH_TEST);                            //Enable depth testing

    glDepthFunc (GL_LEQUAL);                            //Type of depth test to do

    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //Good perspective calculations

    return(true);

}

int Window::clearScreen()
{
    if (!isActive)                                      //If we don't have focus, don't draw.
        return 0;

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear screen and depth buffer

    glLoadIdentity();

    return 0;
}

int Window::swapBuffers()
{
    SDL_GL_SwapBuffers();                               //Display on screen
    return 0;
}

int Window::toggleFullScreen()
{
    SDL_WM_ToggleFullScreen(surface);                   //If toggle fullscreen function called, toggle full screen.
    return 0;
}
