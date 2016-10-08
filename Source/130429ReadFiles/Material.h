#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <string>
using namespace std;

class Material
{
public:

	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess; // min = 0; max = 1
	float alpha;     // min = 0; max = 1

	
	std::string  name;
	std::string  colorMapFilename;
	std::string  bumpMapFilename;
	
	

};


#endif