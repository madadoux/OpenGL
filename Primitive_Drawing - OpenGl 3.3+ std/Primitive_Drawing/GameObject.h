#ifndef GameObject_h__
#define GameObject_h__

#include "Utility.h"

 class GameObject
	{
	

	 static int IntialID; 
	 static int getNextID(); 

	protected:
		int id;
		Transform* transform;
		Mesh* currentMesh; 


	public:	
				World* mScene; 
		vector<Mesh*> meshs ;
		
		string name; 

		Transform* getTransform()  ; 
		virtual void HandelMouseInput();
		virtual void HandelKeyBoardInput(); 
		void   Render();
		virtual Mesh* GetCurrentMesh(); 


		int getID(); 
		GameObject( string name, Transform* t , World* );
		virtual ~GameObject();
	};


#endif // GameObject_h__
