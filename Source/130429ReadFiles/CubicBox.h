#ifndef CUBICBOX2D_H
#define CUBICBOX2D_H

#include "Vector3D.h"

class CubicBox
{
private:
	Vector3D m_vTopLeft;
	Vector3D m_vBottomRight;

	Vector3D m_vCenter;

public:

	CubicBox(Vector3D tl,
		Vector3D rb):m_vTopLeft(tl),
					 m_vBottomRight(rb)
					 
	{
		Vector3D center((m_vTopLeft.x + m_vBottomRight.x)/2, (m_vTopLeft.y + m_vBottomRight.y)/2, (m_vTopLeft.z + m_vBottomRight.z)/2);

		m_vCenter = center;

	}

	bool isOverlappedWith(const CubicBox& other)const
	{
		if((other.Bottom() > this->Top()) || (other.Top() < this->Bottom())) return false;
		if((other.Left() > this->Right()) || (this->Left() > other.Right())) return false;
		if((other.Far() > this->Near())   || (this->Far() > other.Near()))   return false;

		return true;
	}

	Vector3D TopLeft()const{return m_vTopLeft;}
	Vector3D BottomRight()const{return m_vBottomRight;}

	double Top()const{return m_vTopLeft.y;}	
	double Bottom()const{return m_vBottomRight.y;}
	double Left()const{return m_vTopLeft.x;}
	double Right()const{return m_vBottomRight.x;}
	double Near()const{return m_vTopLeft.z;}
	double Far()const{return m_vBottomRight.z;}

	void Render(){}

};

#endif