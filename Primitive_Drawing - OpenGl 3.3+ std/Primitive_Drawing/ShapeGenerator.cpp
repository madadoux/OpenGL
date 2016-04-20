#include "ShapeGenerator.h"

ShapeGenerator::ShapeGenerator()
{
}


ShapeGenerator::~ShapeGenerator()
{
}


modelData ShapeGenerator::MakeCube(modelData &Output){

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
		 4,7,6 
		,4,5,6
		,7,3,2
		,7,6,2
		,3,0,1
		,3,2,1
		,0,4,5
		,0,1,5
		,0,3,7
		,0,4,7
		,2,1,5
		,2,6,5 };
	
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
	Output.pushUV(vec2(.25+.5, .33));
	Output.pushUV(vec2(.5+.5, .33));
	Output.pushUV(vec2(.5+.5, .66));
	Output.pushUV(vec2(.25+.5, .66));
	

	//reverse(Output.UVdata.begin() +4, Output.UVdata.end());

	return Output; 

}



modelData ShapeGenerator::MakeSquare(modelData &Output){

	Output.cleanUp();
	Output.pushVert(vert(vec3(1, 1, 0), color::Blue()));
	Output.pushVert(vert(vec3(-1, 1, 0), color::Green()));
	Output.pushVert(vert(vec3(-1, -1, 0), color::White()));
	Output.pushVert(vert(vec3(1, -1, 0), color::Blue()));
	
	
	
	vector<GLushort> indices =
	{
		 3, 0, 1
		, 3, 2, 1
		 };

	Output.setSimpleIndices(indices);
	Output.pushUV(vec2(.5, .33));
	Output.pushUV(vec2(.25, .33));
	Output.pushUV(vec2(.25, .66));
	Output.pushUV(vec2(.5, .66));
	return Output; 
}


modelData ShapeGenerator::MakeTriangle(modelData &Output){

	Output.cleanUp();
	Output.pushVert(vert(vec3(1.0f, 1.0f, 0.0f), color::Green()));
	Output.pushVert(vert(vec3(1.0f, -1.0f, 0.0f), color::Green()));
	Output.pushVert(vert(vec3(-1.0f, -1.0f, 0.0f), color::Green()));
	
	vector<GLushort> indices = { 0, 1, 2 }; 
	Output.setSimpleIndices(indices);


	return Output; 
}


modelData ShapeGenerator::MakeSkyBOx(vector < modelData> & Output){



 Texture* t1 = new Texture("Day_Skybox.PNG", 1) ; 
 modelData face; 
 MakeSquare(face);
 face.pushUV(vec2(.5, .333333));
 face.pushUV(vec2(.25, .33333));
 face.pushUV(vec2(.25, .666666));
 face.pushUV(vec2(.5, .66666));
 face.EnableTexture = 1; 
 face.EnableColor = 0; 
 
 face.mTextures.push_back(t1); 

 //middle
 Output.push_back(face); 
 face.ClearUVs(); 


 face.pushUV(vec2(.75, .333333));
 face.pushUV(vec2(.5, .333333));
 face.pushUV(vec2(.5, .66666));
 face.pushUV(vec2(.75, .66666));
 //middle +1 
 Output.push_back(face);
 face.ClearUVs();
 face.pushUV(vec2(1, .33333));
 face.pushUV(vec2(.75, .33333));
 face.pushUV(vec2(.75, .66666));
 face.pushUV(vec2(1 , .66666));
 //middle +2 
 Output.push_back(face);
 face.ClearUVs();
 face.pushUV(vec2(.25, .33333));
 face.pushUV(vec2(0, .33333));
 face.pushUV(vec2(0 , .66666));
 face.pushUV(vec2(.25, .66666));
 //middle -1 
 Output.push_back(face);


 face.ClearUVs();
 face.pushUV(vec2(.5, 0));
 face.pushUV(vec2(.25, 0));
 face.pushUV(vec2(.25, .33333));
 face.pushUV(vec2(.5, .333333));
 
 //up
 Output.push_back(face);


 face.ClearUVs();

 face.pushUV(vec2(.5, .66666));
 face.pushUV(vec2(.25, .6666));
 face.pushUV(vec2(.25, 1));
 face.pushUV(vec2(.5, 1 ));

 //down 
 Output.push_back(face);


 return face; 

}