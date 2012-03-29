#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "DataTypes.h"
#include "StaticObject.h"

namespace phen {

class ModelLoader
{
    public:
        ModelLoader();
        virtual ~ModelLoader();
        StaticObject* loadOBJ(std::string, std::string);

    protected:
    private:
        GLuint numIndices;
};

} //End Namespace

#endif // MODELLOADER_H
