#pragma once
#include <glm\glm.hpp>
#include < vector>
#include "Utility.h"
#include <gl/glew.h>
using namespace glm; 
using namespace std; 
using namespace deux;



enum RenederMode{
	VBO, IBO
};
class modelData
{

	RenederMode renderMode = RenederMode::IBO; 
	vector <vec3 > vertsPos; 
	vector <vec4 > vertColor;

	vector<GLushort> indices;

	int _attributeCount ;
	 
	GLuint mVertexArrayObjectID; 
	GLuint v_myBufferID, c_myBufferID, i_myBufferID, uv_myBufferID;

	
public:
	vector < vec2 > UVdata; 
	void setRenderMode(RenederMode); 
	bool EnableColor , EnableTexture ;
	void cleanUp(); 
	void pushVert(vert  v); 
	void setAttCount(int); 
	int getAttCount(); 
	int IndicesBufSize(); 
		
	int getVertPosBufSize();
	int getVerColBufSize();
	vector<vec3> GetVertPosData();
	vector<vec4> GetColorPosData();
    vector< GLushort > getIndices();
    vector < vec2> getUVdata(); 

	void insertVert(vert v, uint pos); 
	void deleteVert( uint pos);
	void addTriangleIndices(short a, short b, short c); 
	void setSimpleIndices(vector<GLushort> ind);

	void pushUV(vec2 v); 
	int getUVBufSize(); 


	void Initialize(); 
	void Draw(); 





	void* getVertPos_dataPtr(){
		return &vertsPos[0];
	}


	void* getVertColor_dataPtr(){
		return &vertColor[0];
	}

	void* getUV_dataPtr(){
		return &UVdata[0]; 
	}


	modelData();

	void* getIndicesPtr(){
		return &indices[0];
	}
	int getTriangleCount(){
		if (indices.size() % 3 != 0)  throw  new exception("Object trangulation maybe Invalid ");
		else
		return indices.size() / 3; 
	}
};

