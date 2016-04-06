#pragma once 
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp> 

namespace deux{

	class  Transform {

	protected:
		///transformation matrix
		   glm::mat4 matrix;
	public:
     
		///postion vector
		glm::vec3 position;
		///rotation quaternion
		glm::quat rotation;
		///scale vector
		glm::vec3 scale;

		///default constructor
		Transform(const glm::vec3 pos = glm::vec3(0),
			const glm::quat rot = glm::quat(),
			glm::vec3 scle = glm::vec3(1, 1, 1));

		///copy constructor
		Transform(const Transform& val);

		///transformation matrix getter
		glm::mat4 getMatrix();
		void setMat(glm::mat4 mat); 
		glm::mat4 get_mat(); 

		
		void rotate(float angle, const glm::vec3 axis);

		///moves the object in some direction by some amount
		void move(const glm::vec3 dir, float val);

	   void  RotateAround( glm::vec3 point, float angle, glm::vec3 axis);
		///returns a look at roataion vecto
		glm::vec4 getLookAt(glm::vec3 point, glm::vec3 up);


		~Transform(); 
	};
}
