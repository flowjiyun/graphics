#include <iostream>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
  SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
    key, scancode,
    action == GLFW_PRESS ? "pressed" :
    action == GLFW_RELEASE ? "released":
    action == GLFW_REPEAT ? "repeat" : "unknown",
    mods & GLFW_MOD_CONTROL ? "C" : "-",
    mods & GLFW_MOD_SHIFT ? "S" : "-",
    mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }
}
void onFrameBufferSizeChange(GLFWwindow* window, int width, int height) {
  SPDLOG_INFO("frame buffer size changed: ({} x {})", width, height);
  glViewport(0, 0, width, height);
}

void render() {
  glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

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

  onFrameBufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(window, onFrameBufferSizeChange);
  glfwSetKeyCallback(window, onKeyEvent);

  SPDLOG_INFO("Start main loop");
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    render();
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}