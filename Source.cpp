
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <GL/glut.h>


float cloud1_movement = 0;
float cloud2_movement = 0;
float Sun_movement = 0;
bool morning = true;
int alternator = 1;
float jetMovement = 0;
float jetMovement2 = 0;

float heli_moveX = 0;

double backgroundR = 0.5;
double backgroundG = 0.8;
double backgroundB = 0.9;

double s1 = 0.98;
double s2 = 0.83;
double s3 = 0.25;

double R = 0.09;
double G = 0.52;
double B = 0.17;

double R2 = 0.09;
double G2 = 0.52;
double B2 = 0.17;

bool hit1 = false;
bool hit2 = false;

bool throw1 = false;
bool throw2 = false;

bool powerbar1 = false;
bool powerbar2 = false;
double power1 = 20;
double power2 = 20;
double powerbarMax1 = 0;
double powerbarMax2 = 0;

double def_x = 0;
bool touch = false;
double scene = 0;
bool touch2 = false;
double sun = 0;
double touch3 = false;
double ball = 0;
bool touch4 = false;


double projX1 = 0;
double projY1 = 0;
double projX2 = 0;
double projY2 = 0;

int p0[2];
int p1[2];
int p2[2];
int p3[2];
int tar = 4;


int health1 = 100;
int health2 = 100;



bool player1turn = true;
bool player2turn = false;

int p1_range = 500;

float t1 = 0;
float t2 = 0;





int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3) * p0[0] + 3 * t * pow((1 - t), 2) * p1[0] + 3 * pow(t, 2) * (1 - t) * p2[0] + pow(t, 3) * p3[0];
	res[1] = pow((1 - t), 3) * p0[1] + 3 * t * pow((1 - t), 2) * p1[1] + 3 * pow(t, 2) * (1 - t) * p2[1] + pow(t, 3) * p3[1];
	return res;
}

void key(unsigned char k, int x, int y)

{
	printf("%d\n", player1turn);

	if (k == 'm' && player1turn == true) {		  // for player 1
		powerbar1 = true;
	}

	if (k == 'c' && player2turn == true) {		  // for player 2
		powerbar2 = true;
	}
	glutPostRedisplay();
}

void keyUp(unsigned char k, int x, int y)//keyboard up function is called whenever the keyboard key is released				
										 //for throwing 
{
	if (k == 'm' && player1turn == true) {       // for player 1
		throw1 = true;
		powerbar1 = false;
		power1 = 20;
		player1turn = false;
		player2turn = true;
		powerbarMax1 = 0;
	}
	if (k == 'c' && player2turn == true) {		  // for player 2
		throw2 = true;
		powerbar2 = false;
		power2 = 20;
		player2turn = false;
		player1turn = true;
		powerbarMax2 = 0;

	}
	glutPostRedisplay();
}




void displayText(float x, float y, int r, int g, int b, const char* string) {
	int j = strlen(string);

	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}




