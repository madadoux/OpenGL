#pragma once



#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <math.h>
#include <sstream>
#include <vector>
#include <sstream>
#include <cstdio>
#include <set>
#include <stack>
#include <queue>
#include <time.h>
#include <map>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <list>
#include <time.h>
#include <limits.h>
#include <stdint.h>
#include <glm\glm.hpp> 

#include <glm\gtx\transform.hpp> 
#include <glm\gtx\quaternion.hpp>
#include <gl/glew.h>
#include <memory>
#include <glm\glm.hpp>
#include <Windows.h>
#include <gl/glew.h>
#include <gl/glfw3.h>


#define ss stringstream
#define all(T)  T.begin() , T.end()
#define allr(T)  T.rbegin() , T.rend()
#define pii pair<int ,int >
#define ll long long
#define uint unsigned int
#define vi vector<ll>
#define ef else if
#define re  return
#define rep2(n,m)  for(int i= 0 ; i<n ; i++) for(int j= 0 ; j<m ; j++)
#define repr(a,b)  for( int i =a ;i< b ;i++)
#define rep(n) for(int i= 0 ; i<n ; i++)
#define rep1(n) for (int i=1 ;i<=n ;i++)
#define repit(cont)  for ( auto it = cont.begin() ; it!= cont.end() ; it++)
#define repitr(a,b) for ( auto it = a ; it!= b ; it++)
#define  _main_scene ApplicationManager::getMainScene()


using namespace std;
using namespace glm;

class camera; 
class GameObject;
class Transform; 
class Mesh;
class Renderer; 
class ShapeGenerator; 
class Time; 
class Texture; 
class World;
class shader;
class ApplicationManager; 
class tcamera; 
class AirCraft; 
enum LightMode
{
	amb =1 , diffuse , specular 
};

enum std_meshs
{
	quad = 1 

};
	
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
		static inline glm::vec3 vec3Zero(){ return glm::vec3(0, 0, 0); };
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

		vec4 toVec4(){
			return vec4(r, g, b, a); 
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
		static color NULLC(){
			 return color(0, 0, 0, 0);
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

	



	//freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
	//DEUX_COPY_RIGHTS_RESERVED


	//ll OO = 10e9;

	//Computational Geometery
	class Vector2D
	{
	public:

		float   x;
		float   y;

		Vector2D() {}

		Vector2D(float r, float s)
		{
			x = r;
			y = s;
		}

		Vector2D& Set(float r, float s)
		{
			x = r;
			y = s;
			return (*this);
		}

		float& operator [](long k)
		{
			return ((&x)[k]);
		}

		const float& operator [](long k) const
		{
			return ((&x)[k]);
		}

		Vector2D& operator +=(const Vector2D& v)
		{
			x += v.x;
			y += v.y;
			return (*this);
		}

		Vector2D& operator -=(const Vector2D& v)
		{
			x -= v.x;
			y -= v.y;
			return (*this);
		}

		Vector2D& operator *=(float t)
		{
			x *= t;
			y *= t;
			return (*this);
		}

		Vector2D& operator /=(float t)
		{
			float f = 1.0F / t;
			x *= f;
			y *= f;
			return (*this);
		}

		Vector2D& operator &=(const Vector2D& v)
		{
			x *= v.x;
			y *= v.y;
			return (*this);
		}

		Vector2D operator -(void) const
		{
			return (Vector2D(-x, -y));
		}

		Vector2D operator +(const Vector2D& v) const
		{
			return (Vector2D(x + v.x, y + v.y));
		}

		Vector2D operator -(const Vector2D& v) const
		{
			return (Vector2D(x - v.x, y - v.y));
		}

		Vector2D operator *(float t) const
		{
			return (Vector2D(x * t, y * t));
		}

		Vector2D operator /(float t) const
		{
			float f = 1.0F / t;
			return (Vector2D(x * f, y * f));
		}

		float operator *(const Vector2D& v) const
		{
			return (x * v.x + y * v.y);
		}

		Vector2D operator &(const Vector2D& v) const
		{
			return (Vector2D(x * v.x, y * v.y));
		}

		bool operator ==(const Vector2D& v) const
		{
			return ((x == v.x) && (y == v.y));
		}

		bool operator !=(const Vector2D& v) const
		{
			return ((x != v.x) || (y != v.y));
		}

		Vector2D& Normalize(void)
		{
			return (*this /= sqrtf(x * x + y * y));
		}

		Vector2D& Rotate(float angle){
			float s = sinf(angle);
			float c = cosf(angle);

			float nx = c * x - s * y;
			float ny = s * x + c * y;

			x = nx;
			y = ny;

			return (*this);
		};
	};


	class Point2D : public Vector2D
	{
	public:

		Point2D() {}

		Point2D(float r, float s) : Vector2D(r, s) {}

		Point2D& operator =(const Vector2D& v)
		{
			x = v.x;
			y = v.y;
			return (*this);
		}

		Point2D& operator *=(float t)
		{
			x *= t;
			y *= t;
			return (*this);
		}

		Point2D& operator /=(float t)
		{
			float f = 1.0F / t;
			x *= f;
			y *= f;
			return (*this);
		}

		Point2D operator -(void) const
		{
			return (Point2D(-x, -y));
		}

		Point2D operator +(const Vector2D& v) const
		{
			return (Point2D(x + v.x, y + v.y));
		}

		Point2D operator -(const Vector2D& v) const
		{
			return (Point2D(x - v.x, y - v.y));
		}

		Vector2D operator -(const Point2D& p) const
		{
			return (Vector2D(x - p.x, y - p.y));
		}

		Point2D operator *(float t) const
		{
			return (Point2D(x * t, y * t));
		}

		Point2D operator /(float t) const
		{
			float f = 1.0F / t;
			return (Point2D(x * f, y * f));
		}
	};


	inline Vector2D operator *(float t, const Vector2D& v)
	{
		return (Vector2D(t * v.x, t * v.y));
	}

	inline Point2D operator *(float t, const Point2D& p)
	{
		return (Point2D(t * p.x, t * p.y));
	}

	inline float Dot(const Vector2D& v1, const Vector2D& v2)
	{
		return (v1 * v2);
	}

	inline float Magnitude(const Vector2D& v)
	{
		return (sqrtf(v.x * v.x + v.y * v.y));
	}

	inline float InverseMag(const Vector2D& v)
	{
		return (1.0F / sqrtf(v.x * v.x + v.y * v.y));
	}

	inline float SquaredMag(const Vector2D& v)
	{
		return (v.x * v.x + v.y * v.y);
	}


	struct Origin2D_
	{
		const Point2D& operator +(const Vector2D& v)
		{
			return (static_cast<const Point2D&>(v));
		}

		Point2D operator -(const Vector2D& v)
		{
			return (Point2D(-v.x, -v.y));
		}
	};

	struct P {
		P(int x, int y)
		{
			this->x = x;
			this->y = y;
		}
		double x, y;
	};

	//END
