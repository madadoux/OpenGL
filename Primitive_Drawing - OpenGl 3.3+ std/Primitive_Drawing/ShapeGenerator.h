#pragma once
#include "modelData.h"
class ShapeGenerator
{


public:
	void MakeTriangle( modelData& Output );
	void MakeCube(modelData& Output); 
	void MakeCircle(modelData& Output);
	void MakeCone(modelData& Output);
	void MakeSquare(modelData& Output);
	void MakeSphere(modelData& Output);
	void MakeCapsule(modelData& Output);

	ShapeGenerator();
	~ShapeGenerator();
};

