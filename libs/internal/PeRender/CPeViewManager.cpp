#include "CPeViewManager.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

vk::ViewManager::ViewManager(vk::GenericRenderer& renderer) :
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	eye(glm::vec3(2.0f, 0.0f, 0.0f)),
	center(glm::vec3(0.0f, 0.0f, 0.0f)),
	viewMatrix(glm::lookAt(eye, center, up)),
	renderer(renderer)
	{}

void vk::ViewManager::rotateAroundX(float angle)
{
	glm::vec3 direction = glm::normalize(center - eye);
	glm::vec3 newDirection = glm::rotateY(direction, angle);
	float norm = glm::length(center - eye);
	glm::vec3 newCenter = newDirection * norm + eye;
	changeCameraOrientation(newCenter.x, newCenter.y, newCenter.z);
}

void vk::ViewManager::rotateAroundY(float angle)
{
	glm::vec3 direction = glm::normalize(center - eye);
	glm::vec3 newDirection = glm::rotateX(direction, angle);
	float norm = glm::length(center - eye);
	glm::vec3 newCenter = newDirection * norm + eye;
	changeCameraOrientation(newCenter.x, newCenter.y, newCenter.z);
}

void vk::ViewManager::rotateAroundZ(float angle)
{
	glm::vec3 direction = glm::normalize(center - eye);
	glm::vec3 newDirection = glm::rotateZ(direction, angle);
	float norm = glm::length(center - eye);
	glm::vec3 newCenter = newDirection * norm + eye;
	changeCameraOrientation(newCenter.x, newCenter.y, newCenter.z);
}

void vk::ViewManager::rotateAroundAxis(float angle, float x, float y, float z) {
	glm::vec3 direction = glm::normalize(center - eye);
	glm::mat4 rotMat = glm::rotate<float>(angle,glm::vec3(x, y, z));
	glm::vec3 newDirection = glm::vec3(rotMat * glm::vec4(direction,1.0f));

	if (std::abs(glm::dot(glm::normalize(newDirection), glm::vec3(0.0f, 1.0f, 0.0f))) <= 0.90f) {
		float norm = glm::length(center - eye);
		glm::vec3 newCenter = newDirection * norm + eye;
		std::cout << "Change orientation : x: " << newDirection.x << "; y : " << newDirection.y << ";z : " << newDirection.z << std::endl;
		changeCameraOrientation(newCenter.x, newCenter.y, newCenter.z);
	}
}

void vk::ViewManager::rotateUpDown(float angle) {
	glm::vec3 direction = center - eye;
	direction.y = 0;
	direction = glm::normalize(direction);
	direction = glm::rotateY(direction, glm::pi<float>() / 2);
	rotateAroundAxis(angle, direction.x, direction.y, direction.z);
}

void vk::ViewManager::goForward(float distance) {
	glm::vec3 direction = center - eye;
	direction.y = 0;
	direction = glm::normalize(direction)*distance;
	changeCameraPosition(eye.x + direction.x, eye.y, eye.z + direction.z);
}

void vk::ViewManager::goRight(float distance) {
	glm::vec3 direction = center - eye;
	direction.y = 0;
	direction = glm::normalize(direction) * distance;
	direction = glm::rotateY(direction, -glm::pi<float>() / 2);
	changeCameraPosition(eye.x + direction.x, eye.y, eye.z + direction.z);
}

void vk::ViewManager::goUp(float distance) {
	changeCameraPosition(eye.x, eye.y + distance, eye.z);
}

void vk::ViewManager::goForwardX(float distance)
{
	changeCameraPosition(eye.x + distance, eye.y, eye.z);
}

void vk::ViewManager::goForwardY(float distance)
{
	changeCameraPosition(eye.x, eye.y + distance, eye.z);
}

void vk::ViewManager::goForwardZ(float distance)
{
	changeCameraPosition(eye.x, eye.y, eye.z + distance);
}

void vk::ViewManager::submitViewMatrix()
{
	renderer.setViewMatrix(viewMatrix);
}



void vk::ViewManager::changeCameraOrientation(float centerX, float centerY, float centerZ)
{
	center = glm::vec3(centerX, centerY, centerZ);
	//std::cout << "x: " << centerX << "; y: " << centerY << "; z: " << centerZ << std::endl;
	viewMatrix = glm::lookAt(eye,center,up);
}

void vk::ViewManager::changeCameraPosition(float eyeX, float eyeY, float eyeZ)
{
	glm::vec3 distance = center - eye;
	eye = glm::vec3(eyeX, eyeY, eyeZ);
	//std::cout << "eye x : " << eye.x << ";eye y : " << eye.y << ";eye z : " << eye.z << std::endl;
	//std::cout << "center x : " << center.x << ";center y : " << center.y << ";center z : " << center.z << std::endl;
	center = eye + distance;
	viewMatrix = glm::lookAt(eye,center,up);
}
