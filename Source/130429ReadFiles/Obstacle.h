#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Vector3D.h"
#include "BaseGameEntity.h"


class Obstacle : public BaseGameEntity
{
public :
	
	Obstacle(double x,
			 double y,
			 double z,
			 double r): BaseGameEntity(0, Vector3D(x,y,z),r)
	{
	
	}

	Obstacle(Vector3D pos, double radius): BaseGameEntity(0, pos, radius)
	{}

	virtual ~Obstacle(){}

	//this is defined as a pure virtual function in Basegame
	//it must be implemented
	void	Update(){}

	void	Render(); // Draw sphere from mesh triangles
};

#endif