
#include <iostream>
#include "GameWorld.h"
#include "ProcessFileClass.h"
#include <math.h>
#include "Turret.h"
#include "Vectors.h"
#include "Matrices.h"
#include "Aircraft.h"
#include "SpaceShip.h"
#include "Tank.h"
#include "Missile.h"
#include "Bitmap.h"
#include "Transformations.h"
#include <stdio.h>
#include <ctime>
//#include <windows.h>
#include <gl/glut.h>
#include <gl/gl.h>



class Bitmap;
class GameWorld;
class Tank;
class SpaceShip;
class Aircraft;
class ProcessFile;
class Turret;
class Missile;

ProcessFile	testFile(2);
ProcessFile airCraft1(1);
ProcessFile airCraft2(2);
ProcessFile tank(3);
ProcessFile spaceship(4);
ProcessFile turret(5);
ProcessFile turretBase(6);
ProcessFile missile(7);
ProcessFile treeType1(8);
ProcessFile treeType2(9);
Bitmap		*bitmapFile;

FILE *textureFile = fopen("dirt3.bmp", "rb");
GLuint m_iTextID;

//Turret* myTurret;
//SpaceShip* mySpaceShip;
//Aircraft*  myAircraft1;
//Aircraft*  myAircraft2;
//Tank*	   myTank;
//Missile*   myMissile;
GameWorld* myGameWorld;
int viewMode = 1; // free view mode; = 2 FPS view mode
int renderMode = 1; // 1 - WIREFRAME, 2- WIREFRAME with HSR, 3-FLAT Shading, 4-Gouraud Shading, 5-Gouraud Shading with Texture


GLfloat cameraPosX = 1.0;
GLfloat cameraPosY = 1.0;
GLfloat cameraPosZ = 50.0;

GLuint id1;
GLuint id2; // aircraft2
GLuint idTank;
GLuint idSpaceship;
GLuint idTurret;

//Moving Camera
int width;
int height;

float centerX;
float centerY;

float  currentX;
float  currentY;

//float moveX = 0.0f;
//float moveY = 0.0f;

//GLUT CALLBACK functions
void displayCB();
void reshapeCB(int w, int h);
void timerCB(int millisec);
void idleCB();
void keyboardCB(unsigned char key, int x, int y);
void mouseCB(int button, int stat, int x, int y);
void mouseMotionCB(int x, int y);

//CALLBACK function when exit() called
void exitCB();

void initGL();
void initGLUT();
bool initSharedMem();
void clearSharedMem();
void initLights();
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
void drawString(const char *str, int x, int y, float color[4], void *font);
void drawString3D(const char *str, float pos[3], float color[4], void *font);
void showInfo();
void toOrtho();
void toPerspective();
void drawAxis(float size = 2.5f);
void drawGrid(float size = 10.0f, float step = 1.0f);
void drawModel();
void anglesToMatrix(const Vector3 angles, Matrix4& matrix);
Matrix4 setFrustum(float l, float r, float b, float t, float n, float f);
Matrix4 setFrustum(float fovY, float aspectRatio, float front, float back);
Matrix4 setOrthoFrustum(float l, float r, float b, float t, float n, float f);


// constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT= 480;
const float CAMERA_DISTANCE = 6.0f;
const int TEXT_WIDTH		= 8;
const int TEXT_HEIGHT	    = 13;
const float DEG2RAD			= 3.141493f/ 180;

//global variables
void  *font = GLUT_BITMAP_8_BY_13;
int   screenWidth;
int   screenHeight;
bool  mouseLeftDown;
bool  mouseRightDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance;
int   drawMode = 0;
Matrix4 matrixView;
Matrix4 matrixModel;
Matrix4 matrixModelView;
Matrix4 matrixProjection;
Matrix4 testMatrix;



//menu
void menu(int value)
{
	renderMode = value;
	glutPostRedisplay();
}


