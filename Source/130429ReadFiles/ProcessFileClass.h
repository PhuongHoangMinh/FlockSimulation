#ifndef PROCESSFILE
#define PROCESSFILE

#include <stdlib.h> //atof, atoi function
#include <iostream>
#include <vector>
#include <stdio.h>  // fgets, printf, File processing
#include <string>
#include <fstream>
#include "Vector3D.h"
#include "Mesh.h"
using namespace std;

class Index;
class Mesh;
class Polygon;
class Vector3D;

#define AIRCRAFT1   "aircraft1.obj"
#define AIRCRAFT2	"aircraft2.obj"
#define TANK		"tank_project.obj"
#define SPACESHIP	"spaceship.obj"
#define TURRET		"turret_barrrel.obj"
#define TURRET_BASE "turret_base.obj"
#define MISSILE		"Missile.obj"
#define TREE1		"Tree1.obj"
#define TREE2		"Tree2.obj"
#define BIRD		"simple-gull.obj"
#define CRANE		"crane.obj"
#define DOVE		"Dove13.obj"

#define Aircraft1MTL "aircraft1.mtl"
#define Aircraft2MTL "aircraft2.mtl"
#define TankMTL		 "tank_project.mtl"
#define SpaceshipMTL "Spaceship.mtl"
#define TurretMTL	 "turret_barrrel.mtl"
#define TurretBaseMTL "turret_base.mtl"
#define DoveMTL      "Dove13.mtl"



class ProcessFile
{
private:
	int	 m_iFileOption;  // = 1 aircraft1, = 2 aircraft2, =3 tank project, = 4 spaceship, =5 turret
	int  m_inumFaces;
	int  m_inumVertices;
	int  m_inumTexture;
	int  m_inumNormals;

	

	Index perVertexProcessDataIndex(string aVertex);
public:
	int		getFileOption()const{return m_iFileOption;}
	void	setFileOption(int value){m_iFileOption = value;}

	int		getNumberVertices()const{return this->m_inumVertices;}
	void	setNumberVertices(int value){this->m_inumVertices = value;}

	int		getNumberFaces()const{return this->m_inumFaces;}
	void	setNumberFaces(int value){this->m_inumFaces = value;}

	int		getNumberTextures()const{return this->m_inumTexture;}
	void	setNumberTextures(int value){this->m_inumTexture = value;}

	int		getNumberNormals()const{return this->m_inumNormals;}
	void	setNumberNormals(int value){ this->m_inumNormals = value;}
	
	Mesh    m_Mesh;

	ProcessFile()
	{
		m_iFileOption = 1; // default to read aircraft
		m_inumFaces	  = 0;
		m_inumVertices= 0;
		m_inumTexture = 0;
		m_inumNormals = 0;
	}

	ProcessFile(int fileOption)
	{
		setFileOption(fileOption);
		m_inumFaces	  = 0;
		m_inumVertices= 0;
		m_inumTexture = 0;
		m_inumNormals = 0;
	}
	
	void readData();
};


