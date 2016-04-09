#include <gl/glew.h>
#include "shader.hpp"
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp> 
#include"Time.h"
#include "camera.h"
#include <glm\gtx\quaternion.hpp>
#include <vector> 
#include "World.h"
#include "Utility.h"
#include "ShapeGenerator.h"
#include "modelData.h"
using namespace glm; 
using namespace deux; 
using namespace std; 
#pragma once

class Renderer
{
    GLuint vertexArrayID;
    GLuint vertexBufferID;
    GLuint programID;
	mat4 MVP; 
	GLuint MatID;
	World* scene; 
	mat4 vMat, pMat; 
	modelData cube, triangle;
public:	
	
	
	camera* Cam;
    Renderer();
    ~Renderer();
	void HandleMouse(float , float );
    void HandleKeyboardInput(int );
    void Initialize();
    void Draw();
    void Cleanup();
};



