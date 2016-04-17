#pragma once
#include <glm\gtx\transform.hpp> 
#include <glm\gtx\quaternion.hpp>
#include <glm\glm.hpp> 
#include "Transform.h"
#include <vector>


using namespace std;
using namespace glm;
namespace deux {


#define PI 3.14
	class Utility
	{
	public:

		static glm::mat4 RotateAround(Transform* m_trans, glm::vec3 point, float angle, glm::vec3 axis);
		static inline float toDegrees(float rad);
		static inline float toRadian(float degree);
		static inline glm::vec3 vec3Up(){ return glm::vec3(0, 1, 0); };
		static inline glm::vec3 vec3Right(){ return glm::vec3(1, 0, 0); };
		static inline glm::vec3 vec3Forward(){ return glm::vec3(0, 0, 1); };
		static inline void Print(glm::vec3  vec , bool newLine = 0 ){
			switch (newLine)
			{
			case 0: 
				printf("%g %g %g ", vec.x, vec.y, vec.z);
				break; 
			case 1:
				printf("%g %g %g \n", vec.x, vec.y, vec.z);
				break;
			default:
				break;
			}
			
		}
		Utility();
		~Utility();
	};

struct color {
		float r, g, b, a; 
	
		color(float _r, float _g, float _b, float _a) :r(_r) , g(_g), b(_b), a(_a)  {
			
		}
		static color Blue(){
			return color(0, 0, 1, 1); 
		}
		static color Red(){
			return color(1, 0, 0, 1);
		}
		static color Green(){
			return color(0,1, 0, 1);
		}
		static color Yellow(){
			return color(1, 1, 0, 1);
		}
		static color White(){
			return color(1, 1, 1, 1);
		}
		static color Black(){
			return color(0, 0, 0, 1);
		}
	};
	struct vert
	{
		glm::vec3 _position;
		color _color;

    	void  attributeVec(vector<glm::vec4>& _data){
			_data.clear();
			_data.push_back(vec4(_position, 1)); 
			_data.push_back(vec4(_color.r, _color.g, _color.b, _color.a));

		}

		vert(glm::vec3 pos, color col) :_position(pos), _color(col) {};
	};

	
}