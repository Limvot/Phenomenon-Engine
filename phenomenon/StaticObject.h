#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include "Node.h"
#include "DataTypes.h"

namespace phen {

class StaticObject: public Node
{
    public:
        StaticObject(std::string tmp_name);
        StaticObject(std::string tmp_name, GLuint, Vertex*, GLuint, GLuint*);
        virtual ~StaticObject();
        int createVBO(GLuint, Vertex*);
        int createIBO(GLuint, GLuint*);
        int draw(Matrix4f VPmatrix);
    protected:
    private:
        GLuint VBO;
        GLuint IBO;
        GLuint numIndices;
};

} //End Namespace

#endif // STATICOBJECT_H
