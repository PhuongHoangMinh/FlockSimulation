#ifndef SPACESHIP_H
#define SPACESHIP_H


#include <vector>
#include "Mesh.h"
#include "GameWorld.h"
#include "Vehicle.h"
#include "AABB.h"
#include "Bitmap.h"
#include <gl/glut.h>
#include <gl/gl.h>


class GameWorld;
struct AABB;
class Bitmap;
class Vehicle;

class SpaceShip
{
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	
	Mesh	m_pMesh;
	
	bool	m_bFired;

	GameWorld* m_pWorld;

	GLuint	m_iID; // id from GlGenList();

	AABB*	m_Bounding;

	int  m_iTextID;
	
	int  m_iIDNoText;

	Vehicle* m_pVehicle;

	int  m_iSpecialIndx;

	double m_dClosestDistance;

	bool stop;

	int  m_iWaitCount;

public:
	/*SpaceShip(): x(0.0f), y(0.0f), z(0.0f)
	{
		setFired(false);
	}

	SpaceShip(float valx, float valy, float valz): x(valx), y(valy), z(valz)
	{
		setFired(false);
	}

	SpaceShip(float valx, float valy, float valz, Mesh mesh): x(valx), y(valy), z(valz), m_pMesh(mesh)
	{
		setFired(false);
	}*/

	SpaceShip(float valx, 
			 float valy, 
			 float valz, 
			 Mesh mesh, 
			 GameWorld* world): m_pWorld(world), m_pMesh(mesh), x(valx), y(valy), z(valz)
	{
		setFired(false);
		
		/*generateID();

		generateIDNoText();*/
		
		//glDisable(GL_TEXTURE_2D);

		/*m_Bounding = new AABB();
		m_Bounding->centerP.x = this->x;
		m_Bounding->centerP.y = this->y;
		m_Bounding->centerP.z = this->z;

		m_Bounding.r.x = 0.25;
		m_Bounding.r.y = 0.005;
		m_Bounding.r.z = 0.2;*/
		
		Vector3D	StartPos(x, y, z);
		Vector3D    StartVelocity;
		StartVelocity.Zero();
		

		
		m_pVehicle = new Vehicle(m_pWorld, StartPos, 1.0, StartVelocity, 1.0, 50.0, 50.0, 0, 1.0 );
		//m_pVehicle->Steering()->SeekOn();
		//m_pVehicle->Steering()->ArriveOn();
		

		Vector3D posB(this->x, this->y, this->z);
		Vector3D radius(0.25, 0.005, 0.2);

		m_Bounding = new AABB(posB, radius);

		m_dClosestDistance = 100.0;
		
		stop = false;

		m_iWaitCount = 0;
	}
	
	int		generateID()
	{
		//Bitmap file
		FILE *textureFile;
		textureFile	= fopen("spaceship.bmp", "rb");
		
		FILE *textureFile1;
		textureFile1 = fopen("earth.bmp", "rb");
		
		//this->x += 0.1;

		if((!textureFile) || (!textureFile1))
		{
			cout<< "FILE NOT FOUND...."<< endl;
		}
		else
		{	
			Bitmap  *bitmapFile = new Bitmap(textureFile);
			m_iTextID = bitmapFile->Bitmap2TextureName();
			cout<< "TExture ID: "<< m_iTextID;
		}


		m_iID = glGenLists(1);
		glNewList(m_iID, GL_COMPILE);
		this->Render();
		glEndList();
		
		return m_iID;
	}

	int		generateIDNoText()
	{
		m_iIDNoText = glGenLists(1);
		glNewList(m_iIDNoText, GL_COMPILE);
		this->RenderNOTexture();
		glEndList();

		return m_iIDNoText;
	}

	
	GLfloat getX()const {return x;}
	GLfloat getY()const {return y;}
	GLfloat getZ()const {return z;}
	bool	isFired()const {return m_bFired;}
	GLuint	getID()const{ return m_iID;}
	AABB*	getAABB()const{return m_Bounding;}

	GLuint  getIDNoTEXT()const{return m_iIDNoText;}

	void setAABB(AABB* val) {m_Bounding = val;}
	void setFired(bool val) {m_bFired = val;}
	void setX(GLfloat val) {x = val;}
	void setY(GLfloat val) {y = val;}
	void setZ(GLfloat val) {z = val;}

	void setSTOP(bool val){stop = val;}
	void setWaitCount(int val){ m_iWaitCount = val;};

	int  SpecialIndex()const{
		return m_iSpecialIndx;
	}
	void setSpecialIndex(int val) 
	{
		m_iSpecialIndx = val;
	}

	double ClosestDistance()const {return m_dClosestDistance;}
	void   setClosestDistance(double val){ m_dClosestDistance = val;}

	Mesh		getMesh()const {return m_pMesh;}
	void		setMesh(const Mesh valMesh) {m_pMesh = valMesh;}
	
	//Vehicle properties for drawing
	Vector3D	getHeading()const{return m_pVehicle->Heading();}
	Vehicle*	getVehicle()const{return m_pVehicle;}

	void		setAngleRotate(float val)	{ m_pVehicle->setRotateAngle(val);}
	void		setAxisRotate(Vector3D axis){ m_pVehicle->setRotateAxis(axis);}

	void Update();

	void Render();
	
	void RenderNOTexture();
};


#endif