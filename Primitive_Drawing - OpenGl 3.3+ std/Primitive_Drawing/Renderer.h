

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
 tcamera* tCam;
camera* Cam;
		Mesh* gizmoz; 
	

		shared_ptr<Texture> upT, RightT, forwardT; 
	public:



		Renderer( World* _scene );
		~Renderer();
		void HandleMouse(float, float);
		void HandleKeyboardInput(int);
		void Initialize();
		void clearScreen();
		void Draw(GameObject*);
		void Cleanup();
		
	
		vec3 LightIntinsty; 
		LightMode light_mode;

		
		vec3 lightPosition;
		vec3 ambientLight;

	private:
		GLuint ModelMatrixID;
		GLuint LightPositionID;
		GLuint AmbientLightID;
		GLuint EyePositionID;
		GLuint LightChooseID; 
		
	};




#endif // Renderer_h__