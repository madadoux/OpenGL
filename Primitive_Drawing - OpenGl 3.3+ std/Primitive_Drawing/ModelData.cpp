#include "modelData.h"


modelData::modelData()
{
}

void modelData::cleanUp(){

	verts.clear(); 
	data.clear(); 
	this->indices.clear(); 

}


 vector<vec4> modelData::getData(){
	return data; 
}


 vector<vec4> modelData::updateData() {
	 // vert_pos , color , another attributes ...

	 for (int  i = 0; i < verts.size(); i++)
	 {
		 vector<vec4>attribs;
		 verts[i].attributeVec(attribs);
		 data.insert(data.end(), attribs.begin(), attribs.end()); 
	 }

	 return data; 
 }

void  modelData::insertVert( vert  v, uint pos){

	verts.insert(verts.begin() + pos,v); 

 }

void  modelData::pushVert(vert  v){

	verts.push_back(v); 

}

void modelData::deleteVert(uint pos){
	verts.erase(verts.begin() + pos); 
}

int  modelData::DataBufSize(){
	return sizeof(vec4) * data.size(); 

}

int modelData::IndicesBufSize(){
	return sizeof(GLushort)* indices.size(); 
}


void  modelData::setSimpleIndices(vector<GLushort> ind ){
	
	for (int  i = 0; i < ind.size(); i++)
		indices.push_back((GLushort) ind[i] * getAttCount()); 
}

vector<GLushort> modelData::getIndices(){
	return indices; 
}


void modelData::setAttCount(int x){
	_attributeCount = x; 
};

int modelData::getAttCount(){
	return _attributeCount; 
}