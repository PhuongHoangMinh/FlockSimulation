#ifndef GAMEWORLD_H
#define GAMEWORLD_H

//#include "ProcessFileClass.h"
#include "SpaceShip.h"
#include "Tank.h"
#include "Turret.h"
#include "Aircraft.h"
#include <vector>
#include "Missile.h"
#include "Tree.h"
#include "BaseGameEntity.h"
#include "MovingEntity.h"
#include "Obstacle.h"
#include "Vehicle.h"
#include "EntityFunctionTemplates.h"
#include <iostream>
#include <cstdlib>
using namespace std;
#include "Matrices.h"
#include "CellSpacePartition.h"
#include "Point.h"

class Missile;
class SpaceShip;
class Tank;
class Turret;
class Aircraft;
class ProcessFile;
class Tree;
class BaseGameEntity;
class MovingEntity;
class Obstacle;
class Vehicle;
class Point;
//class CellSpacePartition<Vehicle*>;

////Max, Min Value for the cube box
//#define MaxX	0.0f; 
//#define MinX	0.0f;
//#define MaxY	0.0f;
//#define MinY	0.0f;
//#define MaxZ	0.0f;
//#define MinZ	0.0f;

class GameWorld
{
private:
	std::vector<SpaceShip*> m_SpaceShips;
	std::vector<Tank*>		m_Tanks;
	std::vector<Aircraft*>  m_Aircrafts;
	std::vector<Turret*>	m_Turrets;
	std::vector<Missile*>	m_Missiles;
	std::vector<Tree*>		m_Trees;

	std::vector<BaseGameEntity*>  m_Obstacles;
	std::vector<Vehicle*>		  m_Vehilces;

	std::vector<Point*>			  m_Points;

	int						m_iGameMode;
	int						m_iRenderingMode;

	int						m_iCount;
	
	CellSpacePartition<Vehicle*>*  m_pCellSpace;

	
	void CreateGameWorld();
	void ClearGameWorld();

	//Create GameWorld for different Mode
	void CreateGameWorldOffsetPursuit();
	void CreateGameWorldSnake();
	void CreateGameWorldSpecialMode();
	void CreateGameWorldSeek();
	void CreateGameWorldWander();
	void CreateGameWorldFlocking();
	void CreateGameWorldObstacleAvoidance();
	void CreateGameWorldSpecialModeUnfair(); // square path with circle shape seats
	void CreateGameWorldUnPredictableMode();

	Mesh					meshAir1;
	Mesh					meshAir2;
	Mesh					meshTank;
	Mesh					meshTurretBase;
	Mesh					meshTurretBarrel;
	Mesh					meshMissile;
	Mesh					meshSpaceShip;
	Mesh					meshTree1;
	Mesh					meshTree2;

	int					m_iTankID;
	int					m_iTankIDNoText;
	//void					setTankID(int value){m_iTankID = value;}
	//void					setTankIDNoText(int value){m_iTankIDNoText = value;}

	int					m_iAircraft1ID;
	int					m_iAircraft1IDNoText;

	int					m_iAircraft2ID;
	int					m_iAircraft2IDNoText;

	int					m_iSpaceshipID;
	int					m_iSpaceshipIDNoText;
	//void					setSpaceID(int value ) ;

	int					m_iTurretBaseID;
	int					m_iTurretBaseIDNoText;

	int					m_iTurretBarrelID;
	int					m_iTurretBarrelNoTextID;

	bool					m_bPressedFired;
	bool					m_bPressedLeft;
	bool					m_bPressedRight;
	bool					m_bPressedUp;
	bool					m_bPressedDown;

	int						m_bSpecialMode;//SPECIAL MODE: special = 1 - start mode, special = 2 --> Finding position, special = 0 - default - NO special mode

	float					cameraTargetX;
	float					cameraTargetY;
	float					cameraTargetZ;
	
