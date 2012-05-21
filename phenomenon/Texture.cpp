#include "Texture.h"

namespace phen {

Texture::Texture()
{
    name = "no_name";
    texture_id[0] = 0;
}

Texture::Texture(std::string tmp_name)
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

int Texture::load(std::string file_path, GLenum min_filter, GLenum mag_filter)         //Defaults for min_filter and mag_filter in .h file
{
    int return_status = 1; //Return unsucessful if load doesn't suceed

    int w, h, n;            //x, y, and components data from load

    std::cout << "about to load image with stbi\n";

    unsigned char *pixels = stbi_load(file_path.c_str(), &w, &h, &n, 0);    //Load the image

    std::cout << "loaded image sucessfully, will now attempt flip\n";

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
        unsigned char pixel_move[n];                                                       //Flip our image to conform to OpenGL's bottom left coord system.
        GLuint pixel_pos = 0;
        GLuint opposite_pixel_pos = 0;
        GLuint maximum_index = (h*w*n);
        std::cout << "Total number of slots in the array should be: " << maximum_index << ".\n";

        for (GLint x_pos = 0; x_pos < w; x_pos += 1)
        {
            for (GLint y_pos = 0; y_pos < (h/2); y_pos += 1)
            {
                pixel_pos = ((w*y_pos)+x_pos)*n;                                        //((w*y_pos)+x_pos)*n is equal to the specified pixel's position in the array (n is the number of components)
                opposite_pixel_pos = ((w*((h-1)-y_pos))+x_pos)*n;                           //((w*(h-y_pos))+x_pos)*n is equal to the specified pixel's vertical opposite

                if (opposite_pixel_pos > (maximum_index-n))
                {
                    std::cout << "Tried to access opposite_pixel_pos: " << opposite_pixel_pos << " out of a maximum of " << maximum_index << " which would cause an error later.\n";
                    opposite_pixel_pos = (maximum_index-n);
                }

                for (GLint i = 0; i < n; i += 1)
                {
                    pixel_move[i] = pixels[pixel_pos+i];                                //Get all pixel components and put them in our pixel_move array
                }

                for (GLint i = 0; i < n; i += 1)
                {
                    pixels[pixel_pos+i] = pixels[opposite_pixel_pos+i];                 //Set all pixel components of our current location to all pixel components of our locations opposite
                }

                for (GLint i = 0; i < n; i += 1)
                {
                    pixels[opposite_pixel_pos+i] = pixel_move[i];                      //Set all pixel components of the opposite to all pixel components of our pixel_move_array
                }
            }
        }

        return_status = 0; //Texure creation sucessful
        //Create the texture
        glGenTextures(1, &texture_id[0]);
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);
        //Generate the texture
        glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, pixel_format, GL_UNSIGNED_BYTE, pixels);

        //Texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

        if (min_filter == GL_NEAREST_MIPMAP_NEAREST || min_filter == GL_NEAREST_MIPMAP_LINEAR || min_filter == GL_LINEAR_MIPMAP_NEAREST || min_filter == GL_LINEAR_MIPMAP_LINEAR)   //If we're using mipmaps
            glGenerateMipmap(GL_TEXTURE_2D);                                                                                                                                        //Generate them

        std::cout << "freeing pixels\n";
        stbi_image_free(pixels);
        pixels = NULL;
        std::cout << "freed pixels\n";
    } else {std::cout << "Texture load of " << file_path << " failed.\n";}

    return return_status;
}

int Texture::bind()
{
    //Future- investigate glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    return 0;
}

} //End Namespace
