#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include "Shader.h"

using namespace std;

GLuint elements[] = {
    0, 1, 2, 0, 2, 3
};

float vertexInput[] = {
    -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0, 1, //X, Y, R, G, B, U, V
    0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1, 1,
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1, 0,
    -.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0, 0,
};

int main() {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    } else {
        cout << "GLFW initialised successfully" << endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "FUN!", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBufferData(GL_ARRAY_BUFFER, sizeof (vertexInput), vertexInput, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof (elements), elements, GL_STATIC_DRAW);

    Shader shader("vert.vs", "frag.fs");


    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof (GL_FLOAT), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof (GL_FLOAT), (void*) (2 * sizeof (GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof (GL_FLOAT), (void*) (5 * sizeof (GL_FLOAT)));
    glEnableVertexAttribArray(2);


    GLint uniformLocation = glGetUniformLocation(shader.Program, "colorUniform");

    GLuint wallTex, smileTex;
    glGenTextures(1, &wallTex);
    glBindTexture(GL_TEXTURE_2D, wallTex);
    int width, height;
    unsigned char* image = SOIL_load_image("wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &smileTex);
    glBindTexture(GL_TEXTURE_2D, smileTex);
    int width2, height2;
    unsigned char* image2 = SOIL_load_image("smiledog.jpg", &width2, &height2, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image2);
    glBindTexture(GL_TEXTURE_2D, 0);

    int flip = 0;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            flip = flip == 1 ? 0 : 1;
        }
        shader.Use();

        glUniform1i(glGetUniformLocation(shader.Program, "flip"), flip);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, wallTex);
        glUniform1i(glGetUniformLocation(shader.Program, "tex"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, smileTex);
        glUniform1i(glGetUniformLocation(shader.Program, "tex2"), 1);

        float time = (float) clock() / (float) CLOCKS_PER_SEC;
        glUniform3f(uniformLocation, (sin(time * 100.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    glDeleteBuffers(1, &VBO);

    glDeleteVertexArrays(1, &VAO);

    cout << "Killing OpenGL context." << endl;
    glfwTerminate();
    return 0;
}