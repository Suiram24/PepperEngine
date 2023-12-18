#include "CPeCameraController.h"
#include <cmath>
#include <iostream>

controls::CameraController::CameraController() :
	viewManager(nullptr),
	mousePositionX(0.0f),
	mousePositionY(0.0f)
{
}

void controls::CameraController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if ((key == GLFW_KEY_M || key == GLFW_KEY_ESCAPE) && action == GLFW_PRESS) {
		std::cout << "Change mod !" << std::endl;
		getInstance().moveMod = !getInstance().moveMod;
		if (getInstance().moveMod == true) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
}

void controls::CameraController::getKeyboardInputs(GLFWwindow* window) {
	//std::cout << "Key pressed !" << std::endl;
	
	if (getInstance().moveMod) {

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			getInstance().startGoingUp();
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			getInstance().startGoingDown();		
		}

		if (getInstance().isQwerty) {
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				getInstance().startGoingForward();
			}

			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				getInstance().startGoingBackward();
			}

			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				getInstance().startGoingLeft();			
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				getInstance().startGoingRight();			
			}
		}
		else {
			if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
				getInstance().startGoingForward();
			}

			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				getInstance().startGoingBackward();
			}

			if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
				getInstance().startGoingLeft();
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				getInstance().startGoingRight();
			}
		}
		getInstance().viewManager->submitViewMatrix();
	}
}

void controls::CameraController::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (getInstance().moveMod) {
		double movementX = xpos - getInstance().mousePositionX;
		double movementY = ypos - getInstance().mousePositionY;
		if (std::abs(movementX) > 0) {
			getInstance().viewManager->rotateAroundX(-getInstance().orientationSensivity * movementX);
		}
		if (std::abs(movementY) > 0) {
			getInstance().viewManager->rotateUpDown(getInstance().orientationSensivity * movementY);
		}
		getInstance().viewManager->submitViewMatrix();
	}
	getInstance().mousePositionX = xpos;
	getInstance().mousePositionY = ypos;
}

void controls::CameraController::startGoingForward() {
	forward = true;
	viewManager->goForward(getInstance().displacementSensivity);
	forward = false;
}
void controls::CameraController::startGoingBackward() {
	backward = true;
	viewManager->goForward(-getInstance().displacementSensivity);
	backward = false;
}
void controls::CameraController::startGoingLeft() {
	left = true;
	viewManager->goRight(-getInstance().displacementSensivity);
	left = false;
}
void controls::CameraController::startGoingRight() {
	right = true;
	viewManager->goRight(getInstance().displacementSensivity);
	right = false;
}
void controls::CameraController::startGoingUp() {
	up = true;
	viewManager->goUp(getInstance().displacementSensivity);
	up = false;
}
void controls::CameraController::startGoingDown() {
	down = true;
	viewManager->goUp(-getInstance().displacementSensivity);
	down = false;
}

void controls::CameraController::endGoingForward() {
	forward = false;
}
void controls::CameraController::endGoingBackward() {
	backward = false;
}
void controls::CameraController::endGoingLeft() {
	left = false;
}
void controls::CameraController::endGoingRight() {
	right = false;
}
void controls::CameraController::endGoingUp() {
	up = false;
}
void controls::CameraController::endGoingDown() {
	down = false;
}

controls::CameraController& controls::CameraController::getInstance() {
	static CameraController instance;
	return instance;
}

void controls::CameraController::setViewManager(vk::GenericViewManager& viewManager) {
	getInstance().viewManager = &viewManager;
}

void controls::CameraController::InitialiseView()
{
	getInstance().viewManager->submitViewMatrix();
}

void controls::CameraController::ChangeDisplacementSensitivity(float p_sensitivity)
{
	getInstance().displacementSensivity = p_sensitivity;
}

void controls::CameraController::ChangeOrientationSensitivity(float p_sensitivity)
{
	getInstance().orientationSensivity = p_sensitivity;
}
