#include "Texture.h"

Texture::Texture()
{
    name = "no_name";
    texture_id[0] = 0;
}

Texture::Texture(string tmp_name)
{
    name = tmp_name;
    texture_id[0] = 0;
}

Texture::~Texture()
{
    if (texture_id[0] != 0)
    {
        glDeleteTextures(1, texture_id);
        texture_id[0] = 0;
    }
}

int Texture::assignGLid(GLuint texture_id_in)               //Used if not using the load function- the texture has already been loaded by user/library/some other part of phenomenon.
{
    texture_id[0] = texture_id_in;
    return 0;
}

int Texture::load(string file_path)
{
    int return_status = 1; //Return unsucessful if load doesn't suceed

    int w, h, n;            //x, y, and components data from load
    unsigned char *pixels = stbi_load(file_path.c_str(), &w, &h, &n, 0);    //Load the image

    GLenum pixel_format;
    switch (n)                                      //Give OpenGL the same format that is loaded
    {
        case 1:
            pixel_format = GL_LUMINANCE;
            break;

        case 2:
            pixel_format = GL_LUMINANCE8_ALPHA8;    //Pretty sure this is the correct format, but not absolutly positve
            break;

        case 3:
            pixel_format = GL_RGB;
            break;

        case 4:
            pixel_format = GL_RGBA;
            break;

        default:
            pixel_format = GL_RGBA;
            break;
    }


    if (pixels != NULL)
    {
        return_status = 0; //Texure creation sucessful
        //Create the texture
        glGenTextures(1, &texture_id[0]);
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);
        //Generate the texture
        glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, pixel_format, GL_UNSIGNED_BYTE, pixels);

        //Texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {std::cout << "Texture load of " << file_path << " failed.\n";}

    return return_status;
}

int Texture::bind()
{
    //Future- investigate glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    return 0;
}
