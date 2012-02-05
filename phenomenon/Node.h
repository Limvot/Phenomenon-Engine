#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)

//Includes from with in engine
#include "DataTypes.h"      //Also includes ExpandableArray.h

using std::string;

class Node
{
    public:
        Node();
        Node(string tmp_name);
        virtual ~Node();
        int setParent(Node*);
        int addChild(Node*);

        Node* findChild(string);
        int deleteChild(string);

        virtual int draw();
        Vertex getLocalPosition();
        Vertex getGlobalPosition();
        int setLocalPosition(float,float,float);
        int setLocalPosition(Vertex);
        int setColor3f(float,float,float);
        int setLocalScale(float,float,float);
        Vertex getLocalScale();
        Vertex getGlobalScale();
        int setLocalRotation(float,float,float);
        Vertex getLocalRotation();
        Vertex getGlobalRotation();

        string name;
        Color3f color;

    protected:
    Node *parent;
    ExpandableArray<Node*> children;
    Node *tmp_return_child;
    int numChildren;
    Vertex localPosition;
    Vertex globalPosition;
    Vertex localScale;
    Vertex globalScale;
    Vertex localRotation;
    Vertex globalRotation;
};

#endif // NODE_H
