#include "Texture.h"

Texture::Texture()
{
    name = "no_name";
    texture_id = 0;
}

Texture::Texture(string tmp_name)
{
    name = tmp_name;
    texture_id = 0;
}

Texture::~Texture()
{

}

int Texture::load(string file_name)
{
    return 0;
}