//display OpenGL callback
void display()
{
	//comment
	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//comment
	//glMatrixMode (GL_MODELVIEW);
	//glLoadIdentity();

	//gluLookAt(1.0, 1.0, 5.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(cameraPosX, cameraPosY, cameraPosZ, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0); //comment
	//setCamera(cameraPosX, cameraPosY, cameraPosZ, 1.0, 1.0, 0.0);

	glTranslatef(0.0, 0.0, 0.0);

	glColor3f(1.0, 0.0, 0.0);
	/*glBegin(GL_LINE_LOOP);
		glVertex3f(0.0, 1.0, -1.0);
		glVertex3f(0.5, - 0.5 * sqrt(3.), -1.0);
		glVertex3f(-0.5, -0.5 * sqrt(3.), -1.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.5, - 0.5 * sqrt(3.), -1.0);
		glVertex3f(-0.5, -0.5 * sqrt(3.), -1.0);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, -1.0);
		glVertex3f(-0.5, -0.5 * sqrt(3.), -1.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, -1.0);
		glVertex3f(0.5, - 0.5 * sqrt(3.), -1.0);
	glEnd();*/

	//COMMENT
	//myTurret->Render();
	//myMissile->Render();

	////myAircraft1->Render();
	////myAircraft2->Render();
	////myTank->Render();
	////mySpaceShip->Render();
	//if(myAircraft1->isFired())
	//{
	//
	//}
	//else
	//{
	//	glPushMatrix();
	//	glTranslatef(myAircraft1->getX(), myAircraft1->getY(), myAircraft1->getZ());
	//	glCallList(id1);
	//	glPopMatrix();
	//}

	//glCallList(idTank);
	//glCallList(idSpaceship);//END COMMENT
	
	myGameWorld->Render();

	//comment
	//glutSwapBuffers();
}

//init OpenGL callback
void init()
{
	/*width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);
	
	centerX = width/2;
	centerY = height/2;

	currentX = centerX;
	currentY = centerY;
	

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);*/
	
	//COMMENT
	cout<< "Triangles specification: "<< endl;
	testFile.readData();
	
	cout<< "Spaceship specification: "<< endl;
	spaceship.readData();
	
	cout<< "Tank specification: " << endl;
	tank.readData();
	
	cout<< "Aircraft specification: "<< endl;
	airCraft1.readData();
	
	cout<<"Aircraft 2 specification" <<endl;
	airCraft2.readData();

	cout<< "Turret specification: "<< endl;
	turret.readData();
	
	cout<< "Turret Base Specification"<< endl;
	turretBase.readData();
	
	cout<< "Missile Specification " << endl;
	missile.readData();

	cout<< "Tree Specifaction 1: " << endl;
	treeType1.readData();

	cout<< "Tree Specification 2: " << endl;
	treeType2.readData();

	
	if((!textureFile))
	{
		cout<< "FILE NOT FOUND...."<< endl;
	}
	else
	{	
		Bitmap  *bitmapFile = new Bitmap(textureFile);
		m_iTextID = bitmapFile->Bitmap2TextureName();
		//cout<< "TExture SandID: "<< m_iTextID << endl;
	}	
	
	////TEST LOCAL -> World Space
	//testMatrix.identity();
	////testMatrix.rotateZ(180);
	//testMatrix.translate(1, 1,0); // Translate first and then rotate
	//Vector4	 testVector(3,3, 1, 1 );
	////testMatrix.invert();
	//Vector4  resultVector = testMatrix*testVector;
	//cout << "Test Matrix: \n" << testMatrix << endl;
	//cout << "Output: " << resultVector <<endl;

	////TEST World->LOCAL space
	//Vector3D worldPoint = 	PointToLocalSpace(Vector3D(3,3,1), 180, Vector3D(0,0,1), Vector3D(1,1,0));
	//cout << "Output Vector3D: " << worldPoint.x << " " << worldPoint.y << " " << worldPoint.z << endl;
	

	//seed random number generator
	srand((unsigned) time(NULL));
	//srand(0);

	////Bitmap file
	//FILE *textureFile;
	//textureFile	= fopen("spaceship.bmp", "rb");
	//
	//if(!textureFile)
	//{
	//	cout<< "FILE NOT FOUND...."<< endl;
	//}
	//else
	//{	
	//	bitmapFile = new Bitmap(textureFile);
	//}


	myGameWorld = new GameWorld(airCraft1.m_Mesh, airCraft2.m_Mesh, tank.m_Mesh, turretBase.m_Mesh, turret.m_Mesh, missile.m_Mesh, spaceship.m_Mesh, treeType1.m_Mesh, treeType2.m_Mesh);
	

	////Missile
	//myMissile = new Missile(0.0f, 0.0f, 0.0f, missile.m_Mesh);

	////TurretBase
	//myTurret = new Turret(0.0f, 0.0f, 0.0f, turret.m_Mesh);
	//
	////Spaceship
	//mySpaceShip = new SpaceShip(10.0f, 0.0f, 0.0f,spaceship.m_Mesh);
	//idSpaceship = 0;
	//idSpaceship = glGenLists(1);
	//cout<< "SpaceSHIP id: "<< idSpaceship<< endl;
	//glNewList(idSpaceship, GL_COMPILE);
	//mySpaceShip->Render();
	//glEndList();
	//
	////tank
	//myTank = new Tank(0.0f, 0.0f , 0.0f, tank.m_Mesh);
	//idTank = 0;
	//idTank = glGenLists(1);
	//cout<< "Tank ID: " << idTank<< endl;
	//glNewList(idTank, GL_COMPILE);
	//myTank->Render();
	//glEndList();
	//
	////aircraft 1
	//myAircraft1 = new Aircraft(0.0f, 2.0f, 0.0f, airCraft1.m_Mesh);
	////id1 = myAircraft1->Render();
	////myAircraft1->setFired(true);
	//id1 = 0;
	//id1 = glGenLists(1);
	//cout << "AirCraft ID: " << id1<< endl;
	//glNewList(id1, GL_COMPILE);
	//myAircraft1->Render();
	//glEndList();

	////aircraft 2
	//myAircraft2 = new Aircraft(0.0f, 0.0f, 10.0f, airCraft2.m_Mesh);

	//turret
	//myTurret = new Turret(0.0f, 0.0f, 0.0f, turret.m_Mesh);
	
	//turret Base
	//myTurret = new Turret(0.0f, 0.0f, 0.0f, turretBase.m_Mesh);

	//Triangles - aircraft2
	//myTurret = new Turret(0.0f, 0.0f, 0.0f,testFile.m_Mesh);
	

	
}

