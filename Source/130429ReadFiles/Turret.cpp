#include "Turret.h"

void	Turret::generateIDBarrelNoText()
{
	m_iIDBarrelNoText = glGenLists(1);
	glNewList(m_iIDBarrelNoText, GL_COMPILE);

	/*glEnable(GL_TEXTURE_2D);*/
	for(int i = 0; i< m_pMesh.m_Surfaces.size(); i++)
	{
		int numVertex = m_pMesh.m_Surfaces[i]->m_Vertexs->size();

		glBegin(GL_POLYGON);
		for(int b = 0; b < m_pMesh.m_Surfaces[i]->m_Vertexs->size(); b++)
		{
			

			//Normals
			int idxN = m_pMesh.m_Surfaces[i]->m_Vertexs->at(b).idx3 - 1;
			GLfloat nX = m_pMesh.m_Normals[idxN].x;
			GLfloat nY = m_pMesh.m_Normals[idxN].y;
			GLfloat nZ = m_pMesh.m_Normals[idxN].z;
			glNormal3f(nX, nY, nZ);

			//Texture
			int idxT = m_pMesh.m_Surfaces[i]->m_Vertexs->at(b).idx2 - 1;
			GLfloat texX = m_pMesh.m_Textures[idxT].x;
			GLfloat texY = m_pMesh.m_Textures[idxT].y;
			glTexCoord2f(texX, texY);

			//Vertex
			int index	 = m_pMesh.m_Surfaces[i]->m_Vertexs->at(b).idx1 - 1;
			GLfloat xval = m_pMesh.m_Vertices[index].x*0.001;
			GLfloat yval = m_pMesh.m_Vertices[index].y*0.001;
			GLfloat zval = m_pMesh.m_Vertices[index].z*0.001; //*0.001

			glVertex3f(xval, yval, zval);

		}
		glEnd();
	}

	/*glDisable(GL_TEXTURE_2D);*/

	glEndList();

}


