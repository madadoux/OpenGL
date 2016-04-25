#pragma  once
#include "Utility.h"
#include <memory>
#include <vector>






	class World
	{

		static 	int intialID; 
	
		
		map < int, GameObject* > SceneObjects; 
		vector<vector<int>> ParentMat;
		map < int , Mesh*> std_Meshs; 

	static	Transform RootTrans; 
	unordered_map<string, Texture*> std_textures; 
	
 	GameObject* skyBox; 
	public:
	



     camera* MainCamera; 
	Renderer* mRenderer;
		void addGameObject(GameObject*, Transform* Parent = &RootTrans); 
		GameObject* findGameObjectByID(int ID);
		vector<GameObject*> findGameObjectsByName(string name);
		void getChildernOf(GameObject* parent,
			vector<GameObject*>& return1);

		void DestroyGameObject(GameObject*); 
		static Transform* getRootTrans(); 

		void Update();
		void Visualize();

		void AddMesh(Mesh*); 
		World();
		void intialize(); 
		~World();
		void addTexture(string uniqeName, Texture* t);
		void setContent(void(*f)());
	};


