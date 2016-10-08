#ifndef TREE_H
#define TREE_H

#include <vector>
#include "Mesh.h"
#include "GameWorld.h"
#include "AABB.h"
#include <gl/glut.h>
#include <gl/gl.h>


class GameWorld;
class AABB;

class Tree
{
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;

	Mesh	m_pMesh;

	bool	m_bFired;
	

	GameWorld* m_pWorld;

	GLuint	m_iID; // ID from glGenList()
	//GLuint  m_iIDNoText;
	
	GLfloat scale;

	AABB*	m_Bounding;
public:
	

	Tree(float valx, 
			float valy, 
			float valz, 
			Mesh mesh, 
			GameWorld* world, 
			float fscale): m_pWorld(world), m_pMesh(mesh), x(valx), y(valy), z(valz), scale(fscale)
	{
		setFired(false);

		m_iID = glGenLists(1);
		glNewList(m_iID, GL_COMPILE);
		this->Render();
		glEndList();

		/*m_iIDNoText = glGenLists(1);
		glNewList(m_iIDNoText, GL_COMPILE);
		this->RenderNoText();
		glEndList();*/


		Vector3D posB(this->x, this->y, this->z);
		Vector3D radius(0.4, 0.125, 0.25);

		m_Bounding = new AABB(posB, radius);
	}



	Mesh		getMesh()const {return m_pMesh;}
	void		setMesh(const Mesh valMesh) {m_pMesh = valMesh;}

	GLfloat getX()const {return x;}
	GLfloat getY()const {return y;}
	GLfloat getZ()const {return z;}
	bool	isFired()const {return m_bFired;}
	GLuint	getID()const{ return m_iID;}
	AABB*	getAABB()const{return m_Bounding;}

	//GLuint  getIDNoText()const{return  m_iIDNoText;}

	void setAABB(AABB* val) {m_Bounding = val;}
	void setFired(bool val) {m_bFired = val;}
	void setX(GLfloat val) {x = val;}
	void setY(GLfloat val) {y = val;}
	void setZ(GLfloat val) {z = val;}
	
	//void Update();

	void Render();


};

#endif