/*
This is main.cpp, a demo file for the phenomenon engine. It will start the engine and run some sort of demo.
It is an ideal base and tutorial for using phenomenon.
It is also the main method of testing and experementing with the engine.
One important part to notice is that this file uses the SDL_Event system, and passes events that it doesn't handle to the engine.
This is important, as the engine uses it to handle window resizes, window loss of focus, and quit events from the system.
*/

#include <iostream>
#include "phenomenon/Window.h"
#include "phenomenon/Node.h"
#include "phenomenon/Triangle.h"
#include "phenomenon/Square.h"

using namespace std;

int main()
{
    Node rootNode;                                     //All objects are represented with nodes. Basic nodes can be used to group together other nodes. This node is the root node.
    Node* childNode = new Triangle;                    //The Triangle class inherets the Node class, but draws a triangle on draw().
    Node* childNode2 = new Square;                     //Same with the Square class, but it draws a square.

    rootNode.addChild(childNode);
    childNode->addChild(childNode2);

    rootNode.setLocalPosition(0.0f, 0.0f, -6.0f);        //This is to show that position is inhereted from parent to child. The childNode will end up with a position of 1.0, 0.0, -6.0.
    childNode->setLocalPosition(-2.0f,0.0f,0.0f);
    childNode2->setLocalPosition(4.0f, 0.0f, 0.0f);


    Window window;                                         //Create our window class, which handles all the

    int done = false;   //Main loop variable
    SDL_Event *event;    //Useed in collecting events
    event = new SDL_Event;

    window.start(640,480,32);                          //Start the engine. Sets up SDL and OpenGL, sets some variables

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
                        window.quit();
                        break;

                    case SDLK_F1:
                        window.toggleFullScreen();
                        break;

                    default:
                        break;
                }

            } else                                      //If not a keypress, let the engine handle the event. Possibilities include window resize, losing window focus, (X) button being pressed, etc
            {
                window.handleEvent(event);
            }
        } //end while

        if (window.isActive)
        {
            window.clearScreen();
            rootNode.draw();                          //All nodes draw() function, including basic nodes like rootNode, calls the draw() functions of their children.
            window.swapBuffers();                      //Thus, calling rootNode.draw() will draw the entire scene.
        }

    }

    cout << "about to delete nodes\n";
    delete childNode;

    return 0;
}
