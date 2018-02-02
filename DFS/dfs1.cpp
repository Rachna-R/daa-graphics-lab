/*TITLE   : DEPTH FIRST SEARCH ALGORITHM
  AUTHOR  : RACHNA RAMESH
  ROLL NO : 246

 INPUT : The number of nodes
*/

#include<iostream>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<unistd.h>
#include<GL/gl.h>

using namespace std;

int xc[100], yc[100],xLine[100], yLine[100], nodesDrawn = 0, pointsDrawn = 0, radius = 25, mouseX, mouseY, mouseLX, mouseLY, row, col;
int slope = 2, nodeCount;
int adjMatrix[10][10], Squeue[10], front = -1, rear = -1, color[3], parent[10], initialTime[10], finalTime[10], time1, k=0;

struct Color 						// Structure which stores the RGB values
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

int sign(int x)                                       //to determine the sign, used in bressenham's function
{
	return((x > 0) ? 1 : ((x < 0) ? -1 : 0));
}

void setPixelLine(float x, float y) 			//function to plot the points obtained from bressenham's algorithm
{
  	glColor3f(0.8, 0.0, 0.0 );
  	glBegin(GL_POINTS);
  	glVertex2f(x,y);
  	glEnd();
}

void circlePlotPoints( int x, int y )				//Plots the circle points obtained from the mid-point algorithm
{
	glPointSize( 1.0 );
	for ( int i = 0; i < nodesDrawn; i++ )
	{
		if ( color[i] == 0 )
			glColor3f(1.0, 1.0, 1.0);
		if ( color[i] == 1 )
			glColor3f( 0.5, 0.5, 0.5 );
		else if ( color[i] == 2 )			//assigns rgb values to the color array
			glColor3f( 0, 1, 0 );
		glBegin(GL_LINES);
			glVertex2i(xc[i] + x, yc[i] + y );
			glVertex2i((xc[i] + x), (-y + yc[i] ));
		glEnd();
	}
}

Color getPixelColor(GLint x, GLint y) 					//Function to read the color of the pixel(x, y)
{
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

/*void floodFill( int x, int y, int borderColor )
{
	Color color = getPixelColor( x, y );	
	Color fillColor;
	if ( borderColor == 0 )
	{
		fillColor.r = 1;
		fillColor.g = 1;
		fillColor.b = 1;
	}
	else if ( borderColor == 1 )
	{
		fillColor.r = 0.5;
		fillColor.g = 0.5;
		fillColor.b = 0.5;
	}
	else
	{
		fillColor.r = 0;
		fillColor.g = 1;
		fillColor.b = 0;
	}
	if(!(abs(color.r - fillColor.r) < 0.1 && abs( color.g - fillColor.g) < 0.1 && abs( color.b - fillColor.b) < 0.1))
	{
	        glColor3f ( fillColor.r, fillColor.g, fillColor.b );
	        glBegin( GL_POINTS );
	        	glVertex2i( x, y );
	        glEnd();
	        glFlush();
	        floodFill(x+1, y, borderColor);
	        floodFill(x, y+1, borderColor);
	        floodFill(x-1, y, borderColor);
	        floodFill(x, y-1, borderColor);
	}
	return;	
}*/

void midPointCircle()
{
	float p, x, y;
	p = 1 - radius;						// p is the decision parameter
	x = 0;
	y = radius;
	circlePlotPoints(x, y);					//plots the points (x, y) and others using the property of symmetry
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
		circlePlotPoints(x, y);
		circlePlotPoints(-x, y);
		circlePlotPoints(-y, x);
		circlePlotPoints(y, x);
		glFlush();
	}
	/*for ( int i = 0; i < nodesDrawn; i++ )
	{	
		floodFill( xc[i], yc[i] , color[i] ); 
	}*/
}

void printAdjMatrix()					//assigns values to the adjacency matrix
{
	adjMatrix[row][col] = 1;
	adjMatrix[col][row] = 1;
}

void bressenham(int x2, int y2, int x3, int y3, int slope)		//Bressenham's line drawing algorithm
{
	int dx, dy, dx2, dy2, x, y, s1, s2, p;
	if(slope == 2)							//if slope is negative, exchange x and y for both endpoints
	{
		int temp = x2;
		x2 = y2;
		y2 = temp;
		temp = x3;
		x3 = y3;
		y3 = temp; 
	}
	dx = abs(x3 - x2);
	dx2 = 2 * dx;
	dy = abs(y3 - y2);
	dy2 = 2 * dy;
	s1 = sign(x3 - x2);				 //s1 and s2 denote the sign of dx and dy respectively  
	s2 = sign(y3 - y2);	
	if(dy > dx)
	{
		int temp = dx;
		dx = dy;
		dy = temp;	
	}
	p = dy2 - dx;
	x = x2;
	y = y2;
	for(int i = 0; i <= dx; i++)
	{
		if( slope == 1)
			setPixelLine(x, y);
		else
			setPixelLine(y, x);
		x = x + s1;
		if(p >= 0)
		{
			y = y + s2;
			p = p + 2 * (dy - dx);
		}
		else
			p = p + dy2;
	}
	glFlush();			
}

