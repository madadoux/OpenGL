#pragma once
#include "Utility.h"
#include "GameObject.h"

class AirCraft : public GameObject
{





public:

	float max_speed = 0.1f; 

	void HandelKeyBoardInput(int Key)override;

	GameObject* myGameObj(); 

	AirCraft();
	~AirCraft();
};