//reshape callback
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	//gluPerspective(60.0, 1.0, 1.0, 1000.0);
	gluPerspective(60, 1.0, 1.0, 2000.0);
	
}

//special Keys callback
void specialKeys(int key, int x, int y)
{
	
	switch(key)
	{
	case GLUT_KEY_DOWN:
		myGameWorld->setPressedDown(true);
		break;

	case GLUT_KEY_UP:
		myGameWorld->setPressedUp(true);
		break;

	case GLUT_KEY_LEFT:
		myGameWorld->setPressedLeft(true);
			break;
	case GLUT_KEY_RIGHT:
		myGameWorld->setPressedRight(true);
		break;
	case GLUT_KEY_F5:
		myGameWorld->m_bEnter = true;
		break;
	case GLUT_KEY_F4:
		myGameWorld->m_bStartScreen = true;
		break;
	case GLUT_KEY_F12:
		myGameWorld->setMode(3);
		break;
	

	}

}

//keyboard callback
void keyboard(unsigned char key, int x, int y)
{
	
}

void mouse(int button, int state, int x, int y){
	
	mouseX = x;
	mouseY = y;

	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			mouseLeftDown = true;
			
			cameraPosZ -= 3.0;
			cameraPosX += 0.5;
			cameraPosY += 2.0;


			
		}
		else if(state == GLUT_UP)
			mouseLeftDown = false;
	}
	else if(button == GLUT_RIGHT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			mouseRightDown = true;
		}
		else if(state = GLUT_UP)
			mouseRightDown = false;
	}

	//if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

	//	//float moveX = x - currentX;
	//	//float moveY = y - currentY;
	//	//
	//	//cameraPosX += moveX;
	//	//cameraPosY += moveY;

	//	currentY = y;
	//	currentX = x;
	//		
	
	//	/*glMatrixMode(GL_MODELVIEW);
	//	glLoadIdentity();
	//	gluLookAt(cameraPosX, cameraPosY, cameraPosZ, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0);*/
	//}

	//if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	//{
	//	currentX = x;
	//	currentY = y;
	//}

	//if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	//{
	//	cameraPosZ -= 3.0;
	//}
	
	
	glutPostRedisplay();
}

