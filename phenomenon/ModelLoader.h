#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "DataTypes.h"
#include "StaticObject.h"
#include "Shader.h"
#include "Scene.h"

namespace phen {

class ModelLoader
{
    public:
        ModelLoader();
        ModelLoader(Scene* set_scene, Shader* default_shader_in, GLenum min_filter_in = GL_NEAREST, GLenum mag_filter_in = GL_LINEAR);
        virtual ~ModelLoader();
        int setScene(Scene* set_scene);
        int setDefaultShader(Shader* default_shader_in);
        int setTextureFilters(GLenum min_filter_in, GLenum mag_filter_in);
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
        GLenum min_filter, mag_filter;
        Material* default_material;
        Shader* default_shader;
};

} //End Namespace

#endif // MODELLOADER_H
