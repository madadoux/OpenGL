#include "ShapeGenerator.h"
#include "modelData.h"
#include "Transform.h"
#include "GameObject.h"
#include "ApplicationManager.h"
#include "World.h"

using namespace glm; 



	ShapeGenerator::ShapeGenerator()
	{
	}


	ShapeGenerator::~ShapeGenerator()
	{
	}


	GameObject*  ShapeGenerator::Model(string modelPath , string objName , string texName , bool EnableTex ){

	    Mesh*	modelMesh = new Mesh();
		_main_scene->AddMesh(modelMesh);
		modelMesh->LoadFromObj(modelPath+"/"+objName); 
		auto	mTexture = new Texture(modelPath + "/" + texName, 1  );
		_main_scene->addTexture(objName + "_" + texName, mTexture);



		//modelMesh->mTextures.push_back()
		if (EnableTex){
			modelMesh->EnableColor = 0;
			modelMesh->EnableTexture = 1;
		}
		else {
			modelMesh->EnableColor = 1;
			modelMesh->EnableTexture = 0;
			
		}

		GameObject* Obj = new GameObject(objName, new Transform(), _main_scene); 
		GameObject* meshObj = new GameObject(objName+"mesh", new Transform(), _main_scene);

		meshObj->meshs.push_back(modelMesh); 
		meshObj->meshs[0]->mTextures.push_back(mTexture); 

		_main_scene->addGameObject(meshObj, Obj->getTransform()); 

		return Obj; 

	}

	Mesh ShapeGenerator::MakeCube(Mesh &Output){

		Output.cleanUp();
		Output.pushVert(vert(vec3(0.5f, 0.5f, .50f), color::Blue()));
		Output.pushVert(vert(vec3(0.5f, -0.5f, .50f), color::Blue()));
		Output.pushVert(vert(vec3(-0.5f, -0.5f, .50f), color::White()));
		Output.pushVert(vert(vec3(-0.5f, 0.5f, .50f), color::Green()));
		Output.pushVert(vert(vec3(0.5f, 0.5f, -.50f), color::Black()));
		Output.pushVert(vert(vec3(0.5f, -0.5f, -.50f), color::Black()));
		Output.pushVert(vert(vec3(-0.5f, -0.5f, -.50f), color::Red()));
		Output.pushVert(vert(vec3(-0.5f, 0.5f, -.50f), color::Black()));
		vector<GLushort> indices =
		{
			4, 7, 6
			, 4, 5, 6
			, 7, 3, 2
			, 7, 6, 2
			, 3, 0, 1
			, 3, 2, 1
			, 0, 4, 5
			, 0, 1, 5
			, 0, 3, 7
			, 0, 4, 7
			, 2, 1, 5
			, 2, 6, 5 };

		Output.setSimpleIndices(indices);

		//	Output.setRenderMode(RenederMode::VBO); 

		//rep(12){

		/*	Output.pushUV(vec2(.5, .33));
			Output.pushUV(vec2(.25, .33));
			Output.pushUV(vec2(.25, .66));
			Output.pushUV(vec2(.5, .33));
			Output.pushUV(vec2(.5, .66));
			Output.pushUV(vec2(.25, .66));*/
		//Output.pushUV(vec2(.25, .33));
		//}




		Output.pushUV(vec2(.5, .33));
		Output.pushUV(vec2(.25, .33));
		Output.pushUV(vec2(.25, .66));
		Output.pushUV(vec2(.5, .66));
		//reverse(Output.UVdata.begin(), Output.UVdata.end()); 
		Output.pushUV(vec2(.25 + .5, .33));
		Output.pushUV(vec2(.5 + .5, .33));
		Output.pushUV(vec2(.5 + .5, .66));
		Output.pushUV(vec2(.25 + .5, .66));


		//reverse(Output.UVdata.begin() +4, Output.UVdata.end());

		return Output;

	}

	Mesh* ShapeGenerator::makeQuadMesh(){

		if (Quad == nullptr){
			Quad = new Mesh();


			Quad->EnableColor = 1;

			Quad->pushVert(vert(vec3(-1, -1, 0), color(1,0,0,.1f)));
			Quad->pushVert(vert(vec3(-1, 1, 0), color::Green()));
			Quad->pushVert(vert(vec3(1, -1, 0), color::White()));
			Quad->pushVert(vert(vec3(1, 1, 0), color::Blue()));

			vector<GLushort> indices =
			{
				1, 0, 2,
				2, 3, 1
			};

			Quad->setSimpleIndices(indices);
			Quad->EnableColor = 1;

			_main_scene->AddMesh(Quad);

		}
		
		return Quad; 
	}
	
	 GameObject* ShapeGenerator::MakeQuadObj( bool new_mesh){


		GameObject* object = new GameObject("Quad", new Transform(), _main_scene); 

		Mesh* mesh;
		if (new_mesh){
			mesh =  new Mesh(makeQuadMesh());
			_main_scene->AddMesh(mesh);

		}
		else
		{
			mesh = makeQuadMesh(); 
		}
		object->meshs.push_back(mesh); 


		return object; 
	
	}


	 GameObject* ShapeGenerator::MakeTriangleObj(){


		 GameObject* object = new GameObject("Tri", new Transform(), _main_scene);

		 auto mesh = MakeTriangle();
		 object->meshs.push_back(mesh);


		 return object;

	 }

