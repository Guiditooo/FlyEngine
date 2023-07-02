#ifndef VERTICES_H
#define VERTICES_H

namespace FLY_ENGINE
{

	struct Vertice
	{
		float posX;
		float posY;
		float posZ;
		float colR;
		float colG;
		float colB;
		float U;
		float V;
		float norX;
		float norY;
		float norZ;

		Vertice(float newPosX, float newPosY, float newPosZ, 
				float newColR, float newColG, float newColB, 
				float newU, float newV, 
				float newNorX, float newNorY, float newNorZ)
		{
			posX = newPosX;
			posY = newPosY;
			posZ = newPosZ;
			colR = newColR;
			colG = newColG;
			colB = newColB;
			U    = newU;
			V    = newV;
			norX = newNorX;
			norY = newNorY;
			norZ = newNorZ;
		}

	};

}
#endif // !VERTICES_H
