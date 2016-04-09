#include "ShapeGenerator.h"


ShapeGenerator::ShapeGenerator()
{
}


ShapeGenerator::~ShapeGenerator()
{
}


void ShapeGenerator::MakeCube(modelData &Output){

	Output.cleanUp();
	Output.pushVert(vert(vec3(0.5f, 0.5f, .50f), color::Black()));
	Output.pushVert(vert(vec3(0.5f, -0.5f, .50f), color::Blue()));
	Output.pushVert(vert(vec3(-0.5f, -0.5f, .50f), color::White()));
	Output.pushVert(vert(vec3(-0.5f, 0.5f, .50f), color::Green()));
	Output.pushVert(vert(vec3(0.5f, 0.5f, -.50f), color::Black()));
	Output.pushVert(vert(vec3(0.5f, -0.5f, -.50f), color::Black()));
	Output.pushVert(vert(vec3(-0.5f, -0.5f, -.50f), color::Red()));
	Output.pushVert(vert(vec3(-0.5f, 0.5f, -.50f), color::Black()));
	Output.indices =
	{
		8, 10, 12,
		8, 12, 14,
		0, 8, 6,
		14, 8, 6,
		2, 4, 10,
		12, 4, 10,
		0, 2, 10,
		0, 10, 8,
		6, 4, 12,
		6, 12, 14,
		0, 2, 4,
		0, 4, 6 };

	Output.updateData();


}



void ShapeGenerator::MakeTriangle(modelData &Output){

	Output.cleanUp();
	Output.pushVert(vert(vec3(1.0f, 1.0f, 0.0f), color::Black()));
	Output.pushVert(vert(vec3(1.0f, -1.0f, 0.0f), color::Red()));
	Output.pushVert(vert(vec3(-1.0f, -1.0f, 0.0f), color::Yellow()));
	
	vector<GLushort> indices = { 0, 1, 2 }; 
	Output.setSimpleIndices(indices);
	Output.updateData();


}