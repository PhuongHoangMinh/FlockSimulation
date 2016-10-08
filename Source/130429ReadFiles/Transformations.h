#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H


#include <vector>

#include "Vector3D.h"
#include "Matrices.h"


//--------------------- PointToWorldSpace --------------------------------
//
//  Transforms a point from the agent's local space into world space
//------------------------------------------------------------------------
inline Vector3D	PointToWorldSpace(const Vector3D& point,
								  const double angle,
								  const	Vector3D& rotateAxis,
								  const Vector3D& position)
{
	Vector4 TransPoint(point.x, point.y, point.z, 1);

	Matrix4	 matTransform;

	matTransform.identity();

	matTransform.rotate(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);

	matTransform.translate(position.x, position.y, position.z);

	Vector4 WorldPoint = matTransform*TransPoint;

	Vector3D worldResultPoint(WorldPoint.x, WorldPoint.y, WorldPoint.z);
	
	return worldResultPoint;
}

inline Vector3D VectorToWorldSpace(const Vector3D &vec,
								   const double angle,
								   const Vector3D& rotateAxis)
{
	Vector4 TransVec(vec.x, vec.y, vec.z, 1);

	Matrix4 matTransform;

	matTransform.identity();
	matTransform.rotate(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);

	Vector4 WorldVector = matTransform*TransVec;

	Vector3D worldResultVector(WorldVector.x, WorldVector.y, WorldVector.z);

	return worldResultVector;
}


//--------------------- PointToLocalSpace --------------------------------
//
//------------------------------------------------------------------------
inline Vector3D PointToLocalSpace(const Vector3D& point,
								  const double angle,
								  const	Vector3D& rotateAxis,
								  const Vector3D& position)
{
	Vector4 TransPoint(point.x, point.y, point.z, 1);

	Matrix4	 matTransform;

	matTransform.identity();

	matTransform.rotate(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);

	matTransform.translate(position.x, position.y, position.z);

	matTransform.invert();

	Vector4 LocalPoint = matTransform*TransPoint;

	Vector3D LocalResultPoint(LocalPoint.x, LocalPoint.y, LocalPoint.z);
	
	return LocalResultPoint;
}




#endif