#define  TGA 1 
#define  photo 0




	 Mesh* ShapeGenerator::Quad = nullptr;
	 Mesh* ShapeGenerator::triangel = nullptr; 
	 Mesh* ShapeGenerator::MakeTriangle(){
		 if (triangel == nullptr){
			
			 triangel = new Mesh(); 

			 triangel->EnableColor = 1;
			 triangel->EnableTexture = 0;
			 _main_scene->AddMesh(triangel);

		
	
			 triangel->pushVert(vert(vec3(1.0f, 1.0f, 0.0f), color::Green()));
			 triangel->pushVert(vert(vec3(1.0f, -1.0f, 0.0f), color::Green()));
			 triangel->pushVert(vert(vec3(-1.0f, -1.0f, 0.0f), color::Green()));

		vector<GLushort> indices = { 0, 1, 2 };
		triangel->setSimpleIndices(indices);
		 }

		 return triangel;

		
	}


		GameObject* ShapeGenerator::MakeSkyBOx(){

	#if TGA
	auto	mTexture2 = new Texture("tex/darkskies_rt.TGA", 1);
		auto	mTexture3 = new Texture("tex/darkskies_lf.TGA", 1);
		auto	mTexture4 = new Texture("tex/darkskies_up.TGA", 1);
		auto	mTexture5 = new Texture("tex/darkskies_dn.TGA", 1);
		auto	mTexture6 = new Texture("tex/darkskies_bk.TGA", 1);
		auto	mTexture7 = new Texture("tex/darkskies_ft.TGA", 1);
#endif

		_main_scene->addTexture("sky_texture1", mTexture2); 
		_main_scene->addTexture("sky_texture2", mTexture3);
		_main_scene->addTexture("sky_texture3", mTexture4);
		_main_scene->addTexture("sky_texture4", mTexture5);
		_main_scene->addTexture("sky_texture5", mTexture6);
		_main_scene->addTexture("sky_texture6", mTexture7);




		GameObject* object = new GameObject("SkyBox", new Transform(), _main_scene);
		object->getTransform()->setScl( vec3(300, 300, 300));
_main_scene->addGameObject(object, _main_scene->getRootTrans());

		vector<GameObject*> faces;

		rep(6)
		{
			auto face = MakeQuadObj(true);  
			face->meshs[0]->EnableTexture = 1;
			face->meshs[0]->EnableColor = 0;
			faces.push_back(face);
	   
		}
		faces[0]->meshs[0]->mTextures.push_back(mTexture6); 
		faces[1]->meshs[0]->mTextures.push_back(mTexture7);
		faces[2]->meshs[0]->mTextures.push_back(mTexture2);
		faces[3]->meshs[0]->mTextures.push_back(mTexture3);
		faces[4]->meshs[0]->mTextures.push_back(mTexture5);
		faces[5]->meshs[0]->mTextures.push_back(mTexture4);




		glm::mat4 square1M, square2M, square3M, square4M, square5M, square6M; 
		square1M = glm::translate(0.0f, 0.0f, -01.0f)*glm::rotate(180.0f, 0.0f, 0.0f, 1.0f);
		square2M = glm::translate(0.0f, 0.0f, 01.0f)*glm::rotate(180.0f, 0.0f, 0.0f, 1.0f)*glm::rotate(180.0f, 0.0f, 1.0f, 0.0f);
		square3M = glm::translate(-01.0f, 0.0f, 0.0f)*glm::rotate(90.0f, 0.0f, 1.0f, 0.0f)*glm::rotate(180.0f, 0.0f, 0.0f, 1.0f);
		square4M = glm::translate(01.0f, 0.0f, 0.0f)*glm::rotate(90.0f, 0.0f, -1.0f, 0.0f)*glm::rotate(180.0f, 0.0f, 0.0f, 1.0f);
		square5M = glm::translate(0.0f, -01.0f, 0.0f)*glm::rotate(180.0f, 0.0f, 1.0f, 0.0f)*glm::rotate(90.0f, -1.0f, 0.0f, 0.0f);
		square6M = glm::translate(0.0f, 01.0f, 0.0f)*glm::rotate(180.0f, 0.0f, 1.0f, 0.0f)*glm::rotate(90.0f, 1.0f, 0.0f, 0.0f);


		rep(6){
			faces[i]->meshs[0]->pushUV(vec2(0, 0));
			faces[i]->meshs[0]->pushUV(vec2(0, 1));
			faces[i]->meshs[0]->pushUV(vec2(1, 0));
			faces[i]->meshs[0]->pushUV(vec2(1, 1));
		}

#pragma region TGA_TEX

		faces[4]->meshs[0]->ClearUVs();
		

		faces[4]->meshs[0]->pushUV(vec2(1, 0));
		faces[4]->meshs[0]->pushUV(vec2(1, 1));
        faces[4]->meshs[0]->pushUV(vec2(0, 0));
		faces[4]->meshs[0]->pushUV(vec2(0, 1));


		faces[5]->meshs[0]->ClearUVs();


		faces[5]->meshs[0]->pushUV(vec2(1, 0));
		faces[5]->meshs[0]->pushUV(vec2(1, 1));
		faces[5]->meshs[0]->pushUV(vec2(0, 0));
		faces[5]->meshs[0]->pushUV(vec2(0, 1));
#pragma endregion TGA_TEX

		faces[0]->getTransform()->applyMatrix(square1M);
		faces[1]->getTransform()->applyMatrix(square2M);
		faces[2]->getTransform()->applyMatrix(square3M);
		faces[3]->getTransform()->applyMatrix(square4M);
		faces[4]->getTransform()->applyMatrix(square5M);
		faces[5]->getTransform()->applyMatrix(square6M);



		rep(6)
			_main_scene->addGameObject(faces[i], object->getTransform()); 

	
		 
		return object; 
}

