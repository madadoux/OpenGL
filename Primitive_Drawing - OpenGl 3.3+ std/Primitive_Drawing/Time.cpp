#include "Time.h"


Time::Time()
{


}


Time::~Time()
{
}


 double Time::DeltaTime(){

	double currentTime = glfwGetTime(); 
	double deltaTime = (currentTime - time) * 1000; 
	time = currentTime; 
	return deltaTime;

}

 double  Time::time = glfwGetTime();