#include "ModelLoader.h"

ModelLoader::ModelLoader()
{
    numIndices = 0;
}

ModelLoader::~ModelLoader()
{

}

StaticObject* ModelLoader::loadOBJ(string file_path, string name)
{
    std::vector<Vector> vertices;
    std::vector<Vector2f> uvs;
    std::vector<Vector> normals;
    std::vector<GLuint> vertices_indices, uv_indices, normal_indices;
    std::vector<Vertex> out_vertices;
    std::vector<GLuint> out_indices;

    FILE * file = fopen(file_path.c_str(), "r");
    if (file == NULL)
    {
        std::cout << "Could not open file.\n";
        return false;
    }

    while (1)
    {
        char lineHeader[128];                   //Assuming words are less than 128 chars, which is pretty bad

        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;                              //Reached end of file

        if (strcmp(lineHeader, "v") == 0)
        {
            Vector vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            vertices.push_back(vertex);
        }

        if (strcmp(lineHeader, "vt") == 0)
        {
            Vector2f uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            uvs.push_back(uv);
        }

        if (strcmp(lineHeader, "vn") == 0)
        {
            Vector normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            normals.push_back(normal);
        }

        if (strcmp(lineHeader, "f") == 0)
        {
            GLuint vertex_index[3], uv_index[3], normal_index[3];
            GLuint num_values = 0;

            num_values = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_index[0], &uv_index[0], &normal_index[0], &vertex_index[1], &uv_index[1], &normal_index[1], &vertex_index[2], &uv_index[2], &normal_index[2]);
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
                out_indices.push_back(j);
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
    return loaded_obj;
}



