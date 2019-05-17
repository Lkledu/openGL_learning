#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window; //Struct de janela

#include <glm/glm.hpp>
using namespace glm;

void printVersion() {
	printf("openGL version: %s\nrender version: %s\n", glGetString(GL_VERSION), glGetString(GL_RENDERER));
}

int initGLFW() {
	if (!glfwInit()) {
		
fprintf(stderr, "Failed to initialize GLFW\n");
		printf("Failed to initialize GLFW\n");
		return -1;
	}
	else {
		printf("Initialize GLFW\n");
	}
}

int initGLEW() {
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		printf("Failed to initialize GLEW\n");
		return -1;
	}
	else {
		printf("Initialize GLEW\n");
	}
}

//jun��o das chamadas fun��es windowsHint
void glfwHintSetup() {

	glfwWindowHint(GLFW_SAMPLES, 4); //anti alisign 4x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //to work on MacOS well
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // to not use older versions

	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
}

GLFWwindow* windowCreation() {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	return glfwCreateWindow(mode->width, mode->height, "My Title", NULL, NULL);
}

int setContextWindow(GLFWwindow *window) {
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		printf("Failed to open GLFW window\n");
		glfwTerminate();
		return -1;
	}
	else {
		glfwMakeContextCurrent(window); //define a janela como o contexto atual
		printf("GLFW window opened\n"); 
	}
}


void VAO() {
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

GLuint createTriangle() {
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexbuffer;
}

void drawTriangle(GLuint vertexbuffer) {
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}

int main(void) {
	initGLFW();
	glfwHintSetup();

	window = windowCreation();
	setContextWindow(window);
	initGLEW();
	
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); //define input mode para aceitar valores do teclado
	
	VAO();
	GLuint vertexBuffer = createTriangle();
	do {
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw nothing, see you in tutorial 2 !
		drawTriangle(vertexBuffer);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}