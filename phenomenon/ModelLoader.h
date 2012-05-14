#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "DataTypes.h"
#include "StaticObject.h"
#include "Scene.h"

namespace phen {

class ModelLoader
{
    public:
        ModelLoader();
        ModelLoader(Scene* set_scene);
        virtual ~ModelLoader();
        int setScene(Scene* set_scene);
        int loadMTL(std::string file_path);
        Node* loadOBJ(std::string file_path, std::string name);
        int loadOBJpart(FILE* file_path, std::string name, Node* loaded_obj_group);
        std::string findBasePath(std::string file_path);

    protected:
    private:
        Scene* current_scene;
        GLuint numIndices;
        std::vector<Vector> vertices;
        std::vector<Vector2f> uvs;
        std::vector<Vector> normals;
};

} //End Namespace

#endif // MODELLOADER_H