void mouseMoveCallBack(int x, int y)
{
		//float moveX = x - currentX;
		//float moveY = y - currentY;

		//cout<< "moveX : " << moveX;
		//cout<< "moveY : " << moveY;
		//
		////cameraPosX += moveX;
		////cameraPosY += moveY;

		//currentX = x;
		//currentY = y;

		////cout<< "CameraPosX: " << cameraPosX;
		////cout<< "CameraPosY: " << cameraPosY;
		//if(moveX > 0)
		//{
		//	cout<< "Move to Right" << endl;
		//}
		//else
		//{
		//	cout<< "Move to Left" << endl;
		//}

	if(mouseLeftDown)
	{
		cameraAngleX += (x - mouseX);
		cameraAngleY += (y - mouseY);
		mouseX		  = x;
		mouseY		  = y;
	}
	if(mouseRightDown)
	{
		cameraDistance -= (y-mouseY)*0.2f;
		mouseY			= y;
	}
}



int windowWidth  = 640;     // Windowed mode's width
int windowHeight = 480;     // Windowed mode's height
int windowPosX   = 50;      // Windowed mode's top-left corner x
int windowPosY   = 50;		// Windowed mode's top-left corner y


int main()
{
	//glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	//glutInitWindowSize (500, 500); 
	//glutInitWindowPosition (100, 100);
	//glutCreateWindow("HW3-Defense Game");

	//init();

	//glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);
	//glutMotionFunc(mouseMoveCallBack);

	//glutMainLoop();


	//TEST version
	initSharedMem();

	initGLUT();
	initGL();

	glutMainLoop();
	return 0;


}
//---------------------------------------------------
//Draw a grid on XZ plane
//---------------------------------------------------
void drawGrid(float size, float step)
{
	//enable/disable lighting
	glDisable(GL_LIGHTING);
	//glEnable(GL_LIGHTING);
	
	glBegin(GL_LINES);
		glColor3f(0.5f, 0.5f, 0.5f);
		for(float i = step; i<= size; i+= step)
		{
			glVertex3f(-size, 0, i); // lines parallel to X-axis
			glVertex3f(size, 0, i);
			glVertex3f(-size, 0, -i);//lines parallel to X-axis
			glVertex3f(size, 0, -i);

			glVertex3f(i, 0, -size); //lines parallel to Z-axis
			glVertex3f(i, 0, size);
			glVertex3f(-i, 0, -size);
			glVertex3f(-i, 0, size);
		}

		//x-axis
		glColor3f(1,0,0);
		glVertex3f(-size, 0, 0);
		glVertex3f(size, 0, 0);

		//z-axis
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, -size);
		glVertex3f(0, 0, size);

	glEnd();

		
	//if(renderMode == 5)
	//{
	//	
	//	glEnable(GL_TEXTURE_2D);
	//	glBindTexture(GL_TEXTURE_2D, m_iTextID);
	//
	//	glColor3f(0.5f, 0.7f, 0.6f);
	//	for(float i = step; i<= size; i+= step)
	//	{
	//		glBegin(GL_POLYGON);

	//		glTexCoord2f(-1.0, -1.0);
	//		glVertex3f(-size, 0, -i);
	//		
	//		glTexCoord2f(-1.0, 1.0f);
	//		glVertex3f(-size, 0, i); // lines parallel to X-axis
	//		
	//		glTexCoord2f(1.0, 1.0f);
	//		glVertex3f(size, 0, i);
	//		
	//		glTexCoord2f(1.0, -1.0);
	//		glVertex3f(size, 0, -i);
	//		glEnd();
	//		
	//		//glBegin(GL_POLYGON);
	//		//glVertex3f(i, 0, -size); //lines parallel to Z-axis
	//		//glVertex3f(i, 0, size);
	//		//glVertex3f(-i, 0, -size);
	//		//glVertex3f(-i, 0, size);
	//		//glEnd();
	//	}
	//	glDisable(GL_TEXTURE_2D);

	//	glEnable(GL_LIGHTING);
	//}
	//else
	//{
	//	glColor3f(0.5f, 0.7f, 0.6f);
	//	for(float i = step; i<= size; i+= step)
	//	{
	//		glBegin(GL_POLYGON);

	//		glTexCoord2f(-1.0, -1.0);
	//		glVertex3f(-size, 0, -i);
	//		
	//		glTexCoord2f(-1.0, 1.0f);
	//		glVertex3f(-size, 0, i); // lines parallel to X-axis
	//		
	//		glTexCoord2f(1.0, 1.0f);
	//		glVertex3f(size, 0, i);
	//		
	//		glTexCoord2f(1.0, -1.0);
	//		glVertex3f(size, 0, -i);
	//		glEnd();
	//		
	//		//glBegin(GL_POLYGON);
	//		//glVertex3f(i, 0, -size); //lines parallel to Z-axis
	//		//glVertex3f(i, 0, size);
	//		//glVertex3f(-i, 0, -size);
	//		//glVertex3f(-i, 0, size);
	//		//glEnd();
	//	}
	//	
	//	glEnable(GL_LIGHTING);
	//}

}
void drawAxis(float size)
{
    glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines
    glDisable(GL_LIGHTING);
	//glEnable(GL_LIGHTING);

    // draw axis
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(size, 0, 0);
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, size, 0);
        glColor3f(0, 1, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, size);
    glEnd();
    glLineWidth(1);

    // draw arrows(actually big square dots)
    glPointSize(5);
    glBegin(GL_POINTS);
        glColor3f(1, 0, 0);
        glVertex3f(size, 0, 0);
        glColor3f(0, 1, 0);
        glVertex3f(0, size, 0);
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, size);
    glEnd();
    glPointSize(1);

    // restore default settings
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
}

