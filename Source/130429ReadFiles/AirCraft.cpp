#include "Aircraft.h"



void Aircraft::Render()
{
	float scale = 0.0f;
	float alignX = 0.0f;
	float alignY = 0.0f;
	float alignZ = 0.0f;
	float rotateAngle = 0.0f;

	switch(m_itype){
		case 1:
			scale = 0.000075f;
			alignZ = 0.8f;
			rotateAngle = -180.0f;
			break;
		case 2:
			rotateAngle = 0.0f;
			scale  = 0.001f;
			alignX = -0.52f;
			alignZ = 0.52f;
			break;
	}

	//float size = 3;
	//glLineWidth(2);
 //   glBegin(GL_LINES);
 //       glColor3f(1, 0, 0);
 //       glVertex3f(0, 0, 0);
 //       glVertex3f(size, 0, 0);

 //       glColor3f(1, 1, 0);
 //       glVertex3f(0, 0, 0);
 //       glVertex3f(0, size, 0);
 //       
	//	glColor3f(0, 0, 1);
 //       glVertex3f(0, 0, 0);
 //       glVertex3f(0, 0, size);
 //   glEnd();
	
		glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);
		glTranslatef(alignX, alignY, alignZ);
		
		glDisable(GL_TEXTURE_2D);

		for(int a = 0; a< m_pMesh.m_Surfaces.size(); a++)
		{
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT, GL_AMBIENT);
			glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.ambient[0], m_pMesh.m_Surfaces[a]->m_pMaterial.ambient[1], m_pMesh.m_Surfaces[a]->m_pMaterial.ambient[2]);
			//glColor3f(1.0, 0.5f, 0.4f);

			glColorMaterial(GL_FRONT, GL_DIFFUSE);
			glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[0],m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[1], m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[2]);
			//glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[0], m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[1], m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[2]);

			glColorMaterial(GL_FRONT, GL_SPECULAR);
			glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.specular[0], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[1], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[2]);
			//glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.specular[0], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[1], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[2]);

			glBegin(GL_POLYGON);
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

				GLfloat valx = m_pMesh.m_Vertices[idx].x*scale;
				GLfloat valy = m_pMesh.m_Vertices[idx].y*scale;
				GLfloat valz = m_pMesh.m_Vertices[idx].z*scale;

				glVertex3f(valx, valy, valz);
			}
			glEnd();
		
		glDisable(GL_COLOR_MATERIAL);
		
		}

}

void Aircraft::RenderNoText()
{
	float scale = 0.0f;
	float alignX = 0.0f;
	float alignY = 0.0f;
	float alignZ = 0.0f;
	float rotateAngle = 0.0f;

	switch(m_itype){
		case 1:
			scale = 0.000075f;
			alignZ = 0.8f;
			rotateAngle = -180.0f;
			break;
		case 2:
			rotateAngle = 0.0f;
			scale  = 0.001f;
			alignX = -0.52f;
			alignZ = 0.52f;
			break;
	}

	//float size = 3;
	//glLineWidth(2);
 //   glBegin(GL_LINES);
 //       glColor3f(1, 0, 0);
 //       glVertex3f(0, 0, 0);
 //       glVertex3f(size, 0, 0);

 //       glColor3f(1, 1, 0);
 //       glVertex3f(0, 0, 0);
 //       glVertex3f(0, size, 0);
 //       
	//	glColor3f(0, 0, 1);
 //       glVertex3f(0, 0, 0);
 //       glVertex3f(0, 0, size);
 //   glEnd();
	
		glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);
		glTranslatef(alignX, alignY, alignZ);
		
		glDisable(GL_TEXTURE_2D);

		for(int a = 0; a< m_pMesh.m_Surfaces.size(); a++)
		{
			//glEnable(GL_COLOR_MATERIAL);
			//glColorMaterial(GL_FRONT, GL_AMBIENT);
			//glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.ambient[0], m_pMesh.m_Surfaces[a]->m_pMaterial.ambient[1], m_pMesh.m_Surfaces[a]->m_pMaterial.ambient[2]);
			////glColor3f(1.0, 0.5f, 0.4f);

			//glColorMaterial(GL_FRONT, GL_DIFFUSE);
			//glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[0],m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[1], m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[2]);
			////glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[0], m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[1], m_pMesh.m_Surfaces[a]->m_pMaterial.diffuse[2]);

			//glColorMaterial(GL_FRONT, GL_SPECULAR);
			//glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.specular[0], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[1], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[2]);
			////glColor3f(m_pMesh.m_Surfaces[a]->m_pMaterial.specular[0], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[1], m_pMesh.m_Surfaces[a]->m_pMaterial.specular[2]);

			glBegin(GL_POLYGON);
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

				GLfloat valx = m_pMesh.m_Vertices[idx].x*scale;
				GLfloat valy = m_pMesh.m_Vertices[idx].y*scale;
				GLfloat valz = m_pMesh.m_Vertices[idx].z*scale;

				glVertex3f(valx, valy, valz);
			}
			glEnd();
		
		//glDisable(GL_COLOR_MATERIAL);
		
		}
}

void Aircraft::Update()
{
	if(this->isFired())
	{
		//No update	
	}
	else
	{	
		//Move it along Z direction
		float temp = getZ() - 0.005;
		this->setZ(temp);
		
		if(this->z < 0.0f)
		{
			int tempCross = m_pWorld->getNoCross();
			m_pWorld->setNoCross(++tempCross);

			
			this->setFired(true);
			//cout<< "No Cross" << m_pWorld->m_iNoCross<< endl;
		}

		//Check collide with Missiles
		int loop = m_pWorld->Missiles().size();
		for(int i = 0; i< loop; i++)
		{
			//AABB collision detection
			//if collide
			//this->setFired(true);
			//m_pWorld->Missiles()[i]->setTouch(true);
			
			////BOUNDing box test
			///*int test = TestAABBCollision(m_Bounding, m_pWorld->Missiles()[i]->getAABB());*/
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
			
			if(m_itype == 1)
			{
				if((tempDisX < (1 + 0.25)) && (tempDisY < (0.16 + 0.0025)) && (tempDisZ < (0.85 +  0.005)))
				{
					/*cout<< "COllision Aircraft !!!"<< endl;
					cout<< "MissileX " << m_pWorld->Missiles()[i]->getX()<< endl;
					cout<< "AircraftX " << this->x << endl;
					cout<< "tempDisX: " << tempDisX<< endl;*/

					this->setFired(true);
					m_pWorld->Missiles()[i]->setTouch(true);
					m_pWorld->m_iAircraftDestroy++;
				}
			}
			if(m_itype == 2)
			{
				if((tempDisX < (0.5 + 0.25)) && (tempDisY < (0.075 + 0.0025)) && (tempDisZ < (0.5 +  0.005)))
				{
					/*cout<< "COllision Aircraft !!!"<< endl;
					cout<< "MissileX " << m_pWorld->Missiles()[i]->getX()<< endl;
					cout<< "AircraftX " << this->x << endl;
					cout<< "tempDisX: " << tempDisX<< endl;*/

					this->setFired(true);
					m_pWorld->Missiles()[i]->setTouch(true);
					m_pWorld->m_iAircraftDestroy++;
				}
				
				

			}
			
			
			

		}
	}
	
}