#include "GameWorld.h"




void GameWorld::ClearGameWorld()
{
	if(m_Tanks.size() > 0)
	{
		m_Tanks.clear();
	}
	if(m_Aircrafts.size() >0)
	{
		m_Aircrafts.clear();
	}

	if(m_SpaceShips.size() >0)
	{
		m_SpaceShips.clear();
	}
	if(m_Missiles.size() > 0)
	{
		this->m_Missiles.clear();
	}

	if(m_Turrets.size() >0 )
	{
		m_Turrets.clear();
	}
		//if(m_Vehilces.size() > 0)

	if(m_Points.size() > 0)
	{
		m_Points.clear();
	}

	if(m_Vehilces.size() > 0)
	{
		m_Vehilces.clear();
	}

	if(m_bFirtTime)
	{
		m_iAircraft1ID = 0;
		m_iAircraft1IDNoText = 0;
		m_iAircraft2ID = 0;
		m_iAircraft2IDNoText = 0;
		m_iSpaceshipID = 0;
		m_iSpaceshipIDNoText = 0;
		m_iTankID = 0;
		m_iTankIDNoText = 0;

		m_iTurretBaseID = 0;
		m_iTurretBaseIDNoText = 0;

		m_iTurretBarrelID = 0;
		m_iTurretBarrelNoTextID = 0;
		
	}
	
	
}

void GameWorld::CreateGameWorld()
{
	int NoTank = 1;
	int NoSpaceShip = 100;
	int NoAirCraft = 2;
	int NoTrees	   = 0;
	
	m_bPressedFired = false;
	m_bPressedLeft = false;
	m_bPressedRight = false;
	m_bPressedUp = false;
	m_bPressedDown = false;
	
	this->cameraTargetX = 0.0f;
	this->cameraTargetY = 0.0f;
	this->cameraTargetZ = 0.0f;
	
	//POINTs
	Vector3D pointPos0(-3,0,3);
	Point* newPoint0 = new Point(-3, 0, -3);
	Point* newPoint1 = new Point(0,0,-3);
	Point* newPoint2 = new Point(3,0,-3);
	Point* newPoint3 = new Point(3,0,0);
	Point* newPoint4 = new Point(3,0,3);
	Point* newPoint5 = new Point(0,0,3);
	Point* newPoint6 = new Point(-3,0,3);
	Point* newPoint7 = new Point(-3,0, 0);
	m_Points.push_back(newPoint0);
	m_Points.push_back(newPoint1);
	m_Points.push_back(newPoint2);
	m_Points.push_back(newPoint3);
	m_Points.push_back(newPoint4);
	m_Points.push_back(newPoint5);
	m_Points.push_back(newPoint6);
	m_Points.push_back(newPoint7);

	
	//CellSpacePartition
	//if(m_bFirtTime)
	//{
	//	m_pCellSpace = new CellSpacePartition<Vehicle*>(80.0, 80.0, 80.0, 10, 10, 10, 1000); //these paras can be written from a file
	//	
	//}

	//Create Tree
	Mesh tempMeshTree = meshTree2;
	float randTreeX = 1.0f;
	float randTreeY = 0.0f;
	float randTreeZ = 2.0f;
	int	  treeType  = 2;
	float scaleTree     = 0.05;
	for(int i = 0; i< NoTrees; i++)
	{

		if(treeType == 1)
		{
			tempMeshTree = meshTree2;
			treeType = 2;
			scaleTree= 0.05;
		}
		else
		{
			tempMeshTree = meshTree1;
			treeType = 1;
			scaleTree= 0.01;
		}

		Tree* newTree = new Tree(randTreeX, randTreeY, randTreeZ, tempMeshTree, this, scaleTree);
		
		m_Trees.push_back(newTree);
		
		randTreeX = RandIn(-10.0, 10.0);
		randTreeZ = RandIn(0.0, 10.0f);
		
	}

	Tree* markTree = new Tree(4, 0, 6, tempMeshTree, this, scaleTree);
	m_Trees.push_back(markTree);

	////Create Tank
	//for(int i = 0; i< NoTank; i++)
	//{
	//	float randX = -2.0f; //-8.0
	//	float randY = 0.0f;
	//	float randZ = 2.0f;  //8.0

	//	//create Tank
	//	Tank* newTank	= new Tank(randX, randY, randZ, this->meshTank, this);
	//	//push it to vector
	//	m_Tanks.push_back(newTank);
	//	
	//	if(m_bFirtTime)
	//	{
	//		m_iTankID = newTank->generateID();

	//		m_iTankIDNoText = newTank->generateIDNoText();
	//	}
	//}
	
	float randSX = 0.0f;//7.0
	float randSY = 0.0f;
	float randSZ = 0.0f;//7.0
	//Create SpaceShip
	for(int i = 0; i< NoSpaceShip; i++)
	{
		//create spaceship
		SpaceShip* newObject = new SpaceShip(randSX, randSY, randSZ, this->meshSpaceShip, this);
		//push it to vector
		m_SpaceShips.push_back(newObject);

		if(m_bFirstTimeSpaceShip) //m_bFirstTimeSpaceShip
		{
			m_iSpaceshipID = m_SpaceShips[0]->generateID();
			cout<< "SpaceShip : " << m_iSpaceshipID <<endl;

			m_iSpaceshipIDNoText = m_SpaceShips[0]->generateIDNoText();
			cout<< "SpaceShip NOTEXT: " << m_iSpaceshipIDNoText << endl;
			m_bFirstTimeSpaceShip = false;
		}
		
		//randSX += 1.5;
		randSX = RandIn(-5, 5);
		randSY = RandIn(-5, 5);
		randSZ = RandIn(-5, 5);
	}
	
	//if(m_bFirtTime)
	//{
		for(int i = 0; i< m_SpaceShips.size(); i++)
		{
			
			m_Vehilces.push_back(m_SpaceShips[i]->getVehicle());
			
			//if(m_pCellSpace)
			//m_pCellSpace->AddEntity(m_SpaceShips[i]->getVehicle());
		}
		
		cout<< "Number of Vehicles: "<< m_Vehilces.size();
		m_bFirtTime = false;
	//}



	//---------FLOCKING----------------------
	int sizeVehicle = m_SpaceShips.size();
	for(int i= 0; i< m_SpaceShips.size(); i++)
	{
		m_SpaceShips[i]->getVehicle()->Steering()->FlockingOn();
		//m_SpaceShips[i]->getVehicle()->Steering()->ToggleSpacePartitioningOnOff();
	}

	//m_SpaceShips[2]->getVehicle()->Steering()->PursuitOn(m_SpaceShips[0]->getVehicle());
	//m_SpaceShips[sizeVehicle-1]->getVehicle()->Steering()->WanderOn();
	//m_SpaceShips[i]->getVehicle()->Steering()->WanderOn();

	//m_SpaceShips[0]->getVehicle()->Steering()->ArriveOn();
	//m_SpaceShips[0]->getVehicle()->Steering()->SeekOn();

	//m_SpaceShips[i]->getVehicle()->Steering()->PursuitOn(m_SpaceShips[0]->getVehicle());
	//m_SpaceShips[i]->getVehicle()->Steering()->AlignmentOn();
	//m_SpaceShips[i]->getVehicle()->Steering()->EvadeOn(m_SpaceShips[sizeVehicle-1]->getVehicle()); 
	//sizeVehicle-1


	//------------SNAKE---------------------------
	//m_SpaceShips[0]->getVehicle()->Steering()->WanderOn(); //PathFollowingOn ---> better visual effect
	//for(int i = 1; i< 10; i++)
	//{
	//	
	//	m_SpaceShips[i]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[i-1]->getVehicle(), Vector3D(0,0, -0.3));
	//}

	
	//OFFSET PURSUIT & PURSUIT
	/*m_SpaceShips[0]->getVehicle()->Steering()->WanderOn();
	m_SpaceShips[1]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(0.5, 0, -0.5));
	m_SpaceShips[2]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(-0.5, 0, -0.5));
	m_SpaceShips[3]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(0, 0, -0.5));
	m_SpaceShips[4]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(0, 0, -1.0));
	m_SpaceShips[5]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(1.0, 0, -1.0));
	m_SpaceShips[6]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(-1.0, 0, -1.0));
	m_SpaceShips[7]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(-1.5, 0, -1.5));
	m_SpaceShips[8]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(1.5, 0, -1.5));*/
	
	//m_SpaceShips[1]->getVehicle()->Steering()->PursuitOn(m_SpaceShips[0]->getVehicle());
		
	//PATH+ SNAKE
	//m_SpaceShips[0]->getVehicle()->Steering()->FollowPathOn();
	//for(int i = 1; i< m_SpaceShips.size(); i++)
	//{
	//	m_SpaceShips[i]->getVehicle()->Steering()->FollowPathOn();
	//	//m_SpaceShips[i]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[i-1]->getVehicle(), Vector3D(0,0, 1.0));
	//}


	//SPecial + Game
	//for(int i = 0; i< m_SpaceShips.size(); i++)
	//{
	//	//m_SpaceShips[i]->getVehicle()->Steering()->
	//}
	
	//m_SpaceShips[m_SpaceShips.size()-1]->getVehicle()->Steering()->TurnOffAll();



	//SEEK & ARRIVE
	//m_SpaceShips[0]->getVehicle()->Steering()->ArriveOn();
	//m_SpaceShips[0]->getVehicle()->Steering()->SeekOn();


	//Create Turret
	float turretPosX = 0.0f;
	float turretPosY = 0.0f;
	float turretPosZ = 0.0f;
	Turret* newTurret = new Turret(turretPosX, turretPosY, turretPosZ, this->meshTurretBarrel, this->meshTurretBase, this);
	m_Turrets.push_back(newTurret);
	
	if(m_bFirtTime)
	{
		m_Turrets[0]->generateIDBase(); 
		m_Turrets[0]->generateIDBarrel();
		m_Turrets[0]->generateIDBaseNoText();
		m_Turrets[0]->generateIDBarrelNoText();

		
		m_iTurretBaseID			= m_Turrets[0]->getIDBase();		cout<< "TurretBase: "<< m_iTurretBaseID<< endl;
		m_iTurretBaseIDNoText	= m_Turrets[0]->getIDBaseNoText();	cout<< "TurretBaseNoTEXT : " << m_iTurretBaseIDNoText <<endl;
		m_iTurretBarrelID		= m_Turrets[0]->getIDBarrel();		cout<< "TurretBarrel: "<< m_iTurretBarrelID<<endl;
		m_iTurretBarrelNoTextID	= m_Turrets[0]->getIDBarrelNoText();cout<< "TurretBarrelNOTEXT : "<< m_iTurretBarrelNoTextID<<endl;
	
	}

	//float randAX = 0.0f;
	//float randAY = 0.0f;
	//float randAZ = 3.0f;//9.0
	//int	  type  = 1;
	//Mesh  tempMesh;
	////Create Aircraft
	//for(int i = 0; i< NoAirCraft; i++)
	//{
	//	
	//	 // 1- airCraftMesh1 ; 2- airCraftMesh2;
	//	
	//	//create Aircraft
	//	switch( type)
	//	{
	//	case 1:
	//		tempMesh = this->meshAir1;
	//		break;
	//	case 2:
	//		tempMesh = this->meshAir2;
	//		break;
	//	}

	//	Aircraft* newAir = new Aircraft(randAX, randAY, randAZ, tempMesh, this, type);
	//	
	//	/*if(m_bFirtTime)
	//	{
	//		if(type == 1)
	//		{
	//			newAir->generateAircraft1();
	//			m_iAircraft1ID = newAir->getAircraft1ID();
	//		}
	//		if(type == 2)
	//		{
	//			newAir->generateAircraft2();
	//			m_iAircraft2ID = newAir->getAircraft2ID();
	//		}
	//		
	//	}*/
	//	
	//	newAir->generateID();
	//	newAir->generateIDNoText();

	//	if(type == 1)
	//	{
	//		//newAir->generateAircraft1();
	//		m_iAircraft1ID = newAir->getAircraft1ID();
	//		m_iAircraft1IDNoText = newAir->getAircraft1NoTextID();
	//	}
	//	if(type == 2)
	//	{
	//		//newAir->generateAircraft2();
	//		m_iAircraft2ID = newAir->getAircraft2ID();
	//		m_iAircraft2IDNoText = newAir->getAircraft2NoTextID();
	//	}

	//	//push it to vector
	//	m_Aircrafts.push_back(newAir);
	//	
	//	type = 2;
	//	randAY += 1.0;
	//}
	


	

	


	////Missiles
	//float missilePosX =-3.0f;
	//float missilePosY = 0.0f;
	//float missilePosZ = -3.0f;
	//Missile* newMissile = new Missile(missilePosX, missilePosY, missilePosZ, this->meshMissile, this);
	//m_Missiles.push_back(newMissile);
	//

	//float tempX = 2.0f;
	//float tempY = 0.0f;
	//float tempZ = 2.0f;
	//Missile* newMissile1 = new Missile(tempX, tempY, tempZ, this->meshMissile, this);
	//m_Missiles.push_back(newMissile1);

	//tempX = -1.0f;
	//tempY = 0.0f;
	//tempZ = -1.0f;
	//Missile* newMissile2 = new Missile(tempX, tempY, tempZ, this->meshMissile, this);
	//m_Missiles.push_back(newMissile2);
	
	

	m_bFirtTime = false;

	m_bEnter = false;
	m_bStartScreen = false;
	m_iCount =	0;

	m_bRenderMode = false;
	
	m_iMissileType = 2;

	m_iNoCross = 0;
	m_iTankDestroy = 0;
	m_iSpaceShipDestroy = 0;
	m_iAircraftDestroy  = 0;


		
}

