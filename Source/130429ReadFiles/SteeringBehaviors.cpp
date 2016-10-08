#include "SteeringBehaviors.h"
#include "Vehicle.h"
#include "Transformations.h"
#include "GameWorld.h"
#include<iostream>
using namespace std;
#include <cassert>

using std::string;
using std::vector;


//------------------------- ctor -----------------------------------------
//
//------------------------------------------------------------------------
SteeringBehaviors::SteeringBehaviors(Vehicle* agent):                       
								m_pVehicle(agent),
								m_iFlags(0),
								m_dDBoxLength(Prm.MinDetectionBoxLength),
								m_dWeightCohesion(3.0),
								m_dWeightAlignment(1.0),
								m_dWeightSeparation(1.0),
								m_dWeightObstacleAvoidance(Prm.ObstacleAvoidanceWeight),
								m_dWeightWander(1.0),
								m_dWeightWallAvoidance(Prm.WallAvoidanceWeight),
								m_dViewDistance(3.0),
								m_dWallDetectionFeelerLength(Prm.WallDetectionFeelerLength),
								m_Feelers(3),
								m_Deceleration(fast),
								m_pTargetAgent1(NULL),
								m_pTargetAgent2(NULL),
								m_dWanderDistance(WanderDist),
								m_dWanderJitter(WanderJitterPerSec),
								m_dWanderRadius(WanderRad),
								//m_dWaypointSeekDistSq(WaypointSeekDist*WaypointSeekDist),
								m_dWeightSeek(1.0),
								m_dWeightFlee(Prm.FleeWeight),
								m_dWeightArrive(1.0),
								m_dWeightPursuit(Prm.PursuitWeight),
								m_dWeightOffsetPursuit(1.0),
								m_dWeightInterpose(Prm.InterposeWeight),
								m_dWeightHide(Prm.HideWeight),
								m_dWeightEvade(0.01),
								m_dWeightFollowPath(1.0),
								m_bCellSpaceOn(false),
								m_SummingMethod(prioritized)
{

	Vector3D startingForce(0.0f, 0.0f, 0.0f);
	m_vSteeringForce = startingForce;


	m_pPath = new Path();
	m_pPath->LoopOn();

	//Vector3D point1(-8,0,-8);
	//Vector3D point2(0,0,-9);
	//Vector3D point3(8,0,-8);
	//Vector3D point4(8,0,8);
	//Vector3D point5(0,0,9);
	//Vector3D point6(-8,0,8);
	//Vector3D point7(-9,0,0);
	//Vector3D point8(9, 0,0);
	//std::list<Vector3D> listPoint;
	//listPoint.push_back(point1);
	//listPoint.push_back(point2);
	//listPoint.push_back(point3);
	//listPoint.push_back(point8);
	//listPoint.push_back(point4);
	//listPoint.push_back(point5);
	//listPoint.push_back(point6);
	//listPoint.push_back(point7);

	Vector3D point1(10, 0, 0);
	Vector3D point2(8.65, 0, 5);
	Vector3D point3(5, 0, 8.65);
	Vector3D point4(0, 0, 10);
	Vector3D point5(-5, 0, 8.65);
	Vector3D point6(-8.65, 0, 5);
	Vector3D point7(-10, 0, 0);
	Vector3D point8(-8.65, 0, -5);
	Vector3D point9(-5, 0, -8.65);
	Vector3D point10(0, 0 , -10);
	Vector3D point11(5, 0, -8.65);
	Vector3D point12(8.65, 0, -5);
	std::list<Vector3D> listPoint;
	listPoint.push_back(point1);
	listPoint.push_back(point2);
	listPoint.push_back(point3);
	listPoint.push_back(point4);
	listPoint.push_back(point5);
	listPoint.push_back(point6);
	listPoint.push_back(point7);
	listPoint.push_back(point8);
	listPoint.push_back(point9);
	listPoint.push_back(point10);
	listPoint.push_back(point11);
	listPoint.push_back(point12);
	//listPoint.push_back(point12);

	m_pPath->Set(listPoint);
	m_pPath->setCurWayPoint(m_pVehicle->Pos());

	m_dWaypointSeekDistSq = WaypointSeekDist*WaypointSeekDist;

	m_vTarget.x = 0.0;
	m_vTarget.y = 0.0;
	m_vTarget.z = 0.0;
	
}

