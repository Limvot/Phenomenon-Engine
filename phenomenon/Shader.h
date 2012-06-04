#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include "stdlib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

namespace phen {

class Shader
{
    public:
        Shader();
        Shader(std::string tmp_name);
        virtual ~Shader();

        int createShaderProgram(std::string vert_file_path, std::string frag_file_path, GLint trys_remaining = 5);
        int createShaderProgram(std::string shad_file_path, GLenum type);                                        //Overloaded so, if we want, we can load just a fragment shader
        int enableShader();
        int disableShader();
        std::string readFile(std::string file_path);
        GLuint getIndividualShader(std::string file_path, GLenum type, GLint trys_remaining = 5);
        GLuint getShader();

        std::string name;

    protected:
        GLuint shader_program;

    private:
};

} //End Namespace

#endif // SHADER_H
