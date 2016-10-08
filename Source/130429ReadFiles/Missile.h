#ifndef MISSILE_H
#define MISSILE_H

#include "Vectors.h"
#include <vector>
#include "Mesh.h"
#include "Turret.h"
#include "GameWorld.h"
#include "AABB.h"
#include <math.h>
#include <gl/glut.h>
#include <gl/gl.h>


class Turret;
class Mesh;
class GameWorld;
class AABB;

class Missile
{
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	
	Mesh	m_pMesh;

	GameWorld *m_pWorld;

	bool	m_bTouch; // if missiles collide with aircraf/spaceship/tank OR goes beyond boundary of cube box, it will be disappear
	
	GLuint	m_iID;// id from glGenList();

	float   m_V0; //starting velocity
	float   transformX;//starting X in new plane

	float   startingAlpha;
	float   startingBeta;

	AABB*	m_Bounding;

	int		type;

	Vector3	m_velocity;
public:
	
	GLfloat getX()const {return x;}
	GLfloat getY()const {return y;}
	GLfloat getZ()const {return z;}
	bool	isTouch()const {return m_bTouch;}
	GLuint	getID()const{ return m_iID;}
	AABB*	getAABB()const{return m_Bounding;}
	int		getType()const{return type;}
	Vector3 getVelocityVec()const{return m_velocity;}

	void setAABB(AABB* val) {m_Bounding = val;}
	void setTouch(bool val){
		m_bTouch = val;
		setX(-11.0f);
		setY(-1.0f);
		setZ(-11.0f);
	}
	void setX(GLfloat val) {x = val;}
	void setY(GLfloat val) {y = val;}
	void setZ(GLfloat val) {z = val;}

	Mesh		getMesh()const {return m_pMesh;}
	void		setMesh(const Mesh valMesh) {m_pMesh = valMesh;}
	
	/*Missile():x(0.0f), y(0.0f), z(0.0f)
	{
		setTouch(false);
	}
	Missile(float valx, float valy, float valz): x(valx), y(valy), z(valz)
	{
		setTouch(false);
	}
	Missile(float valx, float valy, float valz, Mesh mesh): x(valx), y(valy), z(valz), m_pMesh(mesh)
	{
		setTouch(false);
	}*/
	
	Missile(float valx, 
			float valy, 
			float valz, 
			Mesh mesh, 
			GameWorld* world);

	Missile(float valx,
			float valy,
			float valz,
			Mesh  mesh,
			GameWorld* world,
			Vector3 velocity);
	

	void Update();

	void Render();
};

#endif