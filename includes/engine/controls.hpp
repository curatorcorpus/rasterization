#ifndef CONTROLS_HPP
#define CONTROLS_HPP

/*
	C++ Libraries
*/
#include <iostream>

/*
	C Libraries
*/
#include <stdlib.h>
#include <stdio.h>
#include <png.h>

#include <camera.hpp>
#include <img_writer.hpp>

/*
	External Libraries
*/
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Controls {

private:

	// DATAFIELDS
	Camera* camera;
	GLFWwindow* window;

	int width, height;

	float key_speed;
	float mouse_speed;
	float horizontal_angle;
	float vertical_angle;

	// CALLBACKS
	
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Controls* test = static_cast<Controls*>(glfwGetWindowUserPointer(window));
		test->key_callback(key, scancode, action, mods);
	}

    // OVERRIDE-ABLE METHODS


	// METHODS


    // GETTERS


    // SETTERS

public:

    // CONSTRUCTORS
    Controls(Camera* camera, GLFWwindow* window);

	// DECONSTRUCTOR
	~Controls();

	// CALLBACKS

	// Used more for an interrupt event.
	void key_callback(int key, int scancode, int action, int mods)
	{
		// Reads current pixels in the frame buffer and saves it as png to disk.
		if(key == GLFW_KEY_F12 && action == GLFW_PRESS)
		{
			int w = 1920;
			int h = 1080;
			std::string file_name = "./test.png";
			//glfwGetWindowSize(window, &w, &h); [THIS BREAKS]
		
			uint8_t *pixels = new uint8_t[w * h * 3];
			glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *)pixels);
			ImgWriter::save_png(file_name, w, h, pixels);

			std::cerr << "[DEBUG::CONTROLS] Screenshot saved!" << std::endl;
		}
	}

	// METHODS
	void update();

	// GETTERS


    // SETTERS
};

#endif