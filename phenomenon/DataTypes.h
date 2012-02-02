#ifndef DATATYPES_H
#define DATATYPES_H


class Vertex           //Simple vertex class. May add more data types here.
{
    public:
        Vertex();
        Vertex(float,float,float);
        ~Vertex();
        Vertex operator+ (Vertex);
        Vertex operator- (Vertex);
        float x,y,z;
};

#endif // DATATYPES_H
