// local headers
#include "glitter.hpp"

// system headers
// glad should be included before all other headers
// that need opengl as glad includes OpenGL header in it
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// standard headers
#include <cstdio>
#include <cstdlib>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processUserInput(GLFWwindow* window);

int main(int argc, char* argv[])
{
  // initialize GLFW and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // create window and OpenGL context
  GLFWwindow* m_window = glfwCreateWindow(m_width, m_height, "OpenGL", nullptr, nullptr);

  // check for valid context
  if (m_window == nullptr)
  {
    fprintf(stderr, "Failed to Create OpenGL Context");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  // make the context of the window current for this thread
  glfwMakeContextCurrent(m_window);

  // set the callback that will be fired when the window is resized
  glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

  // load all OpenGL functions and print version
  int const status = gladLoadGL();
  if (!status)
  {
    fprintf(stderr, "Failed to Initialize GLAD");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

  //////////////////////////////////////////////////////
  // Rendering Loop
  /////////////////////////////////////////////////////
  while (!glfwWindowShouldClose(m_window))
  {
    // process user inputs
    processUserInput(m_window);

    //////////////////
    // Render
    /////////////////
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // swap buffers and poll for IO events to fire callbacks
    glfwSwapBuffers(m_window);
    glfwPollEvents();
  }

  // clear GLFW resources
  glfwTerminate();
  return EXIT_SUCCESS;
}

// query GLFW whether relevant keys are pressed/released and react accordingly
void processUserInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// callback fired when window is resized (by OS or user)
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  // set viewport for mapping OpenGL coordinates
  // according to window size
  glViewport(0, 0, width, height);
}
