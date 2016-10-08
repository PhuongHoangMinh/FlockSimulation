#ifndef PATH_H
#define PATH_H

#include <list>
#include <cassert>
#include "Vector3D.h"

class Path
{
private:
	std::list<Vector3D>		m_WayPoints;

	//points to the current point
	std::list<Vector3D>::iterator curWaypoint;

	bool						  m_bLooped;

public:
	Path():m_bLooped(false){}

	Path(int NumWayPoints,
		bool looped): m_bLooped(looped)
	{
		
	}

	Vector3D CurrentWaypoint()const
	{
		return *curWaypoint;
	}

	bool Finished(){return !(curWaypoint != m_WayPoints.end());}

	void SetNextWayPoint()
	{
		/*if(++curWaypoint == m_WayPoints.end())
		{
			if(m_bLooped)
			{
				curWaypoint = m_WayPoints.begin();
			}
		}*/
		curWaypoint++;

		if(m_bLooped)
		{
			if(curWaypoint == m_WayPoints.end())
				curWaypoint = m_WayPoints.begin();
		}
	}

	void setCurWayPoint(Vector3D& pos)
	{
		double closest = Vec3DDistance(pos, *curWaypoint);
		std::list<Vector3D>::iterator  it = m_WayPoints.begin();

		for(it; it != m_WayPoints.end(); ++it)
		{
			double d = Vec3DDistance(pos, *it);

			if( d< closest)
			{
				
				closest = d;

				curWaypoint = it;
			
			}
			
		}

	}


	void LoopOn() {m_bLooped = true;}
	void LoopOff(){m_bLooped = false;}

	void Set(std::list<Vector3D> new_path) {m_WayPoints = new_path; curWaypoint = m_WayPoints.begin();}
	
	void Clear(){m_WayPoints.clear();}
	void Render(); // Path.cpp

};


#endif