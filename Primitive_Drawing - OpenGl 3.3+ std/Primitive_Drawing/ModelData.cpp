#include "modelData.h"
#include "objloader.hpp"


using namespace glm;
using namespace std;



Mesh::~Mesh()
{
	cleanUp(); 
}

Mesh::Mesh()
	{
	EnableColor = 0, EnableTexture = 1;
	_attributeCount = 2;
	this->ID = getNextID();
     mDrawMode = DrawMode::Triangles; 
	}

Mesh::Mesh(Mesh*m)
{
	EnableColor = 0, EnableTexture = 1;
	_attributeCount = 2;
	this->ID = getNextID();
	

	indices.resize(m->indices.size());
	vertsPos.resize(m->vertsPos.size()); 
	mTextures.resize(m->mTextures.size()); 
	vertColor.resize(m->vertColor.size());
	UVdata.resize(m->UVdata.size()); 
	//vertNormal.resize(m->vertNormal.size()); 

	rep(m->indices.size())
		indices[i] = m->indices[i]; 
	rep(m->vertsPos.size())
		vertsPos[i] = m->vertsPos[i];
	rep(m->vertColor.size())
		vertColor[i] = m->vertColor[i];
	rep(m->UVdata.size())
		UVdata[i] = m->UVdata[i]; 
	rep(m->mTextures.size())
		mTextures[i] = m->mTextures[i]; 
	/*rep(m->vertNormal.size())
		vertNormal[i] = m->vertNormal[i];*/
}

int Mesh::NormalsBufSize()
{
	return sizeof(vec3)* vertNormal.size();
}

void Mesh::cleanUp(){


		this->indices.clear();
		this->vertsPos.clear();
		this->vertColor.clear();
		this->vertNormal.clear();

		glDeleteBuffers(1, &v_myBufferID);
		glDeleteBuffers(1, &c_myBufferID);
		glDeleteBuffers(1, &i_myBufferID);
		glDeleteBuffers(1, &uv_myBufferID);
		glDeleteBuffers(1, &n_myBufferID); 
		glDeleteVertexArrays(1, &mVertexArrayObjectID);
	}



	int Mesh::IntialID = 1;

	int Mesh::getNextID()
	{
		return IntialID++;
	}



	void  Mesh::insertVert(vert  v, uint pos){


	}

	void  Mesh::pushVert(vert  v){


		vertsPos.push_back(v._position);
		vertColor.push_back(v._color.toVec4());
		vertNormal.push_back(v.Normal);

	}

	void Mesh::deleteVert(uint pos){

	}


	int Mesh::IndicesBufSize(){
		return sizeof(GLushort)* indices.size();
	}


	void  Mesh::setSimpleIndices(vector<GLushort> ind){

		for (int i = 0; i < ind.size(); i++)
			indices.push_back((GLushort)ind[i]);
	}

	vector<GLushort> Mesh::getIndices(){
		return indices;
	}


	void Mesh::setAttCount(int x){
		_attributeCount = x;
	};

	int Mesh::getAttCount(){
		return _attributeCount;
	}


	vector < vec2 > Mesh::getUVdata(){
		return UVdata;
	}


	void Mesh::pushUV(vec2 v){
		UVdata.push_back(v);
	}


	int  Mesh::getUVBufSize(){
		return sizeof(vec2)* UVdata.size();
	}

	int  Mesh::getVertPosBufSize(){
		return sizeof(vec3)* vertsPos.size();
	}

	int  Mesh::getVerColBufSize(){
		return sizeof(vec4)* vertColor.size();
	}


	void Mesh::Initialize()
	{
		glGenVertexArrays(1, &mVertexArrayObjectID);
		glBindVertexArray(mVertexArrayObjectID);

		if (vertsPos.size() > 0)
		{

			glGenBuffers(1, &v_myBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, v_myBufferID);
			glBufferData(GL_ARRAY_BUFFER, getVertPosBufSize(), getVertPos_dataPtr(), GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3) , 0);
		}
		if (EnableColor && vertColor.size() > 0)
		{
			glGenBuffers(1, &c_myBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, c_myBufferID);
			glBufferData(GL_ARRAY_BUFFER, getVerColBufSize(), getVertColor_dataPtr(), GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0,0);

		}
		if (EnableTexture &&   UVdata.size() > 0)
		{
			glGenBuffers(1, &uv_myBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, uv_myBufferID);
			glBufferData(GL_ARRAY_BUFFER, getUVBufSize(), getUV_dataPtr(), GL_STATIC_DRAW);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) , 0);
		}
		if (renderMode == RenederMode::IBO &&  indices.size() > 0)
		{

			glGenBuffers(1, &i_myBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_myBufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndicesBufSize(), getIndicesPtr(), GL_STATIC_DRAW);

		}

		if ( vertNormal .size() > 0)
		{

			glGenBuffers(1, &n_myBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, n_myBufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, NormalsBufSize(), getNormalsPtr(), GL_STATIC_DRAW);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof (vec3), 0);
		}


	}




	void Mesh::Draw(){


		glBindVertexArray(mVertexArrayObjectID);

	//	printf("drawing mesh ID = %d  ..\n ", ID); 
		if (EnableTexture &&  !mTextures.empty())
			mTextures[0]->Bind();

		if (renderMode == RenederMode::IBO &&  indices.size() > 0)
		{
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);
				/*switch (mDrawMode)
				{
				case Lines:		glDrawElements(GL_LINE_STRIP, indices.size(), GL_UNSIGNED_SHORT, 0);
				break;
				case Triangles: glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);
				break;
				default:
				break;
				}*/
	
		}
		else if (renderMode == RenederMode::VBO)
		{
			//no indices provided.
			


			switch (mDrawMode)
			{
			case Lines:					glDrawArrays(GL_LINES, 0, vertsPos.size());
				break;
			case Triangles: 			glDrawArrays(GL_TRIANGLES, 0, vertsPos.size());
				break;
			default:
				break;
			}
		}

		//if (EnableTexture)
		//{

		//	glDisable(GL_TEXTURE_2D);
		//	glDisable(GL_TEXTURE_CUBE_MAP);
		//}
	}


	void Mesh::LoadFromObj(string path , bool initialColor ,color initialColor1 )
	{

		loadOBJFromFile(path.c_str(), vertsPos, UVdata, vertNormal); 
		int n = vertsPos.size(); 
		rep(n)
		{
			float ratio = (float)i /(float)  n; 
			vertColor.push_back( (initialColor  ) ?  initialColor1.toVec4() :  color(ratio, ratio, ratio, 1).toVec4());
		}
		renderMode = RenederMode::VBO; 
		

	}

	void Mesh::set_current_tex(int index)
	{

		curTexIndex = index; 

	}

	Texture* Mesh::getCurrentTex()
	{
		return  mTextures[curTexIndex]; 
	}

	void Mesh::setRenderMode(RenederMode rm){
		if (rm == renderMode)
			return;


		renderMode = rm;
		if (rm == RenederMode::VBO){

			int pos_prev_size = vertsPos.size();
			for (int i = 0; i < indices.size(); i++)
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
