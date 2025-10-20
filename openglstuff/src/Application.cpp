#include <GL/glew.h> /*include this before openglthings!*/
#include <GLFW/glfw3.h>
#include "solve.h"
#include "move.h"
#include "solve.h"
#include <iostream>
#include "cubie.h"
#include "RubiksCube.h"
#include "../../TwoPhaseSolver/cubie.h"

int main(void)
{

    //rubiks cube test
    RubiksCube cube;
    cubie::test_compile();
    cube.randomize(20);
    cube.isSolved();
    cube.print();

   

    std::cout << "\nCube test done\n";
   

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