//---------------------------------dtor ----------------------------------
//SteeringBehavior::~SteeringBehavior()
//{
//	//delete m_pPath;
//}

Vector3D SteeringBehaviors::Seek(Vector3D TargetPos)
{
	Vector3D Distance = TargetPos - m_pVehicle->Pos();
	Vector3D DesiredVelocity = Vec3DNormalize(Distance)* (m_pVehicle->MaxSpeed()/2) ;//* m_pVehicle->MaxSpeed()

	return (DesiredVelocity - m_pVehicle->Velocity());

}

Vector3D SteeringBehaviors::Flee(Vector3D TargetPos)
{
	Vector3D DesiredVelocity = Vec3DNormalize(m_pVehicle->Pos() - TargetPos) * m_pVehicle->MaxSpeed();
	
	return (DesiredVelocity - m_pVehicle->Velocity());
}

Vector3D SteeringBehaviors::Arrive(Vector3D TargetPos, SteeringBehaviors::Deceleration deceleration)
{
	Vector3D	ToTarget = TargetPos - m_pVehicle->Pos();

	double dist = ToTarget.Length();

	if(dist >0)
	{
		//because Deceleration is enumerated as an int, this value is required
		//to provide fine tweaking of the deceleration..
		
		double DecelerationTweaker = 1;
		/*if(On(offset_pursuit))
		{
			DecelerationTweaker = 0.5;
		}*/

		//calculate the speed required to reach the target given the desired
		//deceleration
		double speed =  dist / ((double)deceleration * DecelerationTweaker);     

		//make sure the velocity does not exceed the max
		speed = min(speed, m_pVehicle->MaxSpeed());

		//from here proceed just like Seek except we don't need to normalize 
		//the ToTarget vector because we have already gone to the trouble
		//of calculating its length: dist. 
		Vector3D DesiredVelocity =  ToTarget * speed / dist;

		return (DesiredVelocity - m_pVehicle->Velocity());
	}
}

Vector3D SteeringBehaviors::Pursuit(const Vehicle* evader)
{
	Vector3D ToEvader = evader->Pos() - m_pVehicle->Pos();

	double RelativeHeading = m_pVehicle->Heading().Dot(evader->Heading());

	if((ToEvader.Dot(m_pVehicle->Heading()) > 0) && (RelativeHeading < -0.95) )
	{
		return Seek(evader->Pos());
	}

	
	double LookAheadTime = ToEvader.Length()/ (m_pVehicle->MaxSpeed() + evader->Speed());

	return Seek(evader->Pos() + evader->Velocity()*LookAheadTime);

	//return Vector3D(0.0, 0.0, 0.0);
}




Vector3D	SteeringBehaviors::Calculate()
{
	//m_vSteeringForce.Zero();

	m_vSteeringForce.Zero();	
	
	if(!isSpacePartitioningOn())
	{
		if(On(separation) || On(allignment) || On(cohesion) )	
		{
		
			m_pVehicle->World()->TagVehiclesWithinViewRange(m_pVehicle, m_dViewDistance);
		}
	}
	else
	{
		
		/*if(On(separation) || On(allignment) || On(cohesion))
		{
			m_pVehicle->World()->CellSpace()->CalculateNeighbors(m_pVehicle->Pos(), m_dViewDistance);
		}*/
	}


	switch(m_SummingMethod)
	{
	case weighted_average:
		m_vSteeringForce = CalculateWeightedSum();
		break;
	case prioritized:
		m_vSteeringForce = CalculatePrioritized();
		break;
	
	}

	return m_vSteeringForce;
	
}

