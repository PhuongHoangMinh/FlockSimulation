#include "Tank.h"

void Tank::RenderNoText()
{
		//glColor3f(1.0f, 1.0f, 1.0);
		glRotatef(-90, 0.0f, 1.0f, 0.0f);
		glTranslatef(-1, 0 ,1.2);
		
		glDisable(GL_TEXTURE_2D);
		
		for(int a = 0; a< m_pMesh.m_Surfaces.size() ; a++)
		{
					
			//glEnable(GL_COLOR_MATERIAL);
			//glColorMaterial(GL_FRONT, GL_AMBIENT);
			//glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.ambient[0], m_pMesh.m_Surfaces[a]->m_pMaterial.ambient[1], m_pMesh.m_Surfaces[a]->m_pMaterial.ambient[2]);
			//

			//glColorMaterial(GL_FRONT, GL_DIFFUSE);
			//glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[0],m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[1], m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[2]);
			////glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[0], m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[1], m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[2]);
			//

			//glColorMaterial(GL_FRONT, GL_SPECULAR);
			//glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.specular[0], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[1], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[2]);
			////glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.specular[0], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[2], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[2]);

			

					glBegin(GL_POLYGON);

					//cout<< "Kd " << m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[0]<< " " << m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[1] << " " << m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[2] << endl;
					

					for(int b = 0; b< m_pMesh.m_Surfaces[a]->m_Vertexs->size(); b++)
					{
						//Normals
						int idxN = m_pMesh.m_Surfaces[a]->m_Vertexs->at(b).idx3 - 1;
						GLfloat nX = m_pMesh.m_Normals[idxN].x;
						GLfloat nY = m_pMesh.m_Normals[idxN].y;
						GLfloat nZ = m_pMesh.m_Normals[idxN].z;
						glNormal3f(nX, nY, nZ);

						//Texture
						int idxT = m_pMesh.m_Surfaces[a]->m_Vertexs->at(b).idx2 - 1;

						//Vertex
						int idx = m_pMesh.m_Surfaces[a]->m_Vertexs->at(b).idx1 - 1;

						GLfloat valx = m_pMesh.m_Vertices[idx].x*0.01;
						GLfloat valy = m_pMesh.m_Vertices[idx].y*0.01;
						GLfloat valz = m_pMesh.m_Vertices[idx].z*0.01;

						glVertex3f(valx, valy, valz);
					}
					

					glEnd();
		
			//glDisable(GL_COLOR_MATERIAL);
		}

}

void Tank::Render()
{
/*		float size = 3;
		glLineWidth(2);
		glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(size, 0, 0);

			glColor3f(1, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, size, 0);
			
			glColor3f(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, size);
		glEnd();*/	

		glRotatef(-90, 0.0f, 1.0f, 0.0f);
		glTranslatef(-1, 0 ,1.2);
		
		glDisable(GL_TEXTURE_2D);
		
		for(int a = 0; a< m_pMesh.m_Surfaces.size() ; a++)
		{
					
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT, GL_AMBIENT);
			glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.ambient[0], m_pMesh.m_Surfaces[a]->m_pMaterial.ambient[1], m_pMesh.m_Surfaces[a]->m_pMaterial.ambient[2]);
			

			glColorMaterial(GL_FRONT, GL_DIFFUSE);
			glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[0],m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[1], m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[2]);
			//glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[0], m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[1], m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[2]);
			

			glColorMaterial(GL_FRONT, GL_SPECULAR);
			glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.specular[0], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[1], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[2]);
			//glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.specular[0], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[2], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[2]);

			

					glBegin(GL_POLYGON);

					//cout<< "Kd " << m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[0]<< " " << m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[1] << " " << m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[2] << endl;
					

					for(int b = 0; b< m_pMesh.m_Surfaces[a]->m_Vertexs->size(); b++)
					{
						//Normals
						int idxN = m_pMesh.m_Surfaces[a]->m_Vertexs->at(b).idx3 - 1;
						GLfloat nX = m_pMesh.m_Normals[idxN].x;
						GLfloat nY = m_pMesh.m_Normals[idxN].y;
						GLfloat nZ = m_pMesh.m_Normals[idxN].z;
						glNormal3f(nX, nY, nZ);

						//Texture
						int idxT = m_pMesh.m_Surfaces[a]->m_Vertexs->at(b).idx2 - 1;

						//Vertex
						int idx = m_pMesh.m_Surfaces[a]->m_Vertexs->at(b).idx1 - 1;

						GLfloat valx = m_pMesh.m_Vertices[idx].x*0.01;
						GLfloat valy = m_pMesh.m_Vertices[idx].y*0.01;
						GLfloat valz = m_pMesh.m_Vertices[idx].z*0.01;

						glVertex3f(valx, valy, valz);
					}
					

					glEnd();
		
			glDisable(GL_COLOR_MATERIAL);
		}
		

		
	
}

void Tank::Update()
{
	if(this->isFired()) // if it is fired, it will stop and invisible
	{
		//No update position
	}
	else
	{
		//Move it along Z-direction
		float temp = getZ() - 0.005;
		this->setZ(temp);

		
		if(this->z < 0.0f)
		{
			int tempCross = m_pWorld->getNoCross();
			m_pWorld->setNoCross(++tempCross);
			//m_pWorld->m_iNoCross++;
			this->setFired(true);
			//cout<< "No Cross" << m_pWorld->m_iNoCross<< endl;
		}

		//Check collide with Missiles
		int loop = m_pWorld->Missiles().size();
		for(int i = 0; i< loop; i++)
		{
			//AABB Collision detection
			//if collide
			//this->setFired(true);
			//m_pWorld->Missiles()[i]->setTouch(true);

			//BOUNDING Box test
			////int test = TestAABBCollision(m_Bounding, m_pWorld->Missiles()[i]->getAABB());
			//int test = m_Bounding->TestAABBCollision(*m_pWorld->Missiles()[i]->getAABB());
			//if(test)
			//{
			//	cout<< " Collision: "<< test << endl;
			//	this->setFired(true);
			//	m_pWorld->Missiles()[i]->setTouch(true);
			//	
			//}

			float tempDisX = abs(this->x - m_pWorld->Missiles()[i]->getX());
			float tempDisY = abs(this->y - m_pWorld->Missiles()[i]->getY());
			float tempDisZ = abs(this->z - m_pWorld->Missiles()[i]->getZ());

			if((tempDisX < (0.4 + 0.25)) && (tempDisY < (0.125 + 0.0025)) && (tempDisZ < (0.25 +  0.005)))
			{
				/*cout<< "COllision Aircraft !!!"<< endl;
				cout<< "MissileX " << m_pWorld->Missiles()[i]->getX()<< endl;
				cout<< "AircraftX " << this->x << endl;
				cout<< "tempDisX: " << tempDisX<< endl;*/
				
				this->setFired(true);
				m_pWorld->Missiles()[i]->setTouch(true);
				m_pWorld->m_iTankDestroy++;
			}
			
			
			
		}
		
	}

}
