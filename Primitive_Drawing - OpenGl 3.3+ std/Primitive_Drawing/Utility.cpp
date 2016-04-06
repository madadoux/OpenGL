#include "Utility.h"

namespace deux {



	Utility::Utility()
	{
	}


	Utility::~Utility()
	{
	}


	glm::mat4 Utility::RotateAround(Transform* m_trans, glm::vec3 point, float angle, glm::vec3 axis){
		

		return m_trans->getMatrix(); 

	}



	static inline float toDegrees(float rad)
	{
		return rad * (180 / PI);
	}
	static inline float toRadians(float  deg)
	{
		return deg * (PI / 180);
	}
}