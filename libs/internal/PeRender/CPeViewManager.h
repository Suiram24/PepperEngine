#ifndef PEENGINE_CPE_VIEW_MANAGER_H
#define PEENGINE_CPE_VIEW_MANAGER_H

#include <glm/glm.hpp>
#include "CPeBluePrints.h"

namespace vk {
	class ViewManager: public GenericViewManager {
	private:
		GenericRenderer& renderer;

		glm::mat4 viewMatrix;
		glm::vec3 up;
		glm::vec3 eye;
		glm::vec3 center;


	public:
		ViewManager(GenericRenderer& renderer);

		void changeCameraOrientation(float centerX, float centerY, float centerZ);
		void changeCameraPosition(float eyeX, float eyeY, float eyeZ);
		void rotateAroundX(float angle);
		void rotateAroundY(float angle);
		void rotateAroundZ(float angle);
		void rotateAroundAxis(float angle, float x, float y, float z);
		void rotateUpDown(float angle);

		void goForwardX(float distance);
		void goForwardY(float distance);
		void goForwardZ(float distance);

		void goForward(float distance);
		void goRight(float distance);
		void goUp(float distance);

		void submitViewMatrix();

	};
}

#endif