///////////////////////////////////////////////////////////////////////////////
// draw a model (tetrahedron)
///////////////////////////////////////////////////////////////////////////////
void drawModel()
{
    //glColor3f(1, 1, 1);
    //glBegin(GL_TRIANGLES);
    //glNormal3f(0.6667f, 0.6667f, 0.3334f);
    //glVertex3f(1, 0, 0);
    //glVertex3f(0, 1, 0);
    //glVertex3f(0, 0, 2);

    //glNormal3f(-0.6667f, 0.6667f, 0.3334f);
    //glVertex3f(-1, 0, 0);
    //glVertex3f(0, 0, 2);
    //glVertex3f(0, 1, 0);

    //glNormal3f(0, 0, -1);
    //glVertex3f(1, 0, 0);
    //glVertex3f(0, 0, 2);
    //glVertex3f(-1, 0, 0);

    //glNormal3f(0, -1, 0);
    //glVertex3f(1, 0, 0);
    //glVertex3f(-1, 0, 0);
    //glVertex3f(0, 1, 0);
    //glEnd();
	switch(renderMode)
	{
	case 1:
		glDisable(GL_DEPTH_TEST);	 //Z-buffer algorithm
		glDisable(GL_CULL_FACE);	 //Cull-Face algorithm
		glDisable(GL_TEXTURE_2D);	 //Texture
		glDisable(GL_LIGHTING);		 //Lighting
		glDisable(GL_LIGHT0);		 //Lighting0
		glDisable(GL_LIGHT1);		 //Lighting1
		glDisable(GL_COLOR_MATERIAL);//Color Material
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		
		break;
	case 2: //Hiden
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_COLOR_MATERIAL);
		glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//myGameWorld->m_bRenderMode = false;

		break;
	case 3://Flat shading
		glShadeModel(GL_FLAT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_COLOR_MATERIAL);
		glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_POLYGON_OFFSET_FILL);

		//myGameWorld->m_bRenderMode = false;
		
		break;
	case 4://Gouraud shading
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_COLOR_MATERIAL);
		glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_POLYGON_OFFSET_FILL);	
		
		//myGameWorld->m_bRenderMode = false;
		break;
	case 5://Gouraud Shading with Texture
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_POLYGON_OFFSET_FILL);

		//myGameWorld->m_bRenderMode = true;
		break;
	}

	display();
}

void initGLUT()
{
	
	glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);

	glutInitWindowSize(screenWidth, screenHeight); // window size

	glutInitWindowPosition(100, 100); // window location
	glutCreateWindow("HW3-Defense Game");

	glutDisplayFunc(displayCB);
	glutTimerFunc(33, timerCB, 33); //redraw only every given millisec
	glutReshapeFunc(reshapeCB);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboardCB);
	glutMouseFunc(mouseCB);
	glutMotionFunc(mouseMotionCB);

	/*glutCreateMenu(menu);
	glutAddMenuEntry("Wire Frame", 0);
	glutAddMenuEntry("Wire Frame with HSR",1);
	glutAddMenuEntry("Flat Shading",2);
	glutAddMenuEntry("Gouraud Shading", 3);
	glutAddMenuEntry("Gouraund Shading with Texture", 4);
	glutAttachMenu(65);*/
	

	init();
	
	/*return 1;*/
}

