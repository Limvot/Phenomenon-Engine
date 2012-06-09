#include "ModelLoader.h"

namespace phen {

ModelLoader::ModelLoader()
{
    numIndices = 0;
    current_scene = NULL;
}

ModelLoader::ModelLoader(Scene* set_scene, Shader* default_shader_in, GLenum min_filter_in, GLenum mag_filter_in)      //min_filter_in and mag_filter_in defaults in .h file
{
    numIndices = 0;
    current_scene = set_scene;
    default_shader = default_shader_in;
    min_filter = min_filter_in;
    mag_filter = mag_filter_in;
}

ModelLoader::~ModelLoader()
{
}

int ModelLoader::setScene(Scene* set_scene)
{
    current_scene = set_scene;
    return 0;
}

int ModelLoader::setDefaultShader(Shader* default_shader_in)
{
    default_shader = default_shader_in;
    return 0;
}

int ModelLoader::setTextureFilters(GLenum min_filter_in, GLenum mag_filter_in)
{
    min_filter = min_filter_in;
    mag_filter = mag_filter_in;
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
    char lineHeader[8192];                   //Assuming words of only 512 chars is silly, but this is a very limited loader
    char valueBuffer[8192];                   //Ditto
    std::string loading_mat_name;
    std::string texture_file_path;
    float set_specular_intensity;
    Color3f set_color;

    while (1)
    {
        int res = fscanf(mtl_file, "%s", lineHeader);
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
                loading_mat->setShader(default_shader);
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
                    std::cout << "loading Texture from " << texture_file_path << "\n";
                    loading_tex->load(texture_file_path, min_filter, mag_filter);
                } else {
                    std::cout << "loading Texture from " << (findBasePath(file_path) + '/' + texture_file_path) << "\n";
                    loading_tex->load(findBasePath(file_path) + '/' + texture_file_path, min_filter, mag_filter);       //If not the above, figure out the base path for the current file, and add the texture_file_path on top of that.
                }
            }
            loading_mat->setTexture(loading_tex);
        }
    }
    fclose(mtl_file);
    return 0;
}

Node* ModelLoader::loadOBJ(std::string file_path, std::string name)
{

    default_material = current_scene->newMaterial("default_material");  //Default material

    FILE * obj_file = fopen(file_path.c_str(), "r");
    if (obj_file == NULL)
    {
        std::cout << "Could not open .obj file.\n";
        return false;
    }

    Node* loaded_obj_group = new Node(name);    //Our group node that all loaded objects will be made a child of.

    char lineHeader[8192];                       //We're only looking for 'o', so 128 chars is fine.
    char valueBuffer[8192];                      //Assuming that object names are less than 512 characters, which could be better.
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

        if (strcmp(lineHeader, "o") == 0)
        {
            fscanf(obj_file, "%s\n", valueBuffer);
            value_string = valueBuffer;
            loadOBJpart(obj_file, value_string, loaded_obj_group);                  //loadOBJpart takes the current .obj file, the name of the object to be created, and the node that serves as the group of the loaded objs. It will attatch the new object, named, to the group.

        }
    }
    fclose(obj_file);
    return loaded_obj_group;                    //Return our group node with all our loaded objects as children.
}

