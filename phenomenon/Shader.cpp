#include "Shader.h"

namespace phen {

Shader::Shader()
{
    name = "no_name";


}

Shader::Shader(std::string tmp_name)
{
    name = tmp_name;
}

Shader::~Shader()
{

}

int Shader::createShaderProgram(std::string vert_file_path, std::string frag_file_path, GLint trys_remaining)
{
    shader_program = glCreateProgram();
    GLuint vert_shader = getIndividualShader(vert_file_path, GL_VERTEX_SHADER);
    GLuint frag_shader = getIndividualShader(frag_file_path, GL_FRAGMENT_SHADER);

    glAttachShader(shader_program, vert_shader);
    glAttachShader(shader_program, frag_shader);
    glLinkProgram(shader_program);

    GLint sucess = 0;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &sucess);
    if (sucess == 0)
    {
        GLchar error_msg[1024];
        glGetProgramInfoLog(shader_program, sizeof(error_msg), NULL, error_msg);
        std::cout << "Error linking program using " << vert_file_path << " and " << frag_file_path << "\nError: " << error_msg << "\n";
        if (trys_remaining > 0)
        {
            trys_remaining--;
            std::cout << "Trying to create program again! " << trys_remaining << " trys remaining.\n";
            createShaderProgram(vert_file_path, frag_file_path, trys_remaining);
        }
    }
    return 0;
}

int Shader::createShaderProgram(std::string shad_file_path, GLenum type)                                     //Overload so, if we want, we can just load a fragment shader
{
    shader_program = glCreateProgram();
    GLuint shader = getIndividualShader(shad_file_path, type);

    glAttachShader(shader_program, shader);
    glLinkProgram(shader_program);

    GLint sucess = 0;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &sucess);
    if (sucess == 0)
    {
        GLchar error_msg[1024];
        glGetProgramInfoLog(shader_program, sizeof(error_msg), NULL, error_msg);
        std::cout << "Error linking program " << shad_file_path << "\n with error: " << error_msg << "\n";
    }
    return 0;
}

int Shader::enableShader()
{
    //glValidateProgram(shader_program);          //Should remove in final code for preformence reasons.
    glUseProgram(shader_program);
    return 0;
}

int Shader::disableShader()
{
    glUseProgram(0);
    return 0;
}

std::string Shader::readFile(std::string file_path)
{
    std::string file_string;
    std::stringstream ss;
    std::ifstream file_stream(file_path.c_str(), std::ifstream::in);

    if (file_stream.is_open())
    {
        ss << file_stream.rdbuf();
    } else {std::cout << "Could not open file: " << file_path << "\n";}
    return ss.str();
}

GLuint Shader::getIndividualShader(std::string file_path, GLenum type, GLint trys_remaining)
{
    GLuint Shader = glCreateShader(type);

    const char* source = readFile(file_path).c_str();           //Returns a string, which we then call c_str() to make a c array
    const char* source_array[1];
    source_array[0] = source;
    GLint length_array[1];
    length_array[0] = strlen(source);

    glShaderSource(Shader, 1, source_array, length_array);

    glCompileShader(Shader);

    GLint sucess;
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        GLchar error_msg[1024];
        glGetShaderInfoLog(Shader, sizeof(error_msg), NULL, error_msg);
        std::cout << "Error compiling shader of type " << type << " from " << file_path << "\nwith error: " << error_msg << "\n";

        if (trys_remaining > 0)
        {
            trys_remaining--;
            std::cout << "Trying to compile shader again! " << trys_remaining << " trys remaining.\n";
            return getIndividualShader(file_path, type, trys_remaining);
        }
    }
    return Shader;
}

GLuint Shader::getShader()
{
    return shader_program;
}

} //End Namespace
