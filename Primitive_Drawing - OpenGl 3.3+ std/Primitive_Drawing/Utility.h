#pragma once
#include <glm\gtx\transform.hpp> 
#include <glm\gtx\quaternion.hpp>
#include <glm\glm.hpp> 
#include "Transform.h"
namespace deux {


#define PI 3.14
	class Utility
	{
	public:

		static glm::mat4 RotateAround(Transform* m_trans, glm::vec3 point, float angle, glm::vec3 axis);
		static inline float toDegrees(float rad);
		static inline float toRadian(float degree);
		Utility();
		~Utility();
	};

}