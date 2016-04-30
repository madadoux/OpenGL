#include "World.h"

#include "camera.h"
#include "Transform.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ShapeGenerator.h"
#include "modelData.h"
#include "Time.h"
#include "tcamera.h"
using namespace glm; 



// 1 reserved for the root 
int World::intialID=1;

Transform World::RootTrans = Transform(vec3(0, 0, 0), quat());

	void World::addGameObject(GameObject* g, Transform* Parent /*= &RootTrans*/)
	{
	
		

			g->getTransform()->parent = Parent;
			SceneObjects[g->getID()] = g;

	if (Parent != &RootTrans){
			ParentMat[Parent->gameObject->getID()].push_back(g->getID()); 
		}
		else {
			ParentMat[1].push_back(g->getID()); 

		}

		
	}

	void World::addGameObject(shared_ptr<GameObject> g, Transform* Parent /*= &RootTrans*/)
	{

		g->getTransform()->parent = Parent;
	//	SceneObjects[g->getID()] = g.get();

		if (Parent != &RootTrans){
			ParentMat[Parent->gameObject->getID()].push_back(g->getID());
		}
		else {
			ParentMat[1].push_back(g->getID());

		}

	}


	GameObject* World::findGameObjectByID(int ID)
	{
		return SceneObjects[ID]; 
	}

	void  World::getChildernOf(GameObject* parent,
		vector<GameObject*>& return1)
	{



		rep(ParentMat[parent->getID()].size())
		{
			return1.push_back(SceneObjects[ ParentMat[parent->getID()][i]]); 
		}


	}

	void World::DestroyGameObject(GameObject* g )
	{
		// need further impl 
		/*
			rep(ParentMat[g->getID()].size())
			{
			auto gg = SceneObjects[ParentMat[g->getID()][i]];
			DestroyGameObject(gg);
			delete gg;
			gg = nullptr;
			}

			Transform* tmp_t =  g->getTransform();
			if (tmp_t != nullptr){
			delete tmp_t;
			tmp_t = nullptr;
			}

			SceneObjects.erase(g->getID());*/
	}

	Transform* World::getRootTrans()
	{
		return &RootTrans;
	}
	

	void World::Update(){
		
		skyBox->getTransform()->setPos(MainCamera->_position); 
	
	//pAirStrike->getTransform()->move(pAirStrike->getTransform()->Forward(), .01f); 
	//	pAirStrike->getTransform()->rotate(-Time::DeltaTime() * .05, pAirStrike->getTransform()->Right()); 

		//pAirStrike->getTransform()->RotateAround( Utility::vec3Right(),Time::DeltaTime() * .05 ,  Utility::vec3Up() );
		_MainCamera->_lookPoint =  10.f * pAirStrike->getTransform()->Forward() +  pAirStrike->getTransform()->getCurrentPos();
		pAirStrike->getTransform()->RotateAround( Utility::vec3Right(), Time::DeltaTime() * .05, Utility::vec3Up());
		//pAirStrike->getTransform()->setRot(glm::lookAt(pAirStrike->getTransform()->getCurrentPos(), MainCamera->_position, glm::normalize(Utility::vec3Up() )));
	
	
			

	}
	void World::Visualize()
	{
		Update(); 
		mRenderer->clearScreen(); 
	
			repit(ParentMat[1])
			{
			auto cur = SceneObjects[*it];
			cur->Render();
			}



	}

	void World::AddMesh(Mesh* m )
	{

		// found already an instance with the same id 
		if (std_Meshs.find(m->getID()) != std_Meshs.end())
		{
			delete std_Meshs[m->getID()]; 
			std_Meshs[m->getID()] = nullptr; 
		}
		 std_Meshs[m->getID()] = m; 

	}

	World::World()
	{

		MainCamera = new camera(); 
		mRenderer = new Renderer(this); 
		ParentMat = vector<vector<int>>(1000, vector<int>());

		
	}


	World::~World()
	{

		repit(std_Meshs)
			delete (it)->second, (it)->second = nullptr;

		repit(std_textures)
			delete (it)->second, (it)->second = nullptr;

		repit(ParentMat[1])
		{
			auto cur = SceneObjects[*it];
			DestroyGameObject(cur);
		}



		delete MainCamera;
		MainCamera = NULL; 
		delete _MainCamera;
		_MainCamera = NULL;
		delete	mRenderer;
		mRenderer = NULL;

	}

	

	//************************************
	// Method:    addTexture
	// FullName:  World::addTexture
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: string uniqeName
	// Parameter: Texture * t
	//************************************
	void World::addTexture(string uniqeName , Texture* t)
{

		std_textures[uniqeName] = t; 
	}



	bool  firstPersonCam = 0; 
	void World::setContent(void(*f)()){


		//auto quad = ShapeGenerator::MakeQuadObj();
		//quad->getTransform()->position = vec3(3, 0, 0);
		//quad->getTransform()->rotation = glm::rotate(60.f, Utility::vec3Up());

		//auto tri1 = ShapeGenerator::MakeTriangleObj();
		//auto tri2 = ShapeGenerator::MakeTriangleObj();
		//auto tri3 = ShapeGenerator::MakeTriangleObj();

		//tri1->getTransform()->position = vec3(0, 3, 0);
		//tri3->getTransform()->position = vec3(0, 1, 0);
		//addGameObject(quad, getRootTrans());
		//addGameObject(tri1, quad->getTransform());

		//tri2->getTransform()->position = vec3(0, 0, 3);
		//addGameObject(tri2, tri1->getTransform());

		//addGameObject(tri3, tri1->getTransform());

		 skyBox = ShapeGenerator::MakeSkyBOx(); 

		  pAirStrike = ShapeGenerator::Model("models/F14","F14N.obj","F14tex.png" ,1); 
	

	 //  pAirStrike->getTransform()->setForwardAndUp( vec3(0, 1, 0), vec3(0, 0, 1));
	 //  pAirStrike->getTransform()->rotate(-90.f, pAirStrike->getTransform()->Forward());	
	  

	 pAirStrike->getTransform()->setRot( glm::rotate(90.f, pAirStrike->getTransform()->Forward()));

		 // pAirStrike->getTransform()->move(Utility::vec3Up(), -200.f);
	//  pAirStrike->getTransform()->setScl(vec3(.1f, .1f, .1f));

		  addGameObject(pAirStrike, getRootTrans());

		  _MainCamera->getTransform()->setPos(vec3(0,5, -5));

		  if (firstPersonCam)
		  {

			  addGameObject(_MainCamera, pAirStrike->getTransform());

			  _MainCamera->getTransform()->setPos(vec3(0, 6, 0));

		  } // thirdPersonCam
 
		  /*  airBroneCarrier = ShapeGenerator::Model("models/sof", "sof_.obj", "sof.mtl", 0);
			airBroneCarrier->getTransform()->setScl(vec3(.5f, .5f, .5f));

			addGameObject(airBroneCarrier, getRootTrans());*/


		f();
	}



	void userContent(){};

	tcamera* World::getMainCam()
	{

		return _MainCamera; 
	}

	void World::intialize(){
		

		_MainCamera = new tcamera(!firstPersonCam);

		setContent(userContent); 
		repit(std_Meshs)
			(it)->second->  Initialize();

		mRenderer->Initialize();

	

	}