	void drawString(const char *str, int x, int y, float color[4], void *font = GLUT_BITMAP_8_BY_13)
	{
		glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
		glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
		glDisable(GL_TEXTURE_2D);

		glColor4fv(color);          // set text color
		glRasterPos2i(x, y);        // place text position

		// loop all characters in the string
		while(*str)
		{
			glutBitmapCharacter(font, *str);
			++str;
		}

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glPopAttrib();
	}

public:
	GameWorld(Mesh airMesh1, 
			 Mesh airMesh2, 
			 Mesh tankMesh, 
			 Mesh turrelBaseMesh, 
			 Mesh turrelBarrelMesh, 
			 Mesh missileMesh, 
			 Mesh spaceShipMesh,
			 Mesh treeMesh1,
			 Mesh treeMesh2): meshAir1(airMesh1), 
								  meshAir2(airMesh2), 
								  meshTank(tankMesh), 
								  meshTurretBase(turrelBaseMesh), 
								  meshTurretBarrel(turrelBarrelMesh), 
								  meshMissile(missileMesh),
								  meshSpaceShip(spaceShipMesh),
								  meshTree1(treeMesh1),
								  meshTree2(treeMesh2)
	{
		m_bFirtTime = true;
		m_bFirstTimeSpaceShip = true;

		//CreateGameWorld();
		
		m_iGameMode = 1;
		m_iRenderingMode = 0;
	}
	
	//Drawing all Virtual elements on game
	void Render();
	//Updating all states of objects in game
	void Update();


	bool					m_bEnter; // play
	bool					m_bStartScreen;// back to startScreen
	
	int						m_iMissileType;

	int						m_iNoCross;
	int						m_iTankDestroy;
	int						m_iSpaceShipDestroy;
	int						m_iAircraftDestroy;

	bool					m_bFirtTime;
	bool					m_bFirstTimeSpaceShip;
	
	//bool					getFirstTime()const {return m_bFirtTime;}
	bool					m_bRenderMode;

	const std::vector<SpaceShip*>&	SpaceShips()const{return m_SpaceShips;}
	const std::vector<Tank*>&		Tanks()const{return m_Tanks;}
	const std::vector<Aircraft*>&	Aircrafts()const{return m_Aircrafts;}
	const std::vector<Turret*>&		Turrets()const{return m_Turrets;}
	const std::vector<Missile*>&	Missiles()const{return m_Missiles;}
	
	const std::vector<Vehicle*>&	Agents(){return m_Vehilces;}
	CellSpacePartition<Vehicle*>*	CellSpace(){return m_pCellSpace;}

	const std::vector<Point*>&		Points(){return m_Points;}
	int	  NoPointOccupied()const 
	{
		int NoOccupied = 0;
		for(int i = 0; i< m_Points.size(); i++)
		{
			if(m_Points[i]->isOccupied())
			{
				NoOccupied++;
			}
		}
		return NoOccupied;
	}	  

	bool  isPressedFired()const{return m_bPressedFired;}
	bool  isPressedUp()const {return m_bPressedUp;}
	bool  isPressedDown()const{return m_bPressedDown;}
	bool  isPressedLeft()const{return m_bPressedLeft;}
	bool  isPressedRight()const{return m_bPressedRight;}

	int  isSpecialMode()const{return m_bSpecialMode;}
	void  setSpecialMode(int val){ m_bSpecialMode = val;}

	void  setPressedFired(bool val) {m_bPressedFired = val;}
	void  setPressedUp(bool val)	{m_bPressedUp = val;}
	void  setPressedDown(bool val)	{m_bPressedDown = val;}
	void  setPressedLeft(bool val)	{m_bPressedLeft = val;}
	void  setPressedRight(bool val) {m_bPressedRight = val;}

	void  setNoCross(int val) {m_iNoCross = val;}
	int	  getNoCross()const {return m_iNoCross;}

	/*void  setSpaceshipNoTextID(int value)*/

	float getCameraTargetX()const {return cameraTargetX;}
	float getCameraTargetY()const {return cameraTargetY;}
	float getCameraTargetZ()const {return cameraTargetZ;}

	int getMode()const{return m_iGameMode;}
	void setMode(int value) { m_iGameMode = value;}
	
	int getRenderingMode()const{return m_iRenderingMode;}
	void setRenderingMode(int val){ m_iRenderingMode = val;}