void Display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(backgroundR, backgroundG, backgroundB, 0.0f);




	//Background
	glPushMatrix();											// the ground
	glColor3f(0.86f, 0.79f, 0.40f);
	glBegin(GL_QUADS);
	glVertex3d(0, 0, 0);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH), 0, 0);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH), 40, 0);
	glVertex3d(0, 40, 0);
	glEnd();

	glColor3f(0.66, 0.66, 0.66);
	glBegin(GL_QUADS);										// flag base
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH) / 2 - 20, 40, 0);
	glVertex3d((glutGet(GLUT_WINDOW_WIDTH) / 2) + 30, 40, 0);
	glVertex3d((glutGet(GLUT_WINDOW_WIDTH) / 2) + 30, 70, 0);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH) / 2 - 20, 70, 0);
	glEnd();

	glBegin(GL_QUADS);										// flag post 
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH) / 2 + 5, 70, 0);
	glVertex3d((glutGet(GLUT_WINDOW_WIDTH) / 2) + 10, 70, 0);
	glVertex3d((glutGet(GLUT_WINDOW_WIDTH) / 2) + 10, 300, 0);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH) / 2 + 5, 300, 0);
	glEnd();
	glPopMatrix();

	glBegin(GL_QUADS);										// flag  red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50, 285, 0);
	glVertex3d((glutGet(GLUT_WINDOW_WIDTH) / 2) + 10, 285, 0);
	glVertex3d((glutGet(GLUT_WINDOW_WIDTH) / 2) + 10, 295, 0);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50, 295, 0);
	glEnd();


	glBegin(GL_QUADS);										// flag  white
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50, 275, 0);
	glVertex3d((glutGet(GLUT_WINDOW_WIDTH) / 2) + 10, 275, 0);
	glVertex3d((glutGet(GLUT_WINDOW_WIDTH) / 2) + 10, 285, 0);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50, 285, 0);
	glEnd();

	glBegin(GL_QUADS);										//flag eagle
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH) / 2 - 25, 276.5, 0);
	glVertex3d((glutGet(GLUT_WINDOW_WIDTH) / 2) - 15, 276.5, 0);
	glVertex3d((glutGet(GLUT_WINDOW_WIDTH) / 2) - 15, 283.5, 0);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH) / 2 - 25, 283.5, 0);
	glEnd();


	glBegin(GL_QUADS);										// flag  black
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50, 265, 0);
	glVertex3d((glutGet(GLUT_WINDOW_WIDTH) / 2) + 10, 265, 0);
	glVertex3d((glutGet(GLUT_WINDOW_WIDTH) / 2) + 10, 275, 0);
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50, 275, 0);
	glEnd();
	glPopMatrix();




	//1st cloud
	glPushMatrix();											// clouds
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(cloud1_movement, 0, 0);
	int number8 = 20; //number of vertices
	float radius8 = 25.0f; //radius
	float twoPi8 = 2.0f * 3.14159f;
	glBegin(GL_POLYGON);
	for (int i = 0; i < number8; i++)
		glVertex3f(radius8 * cosf(i * twoPi8 / number8) + 100,
			radius8 * sinf(i * twoPi8 / number8) + 480, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < number8; i++)
		glVertex3f(radius8 * cosf(i * twoPi8 / number8) + 120,
			radius8 * sinf(i * twoPi8 / number8) + 470, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < number8; i++)
		glVertex3f(radius8 * cosf(i * twoPi8 / number8) + 150,
			radius8 * sinf(i * twoPi8 / number8) + 480, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < number8; i++)
		glVertex3f(radius8 * cosf(i * twoPi8 / number8) + 125,
			radius8 * sinf(i * twoPi8 / number8) + 490, 0.0f);
	glEnd();
	glPopMatrix();

	// 2nd cloud
	glPushMatrix();											// clouds
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(cloud2_movement, 0, 0);
	int number9 = 20; //number of vertices
	float radius9 = 25.0f; //radius
	float twoPi9 = 2.0f * 3.14159f;
	glBegin(GL_POLYGON);
	for (int i = 0; i < number9; i++)
		glVertex3f(radius9 * cosf(i * twoPi9 / number9) + 200,
			radius9 * sinf(i * twoPi9 / number9) + 440, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < number9; i++)
		glVertex3f(radius9 * cosf(i * twoPi9 / number9) + 230,
			radius9 * sinf(i * twoPi9 / number9) + 430, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < number9; i++)
		glVertex3f(radius9 * cosf(i * twoPi9 / number9) + 245,
			radius9 * sinf(i * twoPi9 / number9) + 440, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < number9; i++)
		glVertex3f(radius9 * cosf(i * twoPi9 / number9) + 225,
			radius9 * sinf(i * twoPi9 / number9) + 450, 0.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();											// Sun
	glColor3f(s1, s2, s3);
	glTranslatef(Sun_movement, 0, 0);
	int number10 = 20; //number of vertices
	float radius10 = 50.0f; //radius
	float twoPi10 = 2.0f * 3.14159f;
	glBegin(GL_POLYGON);
	for (int i = 0; i < number10; i++)
		glVertex3f(radius10 * cosf(i * twoPi10 / number10),
			radius10 * sinf(i * twoPi10 / number10) + 550, 0.0f);
	glEnd();
	glPopMatrix();






	//draw tank1
	glPushMatrix();

	glColor3f(R, G, B);
	//mid body
	glBegin(GL_POLYGON);
	glVertex3f(45.0f, 50.0f, 0.0f);
	glVertex3f(85.0f, 50.0f, 0.0f);
	glVertex3f(85.0f, 65.0f, 0.0f);
	glVertex3f(45.0f, 65.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);						//top part
	glVertex3f(50.0f, 65.0f, 0.0f);
	glVertex3f(80.0f, 65.0f, 0.0f);
	glVertex3f(80.0f, 75.0f, 0.0f);
	glVertex3f(50.0f, 75.0f, 0.0f);
	glEnd();


	glBegin(GL_LINE_LOOP);					//the down part
	glVertex3f(43.0f, 40.0f, 0.0f);
	glVertex3f(86.5f, 40.0f, 0.0f);
	glVertex3f(86.5f, 50.0f, 0.0f);
	glVertex3f(43.0f, 50.0f, 0.0f);
	glEnd();


	glBegin(GL_TRIANGLES);					//the wheels
	glVertex3f(43.0f, 40.0f, 0.0f);
	glVertex3f(57.3f, 40.0f, 0.0f);
	glVertex3f(50.0f, 50.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);					//the wheels
	glVertex3f(57.3f, 40.0f, 0.0f);
	glVertex3f(71.6f, 40.0f, 0.0f);
	glVertex3f(64.0f, 50.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);					//the wheels
	glVertex3f(71.6f, 40.0f, 0.0f);
	glVertex3f(86.5f, 40.0f, 0.0f);
	glVertex3f(79.0f, 50.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(75.0f, 65.0f, 0.0f);
	glVertex3f(110.0f, 70.0f, 0.0f);
	glVertex3f(110.0f, 75.0f, 0.0f);
	glVertex3f(75.0f, 70.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(50.0f, 65.0f, 0.0f);
	glVertex3f(80.0f, 65.0f, 0.0f);
	glEnd();

	glPopMatrix();



	//draw tank2
	glPushMatrix();
	glColor3f(R2, G2, B2);					//mid body
	glBegin(GL_POLYGON);
	glVertex3f(1235.0f, 50.0f, 0.0f);
	glVertex3f(1195.0f, 50.0f, 0.0f);
	glVertex3f(1195.0f, 65.0f, 0.0f);
	glVertex3f(1235.0f, 65.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);						//top part
	glVertex3f(1230.0f, 65.0f, 0.0f);
	glVertex3f(1200.0f, 65.0f, 0.0f);
	glVertex3f(1200.0f, 75.0f, 0.0f);
	glVertex3f(1230.0f, 75.0f, 0.0f);
	glEnd();


	glBegin(GL_LINE_LOOP);					//the down part
	glVertex3f(1237.0f, 40.0f, 0.0f);
	glVertex3f(1193.5f, 40.0f, 0.0f);
	glVertex3f(1193.5f, 50.0f, 0.0f);
	glVertex3f(1237.0f, 50.0f, 0.0f);
	glEnd();


	glBegin(GL_TRIANGLES);					//the wheels
	glVertex3f(1237.0f, 40.0f, 0.0f);
	glVertex3f(1222.7f, 40.0f, 0.0f);
	glVertex3f(1230.0f, 50.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);					//the wheels
	glVertex3f(1222.7f, 40.0f, 0.0f);
	glVertex3f(1208.4f, 40.0f, 0.0f);
	glVertex3f(1216.0f, 50.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);					//the wheels
	glVertex3f(1208.4f, 40.0f, 0.0f);
	glVertex3f(1193.5f, 40.0f, 0.0f);
	glVertex3f(1205.0f, 50.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(1205.0f, 65.0f, 0.0f);
	glVertex3f(1170.0f, 70.0f, 0.0f);
	glVertex3f(1170.0f, 75.0f, 0.0f);
	glVertex3f(1205.0f, 70.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(1230.0f, 65.0f, 0.0f);
	glVertex3f(1200.0f, 65.0f, 0.0f);
	glEnd();
	glPopMatrix();


	//glPushMatrix();
	//glColor3f(1.0f, 0.0f, 0.0f);			 // draw defender1
	//glTranslated(def_x, 0, 0);
	//glBegin(GL_QUADS);
	//glVertex3f(1235.0f, 450.0f, 0.0f);
	//glVertex3f(1135.0f, 450.0f, 0.0f);
	//glVertex3f(1135.0f, 430.0f, 0.0f);
	//glVertex3f(1235.0f, 430.0f, 0.0f);
	//glEnd();
	//glBegin(GL_TRIANGLES);
	//glVertex3f(1235.0f, 430.0f, 0.0f);
	//glVertex3f(1135.0f, 430.0f, 0.0f);
	//glVertex3f(1185.0f, 380.0f, 0.0f);

	//glEnd();
	//glPopMatrix();




	glPushMatrix();							//Health bar1
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(10.0f, 140.0f, 0.0f);
	glVertex3f(30.0f, 140.0f, 0.0f);
	glVertex3f(30.0f, 140.0f + health1, 0.0f);
	glVertex3f(10.0f, 140.0f + health1, 0.0f);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);			//Health bar2
	glBegin(GL_QUADS);
	glVertex3f(1250.0f, 140.0f, 0.0f);
	glVertex3f(1270.0f, 140.0f, 0.0f);
	glVertex3f(1270.0f, 140.0f + health2, 0.0f);
	glVertex3f(1250.0f, 140.0f + health2, 0.0f);
	glEnd();
	glPopMatrix();


	glPushMatrix();							//power bar1
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(10.0f, 580.0f, 0.0f);
	glVertex3f(10.0f, 560.0f, 0.0f);
	glVertex3f(10.0f + power1, 560.0f, 0.0f);
	glVertex3f(10.0f + power1, 580.0f, 0.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);			//power bar2
	glBegin(GL_QUADS);
	glVertex3f(1190.0f, 560.0f, 0.0f);
	glVertex3f(1190.0f + power2, 560.0f, 0.0f);
	glVertex3f(1190.0f + power2, 580.0f, 0.0f);
	glVertex3f(1190.0f, 580.0f, 0.0f);
	glEnd();
	glPopMatrix();



	/*glPushMatrix();							//curve part
	glPointSize(1);
	glColor3f(1, 1, 0);
	glBegin(GL_POINTS);
	for (float t = 0; t < 1; t += 0.001)
	{
		int* p = bezier(t, p0, p1, p2, p3);
		glVertex3f(p[0], p[1], 0);
	}
	glEnd();
	glPopMatrix();
	*/


	glPushMatrix();							//the projectile1
	glTranslatef(projX1, projY1, 0);
	glColor3f(0.0f, 0.0f, 0.0f);
	int number5 = 20;
	float radius5 = 5.0f;
	float twoPi5 = 2.0f * 3.14159f;
	glBegin(GL_POLYGON);
	for (int i = 0; i < number5; i++)
		glVertex3f(radius5 * cosf(i * twoPi5 / number5) + 85,
			radius5 * sinf(i * twoPi5 / number5) + 68, 0.0f);
	glEnd();
	glPopMatrix();


	glPushMatrix();							//the projectile2
	glTranslated(projX2, projY2, 0);
	glColor3f(0.0f, 0.0f, 0.0f);
	int number6 = 20;
	float radius6 = 5.0f;
	float twoPi6 = 2.0f * 3.14159f;
	glBegin(GL_POLYGON);
	for (int i = 0; i < number6; i++)
		glVertex3f(radius6 * cosf(i * twoPi6 / number6) + 1190,
			radius6 * sinf(i * twoPi6 / number6) + 68, 0.0f);
	glEnd();
	glPopMatrix();



	// Helicopter
	glPushMatrix();
	glColor3f(0.09f, 0.52f, 0.17f);
	glTranslatef(heli_moveX, 50, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(100, 300, 0);
	glVertex3f(130, 330, 0);
	glVertex3f(160, 300, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(70, 310, 0);
	glVertex3f(110, 310, 0);
	glVertex3f(110, 300, 0);
	glVertex3f(70, 300, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(60, 300, 0);
	glVertex3f(70, 300, 0);
	glVertex3f(70, 320, 0);
	glVertex3f(60, 320, 0);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(90, 330, 0);
	glVertex3f(170, 330, 0);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	int number11 = 20;
	float radius11 = 15.0f;
	float twoPi11 = 2.0f * 3.14159f;
	for (int i = 0; i < number11; i++)
		glVertex3f(radius11 * cosf(i * twoPi11 / number11) + 65,
			radius11 * sinf(i * twoPi11 / number11) + 320, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(138, 320, 0);
	glVertex3f(155, 305, 0);
	glVertex3f(130, 305, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(150, 300, 0);
	glVertex3f(150, 295, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(120, 300, 0);
	glVertex3f(120, 295, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(100, 295, 0);
	glVertex3f(160, 295, 0);
	glEnd();
	glPopMatrix();




	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(jetMovement, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(1200, 420, 0);
	glVertex3f(1240, 439, 0);
	glVertex3f(1240, 401, 0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(1188, 420, 0);
	glVertex3f(1210, 424, 0);
	glVertex3f(1210, 416, 0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(1247, 420, 0);
	glVertex3f(1240, 423, 0);
	glVertex3f(1240, 417, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(1217, 430, 0);
	glVertex3f(1240, 430, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(1217, 409, 0);
	glVertex3f(1240, 409, 0);
	glEnd();

	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_TRIANGLES);
	glVertex3f(1240, 465, 0);
	glVertex3f(1280, 484, 0);
	glVertex3f(1280, 446, 0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(1228, 465, 0);
	glVertex3f(1250, 469, 0);
	glVertex3f(1250, 461, 0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(1287, 465, 0);
	glVertex3f(1280, 468, 0);
	glVertex3f(1280, 462, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(1257, 475, 0);
	glVertex3f(1280, 475, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(1257, 454, 0);
	glVertex3f(1280, 454, 0);
	glEnd();
	glPopMatrix();

	displayText(10, 520, 1, 0, 0, "Power Bar");
	displayText(1160, 520, 1, 0, 0, "Power Bar");
	displayText(10, 100, 1, 0, 0, "Health Bar");
	displayText(1160, 100, 1, 0, 0, "Health Bar");

	if (health1 == 0) {
		displayText(500, 300, 1, 0, 0, "Player2 Wins");
		player1turn = false;
		player2turn = false;
	}
	if (health2 == 0) {
		displayText(500, 300, 1, 0, 0, "Player1 Wins");
		player1turn = false;
		player2turn = false;
	}


	glFlush();

}


void time(int val)
{


	R = 0.09;
	G = 0.52;
	B = 0.17;

	glutPostRedisplay();

}

void time2(int val)
{


	R2 = 0.09;
	G2 = 0.52;
	B2 = 0.17;

	glutPostRedisplay();

}



void Anim() {

	p0[0] = 85;
	p0[1] = 68;

	p1[0] = 100;
	p1[1] = 500;

	p2[0] = 500;
	p2[1] = 500;

	p3[0] = p1_range;
	p3[1] = 40;




	if (def_x > -1100 && touch == false) {	//defender
		def_x = def_x - 0.25;
	}
	if (def_x == -1100) {
		touch = true;
	}
	if (def_x < 0 && touch == true) {
		def_x = def_x + 0.25;
	}
	if (def_x == 0) {
		touch = false;
	}


	if (scene < 1000 && touch2 == false) {
		scene = scene + 0.25;
	}
	if (scene == 1000) {
		touch2 = true;
	}
	if (touch2 == true) {
		scene = 0;
		touch2 = false;
	}


	if (sun > -500 && touch3 == false) {   //sun
		sun = sun - 0.25;
	}
	if (sun == -500) {
		touch3 = true;
	}
	if (sun < 0 && touch3 == true) {
		sun = sun + 0.25;
	}
	if (sun == 0) {
		touch3 = false;
	}


	if (throw1 == true) {				// projectile 1 movement
		int* p = bezier(t1, p0, p1, p2, p3);
		projX1 = p[0];
		projY1 = p[1];
		t1 = t1 + 0.0003;
		if (projX1 + 85 >= glutGet(GLUT_WINDOW_WIDTH)) {
			projX1 = 0;
			projY1 = 0;
			throw1 = false;
			p1_range = 600;
			t1 = 0;
		}

		if (projY1 + 68 >= 300 && projY1 + 68 <= 330 && projX1 + 85 >= 60 + heli_moveX && projX1 + 85 <= 160 + heli_moveX) {     //if projectile 1 touches helicopter
			projX1 = 0;
			projY1 = 0;
			throw1 = false;
			p1_range = 600;
			t1 = 0;
		}


		if (projY1 + 68 >= 0 && projY1 + 68 <= 300 && projX1 + 85 == glutGet(GLUT_WINDOW_WIDTH) / 2 + 5) {     //if projectile 1 touches wall
			projX1 = 0;
			projY1 = 0;
			throw1 = false;
			p1_range = 600;
			t1 = 0;

		}
		if (projY1 + 68 >= 40 && projY1 + 68 <= 75 && projX1 + 85 >= 1195 && projX1 + 85 <= 1237) {     //if projectile 1 touches tank2
			projX1 = 0;
			projY1 = 0;
			throw1 = false;
			p1_range = 600;
			t1 = 0;
			health2 = health2 - 20;
			R2 = 1.0;
			G2 = 0.0;
			B2 = 0.0;
			glutTimerFunc(1000, time2, 0);


		}
		if (projY1 + 40 == 0) {																//if projectile hits ground
			projX1 = 0;
			projY1 = 0;
			throw1 = false;
			p1_range = 600;
			t1 = 0;
		}
	}




	if (throw2 == true) {				// projectile 2 movement
		int* p = bezier(t2, p0, p1, p2, p3);
		projX2 = -p[0];
		projY2 = p[1];
		t2 = t2 + 0.0003;
		if (projX2 <= -glutGet(GLUT_WINDOW_WIDTH)) {
			projX2 = 0;
			projY2 = 0;
			throw2 = false;
			p1_range = 600;
			t2 = 0;

		}


		if (projY2 + 68 >= 320 && projY2 + 68 <= 330 && projX2 + 1190 >= 60 + heli_moveX && projX2 + 1190 <= 160 + heli_moveX) {     //if projectile 2 touches helicopter
			projX2 = 0;
			projY2 = 0;
			throw2 = false;
			p1_range = 600;
			t2 = 0;
		}

		if (projY2 + 68 >= 0 && projY2 + 68 <= 300 && projX2 + 1190 == (glutGet(GLUT_WINDOW_WIDTH) / 2) + 10) {   //if projectile 2 touches wall
			projX2 = 0;
			projY2 = 0;
			throw2 = false;
			p1_range = 600;
			t2 = 0;

		}
		if (projY2 + 68 >= 40 && projY2 + 68 <= 75 && projX2 + 1190 <= 85 && projX2 + 1190 >= 43) {   //if projectile 2 touches tank1
			projX2 = 0;
			projY2 = 0;
			throw2 = false;
			p1_range = 600;
			t2 = 0;
			health1 = health1 - 20;
			hit1 = true;
			R = 1.0;
			G = 0.0;
			B = 0.0;
			glutTimerFunc(1000, time, 0);



		}

		if (projY2 + 68 == 40) {
			projX2 = 0;
			projY2 = 0;
			throw2 = false;
			p1_range = 600;
			t2 = 0;
		}
	}



	if (powerbar1 == true && powerbarMax1 < 50) {						// power charge bar for throw intensity    for player1
		power1 = power1 + 0.1;
		p1_range = p1_range + 1;
		powerbarMax1 = powerbarMax1 + 0.1;
	}

	if (powerbar2 == true && powerbarMax2 < 50) {						// power charge bar for throw intensity    for player2
		power2 = power2 + 0.1;
		p1_range = p1_range + 1;
		powerbarMax2 = powerbarMax2 + 0.1;
	}


	if (cloud1_movement < 1280) {
		cloud1_movement += 0.05;
	}
	else {
		cloud1_movement = 0;
	}
	if (cloud2_movement < 1280) {
		cloud2_movement += 0.05;
	}
	else {
		cloud2_movement = 0;
	}

	if (Sun_movement < 1280) {								// sun movement
		Sun_movement += 0.05;
	}
	else {
		Sun_movement = 0;
		if (alternator % 2 == 0) {							// daylight
			s1 = 0.98;
			s2 = 0.83;
			s3 = 0.25;
			backgroundR = 0.5;
			backgroundG = 0.8;
			backgroundB = 0.9;

		}
		else {												//nighttime
			s1 = 0.65;
			s2 = 0.65;
			s3 = 0.65;
			backgroundR = 0.02;
			backgroundG = 0.043;
			backgroundB = 0.203;
		}
	}


	if (heli_moveX < 1280) {
		heli_moveX += 0.1;
	}
	else {
		heli_moveX = 0;
	}

	if (jetMovement > -1280) {
		jetMovement = jetMovement - 0.5;
	}
	else {
		jetMovement = 0;
	}


	alternator++;

	glutPostRedisplay();



}





void main(int argc, char** argr) {
	glutInit(&argc, argr);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 600);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("Tank vs Tank");
	glutDisplayFunc(Display);
	glutTimerFunc(0, time, 0);
	glutTimerFunc(0, time2, 0);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(Anim);
	glPointSize(25);
	glClearColor(backgroundR, backgroundG, backgroundB, 0.0f);

	gluOrtho2D(0.0, 1280, 0.0, 600);
	glutMainLoop();
}













