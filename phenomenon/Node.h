#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define NO_SDL_GLEXT

#include <GL/glew.h>
#include "SDL.h"
#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)

//Includes from with in engine
#include "DataTypes.h"      //Also includes ExpandableArray.h
#include "Material.h"

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
        int removeChild(string);
        int deleteChild(string);

        virtual int draw();

        int setLocalPosition(float,float,float);
        int setLocalPosition(Vector);
        Vector getLocalPosition();
        Vector getGlobalPosition();

        int setLocalScale(float,float,float);
        int setLocalScale(Vector);
        Vector getLocalScale();
        Vector getGlobalScale();

        int setLocalRotation(float,float,float);
        int setLocalRotation(Vector);
        Vector getLocalRotation();
        Vector getGlobalRotation();

        int increaseLocalPosition(float,float,float);
        int increaseLocalScale(float,float,float);
        int increaseLocalRotation(float,float,float);

        int setMaterial(Material*);

        string name;
        Material* material;

    protected:
    Node *parent;
    ExpandableArray<Node*> children;
    Node *tmp_return_child;
    int numChildren;
    Vector localPosition;
    Vector globalPosition;
    Vector localScale;
    Vector globalScale;
    Vector localRotation;
    Vector globalRotation;
};

#endif // NODE_H
