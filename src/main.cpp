#include "ext/matrix_transform.hpp"
#include "ext/vector_float3.hpp"
#include "trigonometric.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>
#include <stdint.h>

#define u16 uint16_t
#define u32 uint32_t
#define u64 uint32_t

#define i16 int16_t
#define i32 int32_t
#define i64 int64_t

// this define instructs the preprocessor to truncate \
// the header such that it only contains what we use.
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void ProcessInput(GLFWwindow *window);

const char *vertexShaderPath = "src/shaders/vertex.vert";
const char *fragmentShaderPath = "src/shaders/fragment.frag";

const u16 screenWidth = 1280;
const u16 screenHeight = 720;

int main(void) {
  spdlog::info("I love you, you got this <3");

  glfwInit();
  glfwWindowHint(GLFW_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_VERSION_MINOR, 6);

  GLFWwindow *window =
      glfwCreateWindow(screenWidth, screenHeight, "Hello, GL", 0, 0);

  if (window == NULL) {
    spdlog::error("COULD NOT CREATE WINDOW!");
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    spdlog::error("COULD NOT LOAD GLAD");
    return -1;
  }

  glViewport(0, 0, screenWidth, screenHeight);
  Shader shader(vertexShaderPath, fragmentShaderPath);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Define vertex data to send to the GPU
  float verticies[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
  };

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.7f, 5.0f, -15.0f),
		glm::vec3(-2.0f, 5.4f, -2.5f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(2.5f, 0.2f, -1.5f),
	};

  // Define indicies of vertex groups to be rendered, lowering the load on the
  // GPU by removing duplicate verticies.
  unsigned int indices[] = {
      0, 2, 3, 0, 1, 2,
  };

  // Create a new texture
  unsigned int texture;
  glGenTextures(1, &texture);
  // Binds the texture object to the type of GL_TEXTURE_2D
  glBindTexture(GL_TEXTURE_2D, texture);

  // Set the texture repeating mode for the S and T (x and y) directions.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  // set the filtering mode for downscaling (min) and upscaling (max) textures.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Load texture
  int width, height, nrChannels;
  unsigned char *data =
      stbi_load("data/container.jpg", &width, &height, &nrChannels, 0);

  if (data == nullptr) {
    spdlog::error("Failed to load image!");
  } else {
    // Give the GPU the texture data along with all the meta data it needs to
    // render it.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  // Free the image data from ram now that it is in GPU memory.
  stbi_image_free(data);

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  // Sends the data to the GPU.
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // Tells the gpu about how the data is laid out.

  const int vertexStride = 5;

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexStride * sizeof(float),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexStride * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
	
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);


  while (!glfwWindowShouldClose(window)) {
    ProcessInput(window);

	glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.use();
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, texture);


	
	glm::mat4 view = glm::mat4(1);
	view = glm::translate(view, cameraPos);
		
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f); 

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos += glm::vec3(0.001f, 0.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos += glm::vec3(-0.001f, 0.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += glm::vec3(0.0f, 0.0f, 0.001f);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos += glm::vec3(0.0f, 0.0f, -0.001f);
	}
		
	int viewLoc = glGetUniformLocation(shader.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	int projLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	
	for(auto i = 0; i < 10; i++)
	{

		glm::mat4 model = glm::mat4(1);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.05 * (i + 1);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, sin(glfwGetTime() * i), 1.0f));

		int modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow *window) {

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
