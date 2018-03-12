#include<iostream>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<unistd.h>
#include<GL/gl.h>

using namespace std;

int xLine[100], yLine[100], pointsDrawn = 0, slope;

void setPixelLine(float x, float y)                      //function to plot the points obtained from bressenham's algorithm
{
  	glColor3f(0.8, 0.0, 0.0 );
  	glBegin(GL_POINTS);
  		glVertex2f(x,y);
  	glEnd();
}

void dda(int x2, int y2, int x3, int y3)
{
	int dx, dy, step;
	dx = x3 - x2;
	dy = y3 - y2;
	if(dx > dy)
		step = dx;
	else
		step = dy;

	float xInc = dx/(float)step;
	float yInc = dy/(float)step;

	float x = x2;
	float y = y2;
	for(int i = 1; i <= step; i++)
	{
		//cout << "\nIn for " << i; 
		setPixelLine(x, y);
		x += xInc;
		y += yInc;
	}
	glFlush();
}		
			
void drawCircleLine()
{
	//glClearColor(1.0, 1.0, 1.0, 0);
	cout << "\nDrawCircleLine";
	for(int i = 0; i+1 < pointsDrawn && pointsDrawn > 1; i+=2)
	{
		if(abs(xLine[i+1] - xLine[i]) > abs(yLine[i+1] - yLine[i]))      //to determine the sign of slope
			slope = 1;
		else
			slope = 2;
		dda(xLine[i], yLine[i], xLine[i+1], yLine[i+1]);
	}
	//midPointCircle();
}

void mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)     
	{
		xLine[pointsDrawn] = x;
		yLine[pointsDrawn++] = 500 - y;
	}
	drawCircleLine();
}

void init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Bressenham's Line Drawing Algorithm");
	glClear(GL_COLOR_BUFFER_BIT);	
	glClearColor(0.0, 0.0, 0.0, 0);
	glColor3f(1.0, 1.0, 1.0);
	gluOrtho2D(0, 800, 0, 500);
	//initAdjMatrix();
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	init();
	glutMouseFunc(mouse);
	//glutKeyboardFunc(keyboardPress); 
	glutDisplayFunc(drawCircleLine);
	glutMainLoop();
	return 0;
}
