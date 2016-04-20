#include "World.h"

using namespace glm; 
namespace deux{

	World::World()
	{
	}


	World::~World()
	{

		delete sun;
		sun = NULL; 
		delete earth;
		earth = NULL;
		delete moon; 
		moon = nullptr;		
	}

	void World::intialize(){

		sun = new Transform(vec3(0, 0, 0), glm::angleAxis(00.0f , vec3(1,0,0) ) , vec3(100,100,100));
	     earth = new Transform(vec3(3, 0, 3), quat(0, 0, 1, 0),vec3(.5,.5,.5));
		 moon = new Transform(earth->position + vec3(1, 0, 1), quat(0, 0, 1, 0), vec3(.3, .3, .3));


	}
}