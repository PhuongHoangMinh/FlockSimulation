#ifndef POINT_H
#define POINT_H
#include "Vector3D.h"
#include <gl/glut.h>
#include <gl/gl.h>
class Point
{
private:
	Vector3D m_pPos;
	bool	 m_bOccupied;
	
public:
	Point(Vector3D pos): m_pPos(pos), m_bOccupied(false)
	{
	}

	Point(double valx, double valy, double valz): m_bOccupied(false)
	{
		m_pPos.x = valx;
		m_pPos.y = valy;
		m_pPos.z = valz;
	}

	Point(bool occupied,
		Vector3D pos): m_pPos(pos), m_bOccupied(occupied)
	{
				
	}

	Vector3D Pos()const{return m_pPos;}
	bool	 isOccupied()const{return m_bOccupied;}

	void	 setPos(Vector3D pos){ m_pPos = pos;}
	void	 setOccupied(bool val){ m_bOccupied = val;}
	
	void	 Render();
};


#endif