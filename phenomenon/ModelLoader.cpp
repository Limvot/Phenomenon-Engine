#include "ModelLoader.h"

namespace phen {

ModelLoader::ModelLoader()
{
    numIndices = 0;
    current_scene = NULL;
}

ModelLoader::ModelLoader(Scene* set_scene)
{
    numIndices = 0;
    current_scene = set_scene;
}

ModelLoader::~ModelLoader()
{

}

int ModelLoader::setScene(Scene* set_scene)
{
    current_scene = set_scene;
    return 0;
}

int ModelLoader::loadMTL(std::string file_path)
{
    std::cout << "Loading .mtl file " << file_path << ".\n";

    FILE * mtl_file = fopen(file_path.c_str(), "r");
    if (mtl_file == NULL)
    {
        std::cout<< "Could not open .mtl file.\n";
        return 1;
    }

    Material* loading_mat = NULL;
    Texture* loading_tex = NULL;
    char lineHeader[512];                   //Assuming words of only 512 chars is silly, but this is a very limited loader
    char valueBuffer[512];                   //Ditto
    std::string loading_mat_name;
    std::string texture_file_path;
    float set_specular_intensity;
    Color3f set_color;

    while (1)
    {
        int res = fscanf(mtl_file, "%s", lineHeader);
        std::cout << "Scanning .mtl: " << lineHeader << "\n";
        if (res == EOF)
            break;

        if (strcmp(lineHeader, "newmtl") == 0)
        {
            fscanf(mtl_file, "%s\n", valueBuffer);
            loading_mat_name = valueBuffer;
            loading_mat = current_scene->findMaterial(loading_mat_name);

            if (loading_mat == NULL)
            {
                loading_mat = current_scene->newMaterial(loading_mat_name);
                std::cout << "creating new material named " << loading_mat_name << ".\n";

            } else {
                std::cout << "found match for " << loading_mat_name << ".\n";
            }
        }

        if (strcmp(lineHeader, "Ns") == 0)
        {
            fscanf(mtl_file, "%f\n", &set_specular_intensity);
            loading_mat->setSpecularHardness(set_specular_intensity);
        }

        if (strcmp(lineHeader, "Kd") == 0)
        {
            fscanf(mtl_file, "%f %f %f\n", &set_color.r, &set_color.g, &set_color.b);
            loading_mat->setDiffuse(&set_color);
        }

        if (strcmp(lineHeader, "Ks") == 0)
        {
            fscanf(mtl_file, "%f %f %f\n", &set_color.r, &set_color.g, &set_color.b);
            loading_mat->setSpecular(&set_color);
        }

        if (strcmp(lineHeader, "map_Kd") == 0)
        {
            fscanf(mtl_file, "%s\n", valueBuffer);
            texture_file_path = valueBuffer;
            loading_tex = current_scene->findTexture(texture_file_path);
            if (loading_tex == NULL)
            {
                loading_tex = current_scene->newTexture(texture_file_path);
                if (texture_file_path[0] == '/' || !(file_path.find("/")))                      //If the texture_file_path is absolute, or if file_path only contains the name of the current file, meaning it resides in the local directory, then load texture_file_path.
                {
                    loading_tex->load(texture_file_path);
                } else {
                    loading_tex->load(findBasePath(file_path) + '/' + texture_file_path);       //If not the above, figure out the base path for the current file, and add the texture_file_path on top of that.
                }
            }
            loading_mat->setTexture(loading_tex);
        }
    }
    return 0;
}

StaticObject* ModelLoader::loadOBJ(std::string file_path, std::string name)
{
    std::vector<Vector> vertices;
    std::vector<Vector2f> uvs;
    std::vector<Vector> normals;
    std::vector<GLuint> vertices_indices, uv_indices, normal_indices;
    std::vector<Vertex> out_vertices;
    std::vector<GLuint> out_indices;

    FILE * obj_file = fopen(file_path.c_str(), "r");
    if (obj_file == NULL)
    {
        std::cout << "Could not open .obj file.\n";
        return false;
    }



        char lineHeader[128];                   //Assuming words are less than 128 chars, which is pretty bad
        char valueBuffer[512];                  //Ditto, even more so with file paths.
        Material* tmp_mat = NULL;
        std::string value_string;
        int res;

    while (1)
    {
        res = fscanf(obj_file, "%s", lineHeader);
        if (res == EOF)
            break;                              //Reached end of file

        if (strcmp(lineHeader, "mtllib") == 0)
        {
            fscanf(obj_file, "%s\n", valueBuffer);
            value_string = valueBuffer;

            if (value_string[0] == '/' || (file_path.find("/") == std::string::npos))                      //If the value_string is absolute, or if file_path only contains the name of the current file, meaning it resides in the local directory, then load value_string.
            {
                std::cout << "loading mtl with just value_string.\n";
                loadMTL(value_string);
            } else {
                std::cout << "loading mtl with found base path.\n";
                loadMTL(findBasePath(file_path) + '/' + value_string);                  //If not the above, figure out the base path for the current file, and add the value_string on top of that.
            }
        }

        if (strcmp(lineHeader, "usemtl") == 0)
        {
            fscanf(obj_file, "%s\n", valueBuffer);
            value_string = valueBuffer;
            tmp_mat = current_scene->findMaterial(value_string);
            if (tmp_mat == NULL)
            {
                std::cout << "Could not find material referenced! Material should be: " << value_string << ".\n";
            }
        }

        if (strcmp(lineHeader, "v") == 0)
        {
            Vector vertex;
            fscanf(obj_file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            vertices.push_back(vertex);
        }

        if (strcmp(lineHeader, "vt") == 0)
        {
            Vector2f uv;
            fscanf(obj_file, "%f %f\n", &uv.x, &uv.y);
            uvs.push_back(uv);
        }

        if (strcmp(lineHeader, "vn") == 0)
        {
            Vector normal;
            fscanf(obj_file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            normals.push_back(normal);
        }

        if (strcmp(lineHeader, "f") == 0)
        {
            GLuint vertex_index[3], uv_index[3], normal_index[3];
            GLuint num_values = 0;

            num_values = fscanf(obj_file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_index[0], &uv_index[0], &normal_index[0], &vertex_index[1], &uv_index[1], &normal_index[1], &vertex_index[2], &uv_index[2], &normal_index[2]);
            if (num_values != 9)
            {
                std::cout << "This .obj file cannot be loaded by our very limited loader. It must have normals and uvs, and be made of only triangles.\n";
                return NULL;
            }
            vertices_indices.push_back((vertex_index[0])-1);    //.obj indices are 1 based, C++ arrays and OpenGL are 0 based
            vertices_indices.push_back((vertex_index[1])-1);
            vertices_indices.push_back((vertex_index[2])-1);

            uv_indices.push_back((uv_index[0])-1);
            uv_indices.push_back((uv_index[1])-1);
            uv_indices.push_back((uv_index[2])-1);

            normal_indices.push_back((normal_index[0])-1);
            normal_indices.push_back((normal_index[1])-1);
            normal_indices.push_back((normal_index[2])-1);
        }
    }

    bool found_match;

    for (GLuint i = 0; i < vertices_indices.size(); i++)
    {
        Vertex out_vertex(vertices[vertices_indices[i]].x, vertices[vertices_indices[i]].y, vertices[vertices_indices[i]].z, normals[normal_indices[i]].x, normals[normal_indices[i]].y, normals[normal_indices[i]].z, uvs[uv_indices[i]].x, uvs[uv_indices[i]].y);

        found_match = false;
        for (GLuint j = 0; j < out_vertices.size(); j++)
        {
            if (out_vertex == out_vertices[j])
            {
                found_match = true;
                out_indices.push_back(j);                       //Found identicle vertex, so we just add its index to our indicies list and throw the new one away.
                break;
            }
        }
        if (found_match != true)                                //If we didn't find an equal vertex, add this one to out_vertices and its position to out_indices
        {
            out_vertices.push_back(out_vertex);
            out_indices.push_back(out_vertices.size()-1);       //Position of new vertex is the number of vertices - 1, since arrays are 0 indexed.
        }
    }

    Vertex* out_vertices_array = new Vertex[out_vertices.size()];
    copy(out_vertices.begin(), out_vertices.end(), out_vertices_array);

    GLuint* out_indices_array = new GLuint[out_indices.size()];
    copy(out_indices.begin(), out_indices.end(), out_indices_array);

    StaticObject* loaded_obj = new StaticObject(name, out_vertices.size(), out_vertices_array, out_indices.size(), out_indices_array);
    if (tmp_mat != NULL)
        loaded_obj->setMaterial(tmp_mat);
    return loaded_obj;
}

std::string ModelLoader::findBasePath(std::string file_path)
{
    std::string base_path = "";

    if (file_path.rfind('/') != std::string::npos)
    {
        base_path = file_path.substr(0, file_path.rfind('/'));
        std::cout << "file_path was " << file_path << " and the found base path is " << base_path << ".\n";
    }
    return base_path;
}

} //End Namespace

