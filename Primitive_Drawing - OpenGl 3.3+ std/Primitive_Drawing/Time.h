#pragma once
#include <GLFW/glfw3.h>



	class Time
	{
		static double time;

	public:

		static double DeltaTime();
		Time();
		~Time();
	};
