#ifndef PEENGINE_CPE_CAMERA_CONTROLLER_H
#define PEENGINE_CPE_CAMERA_CONTROLLER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "CPeBluePrints.h"

namespace controls {

	class CameraController {
	private:
		vk::GenericViewManager* viewManager;
		float displacementSensivity = 0.1f;
		float orientationSensivity = 0.005f;
		double mousePositionX, mousePositionY;
		bool moveMod = false;
		bool mKeyPressed = false;
		bool isQwerty = true;

		bool forward = false;
		bool backward = false;
		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;

		CameraController();

		CameraController(CameraController const&); // prevent copies
		void operator=(CameraController const&); // prevent assignments

		void startGoingForward();
		void startGoingBackward();
		void startGoingLeft();
		void startGoingRight();
		void startGoingUp();
		void startGoingDown();

		void endGoingForward();
		void endGoingBackward();
		void endGoingLeft();
		void endGoingRight();
		void endGoingUp();
		void endGoingDown();

	public:
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		static void getKeyboardInputs(GLFWwindow* window);

		static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

		static CameraController& getInstance();

		static void setViewManager(vk::GenericViewManager& viewManager);

		static void InitialiseView();

		static void ChangeDisplacementSensitivity(float p_sensitivity);

		static void ChangeOrientationSensitivity(float p_sensitivity);
	};
}
#endif