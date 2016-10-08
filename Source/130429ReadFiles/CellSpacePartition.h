#ifndef CELLSPACEPARTITION_H
#define CELLSPACEPARTITION_H

#include <vector>
#include <list>
#include <cassert>

#include "Vector3D.h"
#include "CubicBox.h"
#include "utils.h"

template <class entity>
struct Cell
{
	//all the object inhabiting this cell
	std::list<entity> Members;

	//the box in 3D environment
	CubicBox	Box;

	Cell(Vector3D topLeft,
		Vector3D  rightBottom):Box(CubicBox(topLeft, rightBottom))
	{}
	

};

template <class entity>
class CellSpacePartition
{
private:
	
	std::vector<Cell<entity>>	m_Cells;

	//this is used to store any valid neighbors when an agent searches
	//its neighboring space
	std::vector<entity>			m_Neighbors;

	//this iterator will be used by the methods next and begin to traverse through the above vector of neighbors
	typename std::vector<entity>::iterator m_curNeighbor;

	//the width and height, depth of the world space
	double m_dSpaceWidth;
	double m_dSpaceHeight;
	double m_dSpaceDepth;

	//the number of cells in x,y, z axis
	int	   m_iNumCellsX;
	int    m_iNumCellsY;
	int    m_iNumCellsZ;

	//size of a cell
	double m_dCellSizeX;
	double m_dCellSizeY;
	double m_dCellSizeZ;

	//given a position of object --> determine the relevant cell index
	inline int PositionToIndex(const Vector3D& pos)const;

public:

	CellSpacePartition(double width,		//width of the enviroment
					   double height,		//height ...
					   double depth,		//depth
					   int    cellsX,		//number of cell x-axis
					   int	  cellsY,		//number of cell y-axis
					   int    cellsZ,		//number of cell z-axis
					   int    MaxEntitys);  //maximum number of entities to add

	//add entites to the class by allocating them to the appropriate cell
	inline void AddEntity(const entity& ent);	//USING template class -- we should use inline function

	//update an entity's cell by calling
	inline void UpdateEntity(const entity& ent, Vector3D oldPos); //oldPos is used to delete the object in the previous cell

	//this method calculates all a target's neighbors and stores them in the neighbor vector.
	inline void CalculateNeighbors(Vector3D TargetPos, double QueryRadius);
	
	//returns a reference to the entity at the front of neighbor vector
	inline entity& begin(){m_curNeighbor = m_Neighbors.begin(); return *m_curNeighbor;}

	//this returns the next entity in the neighbor vector
	inline entity& next(){++m_curNeighbor; return *m_curNeighbor;}

	//returns true if the end of the vector is found
	inline bool end(){return (m_curNeighbor == m_Neighbors.end()) || (*m_curNeighbor == 0);}

	
	//empties the cells of entities
	void EmptyCells();
	


};


template <class entity>
CellSpacePartition<entity>::CellSpacePartition(double width, 
											   double height, 
											   double depth, 
											   int cellsX, 
											   int cellsY, 
											   int cellsZ, 
											   int MaxEntitys):
							/*m_dSpaceWidth(width),
							m_dSpaceHeight(height),
							m_dSpaceDepth(depth),
							m_iNumCellsX(cellsX),
							m_iNumCellsY(cellsY),
							m_iNumCellsZ(cellsZ),*/
							m_Neighbors(MaxEntitys, entity())
{
	
	m_dSpaceWidth = width;
	m_dSpaceHeight= height;
	m_dSpaceDepth = depth;
	m_iNumCellsX  = cellsX;
	m_iNumCellsY  = cellsY;
	m_iNumCellsZ  = cellsZ;

	m_dCellSizeX = (double)(m_dSpaceWidth/(double)m_iNumCellsX);
	m_dCellSizeY = (double)(m_dSpaceHeight/(double)m_iNumCellsY);
	m_dCellSizeZ = (double)(m_dSpaceDepth/(double)m_iNumCellsZ);
	
	double left = 0.0;
	double right= 0.0;
	double bot  = 0.0;
	double top  = 0.0;
	double far  = 0.0;
	double near = 0.0;
	
	//insert cell to m_Cells
	for(int z = -m_iNumCellsZ/2; z< m_iNumCellsZ/2; z++)
	{
		for(int y = -m_iNumCellsY/2; y< m_iNumCellsY/2; y++)
		{
			for(int x = -m_iNumCellsX/2; x< m_iNumCellsX/2; x++)
			{
				left = x*m_dCellSizeX;
				right= left + m_dCellSizeX;

				bot = y*m_dCellSizeY;
				top = bot + m_dCellSizeY;

				far = z*m_dCellSizeZ;
				near  = far + m_dCellSizeZ;

				m_Cells.push_back(Cell<entity>(Vector3D(left,top, near), Vector3D(right, bot, far)));
			}
		}
	}

}