void GameWorld::Update()
{

	switch(m_iGameMode)
	{
	case 1:  //Start Screen Mode
		if(m_bEnter)
		{
			ClearGameWorld();
			/*CreateGameWorld();
			this->setMode(4);
			m_bEnter = false;*/

			//SEEK
			if(this->getRenderingMode() == 1)
			{
				CreateGameWorldSeek();
				this->setMode(4);
				m_bEnter = false;
			}

			//OffsetPursuit
			if(this->getRenderingMode() == 2)
			{
				CreateGameWorldOffsetPursuit();
				this->setMode(4);
				m_bEnter = false;
			}
			
			//SNAKE
			if(this->getRenderingMode() == 3)
			{
				CreateGameWorldSnake();
				this->setMode(4);
				m_bEnter = false;
			}
			
			//SPECIAL MODE
			if(this->getRenderingMode() == 4)
			{
				CreateGameWorldSpecialMode(); //
				this->setMode(4);
				m_bEnter = false;
			}

			if(this->getRenderingMode() == 5)
			{
				CreateGameWorldFlocking();
				this->setMode(4);
				m_bEnter = false;
			}

			if(this->getRenderingMode() == 6)
			{
				CreateGameWorldSpecialModeUnfair(); //
				this->setMode(4);
				m_bEnter = false;
			}

			if(this->getRenderingMode() == 7)
			{
				CreateGameWorldUnPredictableMode();
				this->setMode(4);
				m_bEnter = false;
				
			}

			if(this->getRenderingMode() == 0)
			{
				m_bEnter = true;
			}
			
			
		}
		break;
	case 2: // Game Over Mode
		if(m_bStartScreen)
		{
			m_bStartScreen = false;
			this->setMode(1);
		}

		if(m_bEnter)
		{
			ClearGameWorld();
			CreateGameWorld();
			
			this->setMode(4);
			m_bEnter = false;
		}
		break;
	case 3: // About Mode
		if(m_bStartScreen)
		{
			m_bStartScreen = false;
			this->setMode(1);
		}
		break;
	case 4: // Play Mode

		//Update every objects states
		//TANKS
		//for(int i= 0; i< m_Tanks.size(); i++)
		//{
		//	//m_Tanks[i]->Update();  
		//}
		
		//IMPORTANT----------
		if(m_bStartScreen)
		{
			m_bStartScreen = false;
			m_bEnter = true;
			m_bSpecialMode = 0;
			this->setMode(1);
			//
		}

		for(int i = 0; i< m_SpaceShips.size(); i++)
		{
			m_SpaceShips[i]->Update();

		}


		/*for(int i = 0; i< m_Aircrafts.size(); i++)
		{
			m_Aircrafts[i]->Update();
		}*/

		//for(int i = 0; i< m_Missiles.size(); i++)
		//{
		//	m_Missiles[i]->Update();
		//	//cout<< "Missle Pos"<< m_Missiles[i]->getX()<< " " << m_Missiles[i]->getY()<<" "<< m_Missiles[i]->getZ() << endl;
		//}

		//for(int i = 0; i< m_Turrets.size(); i++)
		//{
		//	/*m_Turrets[i]->Update();*/


		//}
		
		if(this->isPressedLeft())
		{
		/*	float angle = m_Turrets[0]->getHorizontalAngle();
			angle += 1.0;
			m_Turrets[0]->setHorizontalAngle(angle);

			this->setPressedLeft(false);*/
		}
		if(this->isPressedRight())
		{
			//float angle = m_Turrets[0]->getHorizontalAngle();
			//angle -= 1.0;
			//m_Turrets[0]->setHorizontalAngle(angle);
			//this->setPressedRight(false);
		}

		//Move Turret barrel vertically
		if(this->isPressedDown())
		{
			//float angle = m_Turrets[0]->getVerticalAngle();
			//if(angle > 0)
			//{
			//	
			//	angle -= 1.0;
			//	
			//	m_Turrets[0]->setVerticalAngle(angle);

			//	this->setPressedDown(false);
			//}
		}
		if(this->isPressedUp())
		{
			//float angle = m_Turrets[0]->getVerticalAngle();
			//
			//if(angle < 90)
			//{
			//	angle += 1.0;
			//	
			//	m_Turrets[0]->setVerticalAngle(angle);
			//	
			//	this->setPressedUp(false);
			//}
		}


		if(m_bPressedFired)
		{
			//float beta = m_Turrets[0]->getVerticalAngle();
			//float alpha= m_Turrets[0]->getHorizontalAngle();
			//float PI = 3.14159265;


			//float missileX = 1.25*cos(beta*PI/180)*sin(alpha*PI/180);
			//float missileY = 1.25*sin(beta*PI/180);
			//float missileZ = 1.25*cos(beta*PI/180)*cos(alpha*PI/180);
			//
			//Missile* newMissile = new Missile(missileX, missileY, missileZ, this->meshMissile, this);

			//m_Missiles.push_back(newMissile);
			//m_bPressedFired = false;
		}

		//float beta = m_Turrets[0]->getVerticalAngle();
		//float alpha= m_Turrets[0]->getHorizontalAngle();
		//float PI = 3.14159265;

		//cameraTargetX = 1.25*cos(beta*PI/180)*sin(alpha*PI/180);
		//cameraTargetY = 1.25*sin(beta*PI/180);
		//cameraTargetZ = 1.25*cos(beta*PI/180)*cos(alpha*PI/180);

		//Generate new tanks, spaceships, aircrafts, MIssiles
		//if( (m_iCount % 457) == 0)
		//{
		//	float tempX = RandIn(-10.0, 10.0);
		//	float tempZ = RandIn(8.0, 10.0);
		//	float tempY = RandIn(0.5, 1.0);

		//	int	  type  = 2;
		//	// 1- airCraftMesh1 ; 2- airCraftMesh2;
		//	Mesh  tempMesh;
		//	//create Aircraft
		//	tempMesh = this->meshAir2;

		//	Aircraft* newAir = new Aircraft(tempX, tempY, tempZ, tempMesh, this, type);

		//	//push it to vector
		//	m_Aircrafts.push_back(newAir);
		//	
		//}
		//
		//if( (m_iCount % 907) == 0)
		//{
		//	float tempX = RandIn(-10.0, 10.0);
		//	float tempZ = RandIn(8.0, 10.0);
		//	float tempY = RandIn(0.5, 1.5);

		//	int	  type  = 1;
		//	// 1- airCraftMesh1 ; 2- airCraftMesh2;
		//	Mesh  tempMesh;
		//	//create Aircraft
		//	tempMesh = this->meshAir1;

		//	Aircraft* newAir = new Aircraft(tempX, tempY, tempZ, tempMesh, this, type);

		//	//push it to vector
		//	m_Aircrafts.push_back(newAir);
		//	
		//}
		//

		//if((m_iCount % 401) == 0) //Tank
		//{
		//	float tempX = RandIn(-10.0, 10.0);
		//	float tempZ = RandIn(8.0, 10.0);
		//	float tempY = 0.0f;
		//	
		//	//create Tank
		//	Tank* newTank	= new Tank(tempX, tempY, tempZ, this->meshTank, this);
		//	//push it to vector
		//	m_Tanks.push_back(newTank);
		//}

		//907
		//if((m_iCount % 733) == 0) //Spaceship
		//{
		//	float tempX = RandIn(-10.0, 10.0);
		//	float tempZ = RandIn(8.0, 10.0);
		//	float tempY = 0.1f;

		//	SpaceShip* newSpaceship = new SpaceShip(tempX, tempY, tempZ, this->meshSpaceShip, this);
		//	//push it to vector
		//	m_SpaceShips.push_back(newSpaceship);

		//}
		
		
		//Delete objects that pass xy plane and object that have been fired - IF it is fired, it will be deleted
		
		//if(m_bSpecialMode == 2)
		//{
		//	for(int i = 0; i< m_SpaceShips.size(); i++)
		//	{
		//		m_SpaceShips[i]->getVehicle()->Steering()->TurnOffAll();
		//	}
		//}

		//int specialIndex = 0;
		//int    indx = -1;
		//if(m_bSpecialMode == 2)
		//{
		//	//case 0:
		//	//	
		//	//	break;
		//	////Start FollowPath
		//	//case 1:
		//	//	

		//	//	break;
		//	////Finding position
		//	//case 2:
		//		
		//		for(int i = 0; i< m_SpaceShips.size(); i++)
		//		{
		//			//double closestDistance = Vec3DDistance(m_SpaceShips[i]->getVehicle()->Pos(), m_Points[0]->Pos());
		//			double closestDistance = m_SpaceShips[i]->ClosestDistance();
		//			

		//			for(int a = 0; a< m_Points.size(); a++)
		//			{
		//				if(!m_Points[a]->isOccupied())
		//				{
		//					double d = Vec3DDistance(m_SpaceShips[i]->getVehicle()->Pos(), m_Points[a]->Pos());
		//					if(d< closestDistance)
		//					{
		//						closestDistance = d;
		//						indx = a;
		//					}
		//				}
		//			}

		//			if(indx != -1)
		//			{
		//				m_SpaceShips[i]->setSpecialIndex(indx);
		//				Vector3D newTarget = m_Points[indx]->Pos();
		//				m_SpaceShips[i]->getVehicle()->Steering()->SetTarget(newTarget);

		//				m_SpaceShips[i]->getVehicle()->Steering()->TurnOffAll();
		//				m_SpaceShips[i]->getVehicle()->Steering()->SeekOn();
		//			}
		//			else
		//			{
		//				//If cannot find a position, it should wander
		//				//m_SpaceShips[i]->getVehicle()->Steering()->WanderOn();
		//			}
		//			
		//			//Check state
		//			bool seekTarget = m_SpaceShips[i]->getVehicle()->Steering()->isSeekOn();
		//			if(seekTarget)
		//			{
		//				Vector3D targetPos = m_SpaceShips[i]->getVehicle()->Steering()->Target();
		//				Vector3D itsPos    = m_SpaceShips[i]->getVehicle()->Pos();
		//				Vector3D toTarget = itsPos - targetPos;
		//				
		//				
		//				if(toTarget.Length() < 0.2)
		//				{
		//					specialIndex= m_SpaceShips[i]->SpecialIndex();
		//					m_Points[specialIndex]->setOccupied(true);
		//					
		//					m_SpaceShips[i]->setClosestDistance(toTarget.Length());

		//					//Stop all movements
		//					m_SpaceShips[i]->getVehicle()->Steering()->TurnOffAll();

		//					
		//				}
		//			}
		//		}

		//		//break;
		//}

		
		if(m_iNoCross > 9)
			this->setMode(2);
		
		m_iCount++;

		break;
	}
	
	
}

