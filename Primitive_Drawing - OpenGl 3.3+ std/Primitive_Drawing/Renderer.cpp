#include "Renderer.h"

Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    Cleanup();
}

void Renderer::Initialize()
{
	// Creating Vertex-Array-Object (VAO). Not used here, check the handout to see its importance.
	//VertexArrayID variable is defined in the Renderer.h file
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	///////////////////////////////////////////////////////////////////////////////////////////
	/// Start Drawing your primitive
	////////////////////////////////

	// Set the background color to blue
	glClearColor(.00f, 0.0f, 0.0f, .50f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 
	


	Cam = new camera(); 
	scene = new World();
	scene->intialize(); 
	
	ShapeGenerator sh;

	sh.MakeCube(cube); 
	sh.MakeTriangle(triangle); 

	GLuint v_myBufferID, v_myBufferID2, i_myBufferID, i_myBufferID2;

	glGenBuffers(1, &v_myBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, v_myBufferID);
	glBufferData(GL_ARRAY_BUFFER, cube.DataBufSize(), cube.getDataPtr(), GL_DYNAMIC_DRAW);

	glGenBuffers(1, &i_myBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_myBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.IndicesBufSize(), cube.getIndicesPtr(), GL_STATIC_DRAW);





	programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
	


	 MatID = glGetUniformLocation(programID, "MVP"); 


 // glUseProgram(programID);

}

void Renderer::Draw()
{

	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	glUseProgram(programID);

	auto speed = .10f; 
	auto angle = speed * Time::DeltaTime(); 

	//scene->sun->move(Utility::vec3Right(), Time::DeltaTime()*15); 

	//cube 1
	scene->sun->rotate((float)angle, vec3(0, 1, 0)); 
	//scene->sun->move(vec3(1, 0, 0), .001);  
	//scene->sun->RotateAround(vec3(2, 0, 0), angle, vec3(0, 1, 0));
	MVP = Cam->camView() *  scene->sun->getMatrix() ; 
	
		

		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]); 

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (vec4), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof (vec4), (void*)(sizeof(vec4)));
		glDrawElements(GL_TRIANGLES, cube.getTriangleCount() * 3, GL_UNSIGNED_SHORT, 0);

		 
	//	//cube 2

	//scene->earth->RotateAround( scene->sun->position , (float)angle*2, vec3(0, 1, 0));
		//scene->earth->setMat(scene->sun->getMatrix() *scene->earth->getMatrix());
		//scene->earth->rotate(-angle * 2, vec3(0, 1, 0));
		
		scene->earth->RotateAround(scene->sun->getCurrentPos(), angle, Utility::vec3Up()); 
		//scene->earth->move(Utility::vec3Right(), .001); 
		MVP = Cam->camView() * scene->earth->get_mat();
		auto m = scene->earth->get_mat(); 

		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		
		glDrawElements(GL_TRIANGLES, cube.getTriangleCount()*3 , GL_UNSIGNED_SHORT, 0);


		//cube 3
		Utility::Print(scene->earth->getCurrentPos(),1); 
		scene->moon->RotateAround(scene->earth->getCurrentPos(), angle, Utility::vec3Up());
		//scene->earth->move(Utility::vec3Right(), .001); 
		MVP = Cam->camView() * scene->moon->get_mat();
	//	MVP = Cam->camView() * scene->moon->get_mat();

		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);

		glDrawElements(GL_TRIANGLES, cube.getTriangleCount() * 3, GL_UNSIGNED_SHORT, 0);




}
	
void Renderer::CleanUpGeometery() {
	cube.cleanUp();
	triangle.cleanUp();
}

void Renderer::Cleanup() 
{

	CleanUpGeometery(); 
	delete Cam	;
	Cam = NULL;
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &vertexArrayID); //the one we didn't used (will be discussed later)
    glDeleteProgram(programID);
}



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
		this->Cam->Walk(2.0f);

		break;
	case GLFW_KEY_DOWN:
		this->Cam->Walk(-2.0f);

		break;
	case GLFW_KEY_LEFT:
		this->Cam->Strafe(-2.0f);

		break;
	case GLFW_KEY_RIGHT:
		this->Cam->Strafe(+2.0f);
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

void Renderer::HandleMouse(float x, float y){}; 