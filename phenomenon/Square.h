#ifndef SQUARE_H
#define SQUARE_H

#include "Node.h"
#include "DataTypes.h"

class Square: public Node
{
    public:
        Square(string);
        virtual ~Square();
        int draw();
    protected:
    private:
};

#endif // SQUARE_H
