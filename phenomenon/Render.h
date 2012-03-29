#ifndef RENDER_H
#define RENDER_H
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

namespace phen {

class Render
{
    public:
        Render();
        virtual ~Render();
//        virtual int draw(Node* to_draw);

    protected:
};

} //End Namespace

#endif // RENDER_H
