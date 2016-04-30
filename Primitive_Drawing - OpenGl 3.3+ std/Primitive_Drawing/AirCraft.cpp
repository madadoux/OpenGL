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
void AirCraft::HandelKeyBoardInput(int Key){

	switch (Key)
	{

		
	case GLFW_KEY_RIGHT:
		transform->roll(rotateAmount);
		break;

	case GLFW_KEY_LEFT:
		transform->roll(-rotateAmount);
		break;

	case GLFW_KEY_UP:
		transform->pitch(rotateAmount);
		break;


	case GLFW_KEY_DOWN:
		transform->pitch(-rotateAmount);
		break;

	case GLFW_KEY_A:
		max_speed += speedAmount; 
		max_speed = clamp(max_speed, .01f, 1.f); 
		break;

	case GLFW_KEY_S:
		max_speed -= speedAmount;
		max_speed = clamp(max_speed, .01f, 1.f);
	default:
		break;
	}
}

GameObject* AirCraft::myGameObj()
{
	return nullptr; 
}
