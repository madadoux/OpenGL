#pragma once
#include <glm\glm.hpp>
#include < vector>
#include "Utility.h"
#include <gl/glew.h>
using namespace glm; 
using namespace std; 
using namespace deux;
struct modelData
{

	vector<vec4> data; 
	vector<vert> verts;
	vector<GLushort> indices;
	int _attributeCount =2 ;
	
public:

	void cleanUp(); 
	void pushVert(vert  v); 
	void setAttCount(int); 
	int getAttCount(); 
	int IndicesBufSize(); 
	int DataBufSize();
	vector<vec4> getData();
	vector<vec4> updateData(); 
	void insertVert(vert v, uint pos); 
	void deleteVert( uint pos);
	void addTriangleIndices(short a, short b, short c); 
	void setSimpleIndices(vector<GLushort> ind);

	
	vector< GLushort > getIndices();

	modelData();
	void* getDataPtr(){
		return &data[0]; 
	}
	void* getIndicesPtr(){
		return &indices[0];
	}
	int getTriangleCount(){
		if (indices.size() % 3 != 0)  throw  new exception("Object trangulation maybe Invalid ");
		else
		return indices.size() / 3; 
	}
};

