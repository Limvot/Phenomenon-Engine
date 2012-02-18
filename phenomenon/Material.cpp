#include "Material.h"

Material::Material()
{
    name = "no_name";
    material_texture = NULL;

    diffuse[0] = 1.0f;
    diffuse[1] = 1.0f;
    diffuse[2] = 1.0f;


    specular[0] = 1.0f;
    specular[1] = 1.0f;
    specular[2] = 1.0f;

    specularHardness[0] = 128.0f;
}

Material::Material(string tmp_name)
{
    name = tmp_name;
    material_texture = NULL;

    diffuse[0] = 1.0f;
    diffuse[1] = 1.0f;
    diffuse[2] = 1.0f;


    specular[0] = 1.0f;
    specular[1] = 1.0f;
    specular[2] = 1.0f;

    specularHardness[0] = 128.0f;
}

Material::~Material()
{

}

int Material::setDiffuse(float r, float g, float b)
{
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;

    return 0;
}

int Material::setSpecular(float r, float g, float b)
{
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;

    return 0;
}

int Material::setSpecularHardness(float hardness)
{
    specularHardness[0] = hardness;

    return 0;
}

int Material::setTexture(Texture* set_tex)
{
    material_texture = set_tex;
    return 0;
}
