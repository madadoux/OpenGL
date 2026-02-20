#include <iostream>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "ApplicationManager.h"


const int WindowSizeWidth =1024, WindowSizeHeight=768;




int main( void  )
{
	ApplicationManager myApp(3, 3.3);
	if (myApp.InitalizeApplication(WindowSizeWidth, WindowSizeHeight))
	{
		myApp.StartMainLoop();
	}

	#ifdef _WIN32
	system("pause");
	#endif
	return 0;
}

