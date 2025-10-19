#include <GL/glew.h> /*include this before openglthings!*/
#include <GLFW/glfw3.h>

#include <iostream>

#include "RubiksCube.h"

int main(void)
{

    //rubiks cube test
    RubiksCube cube;
    cube.print();

    std::cout << "\nRotating Front face clockwise...\n";
    cube.rotateFace(F, true);
    cube.rotateFrontEdgesClockWise();
    cube.print();

    std::cout << "\nFront counterclockwise...\n";
    cube.rotateFrontEdgesCounterClockWise();
    cube.print();
    std::cout << "Cube logic test done.\n\n";

    ///////

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
   

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "im alive", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) /*needs to be after window context, check glew documentation*/
        std::cout << "Glew Init has failed" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}