void	Turret::generateIDBarrel()
{
	FILE *textureFile1;
	textureFile1 = fopen("earth.bmp", "rb");

	if((!textureFile1))
	{
		cout<< "FILE NOT FOUND...."<< endl;
	}
	else
	{	
		Bitmap  *bitmapFile = new Bitmap(textureFile1);
		m_textureID = bitmapFile->Bitmap2TextureName();
		//cout<< "TExture ID: "<< m_textureID<< endl;

	}

	m_iIDBarrel = glGenLists(1);
	glNewList(m_iIDBarrel, GL_COMPILE);

	glEnable(GL_TEXTURE_2D);
	for(int i = 0; i< m_pMesh.m_Surfaces.size(); i++)
	{
		int numVertex = m_pMesh.m_Surfaces[i]->m_Vertexs->size();

		glBegin(GL_POLYGON);
		for(int b = 0; b < m_pMesh.m_Surfaces[i]->m_Vertexs->size(); b++)
		{
			

			//Normals
			int idxN = m_pMesh.m_Surfaces[i]->m_Vertexs->at(b).idx3 - 1;
			GLfloat nX = m_pMesh.m_Normals[idxN].x;
			GLfloat nY = m_pMesh.m_Normals[idxN].y;
			GLfloat nZ = m_pMesh.m_Normals[idxN].z;
			glNormal3f(nX, nY, nZ);

			//Texture
			int idxT = m_pMesh.m_Surfaces[i]->m_Vertexs->at(b).idx2 - 1;
			GLfloat texX = m_pMesh.m_Textures[idxT].x;
			GLfloat texY = m_pMesh.m_Textures[idxT].y;
			glTexCoord2f(texX, texY);

			//Vertex
			int index	 = m_pMesh.m_Surfaces[i]->m_Vertexs->at(b).idx1 - 1;
			GLfloat xval = m_pMesh.m_Vertices[index].x*0.001;
			GLfloat yval = m_pMesh.m_Vertices[index].y*0.001;
			GLfloat zval = m_pMesh.m_Vertices[index].z*0.001; //*0.001

			glVertex3f(xval, yval, zval);

		}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glEndList();
	

}


void	Turret::generateIDBaseNoText()
{
	m_iIDBaseNoText = glGenLists(1);

	
	glNewList(m_iIDBaseNoText, GL_COMPILE);

	//glEnable(GL_TEXTURE_2D);
	//	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	
	//glBindTexture(GL_TEXTURE_2D, m_textureID);	
	
	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	for(int a = 0; a< m_pMeshBase.m_Surfaces.size(); a++)
	{
		
		
		glBegin(GL_POLYGON);
		for(int b = 0; b< m_pMeshBase.m_Surfaces[a]->m_Vertexs->size(); b++)
		{
			

			////Normals
			int idxN = m_pMeshBase.m_Surfaces[a]->m_Vertexs->at(b).idx3 - 1;
			GLfloat nX = m_pMeshBase.m_Normals[idxN].x;
			GLfloat nY = m_pMeshBase.m_Normals[idxN].y;
			GLfloat nZ = m_pMeshBase.m_Normals[idxN].z;
			glNormal3f(nX, nY, nZ);

			//Texture
			int idxT = m_pMeshBase.m_Surfaces[a]->m_Vertexs->at(b).idx2 - 1;
			GLfloat texX = m_pMeshBase.m_Textures[idxT].x;
			GLfloat texY = m_pMeshBase.m_Textures[idxT].y;
			glTexCoord2f(texX, texY);
			
			//Vertex
			int index = m_pMeshBase.m_Surfaces[a]->m_Vertexs->at(b).idx1 - 1;
			GLfloat xval = m_pMeshBase.m_Vertices[index].x*0.001;
			GLfloat yval = m_pMeshBase.m_Vertices[index].y*0.001;
			GLfloat zval = m_pMeshBase.m_Vertices[index].z*0.001;

			glVertex3f(xval, yval, zval);
		}	
		glEnd();

		
	}

	//glDisable(GL_TEXTURE_2D);

	glEndList();
	

}


void	Turret::generateIDBase()
{

	FILE *textureFile1;
	textureFile1 = fopen("earth.bmp", "rb");

	if((!textureFile1))
	{
		cout<< "FILE NOT FOUND...."<< endl;
	}
	else
	{	
		Bitmap  *bitmapFile = new Bitmap(textureFile1);
		m_textureID = bitmapFile->Bitmap2TextureName();
		//cout<< "TExture ID: "<< m_textureID<< endl;

	}

	m_iIDBase = glGenLists(1);

	
	glNewList(m_iIDBase, GL_COMPILE);

	//glEnable(GL_TEXTURE_2D);
	//	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	
	//glBindTexture(GL_TEXTURE_2D, m_textureID);	
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	for(int a = 0; a< m_pMeshBase.m_Surfaces.size(); a++)
	{
		
		
		glBegin(GL_POLYGON);
		for(int b = 0; b< m_pMeshBase.m_Surfaces[a]->m_Vertexs->size(); b++)
		{
			

			////Normals
			int idxN = m_pMeshBase.m_Surfaces[a]->m_Vertexs->at(b).idx3 - 1;
			GLfloat nX = m_pMeshBase.m_Normals[idxN].x;
			GLfloat nY = m_pMeshBase.m_Normals[idxN].y;
			GLfloat nZ = m_pMeshBase.m_Normals[idxN].z;
			glNormal3f(nX, nY, nZ);

			//Texture
			int idxT = m_pMeshBase.m_Surfaces[a]->m_Vertexs->at(b).idx2 - 1;
			GLfloat texX = m_pMeshBase.m_Textures[idxT].x;
			GLfloat texY = m_pMeshBase.m_Textures[idxT].y;
			glTexCoord2f(texX, texY);
			
			//Vertex
			int index = m_pMeshBase.m_Surfaces[a]->m_Vertexs->at(b).idx1 - 1;
			GLfloat xval = m_pMeshBase.m_Vertices[index].x*0.001;
			GLfloat yval = m_pMeshBase.m_Vertices[index].y*0.001;
			GLfloat zval = m_pMeshBase.m_Vertices[index].z*0.001;

			glVertex3f(xval, yval, zval);
		}	
		glEnd();

		
	}

	glDisable(GL_TEXTURE_2D);

	glEndList();

}



void Turret::Render()
{

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.5f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(m_fHorizontalAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-2.0f, 0.0f , 0.8f);
	//cout<< "Horizontal Angle: "<< m_fHorizontalAngle <<endl;
	//glRotatef(60, 0.0f, 1.0f, 0.0f);
	//Drawing Turret Base
	if(m_pWorld->m_bRenderMode)
	{
		glCallList(m_iIDBase);
	}
	else
	{
		glCallList(m_iIDBaseNoText);
	}
	glPopMatrix();

	//Drawing Turret barrel
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.5f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(m_fHorizontalAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(-m_fVerticalAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-2.0f, 0.0f , 0.8f);
	//Loop over polygonal meshes
	if(m_pWorld->m_bRenderMode)
	{
		glCallList(m_iIDBarrel);
	}
	else
	{
		glCallList(m_iIDBarrelNoText);
	}

	glPopMatrix();

	
}

void Turret::Update()
{
	//is pressed fired key m_pWorld->fired()
	//if(m_pWorld->fired())
	//{ Missile *newMissile = new Missile(posOfTurret.x, PosOfTurret.y, posOfTurret.z,this->m_pWorld);
    // m_pWorld->addMissile(newMissile);
    //}

	//Rotate around  y-axis horizontally
	if(m_pWorld->isPressedLeft())
	{
		m_fHorizontalAngle += 1.0;
		m_pWorld->setPressedLeft(false);
	}
	if(m_pWorld->isPressedRight())
	{
		m_fHorizontalAngle -= 1.0;
		m_pWorld->setPressedRight(false);
	}

	//Move Turret barrel vertically
	if(m_pWorld->isPressedDown())
	{
		if(m_fVerticalAngle > 0)
		{
			m_fVerticalAngle -= 1.0;
			m_pWorld->setPressedDown(false);
		}
	}
	if(m_pWorld->isPressedUp())
	{
		if(m_fVerticalAngle < 90)
		{
			m_fVerticalAngle += 1.0;
			m_pWorld->setPressedUp(false);
		}
	}
}