void GameWorld::Render()
{
	switch(m_iGameMode)
	{
	case 1: //Mode Start Screen
		showInfoStart();
		break;
	case 2: //Mode GameOver and Replay Screen
		showInfoGameOver();
		break;
	case 3://About screen
		showInfoAbout();
		break;
	case 4://Playing Screen
		showInfoOnPlay();
		break;

	}

	for(int i = 0; i< m_Points.size(); i++)
	{
		m_Points[i]->Render();
	}

	//Render Tree
	for(int i = 0; i< m_Trees.size(); i++)
	{
		glPushMatrix();

		glColor3f(0.0f, 0.8f, 0.2f);
		glTranslatef(m_Trees[i]->getX(), m_Trees[i]->getY(), m_Trees[i]->getZ());
		glCallList(m_Trees[i]->getID());

		glPopMatrix();
	}


	//Render Tanks
	for(int i = 0; i< m_Tanks.size(); i++)
	{
		if(m_Tanks[i]->isFired())
		{
			//No call list
		}
		else
		{

			glLineWidth(1);
			glPushMatrix();

			//glColor3f(1.0f, 1.0f , 1.0f);

			//glEnable(GL_COLOR_MATERIAL);
			//glColorMaterial(GL_FRONT, GL_AMBIENT);
			////glColor3f(m_Tanks[i]->getMesh().m_Surfaces[a]->m_pMaterial.ambient[0], m_Tanks[i]->getMesh().m_Surfaces[a]->m_pMaterial.ambient[1], m_Tanks[i]->getMesh().m_Surfaces[a]->m_pMaterial.ambient[2]);
			//glColor3f(1.0, 0.5f, 0.4f);

			//glColorMaterial(GL_FRONT, GL_DIFFUSE);
			////glColor3f(m_Tanks[i]->getMesh().m_Surfaces[a]->m_pMaterial.diffuse[0], m_Tanks[i]->getMesh().m_Surfaces[a]->m_pMaterial.diffuse[1], m_Tanks[i]->getMesh().m_Surfaces[a]->m_pMaterial.diffuse[2]);
			//glColor3f(0.6f, 0.4f, 0.35f);

			//glColorMaterial(GL_FRONT, GL_SPECULAR);
			////glColor3f(m_Tanks[i]->getMesh().m_Surfaces[a]->m_pMaterial.specular[0], m_Tanks[i]->getMesh().m_Surfaces[a]->m_pMaterial.specular[1], m_Tanks[i]->getMesh().m_Surfaces[a]->m_pMaterial.specular[2]);
			//glColor3f(0.7f, 0.8f, 0.3f);

			
			
			glTranslatef(m_Tanks[i]->getX(), m_Tanks[i]->getY(), m_Tanks[i]->getZ());
			glColor3f(1.0f, 0.4f ,0.8f);
			if(this->m_bRenderMode)
			{
				//glCallList(m_Tanks[i]->getID());
				
				glCallList(m_iTankID);
			}
			else
			{
				//glCallList(m_Tanks[i]->getIDNoText());
				
				
				//glColor3f(1.0f, 1.0f ,1.0f);
				glCallList(m_iTankIDNoText);
			}

			glPopMatrix();
		}
	}

	//render Spaceships
	for(int i =0; i< m_SpaceShips.size(); i++)
	{
		if(m_SpaceShips[i]->isFired())
		{
		
		}
		else
		{
			glLineWidth(1);
			glPushMatrix();
			glColor3f(1.0f, 0.4f ,0.5f);
			glTranslatef(m_SpaceShips[i]->getX(), m_SpaceShips[i]->getY(), m_SpaceShips[i]->getZ());
			
			if(!m_SpaceShips[i]->getHeading().isZero())
			{
				float PI = 3.14159265;
				Vector3D	heading = m_SpaceShips[i]->getHeading();
				Vector3		zAxis(0, 0, 1);
				Vector3		transHeading(heading.x, heading.y, heading.z);
				Vector3		rotateAxis = zAxis.cross(transHeading);
				//Vector3		rotateAxis = transHeading.cross(zAxis);
				Vector3D	rotateAxis3D(rotateAxis.x, rotateAxis.y, rotateAxis.z);
				m_SpaceShips[i]->setAxisRotate(rotateAxis3D);

				float lengthHeading = transHeading.length();
				float cosOf2Vectors = zAxis.dot(transHeading)/lengthHeading;
				float rotationAngle = acos(cosOf2Vectors)*180/PI;
				//cout<< "rotationAngle : " << rotationAngle << endl;
				m_SpaceShips[i]->setAngleRotate(rotationAngle);

				glRotatef(rotationAngle, rotateAxis.x, rotateAxis.y, rotateAxis.z);
				
			}


			if(this->m_bRenderMode)
			{
				//glCallList(m_SpaceShips[i]->getID());
				glCallList(m_iSpaceshipID);
			}
			else{
				//glCallList(m_SpaceShips[i]->getIDNoTEXT());

				glCallList(m_iSpaceshipIDNoText);
			}
			glPopMatrix();
		}
	
	}

	//render Aricrafts
	for(int i = 0; i< m_Aircrafts.size(); i++)
	{
		if( m_Aircrafts[i]->isFired())
		{

		}
		else
		{
			glLineWidth(1);
			glPushMatrix();
			
			//glColor3f(1.0f, 1.0f ,1.0f);

			glTranslatef(m_Aircrafts[i]->getX(), m_Aircrafts[i]->getY(), m_Aircrafts[i]->getZ());
			if(m_Aircrafts[i]->getType() == 1)
			{
				if(this->m_bRenderMode)
				{
					glCallList(m_iAircraft1ID);
				}
				else{
					glCallList(m_iAircraft1IDNoText);
				}
			}
			else
			{
				if(this->m_bRenderMode)
				{
					glCallList(m_iAircraft2ID);
				}
				else
				{
					glCallList(m_iAircraft2IDNoText);
				}
			}
			glPopMatrix();
		}
	}

	//render Missiles
	for(int i = 0; i< m_Missiles.size(); i++)
	{
		if(m_Missiles[i]->isTouch())
		{
			
		}
		else
		{
			if(m_Missiles[i]->getType() == 1)
			{
				
				glPushMatrix();
				//glColor3f(1.0f, 1.0f ,1.0f);

				//Rotate to the vector speed direction
				Matrix4 rotateMatrix;
				rotateMatrix.identity();

				Vector3 velo = m_Missiles[i]->getVelocityVec();
				Vector3 yAxis(0, 1, 0);

				Vector3 newZ = velo;
				Vector3 newX = yAxis.cross(velo);
				Vector3 newY = velo.cross(newX);

				rotateMatrix.setColumn(0, newX);
				rotateMatrix.setColumn(1, newY);
				rotateMatrix.setColumn(2, newZ);
				
				/*cout<< "Matrix "<< endl;
				for(int i = 0; i< 16; i++)
				{
					cout<< rotateMatrix[i] <<" ";
					if((i+1)%4 == 0)
					{
						cout<<endl;
					}
				}*/

				//glLoadMatrixf(rotateMatrix.get());

				glRotatef(0.0, velo.x, velo.y, velo.z);

				glTranslatef(m_Missiles[i]->getX(), m_Missiles[i]->getY(), m_Missiles[i]->getZ());
				glColor3f(1.0f, 0.0f, 0.0f);
				glCallList(m_Missiles[i]->getID());
				glPopMatrix();
			}
			else
			{
				
				glPushMatrix();
				glColor3f(1.0f, 0.0f, 0.0f);
				glTranslatef(m_Missiles[i]->getX(), m_Missiles[i]->getY(), m_Missiles[i]->getZ());
				glColor3f(1.0f, 0.0f, 0.0f);
				glCallList(m_Missiles[i]->getID());
				glPopMatrix();
			}
			
			
		}
		
	}

	//render TUrret
	for(int i = 0; i< m_Turrets.size(); i++)
	{


		/*glColor3f(1.0f, 0.0f, 0.0f);
		glPushMatrix();
		glTranslatef(m_Turrets[i]->getX(), m_Turrets[i]->getY(), m_Turrets[i]->getZ());
		glCallList(m_Turrets[i]->getID());
		glPopMatrix();*/
		
		

			//m_Turrets[i]->Render();

		
		
			//Drawing Turret Base
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 0.5f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(m_Turrets[i]->getHorizontalAngle(), 0.0f, 1.0f, 0.0f);
			glTranslatef(-2.0f, 0.0f , 0.8f);
			if(this->m_bRenderMode)
			{
				glCallList(m_iTurretBaseID);
			}
			else
			{
				glCallList(m_iTurretBaseIDNoText);
				
			}
			glPopMatrix();

			//Drawing Turret barrel
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 0.5f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(m_Turrets[i]->getHorizontalAngle(), 0.0f, 1.0f, 0.0f);
			glRotatef(-m_Turrets[i]->getVerticalAngle(), 0.0f, 0.0f, 1.0f);
			glTranslatef(-2.0f, 0.0f , 0.8f);
			//Loop over polygonal meshes
			if(this->m_bRenderMode)
			{
				glCallList(m_iTurretBarrelID);
			}
			else
			{
				glCallList(m_iTurretBarrelNoTextID);
			}

			glPopMatrix();
			
		

	}
}


