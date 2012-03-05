#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "DataTypes.h"
#include "StaticObject.h"

class ModelLoader
{
    public:
        ModelLoader();
        virtual ~ModelLoader();
        StaticObject* loadOBJ(string, string);

    protected:
    private:
        GLuint numIndices;
};

#endif // MODELLOADER_H
