#pragma  once
#include "Utility.h"
#include <memory>
#include <vector>
#include "Sound.h"





	class World
	{

		static 	int intialID; 
	
		
		map < int, GameObject* > SceneObjects; 
		vector<vector<int>> ParentMat;
		map < int , Mesh*> std_Meshs; 

	static	Transform RootTrans; 
	unordered_map<string, Texture*> std_textures; 
	
 	GameObject* skyBox; 
	AirCraft* pAirStrike; 
	GameObject* airBroneCarrier; 
tcamera* _MainCamera;

	public:
	
		void World::addGameObject(shared_ptr<GameObject> g, Transform* Parent /*= &RootTrans*/);
		




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


		tcamera* getMainCam(); 
		void World::HandleKeyboardInput(int Key , int KeyState);
	private:
		LightMode light_mode;
	};


