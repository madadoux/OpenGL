#include "AirCraft.h"
#include "tcamera.h"
#include "Transform.h"
#include "World.h"
#include "ApplicationManager.h"

AirCraft::AirCraft() : GameObject("airCraft", new Transform() , _main_scene)
{
}


AirCraft::~AirCraft()
{
}

#define  rotateAmount 2
#define  speedAmount .01
#define  maxForward 2.f
void AirCraft::HandelKeyBoardInput(int Key){

	float RotRat = 1 / max_speed;
	auto rotateC = clamp(rotateAmount*RotRat, .3f, 2.f); 
	switch (Key)
	{

	case GLFW_KEY_RIGHT:
		transform->roll(rotateC);
		break;

	case GLFW_KEY_LEFT:
		transform->roll(-rotateC);
		break;

	case GLFW_KEY_UP:
		transform->pitch(rotateC);
		break;


	case GLFW_KEY_DOWN:
		transform->pitch(-rotateC);
		break;

	case GLFW_KEY_A:
		max_speed += speedAmount; 
		max_speed = clamp(max_speed, .01f, maxForward); 
		break;

	case GLFW_KEY_S:
		max_speed -= speedAmount;
		max_speed = clamp(max_speed, .01f, maxForward);
	default:
		break;
	}
}

GameObject* AirCraft::myGameObj()
{
	return nullptr; 
}
