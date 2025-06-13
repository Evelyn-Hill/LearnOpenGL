#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

// this define instructs the preprocessor to truncate \
// the header such that it only contains what we use. 
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

const char* vertexShaderPath = "src/shaders/vertex.vert";
const char* fragmentShaderPath = "src/shaders/fragment.frag";

const int screenWidth = 1280;
const int screenHeight = 720;

int main(void) {
	spdlog::info("I love you, you got this <3");

	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);
	
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Hello, GL", 0, 0);	

	if (window == NULL)
	{
		spdlog::error("COULD NOT CREATE WINDOW!");
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		spdlog::error("COULD NOT LOAD GLAD");
		return -1;
	}
	
	glViewport(0, 0, screenWidth, screenHeight);
	Shader shader(vertexShaderPath, fragmentShaderPath);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// Define vertex data to send to the GPU
	float verticies[] = {
		// Position         // Color          // Tex Coords
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};
	
	// Define indicies of vertex groups to be rendered, lowering the load on the GPU by removing
	// duplicate verticies.
	unsigned int indices[] = {
		0, 2, 3,
		0, 1, 2,
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

	// Load texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("data/container.jpg", &width, &height, &nrChannels, 0);

	if (data == nullptr)
	{
		spdlog::error("Failed to load image!");
	}
	else 
	{
		// Give the GPU the texture data along with all the meta data it needs to render it.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Tells the gpu about how the data is laid out. 
	
	const int vertexStride = 8;

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexStride * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexStride * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// Tex Coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexStride * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
