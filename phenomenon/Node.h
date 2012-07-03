#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#define PI 3.141592654

#define NO_SDL_GLEXT

#include <GL/glew.h>
#include "SDL.h"
//#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)

//Includes from with in engine
#include "DataTypes.h"      //Also includes ExpandableArray.h
#include "Renderer.h"
#include "Material.h"

namespace phen {

class Node
{
    public:
        Node();
        Node(std::string tmp_name);
        virtual ~Node();
        int setParent(Node*);
        int addChild(Node*);

        Node* findChild(std::string);
        int removeChild(std::string);
        int deleteChild(std::string);

        virtual int draw(Renderer* renderer);

        int setLocalPosition(float,float,float);
        int setLocalPosition(Vector);
        Vector getLocalPosition();
        Vector getGlobalPosition();
        Matrix4f getGlobalPositionMatrix();

        int setLocalScale(float,float,float);
        int setLocalScale(Vector);
        Vector getLocalScale();
        Vector getGlobalScale();
        Matrix4f getGlobalScaleMatrix();

        int setLocalRotation(float,float,float);
        int setLocalRotation(Vector);
        Vector getLocalRotation();
        Vector getGlobalRotation();
        Matrix4f getGlobalRotationMatrix();

        int increaseLocalPosition(float,float,float);
        int increaseLocalScale(float,float,float);
        int increaseLocalRotation(float,float,float);

        int setMaterial(Material*);

        std::string name;
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

        Matrix4f mat_localPosition;
        Matrix4f mat_globalPosition;
        Matrix4f mat_localScale;
        Matrix4f mat_globalScale;
        Matrix4f mat_localRotation;
        Matrix4f mat_globalRotation;

        Matrix4f mat_transformedMatrix;

};

}   //End namespace

#endif // NODE_H
