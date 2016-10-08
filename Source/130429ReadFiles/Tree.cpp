#include "Tree.h"

void Tree::Render()
{
	glDisable(GL_TEXTURE_2D);

	//for(int a = 0; a< )

	for(int a = 0; a< m_pMesh.m_Surfaces.size(); a++)
	{
	
		glBegin(GL_POLYGON);

		for(int b = 0; b < m_pMesh.m_Surfaces[a]->m_Vertexs->size(); b++)
		{
			
			//Normals
			int idxN = m_pMesh.m_Surfaces[a]->m_Vertexs->at(b).idx3 - 1;
			GLfloat nX = m_pMesh.m_Normals[idxN].x;
			GLfloat nY = m_pMesh.m_Normals[idxN].y;
			GLfloat nZ = m_pMesh.m_Normals[idxN].z;
			glNormal3f(nX, nY, nZ);


			//Texture
			

			//Vertex
			int idx = m_pMesh.m_Surfaces[a]->m_Vertexs->at(b).idx1 - 1;
			GLfloat valx = m_pMesh.m_Vertices[idx].x*scale;
			GLfloat valy = m_pMesh.m_Vertices[idx].y*scale;
			GLfloat valz = m_pMesh.m_Vertices[idx].z*scale;

			glVertex3f(valx, valy, valz);
		
		}

	
		glEnd();
	}

}


