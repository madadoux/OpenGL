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
	// [TODO] 1) create the data array (stored in RAM)
	GLfloat verts[] = {
	0.5f, 0.5f, .50f,
	1, 0, 0,
	0.5f, -0.5f, .50f,
	0, 1, 0,
	-0.5f, -0.5f, .50f,
	0, 0, .5,
	-0.5f, 0.5f, .50f,
	.2, 0, .2,
	0.5f, 0.5f, -.50f,
	0, .5, 0,
	0.5f, -0.5f, -.50f,
	0, .7, 0,
	-0.5f, -0.5f, -.50f,
	.1, .3,0,
	-0.5f, 0.5f, -.50f,
	0, .7, 0,
	};

GLushort indices[] = {  
8 ,10,12,
8,12,14, 
0,8,6 , 
14,8,6 , 
2,4,10 ,
12,4,10 , 
0,2 ,10 ,
0,10,8 ,
6,4,12 , 
6,12,14  ,
0, 2, 4, 
0, 4, 6};


	// [DONE step] 2) create a buffer object name(ID) holder. (initialized in Renderer.h)
	//  its name is "vertexBufferID"
	GLuint v_myBufferID , i_myBufferID;


	glGenBuffers(1, &v_myBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, v_myBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &i_myBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_myBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
	


	 MatID = glGetUniformLocation(programID, "MVP"); 



 // glUseProgram(programID);

}

void Renderer::Draw()
{

	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	glUseProgram(programID);

	

//	
//			float line_vertex[] =
//		{
//			0, 0 ,0,
//			1,0,0,
//			 0, 1,0,
//			0 , 0, 1,
//		};
//
//
//		glVertexPointer(2, GL_FLOAT, 0, line_vertex);
//
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (float)* 3, (void*)0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof (float)* 3, (void*)(sizeof(float)* 3));
//
//MVP = Cam->camView() ; 
//	
//		glDrawArrays(GL_LINES,0, 2);
	

	auto speed = .10f; 
	auto angle = speed * Time::DeltaTime(); 



	//cube 1
	scene->sun->rotate((float)angle, vec3(0, 1, 0)); 
	//scene->sun->move(vec3(1, 0, 0), .001);  
	//scene->sun->RotateAround(vec3(2, 0, 0), angle, vec3(0, 1, 0));
	MVP = Cam->camView() *  scene->sun->getMatrix() ; 
	
		

		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]); 

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT ,GL_TRUE, sizeof (float) *3 , (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof (float)* 3, (void*) (sizeof(float) * 3)) ;
		glDrawElements( GL_TRIANGLES ,12*3, GL_UNSIGNED_SHORT, 0);

		 
	//	//cube 2

	//scene->earth->RotateAround( scene->sun->position , (float)angle*2, vec3(0, 1, 0));
		scene->earth->setMat(scene->sun->getMatrix() *scene->earth->getMatrix());
		scene->earth->rotate(-angle * 2, vec3(0, 1, 0));
		MVP = Cam->camView() * scene->earth->get_mat();



		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		
		glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_SHORT, 0);


		//cube 3
	
	
		scene->moon->setMat(scene->earth->get_mat() *scene->moon->getMatrix());
		scene->moon->rotate(angle * 2, vec3(.5, .5, 0));
		MVP = Cam->camView() * scene->moon->get_mat();

		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);

		glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_SHORT, 0);


}

void Renderer::Cleanup() 
{


	delete Cam	;
	Cam = NULL;
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &vertexArrayID); //the one we didn't used (will be discussed later)
    glDeleteProgram(programID);
}