void GameWorld::CreateGameWorldOffsetPursuit()
{
	int NoTrees	   = 0;
	int NoSpaceShip = 90; //45 = 9*5; 63 = 9*7

	m_bPressedFired = false;
	m_bPressedLeft = false;
	m_bPressedRight = false;
	m_bPressedUp = false;
	m_bPressedDown = false;
	
	this->cameraTargetX = 0.0f;
	this->cameraTargetY = 0.0f;
	this->cameraTargetZ = 0.0f;

	//CellSpacePartition
	//if(m_bFirtTime)
	//{
	//	m_pCellSpace = new CellSpacePartition<Vehicle*>(80.0, 80.0, 80.0, 10, 10, 10, 1000); //these paras can be written from a file
	//}

	float randSX = 0.0f;//7.0
	float randSY = 0.0f;
	float randSZ = 0.0f;//7.0
	//Create SpaceShip
	for(int i = 0; i< NoSpaceShip; i++)
	{
		//create spaceship
		SpaceShip* newObject = new SpaceShip(randSX, randSY, randSZ, this->meshSpaceShip, this);
		//push it to vector
		m_SpaceShips.push_back(newObject);

		if(m_bFirstTimeSpaceShip) //m_bFirstTimeSpaceShip
		{
			m_iSpaceshipID = m_SpaceShips[0]->generateID();
			cout<< "SpaceShip : " << m_iSpaceshipID <<endl;

			m_iSpaceshipIDNoText = m_SpaceShips[0]->generateIDNoText();
			cout<< "SpaceShip NOTEXT: " << m_iSpaceshipIDNoText << endl;
			m_bFirstTimeSpaceShip = false;
		}
		
		//randSX += 1.5;
		randSX = RandIn(-5, 5);
		randSY = RandIn(-5, 5);
		randSZ = RandIn(-5, 5);
	}

	//if(m_bFirtTime)
	//{
	for(int i = 0; i< m_SpaceShips.size(); i++)
	{

		m_Vehilces.push_back(m_SpaceShips[i]->getVehicle());

		//m_pCellSpace->AddEntity(m_SpaceShips[i]->getVehicle());
	}

	//	cout<< "Number of Vehicles: "<< m_Vehilces.size();
	m_bFirtTime = false;
	//}

		//OFFSET PURSUIT & PURSUIT
	//m_SpaceShips[0]->getVehicle()->Steering()->WanderOn();
	//m_SpaceShips[1]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(0.4, 0, -0.4));
	//m_SpaceShips[2]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(-0.4, 0, -0.4));
	//m_SpaceShips[3]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(0, 0, -0.4));
	//m_SpaceShips[4]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(0, 0, -0.8));
	//m_SpaceShips[5]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(0.8, 0, -0.8));
	//m_SpaceShips[6]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(-0.8, 0, -0.8));
	//m_SpaceShips[7]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(-1.5, 0, -1.5));
	//m_SpaceShips[8]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(1.5, 0, -1.5));


	int indxLeader = 0;
	vector<Vector3D> offsetVector;
	offsetVector.push_back(Vector3D(0.4, 0, -0.4));
	offsetVector.push_back(Vector3D(-0.4, 0, -0.4));
	offsetVector.push_back(Vector3D(0, 0, -0.4));
	offsetVector.push_back(Vector3D(0, 0, -0.8));
	offsetVector.push_back(Vector3D(0.8, 0, -0.8));
	offsetVector.push_back(Vector3D(-0.8, 0, -0.8));
	offsetVector.push_back(Vector3D(-1.5, 0, -1.5));
	offsetVector.push_back(Vector3D(1.5, 0, -1.5));
	for(int i = 0; i< m_SpaceShips.size(); i++)
	{
		if((i%9) == 0)
		{
			if((i == 0) || (i == 9))
			{
				m_SpaceShips[i]->getVehicle()->Steering()->FollowPathOn();
			}
			else
			{
				m_SpaceShips[i]->getVehicle()->Steering()->WanderOn();
			}
			indxLeader = i;
		}
		else
		{
			int offsetIndx = i%9;
			m_SpaceShips[i]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[indxLeader]->getVehicle(), offsetVector[offsetIndx-1]);
		}
		
	}


	m_bEnter = false;
	m_bStartScreen = false;
	m_iCount =	0;

	m_bRenderMode = false;
	
	m_iMissileType = 2;

	m_iNoCross = 0;
	m_iTankDestroy = 0;
	m_iSpaceShipDestroy = 0;
	m_iAircraftDestroy  = 0;



	
	
}

