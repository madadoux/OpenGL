#include <gl/glew.h>
#include "shader.hpp"
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp> 
#include"Time.h"
#include "camera.h"
#include <glm\gtx\quaternion.hpp>
#include "World.h"
#include "Utility.h"
using namespace glm; 
using namespace deux; 
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

	
public:	
	
	
	camera* Cam;
    Renderer();
    ~Renderer();
    
    void Initialize();
    void Draw();
    void Cleanup();
};
