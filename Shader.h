/* 
 * File:   Shader.h
 * Author: lolliver
 *
 * Created on 18 February 2015, 18:56
 */

#ifndef SHADER_H
#define	SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

using namespace std;

class Shader {
public:
    Shader();
    GLuint Program;
    Shader(string VertexShaderPath, string FragmentShaderPath);
    virtual ~Shader();
    void Use();
private:

};

#endif	/* SHADER_H */

