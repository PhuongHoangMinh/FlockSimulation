#ifndef POLYGON_H
#define POLYGON_H

#include "Index.h"
#include "Material.h"

class Polygon
{
public: 
	std::vector<Index>* m_Vertexs; // a vector(3 or 4 sets of index) m_Vertex[i][0], m_Vertex[i][2]
	
	Material			m_pMaterial;

	Polygon()
	{
		m_Vertexs = new vector<Index>;
	}

};

//struct Polygon
//{
//	
//	std::vector<vector<int>> m_Vertexs;
//
//};


//struct Polygon
//{
//	std::vector<vector<int>> *m_Vertexs;
//
//	Polygon()
//	{
//		m_Vertexs = new vector<vector<int>>;
//	}
//};

#endif