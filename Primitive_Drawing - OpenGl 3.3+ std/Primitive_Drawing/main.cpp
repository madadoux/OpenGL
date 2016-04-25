#include <iostream>
#include <Windows.h>
#include <gl/glew.h>
#include <gl/glfw3.h>
#include "Renderer.h"
#include "ApplicationManager.h"


const int WindowSizeWidth =1024, WindowSizeHeight=768; 




int main( void  )
{
	
	
	ApplicationManager* myApp = new ApplicationManager(3, 3.3); 
	myApp->InitalizeApplication( WindowSizeWidth , WindowSizeHeight );
	myApp->StartMainLoop(); 
	myApp->CloseApplication(); 

	delete myApp; 
	system("pause");
	return 0;
}