//-----------------------------------------------------------
//initialize OpenGL
//disable/enable features
//-----------------------------------------------------------
void initGL()
{
	

	//glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    //glEnable(GL_DEPTH_TEST); //Z-buffer on hardware algorithm
    /*glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);*/
    //glEnable(GL_CULL_FACE); //back face culling algorithm

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    //glEnable(GL_DEPTH_TEST);
    /*glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);*/
    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);

     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

    initLights();

}


//---------------------------------------------------
//initialize global variables
//---------------------------------------------------
bool initSharedMem()
{
	screenWidth = SCREEN_WIDTH;
	screenHeight= SCREEN_HEIGHT;

	mouseLeftDown = mouseRightDown = false;
	mouseX = mouseY = 0;

	cameraAngleX = cameraAngleY = 0;
	cameraDistance = CAMERA_DISTANCE;

	drawMode = 0; // 0: fill, 1: wireframe, 2: points

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// write 2d text using GLUT
// The projection matrix must be set to orthogonal before call this function.
///////////////////////////////////////////////////////////////////////////////
void drawString(const char *str, int x, int y, float color[4], void *font)
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



///////////////////////////////////////////////////////////////////////////////
// draw a string in 3D space
///////////////////////////////////////////////////////////////////////////////
void drawString3D(const char *str, float pos[3], float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
    glDisable(GL_TEXTURE_2D);

    glColor4fv(color);          // set text color
    glRasterPos3fv(pos);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPopAttrib();
}

//clear shared mem
void clearSharedMem()
{

}

//initialize lights
void initLights()
{
	//LIGHT0
	//set up lights colors (ambient, diffuse, specular)
	GLfloat lightKa[] = {1.0f, 1.0f, .5f, 1.0f};  // ambient light
    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {0.5f, 0.4f, 0.5f, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);
	
	// position the light
    float lightPos[4] = {0, 0, 20, 1}; // positional light -- NOTE
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	

	//LIGHT1
	GLfloat lightKa1[] = {1.f, .5f, .5f, 1.0f};  // ambient light
    GLfloat lightKd1[] = {.2f, .8f, .4f, 1.0f};  // diffuse light
    GLfloat lightKs1[] = {1, 0.2, 0.4, 1};           // specular light
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightKa1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightKd1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightKs1);
	
	// position the light
    float lightPos1[4] = {0, 0, -20, 1}; // positional light -- NOTE
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
	GLfloat whiteLight[] = {0.2, 0.2, 0.2, 0.3};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);


    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
	glEnable(GL_LIGHT1);
	
}


///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}

