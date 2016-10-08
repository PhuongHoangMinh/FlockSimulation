#ifndef GAME_ENTITY_FUNCTION_TEMPLATES
#define GAME_ENTITY_FUNCTION_TEMPLATES

#include "BaseGameEntity.h"

//----------------------- TagNeighbors ----------------------------------
//
//  tags any entities contained in a std container that are within the
//  radius of the single entity parameter
//------------------------------------------------------------------------
template  <class T, class conT>
void TagNeighbors(const T& entity, conT& ContainerOfEntities, double radius)
{
	//iterate through all entites checking for range
	for(typename conT::iterator curEntity = ContainerOfEntities.begin();
		curEntity != ContainerOfEntities.end();
		++curEntity)
	{
		//first clear any current tag
		(*curEntity)->UnTag();
	
		Vector3D to =  (*curEntity)->Pos() - entity->Pos();

		double range = radius ;
		//double range = radius + (*curEntity)->BRadius();

		if( ((*curEntity) != entity) && (to.LengthSq() < range*range))
		{
		
			(*curEntity)->Tag();
		}
	}
	
}



#endif