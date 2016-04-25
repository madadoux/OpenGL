

#include "Utility.h"
#ifndef Renderer_h__
#define Renderer_h__


using namespace glm; 
using namespace std; 



	class Renderer
	{

		GLuint programID;
		mat4 MVP;
		GLuint MatID;
		World* scene;
		camera* Cam;
		Mesh* currentMesh;Mesh* nextmesh;
	
	public:



		Renderer( World* _scene );
		~Renderer();
		void HandleMouse(float, float);
		void HandleKeyboardInput(int);
		void Initialize();
		void clearScreen();
		void Draw(GameObject*);
		void Cleanup();

	};




#endif // Renderer_h__