//set projection matrix as orthogonal
void toOrtho()
{
	//set viewport to be the entire window
	glViewport(0,0, (GLsizei)screenWidth, (GLsizei)screenHeight);

	//set orthorgraphic viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screenWidth, 0, screenHeight, -1, 1);

	//switch to model view matrix in order to set scene
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

///////////////////////////////////////////////////////////////////////////////
// set the projection matrix as perspective
///////////////////////////////////////////////////////////////////////////////
void toPerspective()
{
    // set viewport to be the entire window
    glViewport(0, 0, (GLsizei)screenWidth, (GLsizei)screenHeight);

    // set perspective viewing frustum
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)(screenWidth)/screenHeight, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


///////////////////////////////////////////////////////////////////////////////
// convert Euler angles(x,y,z) to matrix4
// Each column of the rotation matrix represents left, up and forward axis.
// The order of rotation is Roll->Yaw->Pitch (Rx*Ry*Rz)
// Rx: rotation about X-axis, pitch
// Ry: rotation about Y-axis, yaw(heading)
// Rz: rotation about Z-axis, roll
//    Rx           Ry          Rz
// |1  0   0| | Cy  0 Sy| |Cz -Sz 0|   | CyCz        -CySz         Sy  |
// |0 Cx -Sx|*|  0  1  0|*|Sz  Cz 0| = | SxSyCz+CxSz -SxSySz+CxCz -SxCy|
// |0 Sx  Cx| |-Sy  0 Cy| | 0   0 1|   |-CxSyCz+SxSz  CxSySz+SxCz  CxCy|
///////////////////////////////////////////////////////////////////////////////
void anglesToMatrix(const Vector3 angles, Matrix4& matrix)
{
    const float DEG2RAD = 3.141593f / 180;
    float sx, sy, sz, cx, cy, cz, theta;
    Vector3 left, up, forward;

    // rotation angle about X-axis (pitch)
    theta = angles.x * DEG2RAD;
    sx = sinf(theta);
    cx = cosf(theta);

    // rotation angle about Y-axis (yaw)
    theta = angles.y * DEG2RAD;
    sy = sinf(theta);
    cy = cosf(theta);

    // rotation angle about Z-axis (roll)
    theta = angles.z * DEG2RAD;
    sz = sinf(theta);
    cz = cosf(theta);

    // determine left axis
    left.x = cy*cz;
    left.y = sx*sy*cz + cx*sz;
    left.z = -cx*sy*cz + sx*sz;

    // determine up axis
    up.x = -cy*sz;
    up.y = -sx*sy*sz + cx*cz;
    up.z = cx*sy*sz + sx*cz;

    // determine forward axis
    forward.x = sy;
    forward.y = -sx*cy;
    forward.z = cx*cy;

    // write back to matrix
    matrix.setColumn(0, left);
    matrix.setColumn(1, up);
    matrix.setColumn(2, forward);
}

///////////////////////////////////////////////////////////////////////////////
// set a perspective frustum with 6 params similar to glFrustum()
// (left, right, bottom, top, near, far)
// Note: this is for row-major notation. OpenGL needs transpose it
///////////////////////////////////////////////////////////////////////////////
Matrix4 setFrustum(float l, float r, float b, float t, float n, float f)
{
    Matrix4 mat;
    mat[0]  =  2 * n / (r - l);
    mat[2]  =  (r + l) / (r - l);
    mat[5]  =  2 * n / (t - b);
    mat[6]  =  (t + b) / (t - b);
    mat[10] = -(f + n) / (f - n);
    mat[11] = -(2 * f * n) / (f - n);
    mat[14] = -1;
    mat[15] =  0;
    return mat;
}



///////////////////////////////////////////////////////////////////////////////
// set a symmetric perspective frustum with 4 params similar to gluPerspective
// (vertical field of view, aspect ratio, near, far)
///////////////////////////////////////////////////////////////////////////////
Matrix4 setFrustum(float fovY, float aspectRatio, float front, float back)
{
    float tangent = tanf(fovY/2 * DEG2RAD);   // tangent of half fovY
    float height = front * tangent;           // half height of near plane
    float width = height * aspectRatio;       // half width of near plane

    // params: left, right, bottom, top, near, far
    return setFrustum(-width, width, -height, height, front, back);
}


///////////////////////////////////////////////////////////////////////////////
// set a orthographic frustum with 6 params similar to glOrtho()
// (left, right, bottom, top, near, far)
// Note: this is for row-major notation. OpenGL needs transpose it
///////////////////////////////////////////////////////////////////////////////
Matrix4 setOrthoFrustum(float l, float r, float b, float t, float n, float f)
{
    Matrix4 mat;
    mat[0]  =  2 / (r - l);
    mat[3]  =  -(r + l) / (r - l);
    mat[5]  =  2 / (t - b);
    mat[7]  =  -(t + b) / (t - b);
    mat[10] = -2 / (f - n);
    mat[11] = -(f + n) / (f - n);
    return mat;
}


//----------------------------------------------------------
//CALLBACKS
//----------------------------------------------------------
void displayCB()
{
	//clear buffer
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//save the initial ModelView matrix before modifying ModelView matrix
	glPushMatrix();

	if(viewMode == 1)
	{
		//transform camera
		matrixView.identity();
		matrixView.rotate(cameraAngleY, 0, 1, 0);
		matrixView.rotate(cameraAngleX, 1, 0, 0);
		matrixView.translate(0, 0, -cameraDistance);
		//copy view matrix to OpenGL
		glLoadMatrixf(matrixView.getTranspose()); // why to need transpose
	}
	if(viewMode == 2)
	{
		matrixView.identity();

		//setCamera(0.0f, 0.0f, 0.0f, myGameWorld->getCameraTargetX()*4, myGameWorld->getCameraTargetY()*4, myGameWorld->getCameraTargetZ()*4);
		
		setCamera(0.0f, 0.0f, 0.0f, myGameWorld->Aircrafts()[0]->getX(), myGameWorld->Aircrafts()[0]->getY(), myGameWorld->Aircrafts()[0]->getZ());
	}

	

	drawGrid();

	//compute model matrix
	matrixModel.identity();
	//matrixModel.rotate( angle, x, y, z);
	//matrixModel.rotateY(45);
	//matrixModel.translate(0, 1, 0); // move 2 uit up
	


	matrixModelView = matrixView*matrixModel;

	glLoadMatrixf(matrixModelView.getTranspose());

	drawAxis();
	drawModel();
	

	glPopMatrix();
	
	glutSwapBuffers();
}


void reshapeCB(int w, int h)
{
	screenWidth = w;
	screenHeight = h;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h );


	 // set perspective viewing frustum
    glMatrixMode(GL_PROJECTION);
    matrixProjection = setFrustum(45, (float)w/h, 1.0f, 1000.0f);
    glLoadMatrixf(matrixProjection.getTranspose());

	glMatrixMode(GL_MODELVIEW);

}

