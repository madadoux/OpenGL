
#ifndef Transform_h__
#define Transform_h__

#include <glm/gtc/matrix_transform.hpp>
#include <glm\glm.hpp>


#include "Utility.h"



	class  Transform {

	protected:
		///transformation matrix
		   glm::mat4 matrix;	
///position vector
		   glm::vec3 position;
		///rotation quaternion
		glm::mat4 rotation;
		///scale vector
		glm::vec3 scale;	
		vec3 mUp, mRight, mForward;
	public:
    
		GameObject* gameObject; 

		Transform* parent; 
		
	


		///default constructor
		Transform(const glm::vec3 pos = glm::vec3(0),
			const glm::quat rot = glm::quat(),
			glm::vec3 scle = glm::vec3(1, 1, 1) , vec3 forward = vec3(0,0,1) , vec3 up = vec3 (0,1,0));

		///copy constructor
		Transform(const Transform& val);

		void updateMat();
		void setPos(vec3 _pos);
		void setRot(mat4 _rot);
		void setScl(vec3 _scl);
		void applyMatrix(mat4 m);
		///transformation matrix getter
		glm::mat4 getMatrix();
		void setMat(glm::mat4 mat); 
		glm::mat4 get_mat(); 

		
		void rotate(float angle, const glm::vec3 axis);

		///moves the object in some direction by some amount
		void move(const glm::vec3 dir, float val);

	   void  RotateAround( glm::vec3 point, float angle, glm::vec3 axis);
	   void UpdateLocalAxis(mat4 LocalRot);
	   ///returns a look at roataion vecto
		glm::vec4 getLookAt(glm::vec3 point, glm::vec3 up);


		glm::vec3 getCurrentPos();
		glm::vec3 getCurrentScale();
		glm::vec3 getCurrentEulerRot(); 
		glm::quat getCurrentRot();



		void Yaw(float);
		void Pitch(float);
		void Roll(float);

	

		void setForwardAndUp(vec3 forward, vec3 up);
		~Transform();

		vec3 Up();

		glm::vec3 Right();
		glm::vec3 Forward();
	};

#endif // Transform_h__
