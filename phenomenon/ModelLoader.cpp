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
    std::vector<Vector> normals;
    std::vector<Vector2f> uvs;
    std::vector<GLuint> vert_indices;

    ifstream in(file_path.c_str(), ios::in);
    if (!in)
    {
        std::cout << "Could not open file\n";
        return NULL;
    }

    string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ")
        {
            istringstream s(line.substr(2));
            Vector v;
            s >> v.x; s >> v.y; s >> v.z;
            vertices.push_back(v);

        } else if (line.substr(0, 2) == "vn ") {

            istringstream s(line.substr(2));
            Vector n;
            s >> n.x; s >> n.y; s >> n.z;
            normals.push_back(n);

        } else if (line.substr(0, 2) == "vt ") {

            istringstream s(line.substr(2));
            Vector2f t;
            s >> t.x; s >> t.y;
            uvs.push_back(t);

        } else if (line.substr(0, 2) == "f ") {

            istringstream s(line.substr(2));
            GLuint a,b,c;
            s >> a; s >> b; s >> c;
            a--; b--; c--;
            vert_indices.push_back(a); vert_indices.push_back(b); vert_indices.push_back(c);

        } else {/*ignore this line*/}
    }

    Vertex* vertices_out = new Vertex[vertices.size()];

    for (GLuint i = 0; i < vertices.size(); i++)
    {
        vertices_out[i].x = vertices[i].x;
        vertices_out[i].y = vertices[i].y;
        vertices_out[i].z = vertices[i].z;

        std::cout << vertices_out[i].x << "\n";
    }

    GLuint* indices_out = new GLuint[vert_indices.size()];

    for (GLuint i = 0; i < vert_indices.size(); i++)
    {
        indices_out[i] = vert_indices[i];
        std::cout << indices_out[i] << "\n";
    }

    StaticObject* loaded_obj = new StaticObject(name, vertices.size(), vertices_out, vert_indices.size(), indices_out);
    return loaded_obj;
}