void timerCB(int millisec)
{
	myGameWorld->Update();

    glutTimerFunc(millisec, timerCB, millisec);
    glutPostRedisplay();
}

void keyboardCB(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27: // ESCAPE
        exit(0);
        break;

    case ' ':
        break;

	case 's':
		myGameWorld->setPressedFired(true);
		break;
	
	case 'v':
		if( viewMode == 1)
		{
			viewMode = 2;
			cout<< "viewMode " << viewMode<< endl;
		}
		else
		{
			viewMode = 1;
			cout<< "viewMode " << viewMode << endl; 
		}
		break;
	
	case 't':
		if(myGameWorld->m_iMissileType == 1)
		{
			myGameWorld->m_iMissileType = 2;
		}
		else
		{
			myGameWorld->m_iMissileType = 1;
		}
		break;
	
	case 'i':
		myGameWorld->setPressedUp(true);
		break;
	case 'k':
		myGameWorld->setPressedDown(true);
		break;
	case 'j':
		myGameWorld->setPressedLeft(true);
		break;
	case 'l':
		myGameWorld->setPressedRight(true);
		break;

    case 'd': // switch rendering modes (fill -> wire -> point)
    case 'D':
        drawMode = ++drawMode % 3;
        if(drawMode == 0)        // fill mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
        }
        else if(drawMode == 1)  // wireframe mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }
        else                    // point mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }
        break;

	case '1':
		renderMode = 1;
		myGameWorld->m_bRenderMode = false;
		glutPostRedisplay();
		break;
	case '2':
		renderMode = 2;
		myGameWorld->m_bRenderMode = false;
		glutPostRedisplay();
		break;
	case '3':
		renderMode = 3;
		myGameWorld->m_bRenderMode = false;
		glutPostRedisplay();
		break;
	case '4':
		renderMode = 4;
		myGameWorld->m_bRenderMode = false;
		glutPostRedisplay();
		break;
	case '5':
		renderMode = 5;
		myGameWorld->m_bRenderMode = true;
		glutPostRedisplay();
		break;
	case '6':
		myGameWorld->setSpecialMode(2);
		break;

	case '7':
		myGameWorld->setRenderingMode(1);//SEEK
		break;
	case '8':
		myGameWorld->setRenderingMode(2);//OFFSET PURSUIT
		break;
	case '9':
		myGameWorld->setRenderingMode(3);//SNAKE
		break;
	case '0':
		myGameWorld->setRenderingMode(4);//SPECIAL MODE
		break;
	case 'q':
		myGameWorld->setRenderingMode(5);//Flocking MODE
		break;
	case 'u':
		myGameWorld->setRenderingMode(6);//SpecialMode UNFAIR
		break;
	case 'z':
		myGameWorld->setRenderingMode(7);
		break;
	default:
        ;
    }
}

void mouseCB(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }
}


void mouseMotionCB(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance -= (y - mouseY) * 0.2f;
        mouseY = y;
    }
}