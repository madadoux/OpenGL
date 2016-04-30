#pragma once
#include "Utility.h"
#include "GameObject.h"
class tcamera : public GameObject
{



	glm::mat4 vMat, pMat;
	bool _prespective;
	float _FOV;
	float _aspectRatio;
	
	float _near, _far;


	





	

public:
	
	glm::vec3 _lookPoint;
	glm::mat4 camView(bool Prespective, float FOV,
		float aspectRatio,
		glm::vec3 lookPoint, glm::vec3 position, glm::vec3 direction,
		float near, float far);
	glm::mat4 camView();
	glm::mat4 UpdateViewMatrix();
	void zoom(bool inOut, float X);

	tcamera(bool third);

   bool third; 
	
	~tcamera();

};

