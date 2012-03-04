#include "Texture.h"

Texture::Texture()
{
    name = "no_name";
    texture_image[0] = NULL;
    texture_id[0] = 0;
}

Texture::Texture(string tmp_name)
{
    name = tmp_name;
    texture_image[0] = NULL;
    texture_id[0] = 0;
}

Texture::~Texture()
{

}

int Texture::load(string file_path)
{
    int return_status = 1; //Return unsucessful if load doesn't suceed

    if ((texture_image[0] = SDL_LoadBMP(file_path.c_str())))
    {
        return_status = 0; //Texure creation sucessful
        //Create the texture
        glGenTextures(1, &texture_id[0]);
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);
        //Generate the texture
        glTexImage2D(GL_TEXTURE_2D, 0, 3, texture_image[0]->w, texture_image[0]->h, 0, GL_BGR, GL_UNSIGNED_BYTE, texture_image[0]->pixels);

        //Texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    //Free the surface memory, we don't need it anymore
    if (texture_image[0])
        SDL_FreeSurface(texture_image[0]);

    return return_status;
}

int Texture::bind()
{
    //Future- investigate glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    return 0;
}
