#pragma once
#include "modelData.h"
#include "stb_image.h"
#include <memory>
#include < vector >

using namespace std; 
class ShapeGenerator
{


public:
	modelData MakeTriangle(modelData& Output);
	modelData MakeCube(modelData& Output);
	modelData MakeCircle(modelData& Output);
	modelData MakeCone(modelData& Output);
	modelData MakeSquare(modelData& Output);
	modelData MakeSphere(modelData& Output);
	modelData MakeCapsule(modelData& Output);
	modelData MakeSkyBOx(vector < modelData> & Output);
	ShapeGenerator();
	~ShapeGenerator();
};

