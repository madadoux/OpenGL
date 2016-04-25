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


	currentMesh= 	ShapeGenerator::MakeTriangle(); 
	nextmesh = ShapeGenerator::makeQuadMesh(); 

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


		 glUseProgram(programID);

	}


	void Renderer::clearScreen(){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Renderer::Draw(GameObject* current)

	{
		
		glUseProgram(programID);

		//MVP = Cam->camView() * glm::translate(0.f, 0.f, 0.f) * mat4(1.0);
		//glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		//currentMesh->Draw();

		//MVP = Cam->camView() * glm::translate(5.f, 0.f, 0.f) * mat4(1.0);
		//glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		//nextmesh->Draw();


		//MVP = Cam->camView() * glm::translate(0.f, 2.f, 0.f) * mat4(1.0);
		//glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		//currentMesh->Draw();


		//MVP = Cam->camView() * glm::translate(2.f, 0.f, 0.f) * mat4(1.0);
		//glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		//nextmesh->Draw();


if (current != nullptr){
		MVP = Cam->camView() * current->getTransform()->getMatrix();
		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		
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

		default:
			break;
		}
	}

	void Renderer::HandleMouse(float x, float y){

		Cam->Yaw(x);
		Cam->Pitch(-y);
		Cam->UpdateViewMatrix();

	};