void ProcessFile::readData()
{
	std::ifstream myFile;
	//myFile.open("tank_project.obj");
	
	//Material Template Library file
	std::ifstream myMTL;
	
	switch(m_iFileOption)
	{
	case 1:
		myFile.open(AIRCRAFT1);
		myMTL.open(Aircraft1MTL);
		break;
	case 2:
		myFile.open(AIRCRAFT2);
		myMTL.open(Aircraft2MTL);
		break;
	case 3:
		myFile.open(TANK); //TANK
		myMTL.open(TankMTL);
		break;
	case 4:
		myFile.open(DOVE); //   crane  BIRD SPACESHIP(*0.025)  DOVE
		myMTL.open(DoveMTL); //SpaceshipMTL   DoveMTL
		break;
	case 5:
		myFile.open(TURRET);
		myMTL.open(TurretMTL);
		break;
	case 6:
		myFile.open(TURRET_BASE);
		myMTL.open(TurretBaseMTL);
		break;
	case 7:
		myFile.open(MISSILE);
		break;
	case 8:
		myFile.open(TREE1);
		break;

	case 9:
		myFile.open(TREE2);
		break;
	}

	Mesh	aircraft2Mesh;
	//cout<< "Maximum Polygons: " << aircraft2Mesh.m_Surfaces.max_size()<< endl;
	
	string a;

	//while(!myFile.eof())
	//{
	//	getline(myFile, a);
	//	
	//	unsigned pos = a.find("f ");
	//	if( pos != std::string::npos)
	//	{
	//		m_inumFaces++;


	//		unsigned newPos = a.find(" ");
	//		string lastStr = a.substr(newPos+1);

	//		unsigned newEnd = lastStr.find(" ");

	//		string aVertex = lastStr.substr(0, newEnd);
	//		//m_inumVerticesPerFace++;


	//		
	//		Index outIndex = perVertexProcessDataIndex(aVertex);

	//		Index *insertIndex = &outIndex;
	//		

	//		Polygon *tempPolygon = new Polygon();

	//		tempPolygon->m_Vertexs->push_back(outIndex);

	//		while(newEnd != string::npos)
	//		{

	//			lastStr = lastStr.substr(newEnd+ 1);
	//			if(lastStr.length() == 0)
	//			{
	//				break;
	//			}

	//			newEnd = lastStr.find(" ");
	//			aVertex = lastStr.substr(0, newEnd);
	//			//m_inumVerticesPerFace++;

	//			Index inIndex  = perVertexProcessDataIndex(aVertex);

	//			Index *insertIndexIn = &inIndex;

	//			tempPolygon->m_Vertexs->push_back(inIndex);


	//			
	//		}

	//		aircraft2Mesh.m_Surfaces.push_back(tempPolygon);

	//		//m_inumVerticesPerFace = 0;
	//	}//end finding a face
	//	
	//	
	//	//start finding v 
	//	unsigned posV  = a.find("v ");
	//	if(posV != string::npos)
	//	{
	//		//store x, y, z to array of double
	//		double array3[3];
	//		m_inumVertices++;
	//		
	//		unsigned newPos = a.find(" ");
	//		string lastString = a.substr(newPos+ 1);
	//		unsigned newEnd = lastString.find(" ");
	//		string aVertex = lastString.substr(0, newEnd);
	//		
	//		array3[0] = atof(aVertex.c_str());
	//		//cout << "Number at Vertex: " << array3[0]<< endl;
	//		int i = 1;

	//		while(newEnd != string::npos)
	//		{
	//			lastString	   = lastString.substr(newEnd+1);
	//			
	//			newEnd		   = lastString.find(" ");
	//			
	//			aVertex = lastString.substr(0, newEnd);
	//			
	//			array3[i] = atof(aVertex.c_str());
	//			//cout << "Number at Vertex: " << array3[i]<< endl;
	//			i++;
	//		}

	//		Vector3D vertex(array3[0], array3[1], array3[2]);

	//		aircraft2Mesh.m_Vertices.push_back(vertex);
	//	}//end finding a vector
	//	
	//	//start finding a texture
	//	unsigned posVt = a.find("vt ");
	//	if(posVt != string::npos)
	//	{
	//		m_inumTexture++;
	//		double array3[3];

	//		unsigned newPos = a.find(" ");
	//		string lastString = a.substr(newPos+ 1);
	//		unsigned newEnd = lastString.find(" ");
	//		string aVertex = lastString.substr(0, newEnd);

	//		array3[0] = atof(aVertex.c_str());
	//		//cout << "Number at Texture: " << array3[0]<< endl;
	//		int i = 1;

	//		while(newEnd != string::npos)
	//		{
	//			lastString	   = lastString.substr(newEnd+1);
	//			
	//			newEnd		   = lastString.find(" ");
	//			
	//			aVertex = lastString.substr(0, newEnd);

	//			array3[i] = atof(aVertex.c_str());
	//			//cout << "Number Texture: " << array3[i]<< endl;
	//			i++;

	//		}

	//		Vector3D textureVector(array3[0], array3[1], array3[2]);
	//		aircraft2Mesh.m_Textures.push_back(textureVector);
	//	}//end finding a Texture Vector

	//	//start finding normal vector
	//	unsigned posVn = a.find("vn ");
	//	if(posVn != string::npos)
	//	{
	//		m_inumNormals++;
	//		double array3[3];

	//		unsigned newPos = a.find(" ");
	//		string lastString = a.substr(newPos+ 1);
	//		unsigned newEnd = lastString.find(" ");
	//		string aVertex = lastString.substr(0, newEnd);
	//		
	//		array3[0] = atof(aVertex.c_str());
	//		//cout << "Number at Normal: " << array3[0]<< endl;
	//		int i = 1;

	//		while(newEnd != string::npos)
	//		{
	//			lastString	   = lastString.substr(newEnd+1);
	//			
	//			newEnd		   = lastString.find(" ");
	//			
	//			aVertex = lastString.substr(0, newEnd);

	//			array3[i] = atof(aVertex.c_str());
	//			//cout << "Number Normal: " << array3[i]<< endl;
	//			i++;
	//		}

	//		Vector3D normalVector(array3[0], array3[1], array3[2]);
	//		aircraft2Mesh.m_Normals.push_back(normalVector);
	//	}//end finding a Normal Vector


	//}//end while feof(pFile)


//--------------TEST MTL ---------------------------------------
	//Becarefull with MISSILE, SPACESHIP no file
	string materialName;
	Material polygonMaterial;

	
	//PARSE MTL file
	string line;
	Material tempMaterial;
	vector<Material> fileMaterials;

	if(myMTL != NULL)
	{
		while(!myMTL.eof())
		{
			getline(myMTL, line);
			unsigned posMate = line.find("newmtl ");
			
			if(posMate != std::string::npos)
			{	
				string tempName  = line.substr(posMate + 7);
				//cout<< "Material Name : "<< tempName<< endl;

				tempMaterial.name = tempName;

				for(int i = 0; i< 3; i++)
				{
					getline(myMTL, line);
					
					unsigned posKa = line.find("Ka ");
					if(posKa != std::string::npos)
					{
						//cout<< "line " << line<< endl;

						string sub = line.substr(3);
						
						for(int a = 0; a< 3; a++)
						{
							unsigned numberPos = sub.find(" ");
							string number = sub.substr(0, numberPos);
							//cout<< " A " << number;

							sub = sub.substr(numberPos+1);

							tempMaterial.ambient[a] = atof(number.c_str());

							//cout<< " Rest of sub " << sub;
						}
					}
					

					unsigned posKd = line.find("Kd ");
					if(posKd != std::string::npos)
					{
						string sub = line.substr(3);
						
						for(int a = 0; a< 3; a++)
						{
							unsigned numberPos = sub.find(" ");
							string number = sub.substr(0, numberPos);
							//cout<< " D " << number;

							sub = sub.substr(numberPos+1);

							tempMaterial.diffuse[a] = atof(number.c_str());

							//cout<< " Rest of sub " << sub;
						}
						//cout<< "line " << line<< endl;
					}
					//cout<< endl;


					unsigned posKs = line.find("Ks");
					if(posKs != std::string::npos)
					{
						string sub = line.substr(3);
						
						for(int a = 0; a< 3; a++)
						{
							unsigned numberPos = sub.find(" ");
							string number = sub.substr(0, numberPos);
							//cout<< " S " << number;

							sub = sub.substr(numberPos+1);

							tempMaterial.specular[a] = atof(number.c_str());

							//cout<< " Rest of sub " << sub;
						}
						//cout<< "line " << line<< endl;
					}
					//cout<< "Line "<< line <<endl;
				}//end for 
				
				fileMaterials.push_back(tempMaterial);
			}//end if
			
			
		} // end while
	}


	cout<< "Number of Material Per File is: " << fileMaterials.size() << endl;

	while(!myFile.eof())
	{
		getline(myFile, a);
		

		//Finding Material Name
		unsigned posM = a.find("usemtl ");
		if(posM != std::string::npos)
		{
			materialName = a.substr(posM + 7);
			//cout<< "Name: " << materialName << endl;
			
			for(int idx = 0; idx < fileMaterials.size(); idx++)
			{
				if(fileMaterials[idx].name.compare(materialName) == 0)
				{
					
					//aircraft2Mesh.m_Surfaces
					polygonMaterial = fileMaterials[idx];

					/*cout<< "Kd " << polygonMaterial.diffuse[0] << " " << polygonMaterial.diffuse[1] << " " << polygonMaterial.diffuse[2] << endl;*/
				}

			}

		}

		//Finding face
		unsigned pos = a.find("f ");
		if( pos != std::string::npos)
		{
			m_inumFaces++;


			unsigned newPos = a.find(" ");
			string lastStr = a.substr(newPos+1);

			unsigned newEnd = lastStr.find(" ");

			string aVertex = lastStr.substr(0, newEnd);
			//m_inumVerticesPerFace++;


			
			Index outIndex = perVertexProcessDataIndex(aVertex);

			Index *insertIndex = &outIndex;
			

			Polygon *tempPolygon = new Polygon();

			tempPolygon->m_Vertexs->push_back(outIndex);

			while(newEnd != string::npos)
			{

				lastStr = lastStr.substr(newEnd+ 1);
				if(lastStr.length() == 0)
				{
					break;
				}

				newEnd = lastStr.find(" ");
				aVertex = lastStr.substr(0, newEnd);
				//m_inumVerticesPerFace++;

				Index inIndex  = perVertexProcessDataIndex(aVertex);

				Index *insertIndexIn = &inIndex;

				tempPolygon->m_Vertexs->push_back(inIndex);


				
			}
			
			tempPolygon->m_pMaterial = polygonMaterial;

			aircraft2Mesh.m_Surfaces.push_back(tempPolygon);

			//m_inumVerticesPerFace = 0;
		}//end finding a face
		
		
		//start finding v 
		unsigned posV  = a.find("v ");
		if(posV != string::npos)
		{
			//store x, y, z to array of double
			double array3[3];
			m_inumVertices++;
			
			unsigned newPos = a.find(" ");
			string lastString = a.substr(newPos+ 1);
			unsigned newEnd = lastString.find(" ");
			string aVertex = lastString.substr(0, newEnd);
			
			array3[0] = atof(aVertex.c_str());
			//cout << "Number at Vertex: " << array3[0]<< endl;
			int i = 1;

			while(newEnd != string::npos)
			{
				lastString	   = lastString.substr(newEnd+1);
				
				newEnd		   = lastString.find(" ");
				
				aVertex = lastString.substr(0, newEnd);
				
				array3[i] = atof(aVertex.c_str());
				//cout << "Number at Vertex: " << array3[i]<< endl;
				i++;
			}

			Vector3D vertex(array3[0], array3[1], array3[2]);

			aircraft2Mesh.m_Vertices.push_back(vertex);
		}//end finding a vector
		
		//start finding a texture
		unsigned posVt = a.find("vt ");
		if(posVt != string::npos)
		{
			m_inumTexture++;
			double array3[3];

			unsigned newPos = a.find(" ");
			string lastString = a.substr(newPos+ 1);
			unsigned newEnd = lastString.find(" ");
			string aVertex = lastString.substr(0, newEnd);

			array3[0] = atof(aVertex.c_str());
			//cout << "Number at Texture: " << array3[0]<< endl;
			int i = 1;

			while(newEnd != string::npos)
			{
				lastString	   = lastString.substr(newEnd+1);
				
				newEnd		   = lastString.find(" ");
				
				aVertex = lastString.substr(0, newEnd);

				array3[i] = atof(aVertex.c_str());
				//cout << "Number Texture: " << array3[i]<< endl;
				i++;

			}

			Vector3D textureVector(array3[0], array3[1], array3[2]);
			aircraft2Mesh.m_Textures.push_back(textureVector);
		}//end finding a Texture Vector

		//start finding normal vector
		unsigned posVn = a.find("vn ");
		if(posVn != string::npos)
		{
			m_inumNormals++;
			double array3[3];

			unsigned newPos = a.find(" ");
			string lastString = a.substr(newPos+ 1);
			unsigned newEnd = lastString.find(" ");
			string aVertex = lastString.substr(0, newEnd);
			
			array3[0] = atof(aVertex.c_str());
			//cout << "Number at Normal: " << array3[0]<< endl;
			int i = 1;

			while(newEnd != string::npos)
			{
				lastString	   = lastString.substr(newEnd+1);
				
				newEnd		   = lastString.find(" ");
				
				aVertex = lastString.substr(0, newEnd);

				array3[i] = atof(aVertex.c_str());
				//cout << "Number Normal: " << array3[i]<< endl;
				i++;
			}

			Vector3D normalVector(array3[0], array3[1], array3[2]);
			aircraft2Mesh.m_Normals.push_back(normalVector);
		}//end finding a Normal Vector


	}//end while feof(pFile)




	//Test Vector3D & MEsh
	Vector3D myVector;
	myVector.x = 3.0; 
	myVector.y = 10.0;
	myVector.z = 1.0;
	

	std::cout<< "Num of Faces: " << m_inumFaces<< endl;
	std::cout<< "Num of Vertices: " << m_inumVertices<< endl;
	std::cout<< "Num of Textures: " << m_inumTexture<< endl;
	std::cout<< "Num of Normals: "  << m_inumNormals<< endl;
	
	m_Mesh = aircraft2Mesh;
}

Index ProcessFile::perVertexProcessDataIndex(std::string aVertex)
{
{
	int indexex[3];
	int id = 0;
	unsigned posIn  = aVertex.find("/");
	while(posIn != string::npos)
	{
		string	 numStr = aVertex.substr(0, posIn);
		//cout<< "StringNumber: " << numStr << endl;

		indexex[id] = atoi(numStr.c_str());
		//cout<< "CONvert INT: " << indexex[id] << endl;//COMMENT
		id++;


		aVertex = aVertex.substr(posIn+1);
		//cout<< "new AVertex is: " << aVertex << endl;
		posIn = aVertex.find("/");

	}
	if(posIn == string::npos)
	{
		string numStr = aVertex;
		//cout<< "String Number : " << numStr<<endl;
		indexex[id] = atoi(numStr.c_str());
		//cout<< "CONvert INT: " <<  indexex[id] << endl;//COMMENT
	}

	Index returnIndex(indexex[0], indexex[1], indexex[2]);//COMMENT

	return returnIndex;

}
}

#endif