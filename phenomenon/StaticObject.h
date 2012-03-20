#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include "Node.h"
#include "DataTypes.h"

class StaticObject: public Node
{
    public:
        StaticObject(string);
        StaticObject(string, GLuint, Vertex*, GLuint, GLuint*);
        virtual ~StaticObject();
        int createVBO(GLuint, Vertex*);
        int createIBO(GLuint, GLuint*);
        int draw();
    protected:
    private:
        GLuint VBO;
        GLuint IBO;
        GLuint numIndices;
};

#endif // STATICOBJECT_H
