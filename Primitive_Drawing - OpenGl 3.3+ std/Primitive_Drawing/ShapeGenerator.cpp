#include "ShapeGenerator.h"


ShapeGenerator::ShapeGenerator()
{
}


ShapeGenerator::~ShapeGenerator()
{
}


void ShapeGenerator::MakeCube(modelData &Output){

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



}



void ShapeGenerator::MakeTriangle(modelData &Output){

	Output.cleanUp();
	Output.pushVert(vert(vec3(1.0f, 1.0f, 0.0f), color::Green()));
	Output.pushVert(vert(vec3(1.0f, -1.0f, 0.0f), color::Green()));
	Output.pushVert(vert(vec3(-1.0f, -1.0f, 0.0f), color::Green()));
	
	vector<GLushort> indices = { 0, 1, 2 }; 
	Output.setSimpleIndices(indices);

}