/*faces[0]->meshs[0]->pushUV(vec2(.5, .333333));
		faces[0]->meshs[0]->pushUV(vec2(.25, .33333));
		faces[0]->meshs[0]->pushUV(vec2(.25, .666666));
		faces[0]->meshs[0]->pushUV(vec2(.5, .66666));
		//faces[0]->getTransform()->scale = vec3(100, 100, 100);


		//middle


		faces[1]->meshs[0]->pushUV(vec2(.75, .333333));
		faces[1]->meshs[0]->pushUV(vec2(.5, .333333));
		faces[1]->meshs[0]->pushUV(vec2(.5, .66666));
		faces[1]->meshs[0]->pushUV(vec2(.75, .66666));

		//faces[1]->getTransform()->setMat(square1M);
		faces[1]->getTransform()->position = vec3((1.0f, 0.0f, 1.0f));
		faces[1]->getTransform()->rotation = glm::rotate(90.0f, Utility::vec3Up());

		//middle +1


		faces[2]->meshs[0]->pushUV(vec2(1, .33333));
		faces[2]->meshs[0]->pushUV(vec2(.75, .33333));
		faces[2]->meshs[0]->pushUV(vec2(.75, .66666));
		faces[2]->meshs[0]->pushUV(vec2(1, .66666));

		faces[2]->getTransform()->position = vec3((0.0f, 0.0f, 2.0f));
		faces[2]->getTransform()->rotation = glm::rotate(180.0f, Utility::vec3Up());

		//middle +2


		faces[3]->meshs[0]->pushUV(vec2(.25, .33333));
		faces[3]->meshs[0]->pushUV(vec2(0, .33333));
		faces[3]->meshs[0]->pushUV(vec2(0, .66666));
		faces[3]->meshs[0]->pushUV(vec2(.25, .66666));
		faces[3]->getTransform()->position = vec3((-1.0f, 0.0f, 1.0f));
		faces[3]->getTransform()->rotation = glm::rotate(-90.0f, Utility::vec3Up());

		//middle -1



		faces[4]->meshs[0]->pushUV(vec2(.5, 0));
		faces[4]->meshs[0]->pushUV(vec2(.25, 0));
		faces[4]->meshs[0]->pushUV(vec2(.25, .33333));
		faces[4]->meshs[0]->pushUV(vec2(.5, .333333));
		faces[4]->getTransform()->position = vec3((0.0f, 1.0f, 1.0f));
		faces[4]->getTransform()->rotation = glm::rotate(+90.0f, Utility::vec3Right());

		//up





		faces[5]->meshs[0]->pushUV(vec2(.5, .66666));
		faces[5]->meshs[0]->pushUV(vec2(.25, .6666));
		faces[5]->meshs[0]->pushUV(vec2(.25, 1));
		faces[5]->meshs[0]->pushUV(vec2(.5, 1));

		faces[5]->getTransform()->position = vec3((0.0f, -1.0f, 1.0f));
		faces[5]->getTransform()->rotation = glm::rotate(90.0f, Utility::vec3Right());

		//down
		*/