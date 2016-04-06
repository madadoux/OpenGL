#pragma once
#include <glm\glm.hpp>
class camera
{


public:

	glm::mat4 vMat , pMat; 
	bool _prespective;
	float _FOV; 
	float _aspectRatio; 
	glm::vec3 _lookPoint  , _position , _direction ;
	float _near, _far; 

	glm::mat4 camView(bool Prespective , float FOV,
	float aspectRatio,
	glm::vec3 lookPoint, glm::vec3 position, glm::vec3 direction,
	float near, float far);
	glm::mat4 camView(); 

	glm::vec3 mUp, mRight, mDirection; 



	void Yaw(float); 
	void Fly(float);
	void Pitch(float);
	void Roll(float);
	void Walk(float);
	void Strafe(float); 


	glm::mat4 UpdateViewMatrix(); 
	glm::vec3 getLookDirection(); 

	void zoom(bool inOut, float X); 

		camera();
	~camera();
};

