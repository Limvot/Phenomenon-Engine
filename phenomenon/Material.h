#ifndef MATERIAL_H
#define MATERIAL_H


class Material
{
    public:
        Material();
        Material(string);
        virtual ~Material();

        GLfloat MaterialDiffuse[3];    //Material settings
        GLfloat MaterialSpecular[3];
        GLfloat SpecularIntensity;

    protected:
    private:
};

#endif // MATERIAL_H
