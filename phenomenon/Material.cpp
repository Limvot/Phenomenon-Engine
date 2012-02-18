#include "Material.h"

Material::Material()
{
    Material("no_name");
}

Material::Material(string tmp_name)
{

    name = tmp_name;

    MaterialDiffuse[0] = 1.0f;
    MaterialDiffuse[1] = 1.0f;
    MaterialDiffuse[2] = 1.0f;


    MaterialSpecular[0] = 1.0f;
    MaterialSpecular[1] = 1.0f;
    MaterialSpecular[2] = 1.0f;

    SpecularIntensity = 1.0f;

}

Material::~Material()
{

}

