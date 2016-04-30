#include "GameObject.h"

#include "Transform.h"
#include "World.h"
#include "modelData.h"
#include "Renderer.h"



	GameObject::GameObject(   string name, Transform* t , World* scene )
	{
		mScene = scene; 
		this->name = name;
		this->id = getNextID(); 
		t->gameObject = this;
		this->transform = t;

	}


GameObject::~GameObject()
	{

	mScene->DestroyGameObject(this);

	}

	int GameObject::IntialID = 2 ;

	int GameObject::getNextID()
	{
		return IntialID++;
	}

	Transform* GameObject::getTransform()  {


		return transform;

	};

	void GameObject::HandelMouseInput(float x ,float  y)
	{

	}

	void GameObject::HandelKeyBoardInput(int key )
	{

	}

	void  GameObject::Render()
	{
	    mScene->mRenderer->Draw(this); 
		vector<GameObject*>childern;
         mScene->getChildernOf(this, childern);
		
			 repit(childern){
				 auto cur = *it;
				 cur->Render();

			 
		 }
		 
	}

	Mesh* GameObject::GetCurrentMesh()
	{

		return currentMesh;

	}

	int GameObject::getID()
	{
		return id;
	}
