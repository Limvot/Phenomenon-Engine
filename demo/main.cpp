/*
This is main.cpp, a demo file for the phenomenon engine. It will start the engine and run some sort of demo.
It is an ideal base and tutorial for using phenomenon.
It is also the main method of testing and experementing with the engine.
One important part to notice is that this file uses the SDL_Event system, and passes events that it doesn't handle to the engine.
This is important, as the engine uses it to handle window resize and window loss of focus.
*/

#include <iostream>
#include "demo.cpp"
using namespace std;


int main(int argc, char* argv[])
{
    //freopen("CON", "w", stdout);                                //Don't let SDL redirect the standard output to a file
    //freopen("CON", "w", stderr);                                //Same for standard errors`

    Demo* game = new Demo;

    game->start();

    return 0;
}
