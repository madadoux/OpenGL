//
// Created by Moustapha on 07/10/2015.
//

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm\glm.hpp>
#include "Utility.h"


using namespace std;
using namespace glm;
using namespace deux;

Transform::Transform(const glm::vec3 pos, const glm::quat rot, glm::vec3 scl) 
{
	position = pos;
	rotation = rot;
	scale = scl;
}

Transform::Transform(const Transform& val) 
{
	position = val.position;
	rotation = val.rotation;
	scale = val.scale;
}

glm::mat4 Transform::getMatrix()
{
	mat4 translation = translate(mat4(1), position);
	mat4 scl = glm::scale(mat4(1), scale);
	mat4 rot = glm::mat4_cast(rotation);

	return  translation*rot*scl;
}

void Transform::rotate(float angle,const glm::vec3 axis )
{
	rotation = glm::angleAxis(angle, axis) *rotation ;
	getMatrix(); //update matrix
}

void Transform::move(const glm::vec3 dir, float val)
{
	position += dir*val;
}

glm::vec4 Transform::getLookAt(glm::vec3 point, glm::vec3 up)
{
	return vec4(0);
}

Transform::~Transform(){
	printf( "trans dest .\n");
}


void   Transform::RotateAround(glm::vec3 point, float angle, glm::vec3 axis){

    auto T1 = glm::translate(-point);

	auto R = glm::rotate(angle, axis);

	auto T2 = glm::translate(point);
	// world <- local * world 
	rotation = glm::toQuat(T2 * R * T1);

	//matrix =  T2 * R * T1 * matrix; 

}
void Transform::setMat(mat4 mat){
	matrix = mat; 
}

glm::mat4 Transform::get_mat(){
	return matrix; 
}