void drawCharacter(int x, int y, char ch)
{
	//cout << "\nIn draw character";
	glColor3f(0.8, 0.0, 0.0);
	glRasterPos2i(x, y);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ch);
}

void drawString(int x, int y, char *str)
{
	glColor3f(0.8, 0.0, 0.0);
	glRasterPos2i(x, y);
	for( str; *str != '\0'; str++ )
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *str);
}

void drawCircleLine()
{
	//glClearColor(1.0, 1.0, 1.0, 0);
	for(int i = 0; i+1 < pointsDrawn && pointsDrawn > 1; i+=2)
	{
		if(abs(xLine[i+1] - xLine[i]) > abs(yLine[i+1] - yLine[i]))      //to determine the sign of slope
			slope = 1;
		else
			slope = 2;
		if(pointsDrawn % 2 == 0)
			printAdjMatrix();					 // to determine the number of times clicked to draw an edge
		bressenham(xLine[i], yLine[i], xLine[i+1], yLine[i+1], slope);
	}
	midPointCircle();	
}

int DFS_VISIT(int u)
{
	char ch[5];
	time1 = time1 + 1;
	initialTime[u] = time1;					//set the initial time for node u
	color[u] = 1;
	sprintf(ch, "%d", initialTime[u]);
	drawString(xc[u]-3, yc[u]+30, ch); 
	//cout << "\n";
	cout << u << " ";
	for(int v = 0; v < nodeCount; v++)
	{
		if(adjMatrix[u][v] == 1 && color[v] == 0)       //if an edge os present between nodes u and v and if v isnot visited
		{
			parent[v] = u;
			DFS_VISIT(v);				//visit node v
		}
		sleep(1.0);
		drawCircleLine();
	}
	color[u] = 2;                                          //make node u as visited
	time1 = time1 + 1;
	finalTime[u] = time1;					//assign the final time to node u
	sprintf(ch, "%d", finalTime[u]);
	drawString(xc[u]-3, yc[u]-35, ch); 
	//cout << "\n";
}	

void dfs()
{
	int arr[10];
	for( int i = 0; i < nodeCount; i++ )                 //initialize all nodes with color = white and parent = NULL
	{
		parent[i] = NULL; 
		color[i] = 0;
	}
	time1 = 0;
	cout << "\nOrder of traversal : \n";
	for(int i = 0; i < nodeCount; i++)
	{
		if(color[i] == 0)
		{
			DFS_VISIT(i);                    //if the color of a node s white then visit that node
			arr[k++] = i;
		}
	}
	cout << "\nStarting and finishing time : \n";
	for(int i = 0; i < nodeCount; i++)
		cout << i << " -> " << initialTime[i] << "/" << finalTime[i] << endl;
	cout << "\nDFS Finished !" ;
}

void mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if(nodesDrawn < nodeCount)
		{
			xc[nodesDrawn] = mouseX = x;
			yc[nodesDrawn] = mouseY = 500 - y;
			nodesDrawn++;
			
		}
		else
		{
			cout << endl;
			cout << "\nAdjacency Matrix : \n";
			for(int i = 0; i < nodeCount; i++)
			{
				for(int j = 0; j < nodeCount; j++)
					cout << adjMatrix[i][j] << " ";
				cout << endl;
			}
			cout << "\n";
			//bfs(startNode);
		}
	}
	if(state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
	{
		int i = 0;
		for(i = 0; i < nodesDrawn; i++)
		{
			int circleParam = ((pow(x - xc[i], 2) + (pow(500 - y - yc[i], 2) - (pow(radius, 2)))));
			if(circleParam < 0)
			{
				if(pointsDrawn % 2 == 0)
					row = i;
				else
					col = i;
				break;
			}	
		}
		if(i != nodesDrawn)
		{
			xLine[pointsDrawn] = mouseLX = xc[i];
			yLine[pointsDrawn] = mouseLY = yc[i];
			pointsDrawn++;
		}
	}
	drawCircleLine();
}

void keyboardPress(unsigned char key, int x, int y)
{
	switch(key)
	{
		case  's' : dfs();
			break;
		default : cout << "\nUnknown Key " << endl;
	}
}

void initialize()
{
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 10; j++)
			adjMatrix[i][j] = 0;
	for(int i = 0; i < 10; i++)
	{
		initialTime[i] = 0;
		finalTime[i] = 0;
	}
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
	initialize();
}

int main(int argc, char **argv)
{
	cout << "\nEnter the number of nodes : ";
	cin >> nodeCount;
	//dfs();
	glutInit(&argc, argv);
	init();
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboardPress); 
	glutDisplayFunc(drawCircleLine);
	glutMainLoop();
	return 0;
}
