////#include <windows.h>
//#include <stdlib.h> //atof, atoi function
//#include <iostream>
//#include <vector>
//#include <stdio.h>  // fgets, printf, File processing
//#include <string>
//#include <fstream>
//#include <gl/glut.h>
//#include <gl/gl.h>
//#include "Vector3D.h"
//#include "Mesh.h"
//using namespace std;
//
//struct Index;
//struct Mesh;
//struct Polygon;
//struct Vector3D;
//
//int* perVertexProcessData( string Vertex);
//Index perVertexProcessDataIndex(string Vertex);
//
//int main()
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
//	
//	myFile.open("spaceship.obj");
//	Mesh	aircraft2Mesh;
//	cout<< "Maximum Polygons: " << aircraft2Mesh.m_Surfaces.max_size()<< endl;
//	
//	string a;
//
//	while(!myFile.eof())
//	{
//		getline(myFile, a);
//		
//		//COMMENT
//		//std::cout<< a<<endl;
//		
//		char buf[500];
//
//		strcpy(buf, a.c_str());
//	
//		unsigned pos = a.find("f ");
//		if( pos != std::string::npos)
//		{
//			m_inumFaces++;
//
//			/*unsigned newPos = a.find(" ");
//			unsigned newEnd = a.find("/");
//
//			string tempStr = a.substr( newPos + 1, newEnd - newPos - 1);
//			string lastStr = a.substr(newEnd+ 1);*/
//			/*cout << "SUB STRING: "<< tempStr<< endl;
//			cout << "last String: " << lastStr<< endl;*/
//			//
//			////newEnd = lastStr.find("/");
//			////
//
//			////while(newEnd != string::npos)
//			////{
//			////	lastStr = lastStr.substr(newEnd+ 1);
//			////	newEnd = lastStr.find("/");
//			////	
//			////	cout<< "again : " << lastStr<< endl;
//			////	
//			////}
//
//
//			/*while( newPos != string::npos)
//			{
//			lastStr = lastStr.substr(newPos + 1);
//			newPos  = lastStr.find(" ");
//			cout<< "again: " << lastStr<< endl;
//			}*/
//
//			unsigned newPos = a.find(" ");
//			string lastStr = a.substr(newPos+1);
//			
//			//cout<< "Last String First Time: " << lastStr<< endl;
//
//			unsigned newEnd = lastStr.find(" ");
//
//			string aVertex = lastStr.substr(0, newEnd);
//			m_inumVerticesPerFace++;
//
//			/*int* indexexOUT;
//			indexexOUT = perVertexProcessData(aVertex);*/
//			
//			Index outIndex = perVertexProcessDataIndex(aVertex);
//			/*cout<< "tempINDEX AAA: " << outIndex.idx1 <<endl;
//			cout<< "tempINDEX AAA: " << outIndex.idx2 <<endl;
//			cout<< "tempINDEX AAA: " << outIndex.idx3 <<endl;*/ //COMMENT
//
//			Index *insertIndex = &outIndex;
//			
//			//index variable
//			//Index *tempIndex = new Index(indexex[0], indexex[1], indexex[2]);
//			Polygon *tempPolygon = new Polygon();
//			//tempPolygon->m_Vertexs->push_back(insertIndex);
//			tempPolygon->m_Vertexs->push_back(outIndex);
//
//			//tempPolygon.m_Vertexs.push_back(tempIndex);
//			//vector<int> tempVec;
//			
//			/*tempVec.push_back( outIndex.idx1);
//			tempVec.push_back( outIndex.idx2);
//			tempVec.push_back( outIndex.idx3)*/;
//			//tempVec.push_back(&outIndex);
//			
//			//cout<< "tempVEC: " << tempVec.at(0)<< endl;
//			
//			
//
//			//cout << "IIII: " << tempPolygon->m_Vertexs[0]->idx1<< endl;
//			//cout<< "IIII: "<<tempPolygon->m_Vertexs->at(0)->idx1<<endl;
//			//cout<< "INDEX: "<<tempPolygon->m_Vertexs->at(0).at(0);
//
//			//tempPolygon.m_Vertexs.push_back(tempVec);
//			
//			
//			//aircraft2Mesh.m_Surfaces[0].m_Vertexs.push_back(tempIndex);
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
//
//				/*int *indexexIN = perVertexProcessData(aVertex);*/
//				Index inIndex  = perVertexProcessDataIndex(aVertex);
//				////COMMENT
//				//cout<< "INNNN: " << inIndex.idx1<< endl;
//				//cout<< "INNNN: " << inIndex.idx2<< endl;
//				//cout<< "INNNN: " << inIndex.idx3<< endl;
//				Index *insertIndexIn = &inIndex;
//				//tempPolygon->m_Vertexs->push_back(insertIndexIn);
//				tempPolygon->m_Vertexs->push_back(inIndex);
//				//cout << "AVertex " << aVertex << endl; //COMMENT
//
//				//Index* tempIndexIN = new Index(indexexIN[0], indexexIN[1], indexexIN[2]);
//				//tempPolygon.m_Vertexs.push_back(tempIndexIN);
//				/*vector<int>  tempVectorIN;*/
//				/*tempVectorIN.push_back(inIndex.idx1);
//				tempVectorIN.push_back(inIndex.idx2);
//				tempVectorIN.push_back(inIndex.idx3);*/
//				//tempVectorIN.push_back(&inIndex);
//				
//
//				
//				//cout<< "INDEX: "<<tempPolygon->m_Vertexs->at(0)[0];
//				//tempPolygon.m_Vertexs.push_back(tempVectorIN);
//
//				//cout << "LastString: "<< lastStr<< endl;
//				
//			}
//
//			aircraft2Mesh.m_Surfaces.push_back(tempPolygon);
//
//
//			////COMMENT------------
//			//cout<< "Pervertex in 1st surface: "<< aircraft2Mesh.m_Surfaces[0]->m_Vertexs->at(0).idx1<<endl;
//			//cout<< "idx2: " << aircraft2Mesh.m_Surfaces[0]->m_Vertexs->at(0).idx2<<endl;
//			//cout<< "idx2: " << aircraft2Mesh.m_Surfaces[0]->m_Vertexs->at(0).idx3<<endl;
//
//			//cout << "PerVertex in 1st surface: " << aircraft2Mesh.m_Surfaces[0]->m_Vertexs->at(0)[1]<< endl;
//			//cout << "PerVertex in 1st surface: " << aircraft2Mesh.m_Surfaces[0]->m_Vertexs->at(0)[2]<< endl;
//			
//
//			//COMMENT
//			//cout<< "Num of Vertices per Face: " << m_inumVerticesPerFace<< endl;
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
//	//cout << "Vertex 1 : " << aircraft2Mesh.m_Vertices[0].x << " " << aircraft2Mesh.m_Vertices[0].y<< " " << aircraft2Mesh.m_Vertices[0].z<< endl;
//	//cout << "Texture 1: " << aircraft2Mesh.m_Textures[0].x << " " << aircraft2Mesh.m_Textures[0].y<< " " << aircraft2Mesh.m_Vertices[0].z<< endl;
//	//cout << "Normals 1: " << aircraft2Mesh.m_Normals[0].x  << " " << aircraft2Mesh.m_Normals[0].y<<  " " << aircraft2Mesh.m_Normals[0].z<< endl;
//	
//	////SHOW all vertices ------------------------------------------------
//	//for(int i = 0; i< aircraft2Mesh.m_Vertices.size(); i++)
//	//{	
//	//	cout<< "Vertex " << i<< " is: " <<  aircraft2Mesh.m_Vertices[i].x << " " << aircraft2Mesh.m_Vertices[i].y<< " " << aircraft2Mesh.m_Vertices[i].z<< endl;
//	//}
//	////------------------------------------------------------------------
//	
//	//cout << "TEST "<<" NUMBER of surface "<< aircraft2Mesh.m_Surfaces.size()<< endl;
//
//	//cout << "Test number of vertices on 1st surface " << aircraft2Mesh.m_Surfaces[0]->m_Vertexs->size() << endl;
//	//cout << "Test number of vertices on 2nd surface " << aircraft2Mesh.m_Surfaces[1]->m_Vertexs->size() << endl;
//	
//	//SHOW all surfaces index----------------------
//	//for(int i = 0; i< aircraft2Mesh.m_Surfaces.size(); i++)
//	//{
//	//	for(int j = 0; j< aircraft2Mesh.m_Surfaces[i]->m_Vertexs->size(); j++)
//	//	{
//	//	
//	//		cout<< "Vertex of surface "<< i << "at index : " << j << "is " << aircraft2Mesh.m_Surfaces[i]->m_Vertexs->at(j).idx1<< " " 
//	//			<< aircraft2Mesh.m_Surfaces[i]->m_Vertexs->at(j).idx2<< " "
//	//			<< aircraft2Mesh.m_Surfaces[i]->m_Vertexs->at(j).idx3<< endl;
//	//	}
//	//	
//	//	cout<< "Size at "<< i<<" " <<aircraft2Mesh.m_Surfaces[i]->m_Vertexs->size()<< endl;
//	//}
//
//	//cout << "PerVertex in 1st surface: " << aircraft2Mesh.m_Surfaces[0]->m_Vertexs->at(0)->at(0)<< endl;
//	//cout << "PerVertex in 1st surface: " << aircraft2Mesh.m_Surfaces[0]->m_Vertexs->at(0)->at(1)<< endl;
//	//cout << "PerVertex in 1st surface: " << aircraft2Mesh.m_Surfaces[0]->m_Vertexs->at(0)->at(2)<< endl;
//
//	//cout << "Test number of vertices on 1st surface " << aircraft2Mesh.m_Surfaces[0]->m_Vertexs.size()<< endl; 
//	
//
//	std::cout<< "Num of Faces: " << m_inumFaces<< endl;
//	std::cout<< "Num of Vertices: " << m_inumVertices<< endl;
//	std::cout<< "Num of Textures: " << m_inumTexture<< endl;
//	std::cout<< "Num of Normals: "  << m_inumNormals<< endl;
//
//	getchar();
//	return 0;
//}
//
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
