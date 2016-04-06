#pragma once
#include "Transform.h"
namespace deux{
	class World
	{
		

	public:
		Transform* sun;
		Transform*  earth;
		Transform*  moon;
		World();
		void intialize(); 
		~World();
	};

}