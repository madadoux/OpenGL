//
// 
//

#include "Transform.h"
#include "GameObject.h"
#include "World.h"
#include <glm/gtx/quaternion.hpp>
#include <glm\gtx\transform.hpp> 
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\rotate_vector.hpp>
//#include <glm/gtx/>
//#include <glm/gtx/matrix_decompose.hpp>
using namespace std;
using namespace glm;




	Transform::Transform(const glm::vec3 pos, const glm::quat _rot, glm::vec3 _scl , vec3 forward , vec3 up )
	{

		mForward = normalize( forward);
		mUp = normalize(up); 
		this->parent = World::getRootTrans();
		position = pos;
		rotation = glm::mat4_cast(_rot);
		scale = _scl;
		parent = nullptr; 
		mRight = glm::cross(mUp, mForward);
      
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

		matrix = matrix*m ; 

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
		rotation =   rotation*  glm::rotate(angle, axis)  ;
		updateMat(); 

		UpdateLocalAxis(glm::rotate(angle, axis)); 
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


	glm::vec3 Transform::Up()
	{
		return mUp;
	}


	glm::vec3 Transform::Right()
	{
		return mRight;
	}

	glm::vec3 Transform::Forward()
	{
		return mForward;
	}

	void   Transform::RotateAround(glm::vec3 point, float angle, glm::vec3 axis){

		auto T1 = glm::translate(-point);
		auto R = glm::rotate(angle, axis);
		auto T2 = glm::translate(point);
		mat4 localRot = T2* R * T1 ; 
		rotation = rotation* localRot ; 
		updateMat(); 
		UpdateLocalAxis(localRot);


	}



	void Transform::UpdateLocalAxis(mat4 LocalRot){


		quat  tmp(LocalRot);
		vec3 euleredAngled = eulerAngles(tmp);
		Utility::Print(euleredAngled, true);

		Pitch(euleredAngled.x);

		Yaw(euleredAngled.y);

		Roll(euleredAngled.z);
	}
	void Transform::setMat(mat4 mat){
		matrix = mat;
	}

	glm::mat4 Transform::get_mat(){
		return matrix;
	}

	glm::vec3 Transform::getCurrentPos()
	{
		mat4 mat = getMatrix(); 
		return vec3(mat[3].x, mat[3].y, mat[3].z);
	}


	void Transform::Pitch(float angle){

		mUp = glm::rotate(mUp, angle, mRight);
		mForward = glm::rotate(mForward, angle, mRight);

	}

	void Transform::Yaw(float angleDegrees)
	{
		mForward = glm::rotate(mForward, angleDegrees, mUp);
		mRight = glm::rotate(mRight, angleDegrees, mUp);
	}

	void Transform::Roll(float angleDegrees)
	{
		mRight = glm::rotate(mRight, angleDegrees, mForward);
		mUp = glm::rotate(mUp, angleDegrees, mForward);
	}


	void Transform::setForwardAndUp(vec3 forward, vec3 up){
		mUp = up; 
		mForward = forward; 
		mRight = glm::cross(mUp, mForward);
	}	