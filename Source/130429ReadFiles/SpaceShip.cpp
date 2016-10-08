#include "SpaceShip.h"

void SpaceShip::RenderNOTexture()
{
	glDisable(GL_TEXTURE_2D);
	//glRotatef(-180, 0.0f, 1.0f, 0.0f);
	//Loop over polygonal meshes
	for(int a = 0; a< m_pMesh.m_Surfaces.size() ; a++)
	{
		/*glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	
		glBindTexture(GL_TEXTURE_2D, m_iTextID);*/

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
			GLfloat texX = m_pMesh.m_Textures[idxT].x;
			GLfloat texY = m_pMesh.m_Textures[idxT].y;
			glTexCoord2f(texX, texY);


			//Vertex
			int idx = m_pMesh.m_Surfaces[a]->m_Vertexs->at(b).idx1 - 1;

			float valx = m_pMesh.m_Vertices[idx].x; //*0.025
			float valy = m_pMesh.m_Vertices[idx].y; //*0.025
			float valz = m_pMesh.m_Vertices[idx].z; //*0.025

			glVertex3f(valx, valy, valz);
		}
		glEnd();
	}

}

void SpaceShip::Render()
{
	//float size = 3;
	//glLineWidth(2);
	//glBegin(GL_LINES);
	//	glColor3f(1, 0, 0);
	//	glVertex3f(0, 0, 0);
	//	glVertex3f(size, 0, 0);

	//	glColor3f(1, 1, 1);
	//	glVertex3f(0, 1, 0);
	//	glVertex3f(0, size, 0);

	//	glColor3f(0, 1, 1);
	//	glVertex3f(0, 0, 0);
	//	glVertex3f(0, 0, size);
	//glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_iTextID);

	//glRotatef(-180, 0.0f, 1.0f, 0.0f);
	//Loop over polygonal meshes
	for(int a = 0; a< m_pMesh.m_Surfaces.size() ; a++)
	{
		/*glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	
		glBindTexture(GL_TEXTURE_2D, m_iTextID);*/

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
			GLfloat texX = m_pMesh.m_Textures[idxT].x;
			GLfloat texY = m_pMesh.m_Textures[idxT].y;
			glTexCoord2f(texX, texY);


			//Vertex
			int idx = m_pMesh.m_Surfaces[a]->m_Vertexs->at(b).idx1 - 1;

			float valx = m_pMesh.m_Vertices[idx].x; //*0.025
			float valy = m_pMesh.m_Vertices[idx].y; //*0.025
			float valz = m_pMesh.m_Vertices[idx].z; //*0.025

			glVertex3f(valx, valy, valz);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_TEXTURE_2D);
	

}