void GameWorld::CreateGameWorldSnake()
{
	std::list<Vector3D> listSnakePoint;
	Vector3D point1(0,0,0); listSnakePoint.push_back(point1);
	Vector3D point2(2,0,3); listSnakePoint.push_back(point2);
	Vector3D point3(6,0,6); listSnakePoint.push_back(point3);
	Vector3D point4(0,0,9); listSnakePoint.push_back(point4);
	Vector3D point5(-6,0,6);listSnakePoint.push_back(point5);
	Vector3D point6(-2,0,3);listSnakePoint.push_back(point6);
	Vector3D point7(0,0,0); listSnakePoint.push_back(point7);
	Vector3D point8(2, 0,-3);listSnakePoint.push_back(point8);
	Vector3D point9(6, 0, -6);listSnakePoint.push_back(point9);
	Vector3D point10(0,0, -9); listSnakePoint.push_back(point10);
	Vector3D point11(-6, 0, -6);listSnakePoint.push_back(point11);
	Vector3D point12(-2,0, -3);listSnakePoint.push_back(point12);

	std::list<Vector3D> listSpacePoint;
	Vector3D pointS1(0,2,0); listSpacePoint.push_back(pointS1);
	Vector3D pointS2(2,1.5,3); listSpacePoint.push_back(pointS2);
	Vector3D pointS3(6,1.0,6); listSpacePoint.push_back(pointS3);
	Vector3D pointS4(0,0.5,9); listSpacePoint.push_back(pointS4);
	Vector3D pointS5(-6,1.0,6);listSpacePoint.push_back(pointS5);
	Vector3D pointS6(-2,1.5,3);listSpacePoint.push_back(pointS6);
	Vector3D pointS7(0,2,0); listSpacePoint.push_back(pointS7);
	Vector3D pointS8(2, 2.5,-3);listSpacePoint.push_back(pointS8);
	Vector3D pointS9(6, 3.0, -6);listSpacePoint.push_back(pointS9);
	Vector3D pointS10(0,3.25, -9); listSpacePoint.push_back(pointS10);
	Vector3D pointS11(-6, 1.0, -6);listSpacePoint.push_back(pointS11);
	Vector3D pointS12(-2,0.5, -3);listSpacePoint.push_back(pointS12);

	
	std::list<Vector3D> listCirclePoint;
	Vector3D pointC1(20, 0, 0); listCirclePoint.push_back(pointC1);
	Vector3D pointC2(17.3, 0, 10); listCirclePoint.push_back(pointC2);
	Vector3D pointC3(10, 0, 17.3); listCirclePoint.push_back(pointC3);
	Vector3D pointC4(0,  0, 20); listCirclePoint.push_back(pointC4);
	Vector3D pointC5(-10, 0, 17.3); listCirclePoint.push_back(pointC5);
	Vector3D pointC6(-17.3,0, 10 ); listCirclePoint.push_back(pointC6);
	Vector3D pointC7(-20, 0, 0); listCirclePoint.push_back(pointC7);
	Vector3D pointC8(-17.3, 0, -10); listCirclePoint.push_back(pointC8);
	Vector3D pointC9(-10, 0, -17.3); listCirclePoint.push_back(pointC9);
	Vector3D pointC10(0,  0, -20); listCirclePoint.push_back(pointC10);
	Vector3D pointC11(10, 0, -17.3); listCirclePoint.push_back(pointC11);
	Vector3D pointC12(17.3, 0, -10); listCirclePoint.push_back(pointC12);

	std::list<Vector3D> listLinePoint;
	Vector3D pointL1(-14.3, 0, 10);  listLinePoint.push_back(pointL1);
	Vector3D pointL2(-14.3, 0, -10); listLinePoint.push_back(pointL2);
	Vector3D pointL3(-18.3, 0, 0);   listLinePoint.push_back(pointL3);

	int NoTrees	   = 0;
	int NoSpaceShip = 140; //45 = 9*5; 63 = 9*7

	m_bPressedFired = false;
	m_bPressedLeft = false;
	m_bPressedRight = false;
	m_bPressedUp = false;
	m_bPressedDown = false;
	
	this->cameraTargetX = 0.0f;
	this->cameraTargetY = 0.0f;
	this->cameraTargetZ = 0.0f;

	//CellSpacePartition
	//if(m_bFirtTime)
	//{
	//	m_pCellSpace = new CellSpacePartition<Vehicle*>(80.0, 80.0, 80.0, 10, 10, 10, 1000); //these paras can be written from a file
	//}

	float randSX = 0.0f;//7.0
	float randSY = 0.0f;
	float randSZ = 0.0f;//7.0
	//Create SpaceShip
	for(int i = 0; i< NoSpaceShip; i++)
	{
		//create spaceship
		SpaceShip* newObject = new SpaceShip(randSX, randSY, randSZ, this->meshSpaceShip, this);
		//push it to vector
		m_SpaceShips.push_back(newObject);

		if(m_bFirstTimeSpaceShip) //m_bFirstTimeSpaceShip
		{
			m_iSpaceshipID = m_SpaceShips[0]->generateID();
			cout<< "SpaceShip : " << m_iSpaceshipID <<endl;

			m_iSpaceshipIDNoText = m_SpaceShips[0]->generateIDNoText();
			cout<< "SpaceShip NOTEXT: " << m_iSpaceshipIDNoText << endl;
			m_bFirstTimeSpaceShip = false;
		}
		
		//randSX += 1.5;
		randSX = RandIn(-10, 10);
		//randSY = RandIn(-5, 5);
		randSZ = RandIn(-10, 10);
	}

	//if(m_bFirtTime)
	//{
	for(int i = 0; i< m_SpaceShips.size(); i++)
	{

		m_Vehilces.push_back(m_SpaceShips[i]->getVehicle());

		//m_pCellSpace->AddEntity(m_SpaceShips[i]->getVehicle());
	}

	//	cout<< "Number of Vehicles: "<< m_Vehilces.size();
	m_bFirtTime = false;
	//}
	
	for(int i = 0; i< m_SpaceShips.size()-100; i++)
	{
		m_SpaceShips[i]->getVehicle()->Steering()->SetPath(listSnakePoint); //listSnakePoint
		m_SpaceShips[i]->getVehicle()->Steering()->FollowPathOn();

		m_SpaceShips[i]->getVehicle()->Steering()->SeparationOn();
		
		m_SpaceShips[i]->getVehicle()->Steering()->SetNewCurWayPoint();
	}
	
	for(int i = m_SpaceShips.size()-100; i< m_SpaceShips.size()-30; i++)
	{
		m_SpaceShips[i]->getVehicle()->Steering()->SetPath(listCirclePoint); //listSnakePoint
		m_SpaceShips[i]->getVehicle()->Steering()->FollowPathOn();

		m_SpaceShips[i]->getVehicle()->Steering()->SeparationOn();
		
		m_SpaceShips[i]->getVehicle()->Steering()->SetNewCurWayPoint();
	}

	for(int i = m_SpaceShips.size()-30; i< m_SpaceShips.size(); i++)
	{
		m_SpaceShips[i]->getVehicle()->Steering()->SetPath(listLinePoint); //listSnakePoint
		m_SpaceShips[i]->getVehicle()->Steering()->FollowPathOn();

		m_SpaceShips[i]->getVehicle()->Steering()->SeparationOn();
		
		m_SpaceShips[i]->getVehicle()->Steering()->SetNewCurWayPoint();
	}

	m_bEnter = false;
	m_bStartScreen = false;
	m_iCount =	0;

	m_bRenderMode = false;
	
	m_iMissileType = 2;

	m_iNoCross = 0;
	m_iTankDestroy = 0;
	m_iSpaceShipDestroy = 0;
	m_iAircraftDestroy  = 0;




}

