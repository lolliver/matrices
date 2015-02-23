/* 
 * File:   Shader.cpp
 * Author: lolliver
 * 
 * Created on 18 February 2015, 18:56
 */

#include "Shader.h"

Shader::Shader() {
}

Shader::Shader(string VertexShaderPath, string FragmentShaderPath) {

    //load VS and FS code into vars
    string vsCode, fsCode;

    try {
        ifstream VertexShaderFile(VertexShaderPath);
        ifstream FragmentShaderFile(FragmentShaderPath);
        stringstream vertShaderStream, fragShaderStream;
        vertShaderStream << VertexShaderFile.rdbuf();
        fragShaderStream << FragmentShaderFile.rdbuf();
        VertexShaderFile.close();
        FragmentShaderFile.close();
        vsCode = vertShaderStream.str();
        fsCode = fragShaderStream.str();

    } catch (exception e) {
        cout << "EXCEPTION WHILE LOADING SHADER FILES, CHECK PATHS" << endl;
    }

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    
    //create the vert shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* szVertShader = vsCode.c_str();
    glShaderSource(vertex, 1, &szVertShader, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        cout << "* Failed to compile vertex shader." << endl;
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << infoLog << endl;
        exit(EXIT_FAILURE);
    }

    //create the frag shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* szFragShader = fsCode.c_str();
    glShaderSource(fragment, 1, &szFragShader, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        cout << "* Failed to compile fragment shader." << endl;
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout << infoLog << endl;
        exit(EXIT_FAILURE);
    }

    //create and link the program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success) {
        cout << "* Failed to link program." << endl;
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        cout << infoLog << endl;
        exit(EXIT_FAILURE);
    }

    //cleanup
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(this->Program);
}

void Shader::Use() {
    glUseProgram(this->Program);
}

