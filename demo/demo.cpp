/*
This is main.cpp, a demo file for the phenomenon engine. It will start the engine and run some sort of demo.
It is an ideal base and tutorial for using phenomenon.
It is also the main method of testing and experementing with the engine.
One important part to notice is that this file uses the SDL_Event system, and passes events that it doesn't handle to the engine.
This is important, as the engine uses it to handle window resize and window loss of focus.
*/

#include <iostream>
#include "../phenomenon/Phenomenon.h"
using namespace std;
using namespace phen;

Window window;
Scene scene;                                                //Scenes are just that, scenes. They are renderd with a camera. Each scene has its own root node. Rendering will also take place inside of scenes.

Renderer renderer;

Camera camera("camera");                                    //Cameras inherit Node too, and thus require a name. It also dosn't have to be attached to a root node, but can be attached to a node if you wish. Just <dynamic_cast> again.

Node *rootNode, *childNode, *childNode2, *childNode3;



int setup()
{
    window.initGL();
    cout<< "OpenGL version is reported as: " << glGetString(GL_VERSION) << endl;    //Show OpenGL version
    renderer.init(1024.0f, 720.0f, 2.2);
    Shader* fullScreenQuadShader = scene.newShader("fullScreenQuad");

    //fullScreenQuadShader->createShaderProgram("..\\data\\FullScreenQuad.vert", "..\\data\\FullScreenQuad.frag");
    fullScreenQuadShader->createShaderProgram("../data/FullScreenQuad.vert", "../data/FullScreenQuad.frag");

    renderer.initQuad(fullScreenQuadShader);

    rootNode = scene.getRootNode();                       //All objects are represented with nodes. Basic nodes can be used to group together other nodes. This node is the root node.
    childNode = createTriangle("triangle");                 //The Triangle class inherets the Node class, but draws a triangle on draw().
    childNode2 = createSquare("square");                    //Same with the Square class, but it draws a square.
    childNode3 = createSquare("square2");                   //Also, Nodes NEED unique names, or searching for them and deleting them will probally not work, and may delete other nodes.
    //Node* logoNode = createSquare("logo");

    Shader* basic_shader = scene.newShader("basic_shader");

    //basic_shader->createShaderProgram("..\\data\\sample_shader.vert", "..\\data\\sample_shader.frag");
    basic_shader->createShaderProgram("../data/sample_shader.vert", "../data/sample_shader.frag");


    ModelLoader model_loader(&scene, basic_shader);                                   //Our model-loading object

    //Node* loadedObject = model_loader.loadOBJ("../data/Monkey.obj", "monkey");   //loadOBJ returns a pointer to a StaticObject, which is derived from the Node class.
    Node* loadedObject = model_loader.loadOBJ("../data/Monkey.obj", "monkey");   //loadOBJ returns a pointer to a StaticObject, which is derived from the Node class.

    if (loadedObject == NULL)                                                          //Quit if the load failed.
    {
        cout << "Problem loading the demonstration .obj file, will now quit.\n";
        return 0;
    }

    camera.setProjectionMatrix(1024.0f/720.0f, 45, 0.1, 100);


    Material* red_material = scene.newMaterial("red");
    Material* green_material = scene.newMaterial("green");
    Material* blue_material = scene.newMaterial("blue");
    //Material* logo_material = scene.newMaterial("logo");

    childNode->setMaterial(red_material);                       //All nodes that actually draw an object need a material
    red_material->setShader(basic_shader);
    red_material->setDiffuse(1.0f, 0.0f, 0.0f);                 //Default is 1.0f, 1.0f, 1.0f
    red_material->setSpecular(0.0f, 1.0f, 0.0f);                //Default is 1.0f, 1.0f, 1.0f
    red_material->setSpecularHardness(32.0f);                   //Default hardness is 128

    childNode2->setMaterial(green_material);
    green_material->setShader(basic_shader);
    green_material->setDiffuse(0.0f, 1.0f, 0.0f);
    green_material->setSpecular(0.0f, 0.0f, 1.0f);

    childNode3->setMaterial(blue_material);
    blue_material->setShader(basic_shader);
    blue_material->setDiffuse(0.0f, 0.0f, 1.0f);
/*
    logoNode->setMaterial(logo_material);                       //Set this square to use the logo material
    logo_material->setShader(basic_shader);
    Texture* logo_texture = scene.newTexture("logo_texture");   //Create a Texture object named logo_texture
    logo_texture->load("../data/phenomenon.bmp");                //Load the phenomenon.bmp image
    logo_material->setTexture(logo_texture);                    //Have logo_material use the logo_texture Texture.

*/

    rootNode->addChild(childNode);                              //You should add most nodes to your root node so that everything gets deleted properly on exit.
    rootNode->addChild(childNode2);                             //You can also assign a child to a new parent at will, the child will automatically remove itself from its previous parent's index.
    childNode2->addChild(childNode3);
    rootNode->addChild(loadedObject);
   // rootNode->addChild(logoNode);

    rootNode->setLocalPosition(0.0f, 0.0f, 0.0f);               //This is to show that position, scale, and rotation is inhereted from parent to child. The childNode3 will end up with a position of 2.0, -2.0, -6.0, etc.
    childNode->setLocalPosition(-2.0f,0.0f,0.0f);
    childNode2->setLocalPosition(2.0f, 0.0f, 0.0f);
    childNode3->setLocalPosition(0.0f,-2.0f, 0.0f);

    //loadedObject->setLocalPosition(0.0f, 0.0f, 0.0f);

    //logoNode->setLocalPosition(0.0f, 0.0f, 2.0f);

    childNode->setLocalRotation(0.0f, 30.0f, 0.0f);
    childNode2->setLocalRotation(0.0f, 0.0f, 45.0f);
    childNode3->setLocalRotation(45.0f, 0.0f, 0.0f);

    childNode->setLocalScale(1.0f, 1.0f, 1.0f);
    childNode2->setLocalScale(0.5f, 1.0f, 1.0f);
    childNode3->setLocalScale(1.0f, 0.5f, 1.0f);                //Scale is inherited, so now it has a scale of 0.5, 0.5, 1.0, so it is half sized. Also note that scales are multipled together, not added.
    //logoNode->setLocalScale(3.0f, 3.0f, 1.0f);

    loadedObject->setLocalRotation(90.0f, 0.0f, 0.0f);


    camera.setLocalPosition(0.0f, 0.0f, 6.0f);                  //Setting the camera 6 units toward the screen is the same as setting everything else 6 units away.
    camera.setLocalRotation(0.0f, 0.0f, 0.0f);
    camera.setLocalScale(1.0f, 1.0f, 1.0f);

    cout << "j key pressed, ran workarounds\n";
    return 0;
}
int main(int argc, char* argv[])
{
    //freopen("CON", "w", stdout);                                //Don't let SDL redirect the standard output to a file
    //freopen("CON", "w", stderr);                                //Same for standard errors`

    window.create(1024.0f,720.0f,32);                                  //Creates the window. Sets up SDL and OpenGL, sets some variables
    window.setCaption("Phenomenon Engine Test/Demo");           //The window should be created before you start setting up anything that could make SDL or OpenGL calls.

    int done = false;                                           //Main loop variable
    SDL_Event *event;                                           //Useed in collecting events
    event = new SDL_Event;

    bool workaroundsRun = false;

    while(!done)                                                //Main loop
    {
                                                                //Handle events in queue
        while (SDL_PollEvent(event))
        {
            if (event->type == SDL_KEYDOWN)                     //If a key is pressed, we handle it
            {
                switch (event->key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        window.quit();                          //Don't use window after you quit it, it will probally cause a seg fault.
                        done = true;
                        break;

                    case SDLK_F1:
                        window.toggleFullScreen();              //Still needs work. Fails on some systems, and dosn't actually change the OpenGL size on every platform.
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

                    case SDLK_j:
                        setup();
                        workaroundsRun = true;
                        break;

                    default:
                        break;
                }

            } else
            {
                if (event->type == SDL_QUIT)            //If the system wants us to quit, then do so.
                {
                    window.quit();                      //Quit window stuff
                    done = true;
                } else
                {
                    window.handleEvent(event);          //If not a keypress or SDL_QUIT, let the engine handle the event. Possibilities include window resize, losing window focus.
                }
            }
        } //end while

        if (window.isActive && workaroundsRun == true)                            //window.isActive is false if we've already quit, or if we're minimised.
        {
            childNode->increaseLocalRotation(0.0f, 1.0f, 0.0f);
            childNode2->increaseLocalRotation(0.0f, 0.0f, 1.0f);
            childNode3->increaseLocalRotation(1.0f, 0.0f, 0.0f);
            //loadedObject->increaseLocalRotation(0.0f, 0.0f, 1.0f);

            window.clearScreen();
            cout << "about to render!\n";
            renderer.render(&camera, &scene);
            cout << "Finished rendering!\n";
            window.swapBuffers();                       //Thus, calling rootNode.draw() will draw the entire scene. However, to use a camera, you must call drawScene on it
        } else {/*sleep(1);*/}                          //and pass it the scene. It will apply the appropriate translation, rotation, and scale for its own properties,
                                                        //Scene will set up lights and rendering, then call draw() on the root node.
    }
                                /////////////////////////
                                //NOTE
                                /////////////////////////
                                //Nodes get destroyed when their parents falls out of scope.
                                //If you delete them manually (without using the deleteChild(child's name) from the parent node)
                                //the parent will segfault when it trys to delete them.
                                //Here scene owns rootNode, which is the parent of every other dynamically allocated node, so it deletes them all when it falls out of scope.
                                //Materials and textures are handeld by scene as well, and are deleted when it falls out of scope.
    return 0;
}
