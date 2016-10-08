#ifndef MESH_H
#define MESH_H
#include "Index.h"
#include "Polygon.h"
#include "Vector3D.h"
#include "Material.h"
#include <vector>
#include <iostream>
using namespace std;


//#define AVertex  int[3] // 3 index of a vertex


class Mesh
{
public:
	std::vector<Vector3D>	m_Vertices; // a list(vector) of vertex
	std::vector<Vector3D>	m_Textures; // a vector of texture vectors
	std::vector<Vector3D>	m_Normals;  // a vector of normal vectors
	std::vector<Polygon*>	m_Surfaces; // a vector of polygons

	
};

#endif