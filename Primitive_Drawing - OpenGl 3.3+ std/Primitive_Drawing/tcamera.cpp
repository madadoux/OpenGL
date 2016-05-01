#include "tcamera.h"
#include "Transform.h"
#include "World.h"
#include "ApplicationManager.h"
glm::mat4 tcamera::camView(bool Prespective, float FOV, float aspectRatio, glm::vec3 lookPoint, glm::vec3 position, glm::vec3 UP, float Onear, float Ofar)
{
		_prespective = Prespective;
		_FOV = FOV;
		_aspectRatio = aspectRatio;
		_lookPoint = lookPoint;
		transform->setPos(position);

		transform->setForwardAndUp(Utility::vec3Forward(), UP); 
		_near = Onear; _far = Ofar;


		return camView();
}

glm::mat4 tcamera::camView()
{
	UpdateViewMatrix();
	if (_prespective)
		pMat = glm::perspective(_FOV, _aspectRatio, _near, _far);
	else
		pMat = glm::ortho(-50, 50, 50, -50); // need to be fixed 


	return pMat*vMat;
}

glm::mat4 tcamera::UpdateViewMatrix()
{

	vMat = glm::lookAt(
		transform->getCurrentPos(),
		(third ) ? _lookPoint : transform->Forward() + transform->getCurrentPos(),
		 transform->Up() // Utility::vec3Up()
			);
		return vMat;
	
}

void tcamera::zoom(bool inOut, float X)
{

	float  Direction;
	(inOut) ? Direction = -1 : Direction = 1;

	float angelAmount = 5.0f;
	_FOV += Direction * angelAmount * X;

}

tcamera::tcamera(bool _third ) : GameObject("thirdPersonCam", new Transform(), ApplicationManager::getMainScene())
{
	third= _third; 
	_prespective = true;
	_FOV = 60.f;
	_aspectRatio = 4.0 / 3.0f;
	_lookPoint = glm::vec3(0, 0, 0);
	transform->setPos( glm::vec3(0, 5, -10));
	_near = .1f, _far = 5000.0f;

}


tcamera::~tcamera()
{
}
#define cam_walkAmount .5f 

void  tcamera::HandelKeyBoardInput(int Key)  {

	switch (Key)
	{


	case GLFW_KEY_KP_6 : 
		transform->move(-transform->Right(), cam_walkAmount); 
		break; 
	case GLFW_KEY_KP_4:
		transform->move(transform->Right(), cam_walkAmount);
		break;	
	case GLFW_KEY_KP_8:
		transform->move(transform->Forward(), cam_walkAmount);
		break;

	case GLFW_KEY_KP_5:
		transform->move(-transform->Forward(), cam_walkAmount);
		break;

	default:
		break;
	}

}