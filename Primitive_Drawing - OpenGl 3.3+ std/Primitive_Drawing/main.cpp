#include <iostream>
#include <Windows.h>
#include <gl/glew.h>
#include <gl/glfw3.h>
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

	system("pause");
	return 0;
}


