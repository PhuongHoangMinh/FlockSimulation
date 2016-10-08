#ifndef MOVING_ENTITY
#define MOVING_ENTITY


#include <cassert>
#include "Vector3D.h"
#include "BaseGameEntity.h"


class MovingEntity : public BaseGameEntity
{
protected:

  Vector3D    m_vVelocity;
  
  //a normalized vector pointing in the direction the entity is heading. 
  Vector3D    m_vHeading;

  //a vector perpendicular to the heading vector
  //Vector3D    m_vSide; 

  double       m_dMass;
  
  //the maximum speed this entity may travel at.
  double       m_dMaxSpeed;

  //the maximum force this entity can produce to power itself 
  //(think rockets and thrust)
  double        m_dMaxForce;
  
  //the maximum rate (radians per second)this vehicle can rotate         
  double       m_dMaxTurnRate;

public:


  MovingEntity(Vector3D position,
               double    radius,
               Vector3D velocity,
               double    max_speed,
               Vector3D heading,
               double    mass,
               Vector3D scale,
               double    turn_rate,
               double    max_force):BaseGameEntity(0, position, radius),
                                  m_vHeading(heading),
								  m_vVelocity(velocity),
                                  m_dMass(mass),
                                  //m_vSide(m_vHeading.Perp()),
                                  m_dMaxSpeed(max_speed),
                                  m_dMaxTurnRate(turn_rate),
                                  m_dMaxForce(max_force)
  {
    m_vScale = scale;
	
  }

  virtual ~MovingEntity(){}

  //accessors
  Vector3D  Velocity()const{return m_vVelocity;}
  void      SetVelocity(const Vector3D& NewVel){m_vVelocity = NewVel;}
  
  double     Mass()const{return m_dMass;}
  
  //Vector3D  Side()const{return m_vSide;}

  double     MaxSpeed()const{return m_dMaxSpeed;}                       
  void      SetMaxSpeed(double new_speed){m_dMaxSpeed = new_speed;}
  
  double     MaxForce()const{return m_dMaxForce;}
  void      SetMaxForce(double mf){m_dMaxForce = mf;}

  bool      IsSpeedMaxedOut()const{return m_dMaxSpeed*m_dMaxSpeed >= m_vVelocity.LengthSq();}
  double     Speed()const{return m_vVelocity.Length();}
  double     SpeedSq()const{return m_vVelocity.LengthSq();}
  
  Vector3D  Heading()const{return m_vHeading;}
  void      SetHeading(Vector3D new_heading);
  //bool      RotateHeadingToFacePosition(Vector3D target);

  double     MaxTurnRate()const{return m_dMaxTurnRate;}
  void      SetMaxTurnRate(double val){m_dMaxTurnRate = val;}

};

//------------------------- SetHeading ----------------------------------------
//
//  first checks that the given heading is not a vector of zero length. If the
//  new heading is valid this fumction sets the entity's heading and side 
//  vectors accordingly
//-----------------------------------------------------------------------------
inline void MovingEntity::SetHeading(Vector3D new_heading)
{
	assert( (new_heading.LengthSq() - 1.0) < 0.00001);
  
  m_vHeading = new_heading;

  //the side vector must always be perpendicular to the heading
  //m_vSide = m_vHeading.Perp();
}


#endif