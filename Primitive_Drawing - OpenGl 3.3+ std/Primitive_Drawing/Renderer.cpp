#include "Renderer.h"
#include "camera.h"
#include "World.h"
#include "GameObject.h"
#include "modelData.h"
#include "shader.hpp"
#include "ShapeGenerator.h"

	Renderer::Renderer(World* _scene)
	{
		scene = _scene;
	}

	Renderer::~Renderer()
	{
		Cleanup();
	}

	void Renderer::Initialize()
	{
		// Creating Vertex-Array-Object (VAO). Not used here, check the handout to see its importance.
		//VertexArrayID variable is defined in the Renderer.h file


//	currentMesh= 	ShapeGenerator::MakeTriangle(); 
//	nextmesh = ShapeGenerator::makeQuadMesh(); 

		///////////////////////////////////////////////////////////////////////////////////////////
		/// Start Drawing your primitive
		////////////////////////////////

		// Set the background color to blue
		glClearColor(.00f, 0.0f, 0.0f, .50f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		

		Cam = scene->MainCamera;
		programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
		MatID = glGetUniformLocation(programID, "MVP");

	
		ModelMatrixID = glGetUniformLocation(programID, "ModelMatrix");
		//////////////////////////////////////////////////////////////////////////
		// Configure the light.
		//setup the light position.
		LightPositionID = glGetUniformLocation(programID, "LightPosition_worldspace");
		vec3 lightPosition = glm::vec3(1.0, 0.25, 0.0);
		glUniform3fv(LightPositionID, 1, &lightPosition[0]);
		//setup the ambient light component.
		AmbientLightID = glGetUniformLocation(programID, "ambientLight");
		vec3 ambientLight = glm::vec3(0.1, 0.1, 0.1);
		glUniform3fv(AmbientLightID, 1, &ambientLight[0]);
		//setup the eye position.
		EyePositionID = glGetUniformLocation(programID, "EyePosition_worldspace");

		LightChooseID = glGetUniformLocation(programID, "choose_mode");

		 glUseProgram(programID);

	}


	void Renderer::clearScreen(){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Renderer::Draw(GameObject* current)

	{
		
	//	glUseProgram(programID);


if (current != nullptr){

	mat4 modelmat = current->getTransform()->getMatrix();;
	MVP = Cam->camView() * modelmat; 
		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &modelmat[0][0]);

			repit(current->meshs)
			{
			
				(*it)->Draw();
			}
		}
	}


	void Renderer::Cleanup()
	{

		glDeleteProgram(programID);
	}

#define cam_walkAmount .5f 

	void Renderer::HandleKeyboardInput(int Key){

		switch (Key)
		{

		case GLFW_KEY_KP_ADD:
			this->Cam->zoom(1, 2);

			break;
		case GLFW_KEY_KP_SUBTRACT:
			this->Cam->zoom(0, 2);

			break;

		case GLFW_KEY_UP:
			this->Cam->Walk(cam_walkAmount);

			break;
		case GLFW_KEY_DOWN:
			this->Cam->Walk(-cam_walkAmount);

			break;
		case GLFW_KEY_LEFT:
			this->Cam->Strafe(cam_walkAmount);

			break;
		case GLFW_KEY_RIGHT:
			this->Cam->Strafe(-cam_walkAmount);
			break;
		case GLFW_KEY_W:
			this->Cam->Pitch(-2.0f);
			break;

		case GLFW_KEY_S:
			this->Cam->Pitch(+2.0f);
			break;

		case GLFW_KEY_A:
			this->Cam->Yaw(2.0f);
			break;
		case GLFW_KEY_D:
			this->Cam->Yaw(-2.0f);
			break;
		case GLFW_KEY_Q:
			this->Cam->_position.y++;
			break;
		case GLFW_KEY_Z:
			this->Cam->_position.y--;
			break;

		case GLFW_KEY_1:
			light_mode = LightMode::amb; 
			break;
		case GLFW_KEY_2:
			light_mode = LightMode::diffuse;
			break;
		case GLFW_KEY_3:
			light_mode = LightMode::specular;
			break;

		default:
			break;
		}
	}

	void Renderer::HandleMouse(float x, float y){

		Cam->Yaw(x);
		Cam->Pitch(-y);
		Cam->UpdateViewMatrix();

		glUniform3fv(EyePositionID, 1, &Cam->_position[0]);

		glUniform1i(LightChooseID, light_mode); 
	};
