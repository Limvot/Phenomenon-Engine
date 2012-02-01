/*
This is main.cpp, a demo file for the phenomenon engine. It will start the engine and run some sort of demo.
It is an ideal base and tutorial for using phenomenon.
It is also the main method of testing and experementing with the engine.
One important part to notice is that this file uses the SDL_Event system, and passes events that it doesn't handle to the engine.
This is important, as the engine uses it to handle window resizes, window loss of focus, and quit events from the system.
*/

#include <iostream>
#include "phenomenon/Window.h"

using namespace std;

int main()
{
    Window *window;
    window = new Window;

    int done = false;   //Main loop variable
    SDL_Event *event;    //Useed in collecting events
    event = new SDL_Event;

    window->start(640,480,32);                          //Start the engine. Sets up SDL and OpenGL, sets some variables

        while(!done)                                    //Main loop
    {
                                                        //Handle events in queue
        while (SDL_PollEvent(event))
        {
            if (event->type == SDL_KEYDOWN)             //If a key is pressed, we handle it
            {
                switch (event->key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        delete window;
                        window = NULL;
                        break;

                    case SDLK_F1:
                        window->toggleFullScreen();
                        break;

                    default:
                        break;
                }

            } else                                      //If not a keypress, let the engine handle the event. Possibilities include window resize, losing window focus, (X) button being pressed, etc
            {
                window->handleEvent(event);
            }
        } //end while

        window->drawGLScene();                          //Draw the scene! (Note that if the window does not have focus, the engine will not draw.)
    }                                                   //If this is not the desired behavior, it is simple to remove the isActive check in the drawGLScene function.


    delete window;
    window = NULL;

    return 0;
}
