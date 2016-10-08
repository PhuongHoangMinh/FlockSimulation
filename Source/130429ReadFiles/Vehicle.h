#ifndef VEHICLE_H
#define VEHICLE_H

#include "MovingEntity.h"
#include "Vector3D.h"
#include "SteeringBehaviors.h"
#include "CellSpacePartition.h"

#include <vector>
#include <list>
#include <string>

class GameWorld;
class SteeringBehaviors;


class Vehicle : public MovingEntity
{
private:
	//a pointer to the world data. So a vehilce can access any obstacle,
	//path, wall or agent data
	GameWorld*		m_pWorld;
	
	//the steering behavior class
	SteeringBehaviors* m_pSteering;

	//for transforming Local Space to World Space and reversely
	float			m_fRotateAngle;
	Vector3D		m_vRotateAxis;

public:

	Vehicle(GameWorld* world,
		Vector3D position,
		double    rotation,
		Vector3D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale);

	~Vehicle();

	void Update();
	void Render(){}

	float		getRotateAngle()const{return m_fRotateAngle;}
	Vector3D	getRotateAxis()const {return m_vRotateAxis;}

	void		setRotateAngle(float val) { m_fRotateAngle = val;}
	void		setRotateAxis(Vector3D vec) 
	{
		//assert(vec && "RotateAxis not good");

		m_vRotateAxis = vec;
	}

	//---------------------accessor methods
	SteeringBehaviors*const Steering()const{return m_pSteering;}
	GameWorld*const			World()const {return m_pWorld;}
};


#endif