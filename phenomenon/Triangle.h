#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Node.h"
#include "DataTypes.h"

class Triangle: public Node
{
    public:
        Triangle(string);
        virtual ~Triangle();
        int draw();
    protected:
    private:
};

#endif // TRIANGLE_H