//Create GameWorld for special game - who's the owner of seat
void GameWorld::CreateGameWorldSpecialMode()
{


	int NoTrees	   = 0;
	int NoSpaceShip = 13;

	m_bPressedFired = false;
	m_bPressedLeft = false;
	m_bPressedRight = false;
	m_bPressedUp = false;
	m_bPressedDown = false;
	
	this->cameraTargetX = 0.0f;
	this->cameraTargetY = 0.0f;
	this->cameraTargetZ = 0.0f;
	
	//POINTs
	Vector3D pointPos0(-3,0,3);
	Point* newPoint0 = new Point(5, 0, 0);
	Point* newPoint1 = new Point(4.325, 0, 2.5);
	Point* newPoint2 = new Point(2.5, 0, 4.325);
	Point* newPoint3 = new Point(0,0,5);
	Point* newPoint4 = new Point(-2.5, 0, 4.325);
	Point* newPoint5 = new Point(-4.325, 0, 2.5);
	Point* newPoint6 = new Point(-5, 0, 0);
	Point* newPoint7 = new Point(-4.325, 0, -2.5);
	Point* newPoint8 = new Point(-2.5, 0, -4.325);
	Point* newPoint9 = new Point(0, 0, -5); 
	Point* newPoint10= new Point(2.5, 0, -4.325);
	Point* newPoint11= new Point(4.325, 0, -2.5);
	m_Points.push_back(newPoint0);
	m_Points.push_back(newPoint1);
	m_Points.push_back(newPoint2);
	m_Points.push_back(newPoint3);
	m_Points.push_back(newPoint4);
	m_Points.push_back(newPoint5);
	m_Points.push_back(newPoint6);
	m_Points.push_back(newPoint7);
	m_Points.push_back(newPoint8);
	m_Points.push_back(newPoint9);
	m_Points.push_back(newPoint10);
	m_Points.push_back(newPoint11);

	
	//CellSpacePartition
	//if(m_bFirtTime)
	//{
	//	m_pCellSpace = new CellSpacePartition<Vehicle*>(80.0, 80.0, 80.0, 10, 10, 10, 1000); //these paras can be written from a file
	//	
	//}

	//Create Tree
	Mesh tempMeshTree = meshTree2;
	float randTreeX = 1.0f;
	float randTreeY = 0.0f;
	float randTreeZ = 2.0f;
	int	  treeType  = 2;
	float scaleTree     = 0.05;
	for(int i = 0; i< NoTrees; i++)
	{

		if(treeType == 1)
		{
			tempMeshTree = meshTree2;
			treeType = 2;
			scaleTree= 0.05;
		}
		else
		{
			tempMeshTree = meshTree1;
			treeType = 1;
			scaleTree= 0.01;
		}

		Tree* newTree = new Tree(randTreeX, randTreeY, randTreeZ, tempMeshTree, this, scaleTree);
		
		m_Trees.push_back(newTree);
		
		randTreeX = RandIn(-10.0, 10.0);
		randTreeZ = RandIn(0.0, 10.0f);
		
	}

	Tree* markTree = new Tree(4, 0, 6, tempMeshTree, this, scaleTree);
	m_Trees.push_back(markTree);

	
	//Starting Pos
	Vector3D point1(10, 0, 0);
	Vector3D point2(8.65, 0, 5);
	Vector3D point3(5, 0, 8.65);
	Vector3D point4(0, 0, 10);
	Vector3D point5(-5, 0, 8.65);
	Vector3D point6(-8.65, 0, 5);
	Vector3D point7(-10, 0, 0);
	Vector3D point8(-8.65, 0, -5);
	Vector3D point9(-5, 0, -8.65);
	Vector3D point10(0, 0 , -10);
	Vector3D point11(5, 0, -8.65);
	Vector3D point12(8.65, 0, -5);
	std::vector<Vector3D> listPoint;
	listPoint.push_back(point1);
	listPoint.push_back(point2);
	listPoint.push_back(point3);
	listPoint.push_back(point4);
	listPoint.push_back(point5);
	listPoint.push_back(point6);
	listPoint.push_back(point7);
	listPoint.push_back(point8);
	listPoint.push_back(point9);
	listPoint.push_back(point10);
	listPoint.push_back(point11);
	listPoint.push_back(point12);

	float randSX = 10.00f;//7.0
	float randSY = 0.0f;
	float randSZ = 0.0f;//7.0
	//Create SpaceShip
	for(int i = 0; i< NoSpaceShip; i++)
	{
			//create spaceship
			SpaceShip* newObject = new SpaceShip(randSX, randSY, randSZ, this->meshSpaceShip, this);
			//push it to vector
			m_SpaceShips.push_back(newObject);

			if(m_bFirstTimeSpaceShip) //m_bFirstTimeSpaceShip
			{
				m_iSpaceshipID = m_SpaceShips[0]->generateID();
				cout<< "SpaceShip : " << m_iSpaceshipID <<endl;

				m_iSpaceshipIDNoText = m_SpaceShips[0]->generateIDNoText();
				cout<< "SpaceShip NOTEXT: " << m_iSpaceshipIDNoText << endl;
				m_bFirstTimeSpaceShip = false;
			}


			if(i != 12){
				randSX = listPoint[i].x;
				randSZ = listPoint[i].z;
			}
	}
	
	//if(m_bFirtTime)
	//{
		for(int i = 0; i< m_SpaceShips.size(); i++)
		{
			
			m_Vehilces.push_back(m_SpaceShips[i]->getVehicle());
			
			//m_pCellSpace->AddEntity(m_SpaceShips[i]->getVehicle());
		}
		
	//	cout<< "Number of Vehicles: "<< m_Vehilces.size();
		m_bFirtTime = false;
	//}


	//PATH+ SNAKE
	m_SpaceShips[0]->getVehicle()->Steering()->FollowPathOn();
	for(int i = 1; i< m_SpaceShips.size(); i++)
	{
		m_SpaceShips[i]->getVehicle()->Steering()->FollowPathOn();
		m_SpaceShips[i]->getVehicle()->Steering()->SeparationOn();
		//m_SpaceShips[i]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[i-1]->getVehicle(), Vector3D(0,0, 1.0));
	}

	m_bFirtTime = false;

	m_bEnter = false;
	m_bStartScreen = false;
	m_iCount =	0;

	m_bRenderMode = false;
	
	m_iMissileType = 2;

	m_iNoCross = 0;
	m_iTankDestroy = 0;
	m_iSpaceShipDestroy = 0;
	m_iAircraftDestroy  = 0;


}

void GameWorld::CreateGameWorldSeek()
{
	int NoTrees	   = 0;
	int NoSpaceShip = 9;

	m_bPressedFired = false;
	m_bPressedLeft = false;
	m_bPressedRight = false;
	m_bPressedUp = false;
	m_bPressedDown = false;

	this->cameraTargetX = 0.0f;
	this->cameraTargetY = 0.0f;
	this->cameraTargetZ = 0.0f;



	m_bFirtTime = true;
	m_bFirstTimeSpaceShip = true;

	//Create Tree
	float scaleTree     = 0.05;
	Mesh tempMeshTree = meshTree2;
	Tree* markTree = new Tree(4, 0, 6, tempMeshTree, this, scaleTree);
	m_Trees.push_back(markTree);

	float randSX = 0.0f;//7.0
	float randSY = 0.0f;
	float randSZ = 0.0f;//7.0
	//create a spaceship
	SpaceShip* newObject = new SpaceShip(randSX, randSY, randSZ, this->meshSpaceShip, this);
	//push it to vector
	m_SpaceShips.push_back(newObject);
	if(m_bFirstTimeSpaceShip) //m_bFirstTimeSpaceShip
	{
		m_iSpaceshipID = m_SpaceShips[0]->generateID();
		/*cout<< "SpaceShip : " << m_iSpaceshipID <<endl;*/

		m_iSpaceshipIDNoText = m_SpaceShips[0]->generateIDNoText();
		//cout<< "SpaceShip NOTEXT: " << m_iSpaceshipIDNoText << endl;
		m_bFirstTimeSpaceShip = false;
	}

	randSX = 8.0;
	randSZ = 0.0;
	SpaceShip* newArriveObject = new SpaceShip(randSX, randSY, randSZ, this->meshSpaceShip, this);
	m_SpaceShips.push_back(newArriveObject);


	for(int i = 0; i< m_SpaceShips.size(); i++)
	{

		m_Vehilces.push_back(m_SpaceShips[i]->getVehicle());

		//m_pCellSpace->AddEntity(m_SpaceShips[i]->getVehicle());
	}

	m_bFirtTime = false;
	

	//SEEK ON
	m_SpaceShips[0]->getVehicle()->Steering()->SeekOn();
	m_SpaceShips[0]->getVehicle()->Steering()->SetTarget(Vector3D(4,0,6));
	
	//Arive ON
	m_SpaceShips[1]->getVehicle()->Steering()->ArriveOn();
	m_SpaceShips[1]->getVehicle()->Steering()->SetTarget(Vector3D(4,0,6));

	m_bEnter = false;
	m_bStartScreen = false;
	m_iCount =	0;

	m_bRenderMode = false;

	m_iMissileType = 2;

	m_iNoCross = 0;
	m_iTankDestroy = 0;
	m_iSpaceShipDestroy = 0;
	m_iAircraftDestroy  = 0;

}

void GameWorld::CreateGameWorldWander()
{

}

