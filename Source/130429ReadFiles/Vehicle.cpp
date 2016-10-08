#include "Vehicle.h"
#include "GameWorld.h"
#include <iostream>
using namespace std;

//----------------------------- ctor -------------------------------------
//------------------------------------------------------------------------
Vehicle::Vehicle(GameWorld* world,
				Vector3D position,
				double    rotation,
				Vector3D velocity,
				double    mass,
				double    max_force,
				double    max_speed,
				double    max_turn_rate,
				double    scale): MovingEntity(position, 
											   scale, 
											   velocity, 
											   max_speed,
											   Vector3D(0.0f, 0.0f, 0.0f),
											   mass,
											   Vector3D(scale, scale, scale),
											   max_turn_rate,
											   max_force), 
											   m_pWorld(world)
{

	//MovingEntity(position, scale, velocity, max_speed, velocity.normalize(), mass, Vector3D(scale, scale, scale), max_turn_rate, max_force);
	
	m_pSteering = new SteeringBehaviors(this);

}

							
Vehicle::~Vehicle()
{
	delete m_pSteering;

}


void Vehicle::Update()
{
	double time_elapsed = 0.012;

	Vector3D oldPos = Pos();

	Vector3D	SteeringForce = m_pSteering->Calculate();

	/*if(SteeringForce.z < 0)
	{
		std::cout<< " NOTE: wrong"<<std::endl;
	}*/

	Vector3D	acceleration = SteeringForce / m_dMass;

	m_vVelocity += acceleration*time_elapsed;

	m_vVelocity.Truncate(m_dMaxSpeed);

	m_vPos +=	m_vVelocity*time_elapsed;

	m_vHeading = Vec3DNormalize(m_vVelocity);

	if (Steering()->isSpacePartitioningOn())
	{
		//World()->CellSpace()->UpdateEntity(this, oldPos);
		//m_pWorld->CellSpace(
		m_pWorld->CellSpace()->UpdateEntity(this, oldPos);
	}

	

}
				 