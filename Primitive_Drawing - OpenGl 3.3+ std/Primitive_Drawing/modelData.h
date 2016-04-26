#include <vector>
#include <gl\glew.h>
#include "Texture.h"
#include <glm\gtx\transform.hpp> 
#include <glm\gtx\quaternion.hpp>
#include <glm\glm.hpp>
#include "Utility.h"

#ifndef modelData_h__
#define modelData_h__





using namespace glm; 
using namespace std; 



	enum RenederMode{
		VBO, IBO
	};
	class Mesh
	{

		static int IntialID; 
		RenederMode renderMode = RenederMode::IBO;
		vector <vec3 > vertsPos;
		vector <vec4 > vertColor;
		vector < vec3> vertNormal; 
		vector<GLushort> indices;

		int _attributeCount;

		GLuint mVertexArrayObjectID;
		GLuint v_myBufferID, c_myBufferID, i_myBufferID, uv_myBufferID , n_myBufferID;

		int ID;
		int curTexIndex=0;

	public:


		Mesh(Mesh*); 
		void set_current_tex(int index); 
		Texture* getCurrentTex(); 
		vector<Texture*> mTextures;
		vector < vec2 > UVdata;
		void setRenderMode(RenederMode);
		bool EnableColor, EnableTexture;
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
		void deleteVert(uint pos);
		void addTriangleIndices(short a, short b, short c);
		void setSimpleIndices(vector<GLushort> ind);

		void pushUV(vec2 v);
		int getUVBufSize();


		void Initialize();
		void Draw();

		void LoadFromObj(string path); 



		int getID(){
			return ID; 
		}



		static int getNextID(); 


		void* getVertPos_dataPtr(){
			return &vertsPos[0];
		}


		void ClearUVs(){
			UVdata.clear();
		}

		void* getVertColor_dataPtr(){
			return &vertColor[0];
		}

		void* getUV_dataPtr(){
			return &UVdata[0];
		}

		void*	getNormalsPtr()
		{
			return &vertNormal[0]; 
		}
		~Mesh(); 
		Mesh();

		void* getIndicesPtr(){
			return &indices[0];
		}
		int getTriangleCount(){
			if (indices.size() % 3 != 0)  throw  new exception("Object trangulation maybe Invalid ");
			else
				return indices.size() / 3;
		}
	private:
		int NormalsBufSize();
	};

#endif // modelData_h__