//---------------------- CalculatePrioritized ----------------------------
//
//  this method calls each active steering behavior in order of priority
//  and acumulates their forces until the max steering force magnitude
//  is reached, at which time the function returns the steering force 
//  accumulated to that  point
//  Giving a good compromise between speed and accuracy
//------------------------------------------------------------------------
Vector3D	SteeringBehaviors::CalculatePrioritized()
{
	Vector3D force;

	if(On(wall_avoidance))
	{
		
	}

	if(On(obstacle_avoidance))
	{
		//force = ObstacleAvoidance(m_pVehicle->World())
	}

	if(On(evade))
	{
		assert(m_pTargetAgent1 && "Evade Target not assigned");

		force = Evade(m_pTargetAgent1)*m_dWeightEvade;
		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;

	}

	//Flocking - space partitioning or not
	if(!isSpacePartitioningOn())
	{
		if(On(separation))
		{
			force = Separation(m_pVehicle->World()->Agents())*m_dWeightSeparation;

			if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
		}

		if(On(allignment))
		{
			force = Alignment(m_pVehicle->World()->Agents())*m_dWeightAlignment;

			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
		}

		if(On(cohesion))
		{
			force = Cohesion(m_pVehicle->World()->Agents())*m_dWeightCohesion;

			if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
		}
	}
	else
	{
		
		if(On(separation))
		{
		
		}

		if(On(cohesion))
		{
			force = CohesionPlus(m_pVehicle->World()->Agents())*m_dWeightCohesion;
			
			if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
		}

		if(On(allignment))
		{
			force = AlignmentPlus(m_pVehicle->World()->Agents())*m_dWeightAlignment;
			
			if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
		}
	
	}

	if(On(seek))
	{
		Vector3D target = m_vTarget; //(4,0,6 )
		force = Seek(target)*m_dWeightSeek;

		if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}
	
	if(On(arrive))
	{
		Vector3D target = m_vTarget; //(4,0,6 )
		force = m_dWeightArrive*Arrive(target, fast);
	
		if(!AccumulateForce(m_vSteeringForce, force)) 
			return m_vSteeringForce;
	}

	if(On(wander))
	{
		force = m_dWeightWander*Wander();

		if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	
	}

	if(On(pursuit))
	{
		assert(m_pTargetAgent1 && "pursuit target not assigned");
		force = Pursuit(m_pTargetAgent1)*m_dWeightPursuit;

		if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}
	
	if(On(offset_pursuit))
	{
		assert(m_pTargetAgent1 && "offset pursuit not assigned");
		assert(!m_vOffset.isZero() && "No offset assigned");

		force = OffsetPursuit(m_pTargetAgent1, m_vOffset);

		if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if(On(follow_path))
	{
		force = FollowPath()*m_dWeightFollowPath;
		
		if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	return m_vSteeringForce;
}


bool SteeringBehaviors::AccumulateForce(Vector3D &RunningTot, Vector3D ForceToAdd)
{
	//calculate how much steering force the vehicle has used so far
	double MagnitudeSoFar = RunningTot.Length();

	double MagnitudeRemaining = m_pVehicle->MaxForce() - MagnitudeSoFar;

	//return false is no more force left to use
	if(MagnitudeRemaining <= 0.0) return false;

	//calculate the magnitude of the force we want to add
	double MagnitudeToAdd = ForceToAdd.Length();

	if(MagnitudeToAdd < MagnitudeRemaining)
	{
		RunningTot += ForceToAdd;	
	}
	else
	{
		RunningTot += (Vec3DNormalize(ForceToAdd)*MagnitudeRemaining);
	}
	
	return true;
}

//---------------------- CalculateWeightedSum ----------------------------
//
//  this simply sums up all the active behaviors X their weights and 
//  truncates the result to the max available steering force before 
//  returning
//  Tweaking the parameters- weighted- can be a juggling act
//------------------------------------------------------------------------
Vector3D	SteeringBehaviors::CalculateWeightedSum()
{
	if(!isSpacePartitioningOn())
	{
		if(On(separation))
		{
			m_vSteeringForce += Separation(m_pVehicle->World()->Agents())*m_dWeightSeparation;
		}

		if(On(allignment))
		{
			m_vSteeringForce += Alignment(m_pVehicle->World()->Agents())* m_dWeightAlignment;
		}

		if(On(cohesion))
		{
			m_vSteeringForce += Cohesion(m_pVehicle->World()->Agents())* m_dWeightCohesion;
		}
	
	}

	if(On(wander))
	{
		m_vSteeringForce += m_dWeightWander*Wander();
		
	}

	if(On(seek))
	{
		Vector3D target(4,0,6 );
		m_vSteeringForce += m_dWeightSeek*Seek(target);
	}

	if(On(arrive))
	{
		Vector3D target(4,0,6);
		m_vSteeringForce += m_dWeightArrive*Arrive(target, m_Deceleration);
	}
	
	if(On(flee))
	{
		
	
	}

	if(On(pursuit))
	{
		assert(m_pTargetAgent1 && "pursuit target not assigned");

		m_vSteeringForce += Pursuit(m_pTargetAgent1) * m_dWeightPursuit;
	}

	if(On(offset_pursuit))
	{
		assert(m_pTargetAgent1 && "pursuit target not assigned");
		assert(!m_vOffset.isZero() && "No offset assigned");
		
		m_vSteeringForce += OffsetPursuit(m_pTargetAgent1, m_vOffset) * m_dWeightOffsetPursuit;

	}
	
	if(On(interpose))
	{
		assert(m_pTargetAgent1 && m_pTargetAgent2 && "Interpose agents not assigned");

		m_vSteeringForce += Interpose(m_pTargetAgent1, m_pTargetAgent2)*m_dWeightInterpose;
	}

	if(On(hide))
	{
		assert(m_pTargetAgent1 && "Hide target not assigned");

		//m_vSteeringForce += Hide(m_pTargetAgent1, m_pVehicle->World());
	}

	if(On(evade))
	{
		assert(m_pTargetAgent1 && "Evade target not assigned");

		m_vSteeringForce += Evade(m_pTargetAgent1)* m_dWeightEvade;
	}

	m_vSteeringForce.Truncate(m_pVehicle->MaxForce());
	
	double Length = m_vSteeringForce.Length();
	return m_vSteeringForce;
}


//----------------------------- Evade ------------------------------------
//
//  similar to pursuit except the agent Flees from the estimated future
//  position of the pursuer
//------------------------------------------------------------------------
Vector3D SteeringBehaviors::Evade(const Vehicle* pursuer)
{
  /* Not necessary to include the check for facing direction this time */

  Vector3D ToPursuer = pursuer->Pos() - m_pVehicle->Pos();

  //uncomment the following two lines to have Evade only consider pursuers 
  //within a 'threat range'
  const double ThreatRange = 100.0;
  if (ToPursuer.LengthSq() > ThreatRange * ThreatRange) return Vector3D();
 
  //the lookahead time is propotional to the distance between the pursuer
  //and the pursuer; and is inversely proportional to the sum of the
  //agents' velocities
  double LookAheadTime = ToPursuer.Length() / 
			(m_pVehicle->MaxSpeed() + pursuer->Speed());
  
  //now flee away from predicted future position of the pursuer
  return Flee(pursuer->Pos() + pursuer->Velocity() * LookAheadTime);
}

//------------------------- GetHidingPosition ----------------------------
//
//  Given the position of a hunter, and the position and radius of
//  an obstacle, this method calculates a position DistanceFromBoundary 
//  away from its bounding radius and directly opposite the hunter
//------------------------------------------------------------------------
Vector3D	SteeringBehaviors::GetHidingPosition(const Vector3D& posOb, 
												 const double radius, 
												 const Vector3D& posHunter)
{
	
	const double DistanceFromBoundary = 1.0; // NOTE
	double DistAway = radius + DistanceFromBoundary;

	Vector3D	ToOb = Vec3DNormalize(posOb + posHunter);

	return posOb+ (ToOb*DistAway);

}


//--------------------------- Hide ---------------------------------------
//
//------------------------------------------------------------------------
Vector3D	SteeringBehaviors::Hide(const Vehicle* hunter,
									const vector<BaseGameEntity*>& obstacles)
{

	double DistToClosest = MaxDouble;
	Vector3D BestHidingSpot;

	std::vector<BaseGameEntity*>::const_iterator curOb = obstacles.begin();
	std::vector<BaseGameEntity*>::const_iterator closest;

	while(curOb != obstacles.end())
	{
		Vector3D HidingSpot = GetHidingPosition((*curOb)->Pos(), 
												(*curOb)->BRadius(), 
												hunter->Pos());

		double dist = Vec3DDistanceSq(HidingSpot, m_pVehicle->Pos());

		if(dist < DistToClosest)
		{
			DistToClosest  = dist;

			BestHidingSpot = HidingSpot;

			closest		   = curOb;
		}
		++curOb;
	
	}//end while

	if(DistToClosest == MaxFloat)
	{
		return Evade(hunter);
	}

	//else use Arrive on the hiding spot
	return Arrive(BestHidingSpot, fast);

}

//--------------------------- Interpose ----------------------------------
//
//  Given two agents, this method returns a force that attempts to 
//  position the vehicle between them
//------------------------------------------------------------------------
Vector3D SteeringBehaviors::Interpose(const Vehicle* AgentA,
                                     const Vehicle* AgentB)
{
  //first we need to figure out where the two agents are going to be at 
  //time T in the future. This is approximated by determining the time
  //taken to reach the mid way point at the current time at at max speed.
  Vector3D MidPoint = (AgentA->Pos() + AgentB->Pos()) / 2.0;

  double TimeToReachMidPoint = Vec3DDistance(m_pVehicle->Pos(), MidPoint) /
                               m_pVehicle->MaxSpeed();

  //now we have T, we assume that agent A and agent B will continue on a
  //straight trajectory and extrapolate to get their future positions
  Vector3D APos = AgentA->Pos() + AgentA->Velocity() * TimeToReachMidPoint;
  Vector3D BPos = AgentB->Pos() + AgentB->Velocity() * TimeToReachMidPoint;

  //calculate the mid point of these predicted positions
  MidPoint = (APos + BPos) / 2.0;

  //then steer to Arrive at it
  return Arrive(MidPoint, fast);
}

//------------------------- Offset Pursuit -------------------------------
//
//  Produces a steering force that keeps a vehicle at a specified offset
//  from a leader vehicle
//------------------------------------------------------------------------
Vector3D	SteeringBehaviors::OffsetPursuit(const Vehicle* leader,
											 const Vector3D offset)
{
	Vector3D WorldOffsetPos = PointToWorldSpace(offset, 
												leader->getRotateAngle(),
												leader->getRotateAxis(),
												leader->Pos());

	Vector3D ToOffset = WorldOffsetPos - m_pVehicle->Pos();

	double LookAHeadTime = ToOffset.Length()/(m_pVehicle->MaxSpeed() + leader->Speed());

	//return Seek(WorldOffsetPos + leader->Velocity()*LookAHeadTime);
	return Arrive(WorldOffsetPos + leader->Velocity()*LookAHeadTime, fast);
	
}

//--------------------------- Wander -------------------------------------
//
//  This behavior makes the agent wander about randomly
//------------------------------------------------------------------------
Vector3D	SteeringBehaviors::Wander()
{
	//double JitterThis
	//RandInRange(-1, 1);
	RandomClamped();
	double JitterThisTimeSlice = m_dWanderJitter*0.012;
	

	m_vWanderTarget	= Vector3D(RandomClamped()*m_dWanderJitter, 
								RandomClamped()*m_dWanderJitter, 
								RandomClamped()*m_dWanderJitter);
	
	//reproject this new vector back onto a unit circle
	m_vWanderTarget.Normalize();
	

	//increase the length of the vector to the same the radius
	m_vWanderTarget *= m_dWanderRadius;
	Vector3D	TargetLocal;
	if((RandInt(1,3) %3) == 1)
	{
	TargetLocal = m_vWanderTarget + Vector3D(m_dWanderDistance, 0, 0);
	}
	
	if((RandInt(1,3) %3) == 2)
	{
		TargetLocal = m_vWanderTarget + Vector3D(0,  m_dWanderDistance, 0);
	}

	if((RandInt(1,3) %3) == 0)
	{
		TargetLocal = m_vWanderTarget + Vector3D(0, 0,  m_dWanderDistance);
	}

	Vector3D	Target		= PointToWorldSpace(TargetLocal, 
												m_pVehicle->getRotateAngle(),
												m_pVehicle->getRotateAxis(), 
												m_pVehicle->Pos());
	
	return	(Target - m_pVehicle->Pos());
	//return  Seek(Target)/4; //Seek(Target)/4

}


//-------------------------------- Cohesion ------------------------------
//
//  returns a steering force that attempts to move the agent towards the
//  center of mass of the agents in its immediate area
//------------------------------------------------------------------------
Vector3D	SteeringBehaviors::Cohesion(const std::vector<Vehicle*> &agents)
{
	Vector3D CenterOfMass, SteeringForce;
	
	int NeighborCount	= 0;
	for(int a = 0; a< agents.size(); a++)
	{
		if((agents[a] != m_pVehicle) && (agents[a]!= m_pTargetAgent1) && agents[a]->IsTagged())  //
		{
			CenterOfMass += agents[a]->Pos();

			NeighborCount++;
		}
	}

	if(NeighborCount > 0)
	{
		CenterOfMass /= (double)NeighborCount;
		
		SteeringForce = Seek(CenterOfMass);
		//SteeringForce = CenterOfMass - m_pVehicle->Pos();
	}
	
	//the magnitude of cohesion is usuall much larger than separation or alignment so it usually helps to normalize it
	return Vec3DNormalize(SteeringForce);
	//return SteeringForce;
}

//---------------------------- Alignment ---------------------------------
//
//  returns a force that attempts to align this agents heading with that
//  of its neighbors
//------------------------------------------------------------------------
Vector3D	SteeringBehaviors::Alignment(const std::vector<Vehicle*> &agents)
{
	//used to record the average heading o te neighbors
	Vector3D	AverageHeading;

	//used to count the number of vehicles in the neighborhod
	int			NeighborCount = 0;

	for(unsigned int a = 0; a< agents.size(); a++ )
	{
		if( (agents[a] != m_pVehicle) && (agents[a] != m_pTargetAgent1)&& agents[a]->IsTagged() ) 
		{
			AverageHeading += agents[a]->Heading();

			++NeighborCount;
			
		}
	}

	if(NeighborCount > 0)
	{
		AverageHeading	/= (double)NeighborCount;
		AverageHeading	-= m_pVehicle->Heading();
	
	}

	return AverageHeading;
}

//---------------------------- Separation --------------------------------
//
// this calculates a force repelling from the other neighbors
//------------------------------------------------------------------------
Vector3D	SteeringBehaviors::Separation(const std::vector<Vehicle*> &agents)
{
	Vector3D	SteeringForce;

	for(unsigned int a = 0; a< agents.size(); a++)
	{
		if((agents[a] != m_pVehicle) && (agents[a] != m_pTargetAgent1) && (agents[a]->IsTagged()))
		{
			Vector3D ToAgent = m_pVehicle->Pos() - agents[a]->Pos();

			//scale the force inversely propotional to the agents distance
			//from its neighbor
			SteeringForce += Vec3DNormalize(ToAgent)/(ToAgent.Length()*10);
		}
			
	}

	return SteeringForce/2;
}


Vector3D	SteeringBehaviors::AlignmentPlus(const std::vector<Vehicle*> &agents)
{
	Vector3D AverageHeading;

	double NeighborCount = 0.0;

	//iterate through the neighbors and sum up all heading
	for(MovingEntity* pV = m_pVehicle->World()->CellSpace()->begin();
						!m_pVehicle->World()->CellSpace()->end();
						pV = m_pVehicle->World()->CellSpace()->next())
	{
		if(pV != m_pVehicle)
		{
			AverageHeading += pV->Heading();

			++NeighborCount;
		}

	}

	if(NeighborCount > 0.0)
	{
		AverageHeading /= NeighborCount;

		AverageHeading -= m_pVehicle->Heading();
	}

	return AverageHeading;


	return Vector3D(0.0f, 0.0f, 0.0f);
}


Vector3D	SteeringBehaviors::CohesionPlus(const std::vector<Vehicle*> &agents)
{
	//find the center of mass of all agents
	Vector3D CenterOfMass, SteeringForce;

	int NeighborCount = 0;

	for(BaseGameEntity* pV = m_pVehicle->World()->CellSpace()->begin();
		!m_pVehicle->World()->CellSpace()->end();
		pV = m_pVehicle->World()->CellSpace()->next())
	{
		if(pV != m_pVehicle)
		{
			CenterOfMass != pV->Pos();

			++NeighborCount;
		}
	
	}

	if(NeighborCount > 0)
	{
		CenterOfMass /= (double)NeighborCount;

		SteeringForce = Seek(CenterOfMass);
	}


	return Vec3DNormalize(SteeringForce);
	//return Vector3D(0.0f, 0.0f, 0.0f);
}

Vector3D	SteeringBehaviors::SeparationPlus(const std::vector<Vehicle*> &agents)
{
	Vector3D SteeringForce;

	//iterate through the neighbors and sum all the position vectors
	for(BaseGameEntity* pV = m_pVehicle->World()->CellSpace()->begin();
		!m_pVehicle->World()->CellSpace()->end();
		pV = m_pVehicle->World()->CellSpace()->next())
	{
		if(pV != m_pVehicle)
		{
			Vector3D ToAgent = m_pVehicle->Pos() - pV->Pos();

			SteeringForce += Vec3DNormalize(ToAgent)/(ToAgent.Length()*10);
		}
	}

	return SteeringForce/2;
	//return Vector3D(0.0f, 0.0f, 0.0f);
}

Vector3D	SteeringBehaviors::ObstacleAvoidance(const std::vector<BaseGameEntity*> &obstacles)
{
	//the detection box length is proportional to the agent's velocity
	Prm.MinDetectionBoxLength = 10.0f;
	m_dDBoxLength = Prm.MinDetectionBoxLength + 
		(m_pVehicle->Speed()/m_pVehicle->MaxSpeed())*Prm.MinDetectionBoxLength;

	//tag all obstacles within range of the box for processing
	m_pVehicle->World()->TagObstaclesWithinViewRange(m_pVehicle, m_dDBoxLength);

	//this will keep track of the closest intersecting obstacles
	BaseGameEntity* ClosestIntersectingObstacle = NULL;

	//this will be used to track the distance to Closest intersecting point
	double DistToClosestIP = MaxDouble;

	//this will record the transformed local coordinates of the CIB
	Vector3D LocalPosOfClosestObstacle;

	std::vector<BaseGameEntity*>::const_iterator curOb = obstacles.begin();

	while(curOb != obstacles.end())
	{
		if((*curOb)->IsTagged())
		{
			Vector3D LocalPos = PointToLocalSpace((*curOb)->Pos(),
													m_pVehicle->getRotateAngle(),
													m_pVehicle->getRotateAxis(),
													m_pVehicle->Pos());

			if(LocalPos.z >= 0)
			{
				double ExpandedRadius = (*curOb)->BRadius() + m_pVehicle->BRadius();
				
				if((fabs(LocalPos.x) < ExpandedRadius) && (fabs(LocalPos.y) < ExpandedRadius))
				{
				
					double cx = LocalPos.x;
					double cy = LocalPos.y;
					double cz = LocalPos.z;

					double SqrtPart = sqrt(ExpandedRadius*ExpandedRadius - cy*cy - cx*cx);
					
					double ip = cz - SqrtPart;

					if(ip <= 0.0)
					{
						ip = cz + SqrtPart;
					}
					
					//test to see if this is the closest so far. If it is, keep a record of obstacle and its coordinates
					if(ip< DistToClosestIP)
					{
						DistToClosestIP = ip;

						ClosestIntersectingObstacle = *curOb;

						LocalPosOfClosestObstacle = LocalPos;
					}
				}
			}
		}

		++curOb;

	}

	//if we have found an intersecting obstacle, calculate a steering force away from it
	Vector3D	SteeringForce;
	
	if(ClosestIntersectingObstacle)
	{
		//the closer the agent is to an object, the stronger the steering force should be
		double multiplier = 1.0 + (m_dDBoxLength - LocalPosOfClosestObstacle.z)/m_dDBoxLength;
		
		SteeringForce.y = (ClosestIntersectingObstacle->BRadius() - LocalPosOfClosestObstacle.y)*multiplier;
		SteeringForce.x = (ClosestIntersectingObstacle->BRadius() - LocalPosOfClosestObstacle.x)*multiplier;

		const double BrakingWeight = 0.2;

		SteeringForce.z = (ClosestIntersectingObstacle->BRadius() - LocalPosOfClosestObstacle.z)*BrakingWeight;
	}
	
	return VectorToWorldSpace(SteeringForce,
		m_pVehicle->getRotateAngle(),
		m_pVehicle->getRotateAxis());

	//return Vector3D(0.0f, 0.0f, 0.0f);
}


Vector3D SteeringBehaviors::FollowPath()
{
	if(Vec3DDistanceSq(m_pPath->CurrentWaypoint(), m_pVehicle->Pos()) < m_dWaypointSeekDistSq)
	{
		m_pPath->SetNextWayPoint();	
	}
	
	
	if(!m_pPath->Finished())
	{
		return	Arrive(m_pPath->CurrentWaypoint(), normal);
		//return Seek(m_pPath->CurrentWaypoint());
	}
	//else
	//{
	//	 
	//}


	//return Vector3D(0, 0, 0);
}


void SteeringBehaviors::SetNewCurWayPoint()
{
								
	m_pPath->setCurWayPoint(m_pVehicle->Pos());
								
}