	//Tag neigbor
	void TagVehiclesWithinViewRange(BaseGameEntity* pVehicle, double range)
	{
		TagNeighbors(pVehicle, m_Vehilces ,range);
		
		/*int count = 0;
		for(int i = 0; i< m_Vehilces.size(); i++)
		{
			if(m_Vehilces[i]->IsTagged())
			{
				count++;
			}
		}
		cout<< "Tagged " << count << endl;*/
	}

	//Tag Obstacles
	void TagObstaclesWithinViewRange(BaseGameEntity* pVehicle, double range)
	{
		TagNeighbors(pVehicle, m_Obstacles, range);
	}

	//Random Float in Range
	float RandIn(float a, float b)
	{
		return a + RandFloat()*(b-a);
	}

	float RandFloat(){
		
		return (rand()/ (RAND_MAX + 1.0));
	}


	void showInfoStart()
	{

		float color[4] = {1, 1, 1, 1};
		int SCREEN_WIDTH = 640;
		int SCREEN_HEIGHT= 480;

		int screenWidth = SCREEN_WIDTH;
		int screenHeight = SCREEN_HEIGHT;

		int TEXT_WIDTH		= 8;
		int TEXT_HEIGHT	    = 13;

		// backup current model-view matrix
		glPushMatrix();                     // save current modelview matrix
		glLoadIdentity();                   // reset modelview matrix

		// set to 2D orthogonal projection
		glMatrixMode(GL_PROJECTION);        // switch to projection matrix
		glPushMatrix();                     // save current projection matrix
		glLoadIdentity();                   // reset projection matrix
		gluOrtho2D(0, screenWidth, 0, screenHeight); // set to orthogonal projection

		drawString("Press F5- Start Playing -- please PRESS 5-gouraud shading to SPEED UP", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT, color, GLUT_BITMAP_8_BY_13);
		drawString("Press F12- About Screen", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*2, color, GLUT_BITMAP_8_BY_13);
		drawString("Exit - Press Esc", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*3, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 7 to start SEEK mode", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*4, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 8 to start OFFSET PURSUIT mode ", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*5, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 9 to start Fun FACE- offset pursuit mode ", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*6, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 0 to start SPECIAL GAME mode -- PRess 6 to start LOOKING for its position", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*7, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 'q' to start FLOCKING mode  ", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*8, color, GLUT_BITMAP_8_BY_13);
		drawString("Use LEFT Mouse to change the view of viewer (Press & Move)", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*9, color, GLUT_BITMAP_8_BY_13);
		drawString("Use RIGHT Mouse to ZOOM IN & ZOOM OUT (Press & Move) ", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*10, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 1 - WIRE FRAME mode ", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*11, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 2 - WIRE FRAME mode with HSR", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*12, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 3 - Flat Shading mode ", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*13, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 4 - Gouraud Shading mode ", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*14, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 5 - Gouraud Shading mode with Texture Mapping-- NOTE -- Choose it to SPEED UP", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*15, color, GLUT_BITMAP_8_BY_13);



		// restore projection matrix
		glPopMatrix();                   // restore to previous projection matrix

		// restore modelview matrix
		glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
		glPopMatrix();                   // restore to previous modelview matrix
	}

	void showInfoAbout()
	{

		float color[4] = {1, 1, 1, 1};
		int SCREEN_WIDTH = 640;
		int SCREEN_HEIGHT= 480;

		int screenWidth = SCREEN_WIDTH;
		int screenHeight = SCREEN_HEIGHT;

		int TEXT_WIDTH		= 8;
		int TEXT_HEIGHT	    = 13;

		// backup current model-view matrix
		glPushMatrix();                     // save current modelview matrix
		glLoadIdentity();                   // reset modelview matrix

		// set to 2D orthogonal projection
		glMatrixMode(GL_PROJECTION);        // switch to projection matrix
		glPushMatrix();                     // save current projection matrix
		glLoadIdentity();                   // reset projection matrix
		gluOrtho2D(0, screenWidth, 0, screenHeight); // set to orthogonal projection

		drawString("Author- OrbitTeam: Hoang Minh Phuong, Park Jinha", screenWidth/3, SCREEN_HEIGHT/2 - TEXT_HEIGHT, color, GLUT_BITMAP_8_BY_13);
		drawString("FLOCKING - TERM PROJECT",  screenWidth/3, SCREEN_HEIGHT/2 - TEXT_HEIGHT*2, color, GLUT_BITMAP_8_BY_13 );
		drawString("Press F4- To Menu Screen", screenWidth/3, SCREEN_HEIGHT/2 - TEXT_HEIGHT*3, color, GLUT_BITMAP_8_BY_13);
		drawString("Exit - Press Esc", screenWidth/3, SCREEN_HEIGHT/2 - TEXT_HEIGHT*4, color, GLUT_BITMAP_8_BY_13);

		// restore projection matrix
		glPopMatrix();                   // restore to previous projection matrix

		// restore modelview matrix
		glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
		glPopMatrix();                   // restore to previous modelview matrix
	}
	
	void showInfoOnPlay()
	{
		float color[4] = {1, 1, 1, 1};
		int SCREEN_WIDTH = 640;
		int SCREEN_HEIGHT= 480;

		int screenWidth = SCREEN_WIDTH;
		int screenHeight = SCREEN_HEIGHT;

		int TEXT_WIDTH		= 8;
		int TEXT_HEIGHT	    = 13;
		
		char		bufCross[12];
		char		bufMissileType[12];

		itoa(m_iNoCross ,bufCross,10);
		itoa(m_iMissileType, bufMissileType, 10);

		// backup current model-view matrix
		glPushMatrix();                     // save current modelview matrix
		glLoadIdentity();                   // reset modelview matrix

		// set to 2D orthogonal projection
		glMatrixMode(GL_PROJECTION);        // switch to projection matrix
		glPushMatrix();                     // save current projection matrix
		glLoadIdentity();                   // reset projection matrix
		gluOrtho2D(0, screenWidth, 0, screenHeight); // set to orthogonal projection


		drawString("Press 7 then Press F4 to start SEEK mode ", 0, SCREEN_HEIGHT - TEXT_HEIGHT, color, GLUT_BITMAP_8_BY_13);
		//drawString(bufCross, 100, SCREEN_HEIGHT - TEXT_HEIGHT, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 8 then Press F4 to start Offset Pursuit Mode", 0, SCREEN_HEIGHT - TEXT_HEIGHT*2, color, GLUT_BITMAP_8_BY_13 );
		//drawString(bufMissileType, 150, SCREEN_HEIGHT - TEXT_HEIGHT*2, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 9 then Press F4 to start FUN FACE Offset Pursuit Mode", 0, SCREEN_HEIGHT - TEXT_HEIGHT*3, color, GLUT_BITMAP_8_BY_13 );
		drawString("Press 0 then Press F4 to start SPECIAL game mode --> THEN PRESS 6 whenever you want", 0, SCREEN_HEIGHT - TEXT_HEIGHT*4, color, GLUT_BITMAP_8_BY_13 );
		drawString("Press 'u' then Press F4 to start SPECIAL game mode (random position) --> Then Press 6 to ask birds looking for its positions", 0, SCREEN_HEIGHT - TEXT_HEIGHT*5, color, GLUT_BITMAP_8_BY_13 );
		drawString("Press 'q' then Press F4 to start FLOCKING Mode", 0, SCREEN_HEIGHT - TEXT_HEIGHT*6, color, GLUT_BITMAP_8_BY_13 );
		drawString("PRESS F4 to RESTART this mode ", 0, SCREEN_HEIGHT - TEXT_HEIGHT*7, color, GLUT_BITMAP_8_BY_13 );
		drawString("Press 1, 2, 3, 4, or 5 to switch Mode: wire_frame, HSR, Flat shading, Gouraund Shading, Texture Mapping",  0, SCREEN_HEIGHT - TEXT_HEIGHT*8, color, GLUT_BITMAP_8_BY_13);


		// restore projection matrix
		glPopMatrix();                   // restore to previous projection matrix

		// restore modelview matrix
		glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
		glPopMatrix();                   // restore to previous modelview matrix
	
	}

	void showInstruction()
	{
		float color[4] = {1, 1, 1, 1};
		int SCREEN_WIDTH = 640;
		int SCREEN_HEIGHT= 480;

		int screenWidth = SCREEN_WIDTH;
		int screenHeight = SCREEN_HEIGHT;

		int TEXT_WIDTH		= 8;
		int TEXT_HEIGHT	    = 13;

		// backup current model-view matrix
		glPushMatrix();                     // save current modelview matrix
		glLoadIdentity();                   // reset modelview matrix

		// set to 2D orthogonal projection
		glMatrixMode(GL_PROJECTION);        // switch to projection matrix
		glPushMatrix();                     // save current projection matrix
		glLoadIdentity();                   // reset projection matrix
		gluOrtho2D(0, screenWidth, 0, screenHeight); // set to orthogonal projection

		drawString("Press 's' to fire missile", screenWidth/3, SCREEN_HEIGHT/2 - TEXT_HEIGHT, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 't' to change missile",  screenWidth/3, SCREEN_HEIGHT/2 - TEXT_HEIGHT*2, color, GLUT_BITMAP_8_BY_13 );
		drawString("Press 'Esc' to quit", screenWidth/3, SCREEN_HEIGHT/2 - TEXT_HEIGHT*3, color, GLUT_BITMAP_8_BY_13);
		drawString("Press 'F4' to return Menu Screen", screenWidth/3, SCREEN_HEIGHT/2 - TEXT_HEIGHT*4, color, GLUT_BITMAP_8_BY_13);

		// restore projection matrix
		glPopMatrix();                   // restore to previous projection matrix

		// restore modelview matrix
		glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
		glPopMatrix();                   // restore to previous modelview matrix
		
	}

	void showInfoGameOver()
	{

		float color[4] = {1, 1, 1, 1};
		int SCREEN_WIDTH = 640;
		int SCREEN_HEIGHT= 480;

		int screenWidth = SCREEN_WIDTH;
		int screenHeight = SCREEN_HEIGHT;

		int TEXT_WIDTH		= 8;
		int TEXT_HEIGHT	    = 13;

		char					bufTank[12];
		char					bufSpace[12];
		char					bufAircraft[12];
		
		/*sprintf(bufTank, "%f", m_iTankDestroy);
		sprintf(bufSpace, "%f", m_iSpaceShipDestroy);
		sprintf(bufAircraft, "%f", m_iAircraftDestroy);*/
		itoa(m_iTankDestroy, bufTank, 10);
		itoa(m_iSpaceShipDestroy, bufSpace, 10);
		itoa(m_iAircraftDestroy, bufAircraft, 10);

		// backup current model-view matrix
		glPushMatrix();                     // save current modelview matrix
		glLoadIdentity();                   // reset modelview matrix

		// set to 2D orthogonal projection
		glMatrixMode(GL_PROJECTION);        // switch to projection matrix
		glPushMatrix();                     // save current projection matrix
		glLoadIdentity();                   // reset projection matrix
		gluOrtho2D(0, screenWidth, 0, screenHeight); // set to orthogonal projection

		drawString("GameOver", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT, color, GLUT_BITMAP_8_BY_13);
		drawString("No of eliminated Tank",  screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*2, color, GLUT_BITMAP_8_BY_13 );
		drawString(bufTank, screenWidth/2 + 200, SCREEN_HEIGHT/2 - TEXT_HEIGHT*2, color, GLUT_BITMAP_8_BY_13);

		drawString("No of eliminated SpaceShip",  screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*3, color, GLUT_BITMAP_8_BY_13 );
		drawString(bufSpace, screenWidth/2 + 250, SCREEN_HEIGHT/2 - TEXT_HEIGHT*3, color, GLUT_BITMAP_8_BY_13);

		drawString("No of eliminated Aircraft",  screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*4, color, GLUT_BITMAP_8_BY_13 );
		drawString(bufAircraft, screenWidth/2 + 250, SCREEN_HEIGHT/2 - TEXT_HEIGHT*4, color, GLUT_BITMAP_8_BY_13);

		drawString("Press F4- To Menu Screen", screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*5, color, GLUT_BITMAP_8_BY_13);
		drawString("Exit - Press Esc",screenWidth/2, SCREEN_HEIGHT/2 - TEXT_HEIGHT*6, color, GLUT_BITMAP_8_BY_13);

		// restore projection matrix
		glPopMatrix();                   // restore to previous projection matrix

		// restore modelview matrix
		glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
		glPopMatrix();                   // restore to previous modelview matrix
	}
};

#endif