void GameWorld::CreateGameWorldFlocking()
{
	int NoTank = 1;
	int NoSpaceShip = 1000;
	int NoAirCraft = 2;
	int NoTrees	   = 0;
	
	m_bPressedFired = false;
	m_bPressedLeft = false;
	m_bPressedRight = false;
	m_bPressedUp = false;
	m_bPressedDown = false;
	
	this->cameraTargetX = 0.0f;
	this->cameraTargetY = 0.0f;
	this->cameraTargetZ = 0.0f;
	
	//POINTs
	Vector3D pointPos0(-3,0,3);
	Point* newPoint0 = new Point(-3, 0, -3);
	Point* newPoint1 = new Point(0,0,-3);
	Point* newPoint2 = new Point(3,0,-3);
	Point* newPoint3 = new Point(3,0,0);
	Point* newPoint4 = new Point(3,0,3);
	Point* newPoint5 = new Point(0,0,3);
	Point* newPoint6 = new Point(-3,0,3);
	Point* newPoint7 = new Point(-3,0, 0);
	m_Points.push_back(newPoint0);
	m_Points.push_back(newPoint1);
	m_Points.push_back(newPoint2);
	m_Points.push_back(newPoint3);
	m_Points.push_back(newPoint4);
	m_Points.push_back(newPoint5);
	m_Points.push_back(newPoint6);
	m_Points.push_back(newPoint7);

	
	//CellSpacePartition
	//if(m_bFirtTime)
	//{
	//	m_pCellSpace = new CellSpacePartition<Vehicle*>(80.0, 80.0, 80.0, 10, 10, 10, 1000); //these paras can be written from a file
	//	
	//}

	//Create Tree
	Mesh tempMeshTree = meshTree2;
	float randTreeX = 1.0f;
	float randTreeY = 0.0f;
	float randTreeZ = 2.0f;
	int	  treeType  = 2;
	float scaleTree     = 0.05;
	for(int i = 0; i< NoTrees; i++)
	{

		if(treeType == 1)
		{
			tempMeshTree = meshTree2;
			treeType = 2;
			scaleTree= 0.05;
		}
		else
		{
			tempMeshTree = meshTree1;
			treeType = 1;
			scaleTree= 0.01;
		}

		Tree* newTree = new Tree(randTreeX, randTreeY, randTreeZ, tempMeshTree, this, scaleTree);
		
		m_Trees.push_back(newTree);
		
		randTreeX = RandIn(-10.0, 10.0);
		
		randTreeZ = RandIn(0.0, 10.0f);
		
	}

	Tree* markTree = new Tree(4, 0, 6, tempMeshTree, this, scaleTree);
	m_Trees.push_back(markTree);

	////Create Tank
	//for(int i = 0; i< NoTank; i++)
	//{
	//	float randX = -2.0f; //-8.0
	//	float randY = 0.0f;
	//	float randZ = 2.0f;  //8.0

	//	//create Tank
	//	Tank* newTank	= new Tank(randX, randY, randZ, this->meshTank, this);
	//	//push it to vector
	//	m_Tanks.push_back(newTank);
	//	
	//	if(m_bFirtTime)
	//	{
	//		m_iTankID = newTank->generateID();

	//		m_iTankIDNoText = newTank->generateIDNoText();
	//	}
	//}
	
	float randSX = 0.0f;//7.0
	float randSY = 0.0f;
	float randSZ = 0.0f;//7.0
	//Create SpaceShip
	for(int i = 0; i< NoSpaceShip; i++)
	{
		//create spaceship
		SpaceShip* newObject = new SpaceShip(randSX, randSY, randSZ, this->meshSpaceShip, this);
		//push it to vector
		m_SpaceShips.push_back(newObject);

		if(m_bFirstTimeSpaceShip) //m_bFirstTimeSpaceShip
		{
			m_iSpaceshipID = m_SpaceShips[0]->generateID();
			cout<< "SpaceShip : " << m_iSpaceshipID <<endl;

			m_iSpaceshipIDNoText = m_SpaceShips[0]->generateIDNoText();
			cout<< "SpaceShip NOTEXT: " << m_iSpaceshipIDNoText << endl;
			m_bFirstTimeSpaceShip = false;
		}
		
		//randSX += 1.5;
		randSX = RandIn(-5, 5);
		randSY = RandIn(-5, 5);
		randSZ = RandIn(-5, 5);
	}
	
	//if(m_bFirtTime)
	//{
		for(int i = 0; i< m_SpaceShips.size(); i++)
		{
			
			m_Vehilces.push_back(m_SpaceShips[i]->getVehicle());
			
			//m_pCellSpace->AddEntity(m_SpaceShips[i]->getVehicle());
		}

		//for(int i = 0; i< m_SpaceShips.size(); i++)
		//{

		//	m_Vehilces.push_back(m_SpaceShips[i]->getVehicle());

		//	//m_pCellSpace->AddEntity(m_SpaceShips[i]->getVehicle());
		//}
		//
		//cout<< "Number of Vehicles: "<< m_Vehilces.size();
		m_bFirtTime = false;
	//}

	//---------FLOCKING----------------------
	int sizeVehicle = m_SpaceShips.size();
	for(int i= 0; i< m_SpaceShips.size(); i++)
	{
		m_SpaceShips[i]->getVehicle()->Steering()->FlockingOn();
		//m_SpaceShips[i]->getVehicle()->Steering()->ToggleSpacePartitioningOnOff();
	}

	//m_SpaceShips[2]->getVehicle()->Steering()->PursuitOn(m_SpaceShips[0]->getVehicle());
	//m_SpaceShips[sizeVehicle-1]->getVehicle()->Steering()->WanderOn();
	//m_SpaceShips[i]->getVehicle()->Steering()->WanderOn();

	//m_SpaceShips[0]->getVehicle()->Steering()->ArriveOn();
	//m_SpaceShips[0]->getVehicle()->Steering()->SeekOn();

	//m_SpaceShips[i]->getVehicle()->Steering()->PursuitOn(m_SpaceShips[0]->getVehicle());
	//m_SpaceShips[i]->getVehicle()->Steering()->AlignmentOn();
	//m_SpaceShips[i]->getVehicle()->Steering()->EvadeOn(m_SpaceShips[sizeVehicle-1]->getVehicle()); 
	//sizeVehicle-1


	//------------SNAKE---------------------------
	//m_SpaceShips[0]->getVehicle()->Steering()->WanderOn(); //PathFollowingOn ---> better visual effect
	//for(int i = 1; i< 10; i++)
	//{
	//	
	//	m_SpaceShips[i]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[i-1]->getVehicle(), Vector3D(0,0, -0.3));
	//}

	
	//OFFSET PURSUIT & PURSUIT
	/*m_SpaceShips[0]->getVehicle()->Steering()->WanderOn();
	m_SpaceShips[1]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(0.5, 0, -0.5));
	m_SpaceShips[2]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(-0.5, 0, -0.5));
	m_SpaceShips[3]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(0, 0, -0.5));
	m_SpaceShips[4]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(0, 0, -1.0));
	m_SpaceShips[5]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(1.0, 0, -1.0));
	m_SpaceShips[6]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(-1.0, 0, -1.0));
	m_SpaceShips[7]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(-1.5, 0, -1.5));
	m_SpaceShips[8]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[0]->getVehicle(), Vector3D(1.5, 0, -1.5));*/
	
	//m_SpaceShips[1]->getVehicle()->Steering()->PursuitOn(m_SpaceShips[0]->getVehicle());
		
	//PATH+ SNAKE
	//m_SpaceShips[0]->getVehicle()->Steering()->FollowPathOn();
	//for(int i = 1; i< m_SpaceShips.size(); i++)
	//{
	//	m_SpaceShips[i]->getVehicle()->Steering()->FollowPathOn();
	//	//m_SpaceShips[i]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[i-1]->getVehicle(), Vector3D(0,0, 1.0));
	//}


	//SPecial + Game
	//for(int i = 0; i< m_SpaceShips.size(); i++)
	//{
	//	//m_SpaceShips[i]->getVehicle()->Steering()->
	//}
	

	//Create Turret
	float turretPosX = 0.0f;
	float turretPosY = 0.0f;
	float turretPosZ = 0.0f;
	Turret* newTurret = new Turret(turretPosX, turretPosY, turretPosZ, this->meshTurretBarrel, this->meshTurretBase, this);
	m_Turrets.push_back(newTurret);
	
	if(m_bFirtTime)
	{
		m_Turrets[0]->generateIDBase(); 
		m_Turrets[0]->generateIDBarrel();
		m_Turrets[0]->generateIDBaseNoText();
		m_Turrets[0]->generateIDBarrelNoText();

		
		m_iTurretBaseID			= m_Turrets[0]->getIDBase();		cout<< "TurretBase: "<< m_iTurretBaseID<< endl;
		m_iTurretBaseIDNoText	= m_Turrets[0]->getIDBaseNoText();	cout<< "TurretBaseNoTEXT : " << m_iTurretBaseIDNoText <<endl;
		m_iTurretBarrelID		= m_Turrets[0]->getIDBarrel();		cout<< "TurretBarrel: "<< m_iTurretBarrelID<<endl;
		m_iTurretBarrelNoTextID	= m_Turrets[0]->getIDBarrelNoText();cout<< "TurretBarrelNOTEXT : "<< m_iTurretBarrelNoTextID<<endl;
	
	}

	//float randAX = 0.0f;
	//float randAY = 0.0f;
	//float randAZ = 3.0f;//9.0
	//int	  type  = 1;
	//Mesh  tempMesh;
	////Create Aircraft
	//for(int i = 0; i< NoAirCraft; i++)
	//{
	//	
	//	 // 1- airCraftMesh1 ; 2- airCraftMesh2;
	//	
	//	//create Aircraft
	//	switch( type)
	//	{
	//	case 1:
	//		tempMesh = this->meshAir1;
	//		break;
	//	case 2:
	//		tempMesh = this->meshAir2;
	//		break;
	//	}

	//	Aircraft* newAir = new Aircraft(randAX, randAY, randAZ, tempMesh, this, type);
	//	
	//	/*if(m_bFirtTime)
	//	{
	//		if(type == 1)
	//		{
	//			newAir->generateAircraft1();
	//			m_iAircraft1ID = newAir->getAircraft1ID();
	//		}
	//		if(type == 2)
	//		{
	//			newAir->generateAircraft2();
	//			m_iAircraft2ID = newAir->getAircraft2ID();
	//		}
	//		
	//	}*/
	//	
	//	newAir->generateID();
	//	newAir->generateIDNoText();

	//	if(type == 1)
	//	{
	//		//newAir->generateAircraft1();
	//		m_iAircraft1ID = newAir->getAircraft1ID();
	//		m_iAircraft1IDNoText = newAir->getAircraft1NoTextID();
	//	}
	//	if(type == 2)
	//	{
	//		//newAir->generateAircraft2();
	//		m_iAircraft2ID = newAir->getAircraft2ID();
	//		m_iAircraft2IDNoText = newAir->getAircraft2NoTextID();
	//	}

	//	//push it to vector
	//	m_Aircrafts.push_back(newAir);
	//	
	//	type = 2;
	//	randAY += 1.0;
	//}
	


	

	


	////Missiles
	//float missilePosX =-3.0f;
	//float missilePosY = 0.0f;
	//float missilePosZ = -3.0f;
	//Missile* newMissile = new Missile(missilePosX, missilePosY, missilePosZ, this->meshMissile, this);
	//m_Missiles.push_back(newMissile);
	//

	//float tempX = 2.0f;
	//float tempY = 0.0f;
	//float tempZ = 2.0f;
	//Missile* newMissile1 = new Missile(tempX, tempY, tempZ, this->meshMissile, this);
	//m_Missiles.push_back(newMissile1);

	//tempX = -1.0f;
	//tempY = 0.0f;
	//tempZ = -1.0f;
	//Missile* newMissile2 = new Missile(tempX, tempY, tempZ, this->meshMissile, this);
	//m_Missiles.push_back(newMissile2);
	
	

	m_bFirtTime = false;

	m_bEnter = false;
	m_bStartScreen = false;
	m_iCount =	0;

	m_bRenderMode = false;
	
	m_iMissileType = 2;

	m_iNoCross = 0;
	m_iTankDestroy = 0;
	m_iSpaceShipDestroy = 0;
	m_iAircraftDestroy  = 0;

}

