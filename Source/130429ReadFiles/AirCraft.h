#ifndef AIRCRAFT1_H
#define AIRCRAFT1_H


#include <vector>
#include "Mesh.h"
#include "GameWorld.h"
#include "AABB.h"
#include <gl/glut.h>
#include <gl/gl.h>


class Mesh;
class GameWorld;
struct AABB;


class Aircraft
{
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	
	Mesh	m_pMesh;

	bool	m_bFired;
	
	GameWorld* m_pWorld;

	GLuint	m_iID; // id from genList

	GLuint  m_iAircraft1ID;
	GLuint  m_iAircraft1IDNoText;

	GLuint	m_iAircraft2ID;
	GLuint  m_iAircraft2IDNoText;

	int		m_itype;

	AABB*	m_Bounding;
public:
	

	Aircraft(float valx, 
			 float valy, 
			 float valz, 
			 Mesh mesh, 
			 GameWorld* world): m_pWorld(world), m_pMesh(mesh), x(valx), y(valy), z(valz)
	{
		setFired(false);
		setType(1);
		
		/*m_iID = glGenLists(1);
		glNewList(m_iID, GL_COMPILE);
		this->Render();
		glEndList();*/

		//generateID();
	}

	Aircraft(float valx, 
		float valy, 
		float valz, 
		Mesh mesh, 
		GameWorld* world,
		int	type):  m_pMesh(mesh), x(valx), y(valy), z(valz), m_itype(type)
	{
		setFired(false);
		m_pWorld = world;
		//generateID();

		/*m_Bounding = new AABB();
		m_Bounding->centerP.x = this->x;
		m_Bounding->centerP.y = this->y;
		m_Bounding->centerP.z = this->z;


		if(m_itype == 1)
		{
		m_Bounding.r.x = 1;
		m_Bounding.r.y = 0.16;
		m_Bounding.r.z = 0.85;
		}
		else 
		{
		m_Bounding.r.x = 0.5;
		m_Bounding.r.y = 0.075;
		m_Bounding.r.z = 0.5;
		}*/
		


			
		

		Vector3D posB(this->x, this->y, this->z);
		Vector3D radius(1, 0.16, 0.85);

		if(m_itype == 2)
		{
			radius.x = 0.5;
			radius.y = 0.075;
			radius.z = 0.5;
		}

		m_Bounding = new AABB(posB, radius);

	}

	void generateID()
	{
	/*	m_iID = glGenLists(1);
		glNewList(m_iID, GL_COMPILE);
		this->Render();
		glEndList();

		return m_iID;*/

		if(m_itype == 1)
		{
			m_iAircraft1ID  = glGenLists(1);
			glNewList(m_iAircraft1ID , GL_COMPILE);
			this->Render();
			glEndList();

		}
		else
		{
			m_iAircraft2ID  = glGenLists(1);
			glNewList(m_iAircraft2ID , GL_COMPILE);
			this->Render();
			glEndList();

		}
		
	}


	void generateIDNoText()
	{
		if(m_itype == 1)
		{
			m_iAircraft1IDNoText = glGenLists(1);
			glNewList(m_iAircraft1IDNoText, GL_COMPILE);
			this->RenderNoText();
			glEndList();
		}
		else
		{	
			m_iAircraft2IDNoText = glGenLists(1);
			glNewList(m_iAircraft2IDNoText, GL_COMPILE);
			this->RenderNoText();
			glEndList();
		}
		
	}


	int  getAircraft1ID()const {return m_iAircraft1ID;}
	int  getAircraft1NoTextID()const {return m_iAircraft1IDNoText;}

	int  getAircraft2ID()const {return m_iAircraft2ID;}
	int  getAircraft2NoTextID()const {return m_iAircraft2IDNoText;}



	GLfloat getX()const {return x;}
	GLfloat getY()const {return y;}
	GLfloat getZ()const {return z;}
	bool	isFired()const {return m_bFired;}
	GLuint	getID()const{ return m_iID;}
	int		getType()const{return m_itype;}
	AABB*	getAABB()const{return m_Bounding;}
	
	void setAABB(AABB* val) {m_Bounding = val;}
	void setType(int val){ m_itype = val;}
	void setFired(bool val) {m_bFired = val;}
	void setX(GLfloat val) {x = val;}
	void setY(GLfloat val) {y = val;}
	void setZ(GLfloat val) {z = val;}

	Mesh		getMesh()const {return m_pMesh;}
	void		setMesh(const Mesh valMesh) {m_pMesh = valMesh;}
	
	void Update();

	void Render();

	void RenderNoText();

};



#endif