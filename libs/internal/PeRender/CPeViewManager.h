#ifndef PEENGINE_CPE_VIEW_MANAGER_H
#define PEENGINE_CPE_VIEW_MANAGER_H

#include <glm/glm.hpp>
#include "CPeBluePrints.h"

namespace vk {
	class ViewManager {
	private:
		GenericRenderer& renderer;

		glm::mat4 viewMatrix;
		glm::vec3 up;
		glm::vec3 eye;
		glm::vec3 center;


		void changeCameraOrientation(float centerX, float centerY, float centerZ);
		void changeCameraPosition(float eyeX, float eyeY, float eyeZ);
	public:
		ViewManager(GenericRenderer& renderer);

		void rotateAroundX(float angle);
		void rotateAroundY(float angle);
		void rotateAroundZ(float angle);

	};
}

#endif