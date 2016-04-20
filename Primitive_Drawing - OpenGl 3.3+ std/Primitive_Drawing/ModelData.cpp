#include "modelData.h"


modelData::modelData()
{
	 EnableColor = 0, EnableTexture = 1;
	 _attributeCount = 2; 
}

void modelData::cleanUp(){

	
	this->indices.clear(); 
	this->vertsPos.clear(); 
	this->vertColor.clear(); 


	glDeleteBuffers(1, &v_myBufferID);
	glDeleteBuffers(1, &c_myBufferID);
	glDeleteBuffers(1, &i_myBufferID);
	glDeleteBuffers(1, &uv_myBufferID);
	glDeleteVertexArrays(1, &mVertexArrayObjectID);
}





void  modelData::insertVert( vert  v, uint pos){


 }

void  modelData::pushVert(vert  v){


	vertsPos.push_back(v._position); 
	vertColor.push_back(v._color.toVec4()); 


}

void modelData::deleteVert(uint pos){

}


int modelData::IndicesBufSize(){
	return sizeof(GLushort)* indices.size(); 
}


void  modelData::setSimpleIndices(vector<GLushort> ind ){
	
	for (int  i = 0; i < ind.size(); i++)
		indices.push_back((GLushort) ind[i] ); 
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


vector < vec2 > modelData::getUVdata(){
	return UVdata; 
}


void modelData::pushUV(vec2 v){
	UVdata.push_back(v); 
}


int  modelData::getUVBufSize(){
	return sizeof(vec2)* UVdata.size(); 
}

int  modelData::getVertPosBufSize(){
	return sizeof(vec3)* vertsPos .size();
}

int  modelData::getVerColBufSize(){
	return sizeof(vec4)* vertColor.size();
}


void modelData:: Initialize()
{
	glGenVertexArrays(1, &mVertexArrayObjectID);
	glBindVertexArray(mVertexArrayObjectID);

	if ( vertsPos .size()>0)
	{

		glGenBuffers(1, &v_myBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, v_myBufferID);
		glBufferData(GL_ARRAY_BUFFER, getVertPosBufSize(), getVertPos_dataPtr(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (vec3), 0);
	}
	if (EnableColor && vertColor.size() > 0 )
	{
		glGenBuffers(1, &c_myBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, c_myBufferID);
		glBufferData(GL_ARRAY_BUFFER, getVerColBufSize(),  getVertColor_dataPtr(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof (vec4), 0);

	}
	if (EnableTexture &&   UVdata.size()>0)
	{
		glGenBuffers(1, &uv_myBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, uv_myBufferID);
		glBufferData(GL_ARRAY_BUFFER, getUVBufSize(), getUV_dataPtr(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}
	if (renderMode == RenederMode::IBO &&  indices.size() > 0)
	{

		glGenBuffers(1, &i_myBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_myBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndicesBufSize(), getIndicesPtr(), GL_STATIC_DRAW);
		
	}

}




void modelData::Draw(){

	
	glBindVertexArray(mVertexArrayObjectID);

	if (!mTextures.empty())
	mTextures[0]->Bind(); 

	if (renderMode == RenederMode::IBO &&  indices.size() > 0)
	{
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);
	}
	else if (renderMode == RenederMode::VBO)
	{
		//no indices provided.
		glDrawArrays(GL_TRIANGLES, 0, vertsPos.size());
	}
}


void modelData::setRenderMode(RenederMode rm){
	if (rm == renderMode)
		return; 


	renderMode = rm;
	if (rm == RenederMode::VBO){
	
		int pos_prev_size = vertsPos.size();
		for (int  i = 0; i < indices.size(); i++)
		{
			vertsPos.push_back(vertsPos[indices[i]]); 
		}
		int color_prev_size = vertColor.size();
		for (int i = 0; i < indices.size(); i++)
		{
			vertColor.push_back(vertColor[indices[i]]);
		}
		vertsPos.erase(vertsPos.begin(), vertsPos.begin() + pos_prev_size);
		vertColor.erase(vertColor.begin(), vertColor.begin() + color_prev_size);


	}
}