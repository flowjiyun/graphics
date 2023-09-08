#include <iostream>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
  SPDLOG_INFO("Start Program");

  // glfw 라이브러리 초기화
  SPDLOG_INFO("Initialize glfw");
  if (!glfwInit()) {
    const char* description = nullptr;
    glfwGetError(&description);
    SPDLOG_ERROR("fail to initialize glfw: {}", description);
    return -1;
  }

  // 아래 코드 실행시 윈도우 생성이 안됨.. opengl 지원 문제 때문인지...?
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfw 윈도우 생성
  SPDLOG_INFO("Create glfw window");
  auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
  if (!window) {
    SPDLOG_ERROR("failed to create glfw window");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    SPDLOG_ERROR("failed to initialize glad");
    glfwTerminate();
    return -1;
  }

  auto glVersion = glGetString(GL_VERSION);
  SPDLOG_INFO("OpenGL context version: {}", (char*)glVersion);

  SPDLOG_INFO("Start main loop");
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}