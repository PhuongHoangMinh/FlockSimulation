#include "Missile.h"

Missile::Missile(float valx, 
			float valy, 
			float valz, 
			Mesh mesh, 
			GameWorld* world):m_pWorld(world), x(valx), y(valy), z(valz), m_pMesh(mesh)
	{
		setTouch(false);
		
		x = valx;
		y = valy;
		z = valz;

		startingAlpha = m_pWorld->Turrets()[0]->getHorizontalAngle();
		startingBeta  = m_pWorld->Turrets()[0]->getVerticalAngle();

		m_iID = glGenLists(1);
		glNewList(m_iID, GL_COMPILE);
		this->Render();
		glEndList();
		
		float PI = 3.14159265;
		m_V0 = 10;
		transformX = x/ sin(startingAlpha*PI/180);
		
		this->type = m_pWorld->m_iMissileType;

		//m_Bounding->centerP.x = this->x;
		//m_Bounding->centerP.y = this->y;
		//m_Bounding->centerP.z = this->z;

		//m_Bounding->r.x = 0.25;
		//m_Bounding->r.y = 0.0025;
		//m_Bounding->r.z = 0.005;

		Vector3D posB(this->x, this->y, this->z);
		Vector3D radius(0.25, 0.0025, 0.005);

		m_Bounding = new AABB(posB, radius);

		

	}

Missile::Missile(float valx, 
			float valy, 
			float valz, 
			Mesh mesh, 
			GameWorld* world, Vector3 velocity):m_pWorld(world), x(valx), y(valy), z(valz), m_pMesh(mesh),m_velocity(velocity)
	{
		setTouch(false);
		
		startingAlpha = m_pWorld->Turrets()[0]->getHorizontalAngle();
		startingBeta  = m_pWorld->Turrets()[0]->getVerticalAngle();

		m_iID = glGenLists(1);
		glNewList(m_iID, GL_COMPILE);
		this->Render();
		glEndList();
		
		m_V0 = 10;
		transformX = 0.0f;
		
		this->type = m_pWorld->m_iMissileType;

		//m_Bounding->centerP.x = this->x;
		//m_Bounding->centerP.y = this->y;
		//m_Bounding->centerP.z = this->z;

		//m_Bounding->r.x = 0.25;
		//m_Bounding->r.y = 0.0025;
		//m_Bounding->r.z = 0.005;

		Vector3D posB(this->x, this->y, this->z);
		Vector3D radius(0.25, 0.0025, 0.005);

		m_Bounding = new AABB(posB, radius);

		

	}


void Missile::Render()
{
	glPushMatrix();
		glRotatef(startingAlpha, 0.0f, 1.0f, 0.0f);
		glRotatef(-90, 0.0f ,1.0f, 0.0f);
		//
		//glRotatef();
	//glRotatef(-90.0f - startingAlpha, 0.0f, 1.0f, 0.0f);
	//glRotatef(, 0.0f, 1.0f, 0.0f);

		//float size = 3;
		//glLineWidth(2);
		//glBegin(GL_LINES);
		//glColor3f(1, 0, 0);
		//glVertex3f(0, 0, 0);
		//glVertex3f(size, 0, 0);

		//glColor3f(0, 1, 0);
		//glVertex3f(0, 0, 0);
		//glVertex3f(0, size, 0);

		//glColor3f(0, 0, 1);
		//glVertex3f(0, 0, 0);
		//glVertex3f(0, 0, size);
		//glEnd();	


		
		glBegin(GL_POLYGON);
		//Loop over polygonal meshes
		for(int a = 0; a< m_pMesh.m_Surfaces.size() ; a++)
		{
			for(int b = 0; b< m_pMesh.m_Surfaces[a]->m_Vertexs->size(); b++)
			{
				int idx = m_pMesh.m_Surfaces[a]->m_Vertexs->at(b).idx1 - 1;

				GLfloat valx = m_pMesh.m_Vertices[idx].x*0.05;
				GLfloat valy = m_pMesh.m_Vertices[idx].y*0.05;
				GLfloat valz = m_pMesh.m_Vertices[idx].z*0.05;

				glVertex3f(valx, valy, valz);
			}
		}
		glEnd();

		
	glPopMatrix();

	
}

void Missile::Update()
{
	if(this->isTouch())
	{
		// No Update
	}
	else
	{
		//update x,y, z
		//float temp = getZ() - 0.01;
		//this->setZ(temp);
		
		float PI = 3.14159265;
		float g = 9.81;
		float alpha = startingAlpha*PI/180;
		float beta  = startingBeta*PI/180;
		//UPDATE position------------------
		if(this->type  == 1)
		{
			

			transformX += this->m_V0*cos(beta)*0.008;

			this->x = transformX*sin(alpha);
			this->z = transformX*cos(alpha);

			float X2 = transformX*transformX;
			float V02= m_V0*m_V0;
			float cosBeta2 = cos(beta)*cos(beta);
			this->y = tan(beta)*transformX - g*X2/(2*V02*cosBeta2);
		}
		//END UPDATE Position--------------
		


		//UPDATE position------------------
		if(this->type == 2)
		{
			/*transformX += this->m_V0*cos(beta)*0.008;
			this->x = transformX*sin(alpha);
			this->z = transformX*cos(alpha);

			this->y += this->m_V0*sin(beta)*0.008; */

			transformX += this->m_V0*cos(beta)*0.008;

			this->x = transformX*sin(alpha);
			this->z = transformX*cos(alpha);

			/*float X2 = transformX*transformX;
			float V02= m_V0*m_V0;
			float cosBeta2 = cos(beta)*cos(beta);*/
			this->y = tan(beta)*transformX;
		}
		//---------------------------------

		this->m_velocity.x = this->m_V0*cos(beta)*sin(alpha);
		this->m_velocity.z = this->m_V0*cos(beta)*cos(alpha);
		this->m_velocity.y = this->m_V0*sin(beta) - g*0.008;




		//check if go beyond the boundary of cube box
		if(this->y < -0.1f)
		{
			this->setTouch(true);
		}

		if((this->x > 10.0f) || (this->x < -10.0f))
		{
			this->setTouch(true);
			
		}

		if((this->z > 10.0f ) || (this->z < -10.0f))
		{
			this->setTouch(true);
		}

		
	}
}