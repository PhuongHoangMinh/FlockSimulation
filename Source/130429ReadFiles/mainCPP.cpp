////#include <windows.h>
//#include <stdlib.h> //atof, atoi function
//#include <iostream>
////#include <vector>
//#include <stdio.h>  // fgets, printf, File processing
//#include <string>
//#include <fstream>
//#include <gl/glut.h>
//#include <gl/gl.h>
//#include "Vector3D.h"
//#include "Mesh.h"
//using namespace std;
//
//class Index;
//class Mesh;
//class Polygon;
//class Vector3D;
//
//int* perVertexProcessData( string Vertex);
//Index perVertexProcessDataIndex(string Vertex);
//void processFile();
//
//int main()
//{
//
//
//	processFile();
//
//	getchar();
//	return 0;
//}
//
//void processFile()
//{
//	int n;
//	int  m_inumFaces = 0;
//	int  m_inumVertices = 0;
//	int  m_inumTexture  = 0;
//	int  m_inumNormals	= 0;
//	int  m_inumVerticesPerFace= 0;
//	int ch;
//	
//	std::ifstream myFile;
//	myFile.open("tank_project.obj");
//	Mesh	aircraft2Mesh;
//	cout<< "Maximum Polygons: " << aircraft2Mesh.m_Surfaces.max_size()<< endl;
//	
//	string a;
//
//	while(!myFile.eof())
//	{
//		getline(myFile, a);
//		
//		unsigned pos = a.find("f ");
//		if( pos != std::string::npos)
//		{
//			m_inumFaces++;
//
//
//			unsigned newPos = a.find(" ");
//			string lastStr = a.substr(newPos+1);
//
//			unsigned newEnd = lastStr.find(" ");
//
//			string aVertex = lastStr.substr(0, newEnd);
//			m_inumVerticesPerFace++;
//
//
//			
//			Index outIndex = perVertexProcessDataIndex(aVertex);
//
//			Index *insertIndex = &outIndex;
//			
//
//			Polygon *tempPolygon = new Polygon();
//
//			tempPolygon->m_Vertexs->push_back(outIndex);
//
//			while(newEnd != string::npos)
//			{
//
//				lastStr = lastStr.substr(newEnd+ 1);
//				if(lastStr.length() == 0)
//				{
//					break;
//				}
//
//				newEnd = lastStr.find(" ");
//				aVertex = lastStr.substr(0, newEnd);
//				m_inumVerticesPerFace++;
//
//				Index inIndex  = perVertexProcessDataIndex(aVertex);
//
//				Index *insertIndexIn = &inIndex;
//
//				tempPolygon->m_Vertexs->push_back(inIndex);
//
//
//				
//			}
//
//			aircraft2Mesh.m_Surfaces.push_back(tempPolygon);
//
//			m_inumVerticesPerFace = 0;
//		}//end finding a face
//		
//		
//		//start finding v 
//		unsigned posV  = a.find("v ");
//		if(posV != string::npos)
//		{
//			//store x, y, z to array of double
//			double array3[3];
//			m_inumVertices++;
//			
//			unsigned newPos = a.find(" ");
//			string lastString = a.substr(newPos+ 1);
//			unsigned newEnd = lastString.find(" ");
//			string aVertex = lastString.substr(0, newEnd);
//			
//			array3[0] = atof(aVertex.c_str());
//			//cout << "Number at Vertex: " << array3[0]<< endl;
//			int i = 1;
//
//			while(newEnd != string::npos)
//			{
//				lastString	   = lastString.substr(newEnd+1);
//				
//				newEnd		   = lastString.find(" ");
//				
//				aVertex = lastString.substr(0, newEnd);
//				
//				array3[i] = atof(aVertex.c_str());
//				//cout << "Number at Vertex: " << array3[i]<< endl;
//				i++;
//			}
//
//			Vector3D vertex(array3[0], array3[1], array3[2]);
//
//			aircraft2Mesh.m_Vertices.push_back(vertex);
//		}//end finding a vector
//		
//		//start finding a texture
//		unsigned posVt = a.find("vt ");
//		if(posVt != string::npos)
//		{
//			m_inumTexture++;
//			double array3[3];
//
//			unsigned newPos = a.find(" ");
//			string lastString = a.substr(newPos+ 1);
//			unsigned newEnd = lastString.find(" ");
//			string aVertex = lastString.substr(0, newEnd);
//
//			array3[0] = atof(aVertex.c_str());
//			//cout << "Number at Texture: " << array3[0]<< endl;
//			int i = 1;
//
//			while(newEnd != string::npos)
//			{
//				lastString	   = lastString.substr(newEnd+1);
//				
//				newEnd		   = lastString.find(" ");
//				
//				aVertex = lastString.substr(0, newEnd);
//
//				array3[i] = atof(aVertex.c_str());
//				//cout << "Number Texture: " << array3[i]<< endl;
//				i++;
//
//			}
//
//			Vector3D textureVector(array3[0], array3[1], array3[2]);
//			aircraft2Mesh.m_Textures.push_back(textureVector);
//		}//end finding a Texture Vector
//
//		//start finding normal vector
//		unsigned posVn = a.find("vn ");
//		if(posVn != string::npos)
//		{
//			m_inumNormals++;
//			double array3[3];
//
//			unsigned newPos = a.find(" ");
//			string lastString = a.substr(newPos+ 1);
//			unsigned newEnd = lastString.find(" ");
//			string aVertex = lastString.substr(0, newEnd);
//			
//			array3[0] = atof(aVertex.c_str());
//			//cout << "Number at Normal: " << array3[0]<< endl;
//			int i = 1;
//
//			while(newEnd != string::npos)
//			{
//				lastString	   = lastString.substr(newEnd+1);
//				
//				newEnd		   = lastString.find(" ");
//				
//				aVertex = lastString.substr(0, newEnd);
//
//				array3[i] = atof(aVertex.c_str());
//				//cout << "Number Normal: " << array3[i]<< endl;
//				i++;
//			}
//
//			Vector3D normalVector(array3[0], array3[1], array3[2]);
//			aircraft2Mesh.m_Normals.push_back(normalVector);
//		}//end finding a Normal Vector
//
//
//	}//end while feof(pFile)
//
//
//
//
//
//	//Test Vector3D & MEsh
//	Vector3D myVector;
//	myVector.x = 3.0; 
//	myVector.y = 10.0;
//	myVector.z = 1.0;
//	
//
//	std::cout<< "Num of Faces: " << m_inumFaces<< endl;
//	std::cout<< "Num of Vertices: " << m_inumVertices<< endl;
//	std::cout<< "Num of Textures: " << m_inumTexture<< endl;
//	std::cout<< "Num of Normals: "  << m_inumNormals<< endl;
//
//}
//
//int* perVertexProcessData( string aVertex)
//{
//	int indexex[3];
//	int id = 0;
//	unsigned posIn  = aVertex.find("/");
//	while(posIn != string::npos)
//	{
//		string	 numStr = aVertex.substr(0, posIn);
//		//cout<< "StringNumber: " << numStr << endl;
//
//		indexex[id] = atoi(numStr.c_str());
//		cout<< "CONvert INT: " << indexex[id] << endl;
//		id++;
//
//
//		aVertex = aVertex.substr(posIn+1);
//		//cout<< "new AVertex is: " << aVertex << endl;
//		posIn = aVertex.find("/");
//
//	}
//	if(posIn == string::npos)
//	{
//		string numStr = aVertex;
//		//cout<< "String Number : " << numStr<<endl;
//		indexex[id] = atoi(numStr.c_str());
//		cout<< "CONvert INT: " <<  indexex[id] << endl;
//	}
//	return indexex;
//	
//}
//
//
//Index perVertexProcessDataIndex(string aVertex)
//{
//	int indexex[3];
//	int id = 0;
//	unsigned posIn  = aVertex.find("/");
//	while(posIn != string::npos)
//	{
//		string	 numStr = aVertex.substr(0, posIn);
//		//cout<< "StringNumber: " << numStr << endl;
//
//		indexex[id] = atoi(numStr.c_str());
//		//cout<< "CONvert INT: " << indexex[id] << endl;//COMMENT
//		id++;
//
//
//		aVertex = aVertex.substr(posIn+1);
//		//cout<< "new AVertex is: " << aVertex << endl;
//		posIn = aVertex.find("/");
//
//	}
//	if(posIn == string::npos)
//	{
//		string numStr = aVertex;
//		//cout<< "String Number : " << numStr<<endl;
//		indexex[id] = atoi(numStr.c_str());
//		//cout<< "CONvert INT: " <<  indexex[id] << endl;//COMMENT
//	}
//
//	Index returnIndex(indexex[0], indexex[1], indexex[2]);//COMMENT
//
//	return returnIndex;
//
//}
//