int ModelLoader::loadOBJpart(FILE* obj_file, std::string name, Node* loaded_obj_group)
{

    uint face_count = 0;

    std::vector<GLuint> vertices_indices, uv_indices, normal_indices;
    std::vector<Vertex> out_vertices;
    std::vector<GLuint> out_indices;


    char lineHeader[8192];                   //Assuming words are less than 128 chars, which is pretty bad
    char valueBuffer[8192];                  //Ditto, even more so with file paths.
    Material* tmp_mat = NULL;
    std::string value_string;
    int res;

    std::string next_name;
    bool next_obj_exists = false;

    while (1)
    {
        //std::cout << "About to fscanf inside of loadOBJpart\n";
        //std::cout << "lineHeader is equal to " << lineHeader << "\n";
        res = fscanf(obj_file, "%s", lineHeader);
        //std::cout << "lineHeader is now equal to " << lineHeader << ", res is equal to " << res << "\n";
        if (res == EOF)
        {
            //std::cout << "found EOF, breaking\n";
            break;
        }

        if (strcmp(lineHeader, "o") == 0)
        {
            //std::cout << "Found new object, ending this obj.\n";
            fscanf(obj_file, "%s\n", valueBuffer);
            next_name = valueBuffer;
            next_obj_exists = true;
            break;
        }

        if (strcmp(lineHeader, "usemtl") == 0)
        {
            //std::cout << "Found usemtl, trying to use indicated material.\n";
            fscanf(obj_file, "%s\n", valueBuffer);
            value_string = valueBuffer;
            tmp_mat = current_scene->findMaterial(value_string);
            if (tmp_mat == NULL)
            {
                std::cout << "Could not find material referenced! Material should be: " << value_string << ".\n";
                std::cout << "Using a default material.\n";
                tmp_mat = default_material;
            }
        }

        if (strcmp(lineHeader, "v") == 0)
        {
            //std::cout << "found v, adding vertex placement information.\n";
            Vector vertex;
            fscanf(obj_file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            vertices.push_back(vertex);
        }

        if (strcmp(lineHeader, "vt") == 0)
        {
            //std::cout << "found vt, adding tex coord information.\n";
            Vector2f uv;
            fscanf(obj_file, "%f %f\n", &uv.x, &uv.y);
            uvs.push_back(uv);
        }

        if (strcmp(lineHeader, "vn") == 0)
        {
            //std::cout << "found vn, adding vertex normal information.\n";
            Vector normal;
            fscanf(obj_file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            normals.push_back(normal);
        }

        if (strcmp(lineHeader, "f") == 0)
        {
            face_count += 1;
            //std::cout << "found f, adding face information. This is face #" << face_count << ".\n";
            GLuint vertex_index[3], uv_index[3], normal_index[3];
            GLuint num_values = 0;

            num_values = fscanf(obj_file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_index[0], &uv_index[0], &normal_index[0], &vertex_index[1], &uv_index[1], &normal_index[1], &vertex_index[2], &uv_index[2], &normal_index[2]);
            if (num_values != 9)
            {
                std::cout << "This .obj file cannot be loaded by our very limited loader. It must have normals and uvs, and be made of only triangles.\n";
                return 0;
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

    //std::cout << "finished loading information for this obj, now compiling and creating.\n";
    bool found_match;

    for (GLuint i = 0; i < vertices_indices.size(); i++)
    {
        //std::cout << "creating out_vertex\n";
        //std::cout << vertices[vertices_indices[i]].x << vertices[vertices_indices[i]].y << vertices[vertices_indices[i]].z << normals[normal_indices[i]].x << normals[normal_indices[i]].y << normals[normal_indices[i]].z << uvs[uv_indices[i]].x << uvs[uv_indices[i]].y << "end\n";
        Vertex out_vertex(vertices[vertices_indices[i]].x, vertices[vertices_indices[i]].y, vertices[vertices_indices[i]].z, normals[normal_indices[i]].x, normals[normal_indices[i]].y, normals[normal_indices[i]].z, uvs[uv_indices[i]].x, uvs[uv_indices[i]].y);
        //std::cout << "created out_vertex\n";
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

    //std::cout << "finished creating vertexes, now copying to arrays\n";

    Vertex* out_vertices_array = new Vertex[out_vertices.size()];
    copy(out_vertices.begin(), out_vertices.end(), out_vertices_array);

    GLuint* out_indices_array = new GLuint[out_indices.size()];
    copy(out_indices.begin(), out_indices.end(), out_indices_array);

    //std::cout << "Finished creating arrays, now creating a new StaticObject\n";

    StaticObject* loaded_obj = new StaticObject(name, out_vertices.size(), out_vertices_array, out_indices.size(), out_indices_array);
    if (tmp_mat != NULL)
        loaded_obj->setMaterial(tmp_mat);

    //std::cout << "Finished creating new StaticObject!\n";

    loaded_obj_group->addChild(loaded_obj);

    if (next_obj_exists)
    {
        loadOBJpart(obj_file, next_name, loaded_obj_group);
    }

    return 0;
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

