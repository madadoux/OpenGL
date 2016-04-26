//
// 
//

#include "Transform.h"
#include "GameObject.h"
#include "World.h"

//#include <glm/gtx/>

using namespace std;
using namespace glm;




	Transform::Transform(const glm::vec3 pos, const glm::quat _rot, glm::vec3 _scl)
	{
		this->parent = World::getRootTrans();
		position = pos;
		rotation = glm::mat4_cast(_rot);
		scale = _scl;
		parent = nullptr; 

      
	}

	Transform::Transform(const Transform& val)
	{
		parent =  val.parent;
		position = val.position;
		rotation = val.rotation;
		scale = val.scale;
	}

	void Transform::updateMat(){

        mat4 translation = translate(position);
		mat4 scl = glm::scale(scale);
		matrix = translation*rotation*scl;
	
	}


	void Transform::setPos(vec3 _pos){
		position = _pos; 
		updateMat(); 

	}

	void Transform::setRot(mat4 _rot){
		rotation = _rot;
		updateMat();

	}

	void Transform::setScl(vec3 _scl){
		scale = _scl;
		updateMat();

	}
	void  Transform::applyMatrix(mat4 m){

		matrix = m*matrix ; 

	}
	glm::mat4 Transform::getMatrix()
	{
		
		if ( parent!=nullptr)
		return  parent->getMatrix()*  matrix;
		else 
		return  matrix;
	}

	void Transform::rotate(float angle, const glm::vec3 axis)
	{
		rotation = glm::rotate(angle, axis) *rotation;
		updateMat(); 
	}

	void Transform::move(const glm::vec3 dir, float val)
	{
		position += dir*val;
		updateMat();
	}

	glm::vec4 Transform::getLookAt(glm::vec3 point, glm::vec3 up)
	{
		return vec4(0);
	}

	Transform::~Transform(){
		printf("trans dest .\n");
	}


	void   Transform::RotateAround(glm::vec3 point, float angle, glm::vec3 axis){

		auto T1 = glm::translate(-point);
		auto R = glm::rotate(angle, axis);
		auto T2 = glm::translate(point);
		// world <- local * world 
		matrix = T2 * R * T1*matrix;


	}
	void Transform::setMat(mat4 mat){
		matrix = mat;
	}

	glm::mat4 Transform::get_mat(){
		return matrix;
	}

	glm::vec3 Transform::getCurrentPos()
	{
		return vec3(matrix[3].x, matrix[3].y, matrix[3].z);
	}
