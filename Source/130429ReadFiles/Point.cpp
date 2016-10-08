#include "Point.h"

void Point::Render()
{	
	//Draw Sphere
	//GLUquadric *sphere=gluNewQuadric();
	//gluQuadricDrawStyle( sphere, GLU_LINE);
	////gluQuadricNormals( sphere, GLU_SMOOTH);
	//gluQuadricOrientation( sphere, GLU_OUTSIDE);

	//glPushMatrix();
	//glTranslatef(this->Pos().x, this->Pos().y, this->Pos().z);
	//gluSphere(sphere,0.5,10,10);
	//glPopMatrix();
	

	GLfloat ballRadius = 0.6f;
	GLfloat PI = 3.14159265f;

	

	glPushMatrix();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	glTranslatef(this->Pos().x, this->Pos().y, this->Pos().z);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 1.0f);  // Blue
	//glVertex2f(0.0f, 0.0f);       // Center of circle
	int numSegments = 100;
	GLfloat angle;
	for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
		angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
		glVertex3f(cos(angle) * ballRadius, 0.0 ,sin(angle) * ballRadius);
	}
	glEnd();
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glPopMatrix();
	
	
}
