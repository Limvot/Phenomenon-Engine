#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include "Node.h"
#include "DataTypes.h"

class StaticObject: public Node
{
    public:
        StaticObject(string);
        virtual ~StaticObject();
        int createVBO();
        int createIBO();
        int draw();
    protected:
    private:
        GLuint VBO;
        GLuint IBO;
};

#endif // STATICOBJECT_H
