#include "camera.h"
#include <glm\gtx\transform.hpp> 
#include <glm\gtc\matrix_transform.hpp>
#include <glm\glm.hpp> 
#include <glm\gtx\rotate_vector.hpp>


	camera::camera()
	{


		_prespective = true;
		_FOV = 90.f;
		_aspectRatio = 4.0 / 3.0f;
		_lookPoint = glm::vec3(0, 0, 0);
		_position = glm::vec3(0, 5, 10);
		mUp = glm::vec3(0, 1, 0);
		_near = .1f, _far = 1000.0f;

		getLookDirection();
		mRight = glm::cross(mUp, mDirection);
	}


	camera::~camera()
	{

	}



	glm::mat4 camera::camView(bool prespective, float FOV,
		float aspectRatio,
		glm::vec3 lookPoint, glm::vec3 position, glm::vec3 direction,
		float Onear, float Ofar){
		_prespective = prespective;
		_FOV = FOV;
		_aspectRatio = aspectRatio;
		_lookPoint = lookPoint;
		_position = position;

		mUp = direction;
		_near = Onear; _far = Ofar;


		return camView();
	}



	glm::mat4 camera::camView(){

		UpdateViewMatrix();
		if (_prespective)
			pMat = glm::perspective(_FOV, _aspectRatio, _near, _far);
		else
			pMat = glm::ortho(-50, 50, 50, -50); // need to be fixed 


		return pMat*vMat;
	}
	void camera::zoom(bool in, float X){
		float  Direction;
		(in) ? Direction = -1 : Direction = 1;

		float angelAmount = 5.0f;
		_FOV += Direction * angelAmount * X;

	}



	glm::mat4 camera::UpdateViewMatrix(){
		auto center = _position + mDirection;//  getLookDirection(); 
		vMat = glm::lookAt(
			_position,
			center,
			mUp
			);
		_lookPoint = center;
		return vMat;
	}

	glm::vec3 camera::getLookDirection(){

		return (mDirection = glm::normalize(_lookPoint - _position));


	}


	void camera::Pitch(float angle){

		mUp = glm::rotate(mUp, angle, mRight);
		mDirection = glm::rotate(mDirection, angle, mRight);

	}

	void camera::Yaw(float angleDegrees)
	{
		mDirection = glm::rotate(mDirection, angleDegrees, mUp);
		mRight = glm::rotate(mRight, angleDegrees, mUp);
	}

	void camera::Roll(float angleDegrees)
	{
		mRight = glm::rotate(mRight, angleDegrees, mDirection);
		mUp = glm::rotate(mUp, angleDegrees, mDirection);
	}


	void camera::Walk(float dist){
		_position += mDirection * dist;

	}

	void camera::Strafe(float dist){
		_position += mRight * dist;
	}

	void camera::Fly(float dist){
		_position += mUp * dist;
	}
