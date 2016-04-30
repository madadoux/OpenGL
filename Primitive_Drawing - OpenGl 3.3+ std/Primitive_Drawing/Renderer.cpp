#include "Renderer.h"
#include "camera.h"
#include "World.h"
#include "GameObject.h"
#include "modelData.h"
#include "shader.hpp"
#include "ShapeGenerator.h"
#include "tcamera.h"

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
		

//	currentMesh= 	ShapeGenerator::MakeTriangle(); 
//	nextmesh = ShapeGenerator::makeQuadMesh(); 



		gizmoz = ShapeGenerator::MakeTriangle(); 

		upT = shared_ptr<Texture>(new Texture("tex/R.png", 1));
		 RightT = shared_ptr<Texture>(new Texture("tex/G.jpg", 1));
		 forwardT = shared_ptr<Texture>(new Texture("tex/B.jpg", 1));

		// Set the background color to blue
		glClearColor(.00f, 0.0f, 0.0f, .50f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		

		Cam = scene->MainCamera;
		tCam = scene->getMainCam(); 
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
			MVP = tCam->camView() * modelmat;
			glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &modelmat[0][0]);

			repit(current->meshs)
			{

				(*it)->Draw();
			}


			//gizmoz 
			if (current->enableGizmoz == true){
				float scaleFac = 1.f;

				mat4 Gmat = mat4(1.0f);


				vec3 WorldPosUp = current->getTransform()->Up() + current->getTransform()->getCurrentPos();
				Gmat = translate(WorldPosUp)*scale(vec3(scaleFac));


				//	Gmat = current->getTransform()->getMatrix() * Gmat; 

				MVP = tCam->camView() * Gmat;

				glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
				upT->Bind();
				gizmoz->Draw();


				vec3 WorldPosright = current->getTransform()->Right() + current->getTransform()->getCurrentPos();
				Gmat = mat4(1.0f);
				Gmat = translate(WorldPosright)*scale(vec3(scaleFac));




				MVP = tCam->camView() * Gmat;
				glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
				RightT->Bind();
				gizmoz->Draw();

				vec3 WorldPosForward = current->getTransform()->Forward() + current->getTransform()->getCurrentPos();
				Gmat = mat4(1.0f);
				Gmat = translate(WorldPosForward)*scale(vec3(scaleFac));


				//Gmat = current->getTransform()->getMatrix() * Gmat;
				MVP = tCam->camView() * Gmat;
				glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
				forwardT->Bind();
				gizmoz->Draw();
			}
		}

	}


	void Renderer::Cleanup()
	{

		glDeleteProgram(programID);
	}

#define cam_walkAmount .5f 

	void Renderer::HandleKeyboardInput(int Key){


		tCam->HandelKeyBoardInput(Key); 
		switch (Key)
		{

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

		glUniform1i(LightChooseID, light_mode);
	}

	void Renderer::HandleMouse(float x, float y){

		tCam->getTransform()->yaw(x);
		tCam->getTransform() ->pitch(-y);
		tCam->UpdateViewMatrix();

		glUniform3fv(EyePositionID, 1, &tCam->getTransform() ->getCurrentPos()[0]);

	};