//----------------CalculateNeighbors----------------------
//this must be called in SteeringBehaviors.cpp as a vehicle 
//calculates the interaction force on its.
//It updates frequently as a vehicle call SteeringBehaviors.Calculate
//-----------------------------------------------------
template<class entity>
void CellSpacePartition<entity>::CalculateNeighbors(Vector3D TargetPos, 
													double QueryRadius)
{	
	//m_Neighbors is a vector used to store neighbors of a subject
	//Instead of vector.clear() and vector.push_back() method to slow down program
	//previous values are simply overwritten and a zero value is used mark the end of vector
	
	//create an iterator and set it to the begining of the neighbor vector
	std::vector<entity>::iterator curNbor = m_Neighbors.begin();

	//create the query box that is the bounding box of the target's query
	double left = TargetPos.x - QueryRadius;
	double right= TargetPos.x + QueryRadius;
	double top  = TargetPos.y + QueryRadius;
	double bottom = TargetPos.y - QueryRadius;
	double far   = TargetPos.z - QueryRadius;
	double near	 = TargetPos.z + QueryRadius; 
	CubicBox	QueryBox(Vector3D(left, top, near), Vector3D(right, bottom, far));


	//iterate through each cell and test to see if its bounding box overlaps with
	//the query box. If it does and it also contains entities then make further proximity tests
	std::vector<Cell<entity>>::iterator curCell;

	for(curCell = m_Cells.begin(); curCell!= m_Cells.end(); ++curCell)
	{
		if(curCell->Box.isOverlappedWith(QueryBox) && !curCell->Members.empty())
		{
			std::list<entity>::iterator it = curCell->Members.begin();

			for(it; it!= curCell->Members.end(); ++it)
			{
				if(Vec3DDistanceSq((*it)->Pos(), TargetPos) < QueryRadius*QueryRadius)
				{
					*curNbor++ = *it;
				}

			}

		}		
	}// next cell

	//mark the end of the list with a zero
	*curNbor = 0;

}


//clears the cells of all entities
template<class entity>
void CellSpacePartition<entity>::EmptyCells()
{
	std::vector<Cell<entity>>::iterator it = m_Cells.begin();

	for(it; it != m_Cells.end(); ++it)
	{
		it->Members.clear();
	}
}

//------------------PositionToIndex----------------------------
//Given a 3D position within the game world, this method calculates
//an index into its approriate cell
//-------------------------------------------------------------
template<class entity>
inline int CellSpacePartition<entity>::PositionToIndex(const Vector3D &pos) const
{
	int idx = 0;
	idx = (int)(m_iNumCellsX*(pos.x+(m_dSpaceWidth/2))/m_dSpaceWidth) + 
		((int)(m_iNumCellsY*(pos.y +(m_dSpaceHeight/2))/m_dSpaceHeight)*m_iNumCellsX) + 
		((int)(m_iNumCellsZ*(pos.z+(m_dSpaceDepth/2))/m_dSpaceDepth)*m_iNumCellsX*m_iNumCellsY);

	//if the entity's position is equal to Vector3D(m_dSpaceWidth,m_dSpaceHeight, m_dSpaceDepth)
	//then the index will overshoot.
	if(idx > (int)m_Cells.size()-1) idx = (int)m_Cells.size() - 1;

	return idx;

}

//-------------------AddEntity-----------------------------------
//used to add the entitys to the data structure
//---------------------------------------------------------------
template<class entity>
inline void CellSpacePartition<entity>::AddEntity(const entity &ent)
{
	assert(ent);

	int sz = m_Cells.size();
	int idx= PositionToIndex(ent->Pos());
	std::cout<< "IDX: " << idx << endl;
	m_Cells[idx].Members.push_back(ent);
}


//----------------------- UpdateEntity -----------------------------------
//
//  Checks to see if an entity has moved cells. If so the data structure
//  is updated accordingly
//------------------------------------------------------------------------
template<class entity>
inline void CellSpacePartition<entity>::UpdateEntity(const entity &ent, 
													 Vector3D oldPos)
{
	//if the index for the old pos and the new pos are not equal, 
	//then the entity has moved to another cell
	int OldIdx = PositionToIndex(oldPos);
	int NewIdx = PositionToIndex(ent->Pos());

	if(NewIdx == OldIdx) return;

	//the entity has moved into another cell so delete from current cell
	//and add to new one
	m_Cells[OldIdx].Members.remove(ent);
	m_Cells[NewIdx].Members.push_back(ent);

}


#endif