void GameWorld::CreateGameWorldObstacleAvoidance()
{

}


void GameWorld::CreateGameWorldSpecialModeUnfair()
{


	int NoTrees	   = 0;
	int NoSpaceShip = 13;

	m_bPressedFired = false;
	m_bPressedLeft = false;
	m_bPressedRight = false;
	m_bPressedUp = false;
	m_bPressedDown = false;
	
	this->cameraTargetX = 0.0f;
	this->cameraTargetY = 0.0f;
	this->cameraTargetZ = 0.0f;
	
	//POINTs
	Vector3D pointPos0(-3,0,3);
	Point* newPoint0 = new Point(5, 0, 0);
	Point* newPoint1 = new Point(4.325, 0, 2.5);
	Point* newPoint2 = new Point(2.5, 0, 4.325);
	Point* newPoint3 = new Point(0,0,5);
	Point* newPoint4 = new Point(-2.5, 0, 4.325);
	Point* newPoint5 = new Point(-4.325, 0, 2.5);
	Point* newPoint6 = new Point(-5, 0, 0);
	Point* newPoint7 = new Point(-4.325, 0, -2.5);
	Point* newPoint8 = new Point(-2.5, 0, -4.325);
	Point* newPoint9 = new Point(0, 0, -5); 
	Point* newPoint10= new Point(2.5, 0, -4.325);
	Point* newPoint11= new Point(4.325, 0, -2.5);
	m_Points.push_back(newPoint0);
	m_Points.push_back(newPoint1);
	m_Points.push_back(newPoint2);
	m_Points.push_back(newPoint3);
	m_Points.push_back(newPoint4);
	m_Points.push_back(newPoint5);
	m_Points.push_back(newPoint6);
	m_Points.push_back(newPoint7);
	m_Points.push_back(newPoint8);
	m_Points.push_back(newPoint9);
	m_Points.push_back(newPoint10);
	m_Points.push_back(newPoint11);

	
	//CellSpacePartition
	//if(m_bFirtTime)
	//{
	//	m_pCellSpace = new CellSpacePartition<Vehicle*>(80.0, 80.0, 80.0, 10, 10, 10, 1000); //these paras can be written from a file
	//	
	//}

	//Create Tree
	Mesh tempMeshTree = meshTree2;
	float randTreeX = 1.0f;
	float randTreeY = 0.0f;
	float randTreeZ = 2.0f;
	int	  treeType  = 2;
	float scaleTree     = 0.05;
	for(int i = 0; i< NoTrees; i++)
	{

		if(treeType == 1)
		{
			tempMeshTree = meshTree2;
			treeType = 2;
			scaleTree= 0.05;
		}
		else
		{
			tempMeshTree = meshTree1;
			treeType = 1;
			scaleTree= 0.01;
		}

		Tree* newTree = new Tree(randTreeX, randTreeY, randTreeZ, tempMeshTree, this, scaleTree);
		
		m_Trees.push_back(newTree);
		
		randTreeX = RandIn(-10.0, 10.0);
		randTreeZ = RandIn(0.0, 10.0f);
		
	}

	Tree* markTree = new Tree(4, 0, 6, tempMeshTree, this, scaleTree);
	m_Trees.push_back(markTree);

	
	//Starting Pos
	//Vector3D point1(10, 0, 0);
	//Vector3D point2(8.65, 0, 5);
	//Vector3D point3(5, 0, 8.65);
	//Vector3D point4(0, 0, 10);
	//Vector3D point5(-5, 0, 8.65);
	//Vector3D point6(-8.65, 0, 5);
	//Vector3D point7(-10, 0, 0);
	//Vector3D point8(-8.65, 0, -5);
	//Vector3D point9(-5, 0, -8.65);
	//Vector3D point10(0, 0 , -10);
	//Vector3D point11(5, 0, -8.65);
	//Vector3D point12(8.65, 0, -5);
	//std::vector<Vector3D> listPoint;
	//listPoint.push_back(point1);
	//listPoint.push_back(point2);
	//listPoint.push_back(point3);
	//listPoint.push_back(point4);
	//listPoint.push_back(point5);
	//listPoint.push_back(point6);
	//listPoint.push_back(point7);
	//listPoint.push_back(point8);
	//listPoint.push_back(point9);
	//listPoint.push_back(point10);
	//listPoint.push_back(point11);
	//listPoint.push_back(point12);
	
	Vector3D point1(-9,0,-9);
	Vector3D point2(0,0,-10);
	Vector3D point3(9,0,-9);
	Vector3D point4(9,0,9);
	Vector3D point5(0,0,10);
	Vector3D point6(-9,0,9);
	Vector3D point7(-10,0,0);
	Vector3D point8(10, 0,0);
	std::vector<Vector3D> listPoint;
	listPoint.push_back(point1);
	listPoint.push_back(point2);
	listPoint.push_back(point3);
	listPoint.push_back(point8);
	listPoint.push_back(point4);
	listPoint.push_back(point5);
	listPoint.push_back(point6);
	listPoint.push_back(point7);
	listPoint.push_back(point8);


	float randSX = 10.00f;//7.0
	float randSY = 0.0f;
	float randSZ = 0.0f;//7.0
	//Create SpaceShip
	for(int i = 0; i< NoSpaceShip; ++i)
	{
			//create spaceship
			SpaceShip* newObject = new SpaceShip(randSX, randSY, randSZ, this->meshSpaceShip, this);
			//push it to vector
			m_SpaceShips.push_back(newObject);

			if(m_bFirstTimeSpaceShip) //m_bFirstTimeSpaceShip
			{
				m_iSpaceshipID = m_SpaceShips[0]->generateID();
				cout<< "SpaceShip : " << m_iSpaceshipID <<endl;

				m_iSpaceshipIDNoText = m_SpaceShips[0]->generateIDNoText();
				cout<< "SpaceShip NOTEXT: " << m_iSpaceshipIDNoText << endl;
				m_bFirstTimeSpaceShip = false;
			}
			
			

			/*if(i > 7){
			
				randSX = RandInRange(-8, 8);
				randSZ = RandInRange(-9, 9);
				
			}
			else
			{
				randSX = listPoint[i].x;
				randSZ = listPoint[i].z;
			}

			if(i == 12)
			{
				randSX = 0.0;
				randSZ = 0.0;
			}*/
			
			randSX = RandInRange(-10, 10);
			randSZ = RandInRange(-10, 10);
	}
	
	//if(m_bFirtTime)
	//{
		for(int i = 0; i< m_SpaceShips.size(); i++)
		{
			
			m_Vehilces.push_back(m_SpaceShips[i]->getVehicle());
			
			//m_pCellSpace->AddEntity(m_SpaceShips[i]->getVehicle());
		}
		
	//	cout<< "Number of Vehicles: "<< m_Vehilces.size();
		m_bFirtTime = false;
	//}


	//PATH+ SNAKE
	//m_SpaceShips[0]->getVehicle()->Steering()->FollowPathOn();
	for(int i = 0; i< m_SpaceShips.size(); i++)
	{
		m_SpaceShips[i]->getVehicle()->Steering()->FollowPathOn();
		m_SpaceShips[i]->getVehicle()->Steering()->SeparationOn();
		//m_SpaceShips[i]->getVehicle()->Steering()->OffsetPursuitOn(m_SpaceShips[i-1]->getVehicle(), Vector3D(0,0, 1.0));
	}

	m_bFirtTime = false;

	m_bEnter = false;
	m_bStartScreen = false;
	m_iCount =	0;

	m_bRenderMode = false;
	
	m_iMissileType = 2;

	m_iNoCross = 0;
	m_iTankDestroy = 0;
	m_iSpaceShipDestroy = 0;
	m_iAircraftDestroy  = 0;


}

void GameWorld::CreateGameWorldUnPredictableMode()
{


}