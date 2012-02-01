#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)

class Node
{
    public:
        Node();
        virtual ~Node();
        int setParent(Node*);
        int addChild(Node*);

        //Node* getChild(int);
        int getIndex();

        virtual int draw();


        int index;              //What position is this node in the parent's array
    protected:
    Node *parent;
    Node *children;
};

#endif // NODE_H
