

#ifndef _SHAPE_GENERATOR_H 
#define  _SHAPE_GENERATOR_H 




#include "Utility.h"





	using namespace std;
	class ShapeGenerator
	{

		static Mesh* Quad; 
		static Mesh* triangel; 
	public:

		Mesh MakeCube(Mesh& Output);
		Mesh MakeCircle(Mesh& Output);
		Mesh MakeCone(Mesh& Output);

		Mesh MakeSphere(Mesh& Output);
		Mesh MakeCapsule(Mesh& Output);

		
     static Mesh* MakeTriangle();
	
	static	Mesh*   makeQuadMesh();
	static	GameObject* MakeQuadObj(bool  );
	static GameObject* MakeTriangleObj();
	static	GameObject* MakeSkyBOx();

		ShapeGenerator();
		~ShapeGenerator();
	};

	/*
		auto cp = Cam->_position;
		scene  ->Parent->position = vec3(cp.x ,cp.y ,cp.z-100.0f)  ;

		MVP = Cam->camView() * scene->Parent->getMatrix() *  scene->sun->getMatrix();

		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		faces[0].Draw();

		MVP = Cam->camView() * scene->Parent->getMatrix()* glm::translate(100.0f, 0.0f, 100.0f)*  glm::rotate(90.0f, Utility::vec3Up()) * scene->sun->getMatrix();

		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		faces[1].Draw();


		MVP = Cam->camView()* scene->Parent->getMatrix() * glm::translate(00.0f, 0.0f, 200.0f)*  glm::rotate(180.0f, Utility::vec3Up()) * scene->sun->getMatrix();

		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		faces[2].Draw();

		MVP = Cam->camView() * scene->Parent->getMatrix()* glm::translate(-100.0f, 0.0f, 100.0f)*  glm::rotate(-90.0f, Utility::vec3Up()) * scene->sun->getMatrix();

		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		faces[3].Draw();


		MVP = Cam->camView()* scene->Parent->getMatrix() * glm::translate(0.0f, 100.0f, 100.0f)*  glm::rotate(-90.0f, Utility::vec3Right()) * scene->sun->getMatrix();

		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		faces[4].Draw();

		MVP = Cam->camView() * scene->Parent->getMatrix() * glm::translate(0.0f, -100.0f, 100.0f)* glm::rotate(+90.0f, Utility::vec3Right()) * scene->sun->getMatrix();

		glUniformMatrix4fv(MatID, 1, GL_FALSE, &MVP[0][0]);
		faces[5].Draw();*/



#endif 