#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Node.h"

class Triangle: public Node
{
    public:
        Triangle();
        virtual ~Triangle();
        int draw();
    protected:
    private:
};

#endif // TRIANGLE_H
