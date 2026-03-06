#include "config.h"
#include "shader_utils.h"

/**
 * @brief Compiles shaders
 * 
 * @param fileData shader file in memroy
 * @param module_type type of module in openGL
 * @return * unsigned int The Shader module
 */
unsigned int make_module(char *fileData, unsigned int module_type)
{
    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &fileData, NULL);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        fprintf(stderr, "Shader Module compilation error:\n%s\n", errorLog);

        return -1;
    }

    return shaderModule;
}

/**
 * @brief Compiles shaders and makes program
 * 
 * @param vertexShaderFileData vertex shader in memory
 * @param fragmentShaderFileData fragment shader in memory
 * @return unsigned int The Shader program
 */
unsigned int make_shader(char *vertexShaderFileData, char *fragmentShaderFileData)
{
    std::vector<unsigned int> modules;
    modules.push_back(make_module(vertexShaderFileData, GL_VERTEX_SHADER));
    modules.push_back(make_module(fragmentShaderFileData, GL_FRAGMENT_SHADER));

    unsigned int shader = glCreateProgram();

    for (unsigned int shaderModule : modules) {
        glAttachShader(shader, shaderModule);
    }

    glLinkProgram(shader);

    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    
    if (!success) {
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        fprintf(stderr, "Shader compilation error:\n%s\n", errorLog);

        return -1;
    }

    for (unsigned int shaderModule : modules) {
        glDeleteShader(shaderModule);
    }

    return shader;
}