void SpaceShip::Update()
{
	if(this->isFired())
	{
		//No Update
	}
	else
	{
		//move along Z-direction
		/*float temp = getZ() - 0.005;
		this->setZ(temp);*/



		if(this->x > 40.0)
		{
			//m_pVehicle->SetX(m_pVehicle->Pos().x - 0.2);
			m_pVehicle->SetX(-40.0);

		}
		if(this->x < -40.0)
		{
			//m_pVehicle->SetX(m_pVehicle->Pos().x + 0.2);
			m_pVehicle->SetX(40.0);
		}

		if(this->z > 40.0)
		{
			//m_pVehicle->SetZ(m_pVehicle->Pos().z - 0.2);
			m_pVehicle->SetZ(-40.0);
		}
		if(this->z < -40.0)
		{
			//m_pVehicle->SetZ(m_pVehicle->Pos().z + 0.2);
			m_pVehicle->SetZ(40.0);
		}
		if(this->y > 40.0)
		{
			//m_pVehicle->SetY(m_pVehicle->Pos().y - 0.2);
			m_pVehicle->SetY(-40.0);
		}
		if(this->y < -40.0)
		{
			//m_pVehicle->SetY(m_pVehicle->Pos().y + 0.2);
			m_pVehicle->SetY(40.0);
		}

		//CROSS END-LINE --> minus 1 point
		//if(this->z < 0.0f)
		//{
		//	int tempCross = m_pWorld->getNoCross();

		//	m_pWorld->setNoCross(++tempCross);
		//	this->setFired(true);
		//	//cout<< "No Cross" << m_pWorld->m_iNoCross<< endl;
		//}

		//check it collision detection with missiles
		int loop = m_pWorld->Missiles().size();
		int testCollision = 0;
		for(int i = 0; i< loop; i++)
		{
			//AABB Collision detection
			//if collide
			//this->setFired(true);
			//m_pWorld->Missiles()[i]->setTouch(true);

			//int test = TestAABBCollision(this->getAABB(), m_pWorld->Missiles()[i]->getAABB());
			
			//BOUNDING BOX test
			//testCollision = m_Bounding->TestAABBCollision(*m_pWorld->Missiles()[i]->getAABB());
			//m_Bounding->TestAABBCollision(*m_pWorld->Missiles()[i]->getAABB());
			////cout << " "<< testCollision <<endl;
			//if(testCollision)
			//{
			//	//cout<< " Collision: "<< test << endl;
			//	this->setFired(true);
			//	m_pWorld->Missiles()[i]->setTouch(true);
			//	testCollision = 0;
			//}	

			float tempDisX = abs(this->x - m_pWorld->Missiles()[i]->getX());
			float tempDisY = abs(this->y - m_pWorld->Missiles()[i]->getY());
			float tempDisZ = abs(this->z - m_pWorld->Missiles()[i]->getZ());

			if((tempDisX < (0.25 + 0.25)) && (tempDisY < (0.005 + 0.0025)) && (tempDisZ < (0.2 +  0.005)))
			{
				/*cout<< "COllision Aircraft !!!"<< endl;
				cout<< "MissileX " << m_pWorld->Missiles()[i]->getX()<< endl;
				cout<< "AircraftX " << this->x << endl;
				cout<< "tempDisX: " << tempDisX<< endl;*/
				
				this->setFired(true);
				m_pWorld->Missiles()[i]->setTouch(true);
				m_pWorld->m_iSpaceShipDestroy++;
			}
		}
	
		//this->getVehicle()->Steering()->TurnOffAll();

		/*m_pVehicle->Update();
		this->x = m_pVehicle->Pos().x;
		this->y = m_pVehicle->Pos().y;
		this->z = m_pVehicle->Pos().z;*/	

		//DUOI BAT
		int specialIndex = 0;
		int    indx = -1;
		double closestDistance = this->ClosestDistance();
		

		if(m_pWorld->isSpecialMode() == 2)
		{
			//this->getVehicle()->Steering()->TurnOffAll();
			//indx = 2;

			for(int a = 0 ; a< m_pWorld->Points().size(); a++)
			{
				if(!m_pWorld->Points()[a]->isOccupied())
				{
					double d = Vec3DDistance(this->getVehicle()->Pos(), m_pWorld->Points()[a]->Pos());

					if(d < closestDistance)
					{
						closestDistance = d;
						indx = a;
					}
				}
			}

			if(indx != -1)
			{
				this->setSpecialIndex(indx);
				this->getVehicle()->Steering()->SetTarget(m_pWorld->Points()[indx]->Pos());

				
				this->getVehicle()->Steering()->FollowPathOff();
				//this->getVehicle()->Steering()->TurnOffAll();
				this->getVehicle()->Steering()->SeekOn();
			}
			else
			{
				this->getVehicle()->Steering()->TurnOffAll();
				//this->getVehicle()->SetVelocity(Vector3D(0,0,0));
				this->getVehicle()->Steering()->FollowPathOn();
				//this->getVehicle()->Steering()->WanderOn();
			}

			bool seekTarget = this->getVehicle()->Steering()->isSeekOn();
			if(seekTarget)
			{
				Vector3D Target = this->getVehicle()->Steering()->Target();
				Vector3D itsPos = this->getVehicle()->Pos();
				Vector3D toTarget = itsPos - Target;

				if(toTarget.Length() < 0.6)
				{
					this->setClosestDistance(toTarget.Length());
					m_pWorld->Points()[this->SpecialIndex()]->setOccupied(true);
					
					stop = true;
					this->getVehicle()->Steering()->TurnOffAll();
					this->getVehicle()->SetVelocity(Vector3D(0,0,0));
				
				}
				else
				{
						
					
				}
			}
			
			if(m_pWorld->NoPointOccupied() == m_pWorld->Points().size())
			{
				//std::cout<< "FULL occupied" <<endl;

				//wait for 5 seconds
				m_iWaitCount++;
				if(m_iWaitCount == 210)
				{
					std::cout<< "Finish 5 second"<<endl;
					m_iWaitCount = 0;
					
					//after 5 seconds
					//1. reset Points's occupied to FALSE
					//2. Object turnAllOff --> FollowPathOn
					//3. SetCurWayPoint based on position
					//4. m_pWorld->setSpecialMode() != 2; -- to wait for next time
					
					
					for(int i = 0; i< m_pWorld->SpaceShips().size(); i++)
					{
						m_pWorld->SpaceShips()[i]->getVehicle()->Steering()->FollowPathOn();
						m_pWorld->SpaceShips()[i]->getVehicle()->Steering()->SetNewCurWayPoint();
						m_pWorld->SpaceShips()[i]->setSTOP(false);
						m_pWorld->SpaceShips()[i]->setClosestDistance(100);
						m_pWorld->SpaceShips()[i]->setWaitCount(0);
					}
					for(int i = 0; i< m_pWorld->Points().size(); i++)
					{
						m_pWorld->Points()[i]->setOccupied(false);
					}
					m_pWorld->setSpecialMode(0);
					//stop = false;
				}


			}
		
		}

		if(stop)
		{
		
		}
		else
		{
			m_pVehicle->Update();
			this->x = m_pVehicle->Pos().x;
			this->y = m_pVehicle->Pos().y;
			this->z = m_pVehicle->Pos().z;	
		}
		////END DUoi BAT
		

		//if(indx != 2)
		//{
		//	m_pVehicle->Update();
		//	this->x = m_pVehicle->Pos().x;
		//	this->y = m_pVehicle->Pos().y;
		//	this->z = m_pVehicle->Pos().z;		
		//	//this->getVehicle()->Steering()->TurnOffAll();
		//	
		//}
		//else
		//{
		//
		//}


	}
}