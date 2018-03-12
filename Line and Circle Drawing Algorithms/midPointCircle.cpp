#include<iostream>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<unistd.h>
#include<GL/gl.h>

using namespace std;

int xc[100], yc[100],nodesDrawn = 0, radius = 30;

void circlePlotPoints( int x, int y )                       //Plots the circle points obtained from the mid-point algorithm
{
	glPointSize( 1.0 );
	for ( int i = 0; i < nodesDrawn; i++ )
	{
		glColor3f(1.0, 1.0, 1.0);               
		glBegin(GL_LINES);
			glVertex2i(xc[i] + x, yc[i] + y );
			glVertex2i((xc[i] + x), (-y + yc[i] ));
		glEnd();
	}
}

void midPointCircle()
{
	float p, x, y;
	p = 1 - radius;                          // p is the decision parameter
	x = 0;
	y = radius;
	circlePlotPoints(x, y);                  //plots the points (x, y)
	circlePlotPoints(-x, y);
	circlePlotPoints(-y, x);
	circlePlotPoints(y, x);
	while(x <= y)
	{	
		x = x + 1;
		if(p < 0)
		{
			p = p + 2*x + 1;
		}
		else
		{
			y = y - 1;
			p = p + 2*x + 1 - 2*y;
		}
		circlePlotPoints(x, y);                  //plots the points (x, y)
		circlePlotPoints(-x, y);
		circlePlotPoints(-y, x);
		circlePlotPoints(y, x);
		glFlush();
	}
}

void drawCircleLine()
{
	midPointCircle();
}

void mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		xc[nodesDrawn] = x;
		yc[nodesDrawn] = 500 - y;
		nodesDrawn++;
	}
	drawCircleLine();
}

void init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Breadth First Search");
	glClear(GL_COLOR_BUFFER_BIT);	
	glClearColor(1.0, 1.0, 1.0, 0);
	glColor3f(1.0, 1.0, 1.0);
	gluOrtho2D(0, 800, 0, 500);
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
