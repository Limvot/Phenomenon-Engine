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
#include "phenomenon/Camera.h"
#include "phenomenon/Triangle.h"
#include "phenomenon/Square.h"

using namespace std;

int main()
{
    Node rootNode("root");                                      //All objects are represented with nodes. Basic nodes can be used to group together other nodes. This node is the root node.
    Node* childNode = new Triangle("triangle");                 //The Triangle class inherets the Node class, but draws a triangle on draw().
    Node* childNode2 = new Square("square");                    //Same with the Square class, but it draws a square.
    Node* childNode3 = new Square("square2");                   //Also, Nodes NEED unique names, or searching for them and deleting them will probally not work, and may delete other nodes.

    rootNode.addChild(childNode);
    rootNode.addChild(childNode2);
    childNode2->addChild(childNode3);

    rootNode.setLocalPosition(0.0f, 0.0f, 0.0f);                //This is to show that position, scale, and rotation is inhereted from parent to child. The childNode3 will end up with a position of 2.0, -2.0, -6.0, etc.
    childNode->setLocalPosition(-2.0f,0.0f,0.0f);
    childNode2->setLocalPosition(2.0f, 0.0f, 0.0f);
    childNode3->setLocalPosition(0.0f,-2.0f, 0.0f);

    childNode->setColor3f(1.0f, 0.0f, 0.0f);
    childNode2->setColor3f(0.0f, 1.0f, 0.0f);
    childNode3->setColor3f(0.0f, 0.0f, 1.0f);

    childNode->setLocalRotation(0.0f, 30.0f, 0.0f);
    childNode2->setLocalRotation(0.0f, 0.0f, 45.0f);
    childNode3->setLocalRotation(45.0f, 0.0f, 0.0f);

    childNode->setLocalScale(1.0f, 1.0f, 1.0f);
    childNode2->setLocalScale(0.5f, 1.0f, 1.0f);
    childNode3->setLocalScale(1.0f, 0.5f, 1.0f);            //Scale is inherited, so now it has a scale of 0.5, 0.5, 1.0, so it is half sized. Also note that scales are multipled together, not added.


    Camera camera("camera");                                //Cameras inherit Node too, and thus require a name.

    camera.setLocalPosition(0.0f, 0.0f, 6.0f);              //Setting the camera 6 units toward the screen is the same as setting everything else 6 units away.
    camera.setLocalRotation(0.0f, 0.0f, 0.0f);


    Window window;                                          //Create our window class, which handles all the

    int done = false;                                       //Main loop variable
    SDL_Event *event;                                       //Useed in collecting events
    event = new SDL_Event;

    window.create(640,480,32);                              //Creates the window. Sets up SDL and OpenGL, sets some variables
    window.setCaption("Phenomenon Engine Test/Demo");

    cout<< "OpenGL version is reported as: " << glGetString(GL_VERSION) << endl;    //Show OpenGL version

        while(!done)                                        //Main loop
    {
                                                            //Handle events in queue
        while (SDL_PollEvent(event))
        {
            if (event->type == SDL_KEYDOWN)                 //If a key is pressed, we handle it
            {
                switch (event->key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        window.quit();                      //Don't use window after you quit it, it will probally cause a seg fault.
                        done = true;
                        break;

                    case SDLK_F1:
                        window.toggleFullScreen();          //Still needs work. Fails on some systems, and dosn't actually change the OpenGL size on every platform.
                        break;

                    case SDLK_w:
                        camera.rotate(10.0f, 0.0f, 0.0f);
                        break;

                    case SDLK_a:
                        camera.rotate(0.0f, 10.0f, 0.0f);
                        break;

                    case SDLK_s:
                        camera.rotate(-10.0f, 0.0f, 0.0f);
                        break;

                    case SDLK_d:
                        camera.rotate(0.0f, -10.0f, 0.0f);
                        break;

                    case SDLK_UP:
                        camera.goForward(1.0f);
                        break;

                    case SDLK_DOWN:
                        camera.goBackward(1.0f);
                        break;

                    case SDLK_LEFT:
                        camera.goLeft(1.0f);
                        break;

                    case SDLK_RIGHT:
                        camera.goRight(1.0f);
                        break;

                    default:
                        break;
                }

            } else
            {
                if (event->type == SDL_QUIT)            //If the system wants us to quit, then do so.
                {
                    window.quit();
                    done = true;
                } else
                {
                    window.handleEvent(event);          //If not a keypress or SDL_QUIT, let the engine handle the event. Possibilities include window resize, losing window focus.
                }
            }
        } //end while

        if (window.isActive)                            //window.isActive is false if we've already quit, or if we're minimised.
        {
            window.clearScreen();
            camera.drawScene(&rootNode);                //All nodes draw() function, including basic nodes like rootNode, calls the draw() functions of their children.
            window.swapBuffers();                       //Thus, calling rootNode.draw() will draw the entire scene.
        }

    }
                                /////////////////////////
                                //NOTE
                                /////////////////////////
                                //Nodes get destroyed when their parents falls out of scope.
                                //If you delete them manually (without using the deleteChild(child's name) from the parent node)
                                //the parent will segfault when it trys to delete them.
                                //Here rootNode is the parent of every other dynamically allocated node, so it deletes them all when it falls out of scope.
    return 0;
}
