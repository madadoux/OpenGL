#include <iostream>
#include <Windows.h>
#include <gl/glew.h>
#include <gl/glfw3.h>
#include "Renderer.h"
#include "ApplicationManager.h"


const int WindowSizeWidth =1024, WindowSizeHeight=768; 
double MouseXPos; 
double MouseYPos;



int main( void  )
{
	//InitGraphics();
	
	ApplicationManager* myApp = new ApplicationManager(3, 3.3); 
	myApp->InitalizeApplication( WindowSizeWidth , WindowSizeHeight );
	myApp->StartMainLoop(); 
	myApp->CloseApplication(); 
	system("pause");
	return 0;
}


