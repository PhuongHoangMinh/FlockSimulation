#ifndef TURRET_H
#define TURRET_H


#include <vector>
#include "Mesh.h"
#include "GameWorld.h"
#include "Vector3D.h"
#include "AABB.h"
#include "Bitmap.h"
#include <gl/glut.h>
#include <gl/gl.h>


//class Missile;
class Vector3D;
class Mesh;
class GameWorld;
struct AABB;
class Bitmap;

class Turret
{
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;

	//Turret barrel
	Mesh m_pMesh;
	//Turret Base
	Mesh m_pMeshBase;

	GameWorld *m_pWorld;

	GLuint	m_iID; // id from genList

	GLuint  m_iIDBase;
	GLuint	m_iIDBarrel;

	GLuint m_iIDBaseNoText;
	GLuint m_iIDBarrelNoText;

	float	m_fHorizontalAngle;
	float   m_fVerticalAngle;
	


	int  m_textureID;

	
public:
	//Turret():x(0.0f), y(0.0f), z(0.0f)
	//{}

	//Turret(GLfloat valx, GLfloat valy, GLfloat valz): x(valx),y(valy), z(valz)
	//{
	//
	//}

	//Turret(GLfloat valx, GLfloat valy,GLfloat valz ,const Mesh valMesh): x(valx), y(valy), z(valz), m_pMesh(valMesh)
	//{

	//}
	
	Turret(GLfloat valx, 
		   GLfloat valy, 
		   GLfloat valz, 
		   const Mesh meshBarrel, 
		   const Mesh meshBase, 
		   GameWorld* world)
	{
		m_pWorld = world;
		x		 = valx;
		y		 = valy;
		z		 = valz;
		m_pMesh  = meshBarrel;
		m_pMeshBase = meshBase;
		
		m_fHorizontalAngle = 30.0f;
		m_fVerticalAngle   = 30.0f;

		/*m_iID = glGenLists(1);
		glNewList(m_iID, GL_COMPILE);
		this->Render();
		glEndList();*/

		
		
		/*generateIDBase();
		generateIDBarrel();
		
		generateIDBaseNoText();
		generateIDBarrelNoText();*/
		
		
		
	}

	void  generateIDBase();
	void  generateIDBarrel();

	void  generateIDBaseNoText();
	void  generateIDBarrelNoText();

	GLfloat		getX()const {return x;}
	void		setX(GLfloat val) {x = val;}

	GLfloat		getY()const {return y;}
	void		setY(GLfloat val){ y = val;}
	
	GLfloat		getZ()const{return z;}
	void		setZ(GLfloat val){ z = val;}

	Mesh		getMesh()const {return m_pMesh;}
	void		setMesh(const Mesh valMesh) {m_pMesh = valMesh;}

	GLuint	getID()const{ return m_iID;}

	//ID 
	int		getIDBase()const{return m_iIDBase;}
	int		getIDBarrel()const{return m_iIDBarrel;}
	//ID No Text
	int		getIDBaseNoText()const{return m_iIDBaseNoText;}
	int		getIDBarrelNoText()const{return m_iIDBarrelNoText;}

	float	getHorizontalAngle()const{ return m_fHorizontalAngle;}
	float   getVerticalAngle()const{return m_fVerticalAngle;}

	void	setHorizontalAngle(float value) { m_fHorizontalAngle = value;}
	void	setVerticalAngle(float value){ m_fVerticalAngle = value;}

	//Update position of Turret based on Keyboard
	void Update();

	//Draw Object based on m_pMesh - Mesh object
	void Render();

};




#endif