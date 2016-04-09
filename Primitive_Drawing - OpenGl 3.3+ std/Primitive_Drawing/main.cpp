#include <iostream>
#include <Windows.h>
#include <gl/glew.h>
#include <gl/glfw3.h>
#include "Renderer.h"
#include "ApplicationManager.h"

bool InitGraphics();
void Proc_input(int Key, Renderer* renderer);
void initInput(GLFWwindow*);
void SpecialKeyPressed(GLFWwindow* window, int key, int
	scancode, int action, int mods);
void MouseMoved(GLFWwindow* window, double xpos, double ypos);
Renderer *renderer;


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




void initInput(GLFWwindow * window){
	MouseXPos = (double)WindowSizeWidth / 2;
	MouseYPos = (double)WindowSizeHeight / 2;
	glfwSetCursorPos(window, MouseXPos, MouseYPos);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, &SpecialKeyPressed);
	glfwSetCursorPosCallback(window, &MouseMoved);

}

void MouseMoved(GLFWwindow* window, double xpos, double ypos) { 
	MouseXPos = xpos; 
	MouseYPos = ypos; 
}
void SpecialKeyPressed(GLFWwindow* window, int key, int
	scancode, int action, int mods) 
{ 
	int KeyPressed=0; 
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		KeyPressed = key;

		Proc_input(KeyPressed, renderer);
	}
}

void Proc_input( int Key , Renderer* renderer ){
	
	
	switch (Key)
	{

	case GLFW_KEY_KP_ADD :
		renderer->Cam->zoom(1, 2); 
	
		break; 
	case GLFW_KEY_KP_SUBTRACT:
		renderer->Cam->zoom(0, 2);
		
		break;

	case GLFW_KEY_UP:
		renderer->Cam->Walk(2.0f);
		
		break;
	case GLFW_KEY_DOWN:
		renderer->Cam->Walk(-2.0f);
		
		break;
	case GLFW_KEY_LEFT:
		renderer->Cam->Strafe(-2.0f);
		
		break;
	case GLFW_KEY_RIGHT:
		renderer->Cam->Strafe(+2.0f);
		break; 
	case GLFW_KEY_W:
		renderer->Cam->Pitch(-2.0f);
		break; 

	case GLFW_KEY_S :
		renderer->Cam->Pitch(+2.0f);
		break;

	case GLFW_KEY_A:
		renderer->Cam->Yaw(2.0f);
		break;
	case GLFW_KEY_D:
		renderer->Cam->Yaw(-2.0f);
		break;
	case GLFW_KEY_Q:
		renderer->Cam->_position.y++;
		break;
	case GLFW_KEY_Z:
		renderer->Cam->_position.y--;
		break;

	default:
		break;
	}	
}

/** 
Creates the main window and initializes OpenGL stuff.
*/
bool InitGraphics()
{
	renderer = new Renderer(); //All drawing code goes here
	GLFWwindow* window;

	// ******************** Initialise GLFW ******************** //
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OpenGL version 3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //If requesting an OpenGL version below 3.2, GLFW_OPENGL_ANY_PROFILE

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( WindowSizeWidth, WindowSizeHeight, "Red triangle", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// ******************** Initialize GLEW ******************** //
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}

	// Ensure we can capture the escape key being pressed below
	
	initInput(window); 


	// ******************** Initialize OpenGL ******************** //
	renderer->Initialize();

	do{ // Loop
	
		//printf("%g  %g \n", MouseXPos, MouseYPos); 

		renderer->Draw();

		// Swap buffers
		glfwSwapBuffers(window); //Displaying our finished scene
		glfwPollEvents(); //try to comment it

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
    // Deleting renderer object will deallocate it's memory and call it's destructor (which calls the renderer's Cleanup method)
    delete renderer;
    return true;

}
