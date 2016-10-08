#ifndef AABB_H
#define AABB_H

#include "Vector3D.h"
#include <math.h>

class Vector3D;

class AABB{
	
public:
	Vector3D centerP;
	Vector3D	 r;
	
	AABB(Vector3D pos, Vector3D radius): centerP(pos), r(radius)
	{
	}
	

	int TestAABBCollision(AABB b)
	{

		float dX = this->centerP.x - b.centerP.x;
		float dY = this->centerP.y - b.centerP.y;
		float dZ = this->centerP.z - b.centerP.z;

		float totalX = this->r.x + b.r.x;
		float totalY = this->r.y + b.r.y;
		float totalZ = this->r.z + b.r.z;

		if(abs(this->centerP.x - b.centerP.x) > (this->r.x + b.r.x)) return 0;

		if(abs(this->centerP.y - b.centerP.y) > (this->r.y + b.r.y)) return 0;

		if(abs(this->centerP.z - b.centerP.z) > (this->r.z + b.r.z)) return 0;

		return 1;
	}
	
	
};

//inline int TestAABBCollision(AABB a, AABB b)
//{
//	
//	float dX = a.centerP.x - b.centerP.x;
//	float dY = a.centerP.y - b.centerP.y;
//	float dZ = a.centerP.z - b.centerP.z;
//
//	float totalX = a.r.x + b.r.x;
//	float totalY = a.r.y + b.r.y;
//	float totalZ = a.r.z + b.r.z;
//
//	if(abs(a.centerP.x - b.centerP.x) > (a.r.x + b.r.x)) return 0;
//
//	if(abs(a.centerP.y - b.centerP.y) > (a.r.y + b.r.y)) return 0;
//
//	if(abs(a.centerP.z - b.centerP.z) > (a.r.z + b.r.z)) return 0;
//
//	return 1;
//}

#endif