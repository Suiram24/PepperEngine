#include "CPeViewManager.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
//#include <iostream>

vk::ViewManager::ViewManager(vk::GenericRenderer& renderer) :
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	eye(glm::vec3(2.0f, 2.0f, 2.0f)),
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

void vk::ViewManager::changeCameraOrientation(float centerX, float centerY, float centerZ)
{
	center = glm::vec3(centerX, centerY, centerZ);
	//std::cout << "x: " << centerX << "; y: " << centerY << "; z: " << centerZ << std::endl;
	viewMatrix = glm::lookAt(eye,center,up);
	renderer.setViewMatrix(viewMatrix);
}

void vk::ViewManager::changeCameraPosition(float eyeX, float eyeY, float eyeZ)
{
	eye = glm::vec3(eyeX, eyeY, eyeZ);
	center += eye;
	viewMatrix = glm::lookAt(eye,center,up);
	renderer.setViewMatrix(viewMatrix);
}
