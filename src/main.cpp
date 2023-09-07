#include <iostream>
#include <spdlog/spdlog.h>
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
  // glfw 윈도우 생성
  SPDLOG_INFO("Create glfw window");
  auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
  if (!window) {
    SPDLOG_ERROR("failed to create glfw window");
    glfwTerminate();
    return -1;
  }

  SPDLOG_INFO("Start main loop");
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}