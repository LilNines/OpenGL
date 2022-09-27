//
//  main1.cpp
//

#include "glut.h"
#include "Sleep.h"

// function prototypes
void keyboard(unsigned char key, int x, int y); // for user input
void special(int special_key, int x, int y);
void idle(); //for rotation
void display ();

//declare global variables here
//rotation
float pentagonDegrees = 0.0f;
float degreesIncrement = 2.0f;
//move
float xPosition = 0.0f;
float xIncrement = 0.01f;
float yPosition = 0.75f;
float yIncrement = 0.01f;


int main (int argc, char** argv)
{
	// initialize OpenGL; pass it the command line arguments
	glutInit(&argc, argv);	
	
	glutCreateWindow("First OpenGL Program");
	glutKeyboardFunc(keyboard); //to handle keyboard input of ASCII keys immediately
	glutSpecialFunc(special); //to handle the special keys, such as the arrow keys
	glutIdleFunc(idle);
	glutDisplayFunc(display);

	glutMainLoop();  // contains an infinite loop, so it never returns
	return 1;
}

//add user input
//The user will be able to reset the triangle to its starting position with the [R] key and exit the program with the [ESC] key.
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'R':
	case 'r':
		xPosition = 0.0;
		break;
	case 'a':
	case 'A':
		xPosition -= xIncrement; //move left
		break;
	case 'D':
	case 'd':
		xPosition += xIncrement; //move right
		break;
	case 'W':
	case 'w':
		yPosition += yIncrement; //move up
		break;
	case 'S':
	case 's':
		yPosition -= yIncrement; //move down
		break;
	case 27: // on [ESC]
		exit(0); // normal exit
		break;
	}
}

void special(int special_key, int x, int y)
{
	switch (special_key)
	{
	case GLUT_KEY_LEFT:
		pentagonDegrees += degreesIncrement; //spin counterclockwise
		break;
	case GLUT_KEY_RIGHT:
		pentagonDegrees -= degreesIncrement; //spin clockwise
		break;
	}
}

void idle()
{
	// The angle will be increased every time OpenGL is idle.(automatically)
	//pentagonDegrees += 2.0f;
	//if (pentagonDegrees >= 360.0f)
	//	pentagonDegrees -= 360.0f;

	//move the triangle automatically
	//xPosition += xIncrement;
	//if (xPosition > 1.0f || xPosition < -1.0f)
	//	xIncrement = -xIncrement;

	sleep(0.01);  // wait for 0.01 seconds
	// tell OpenGL to redisplay the window
	glutPostRedisplay();
}

void display ()
{
	//tells OpenGL that we want our matrix commands (below) to apply to the modelview matrix, 
	//which is the normal one and controls where things appear on the screen.
	//告诉 OpenGL 我们希望我们的矩阵命令应用于模型视图矩阵，这是一个正常的矩阵，并控制屏幕上出现的位置。
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	// clear the screen, any drawing before here will not display

	//to move the triangle
	//The green triangle should be one quarter of its previous size (glScaled) and 
	//The green triangle should now move back and forth across the top of the screen(glTranslatef)
	glPushMatrix();
	glTranslatef(xPosition, yPosition, 0.0f); //The three parameters are how far to move in the X, Y, and Z directions.
	glScalef(0.25f, 0.25f, 0.25f);
    //display a green trangle //change to brown octagon
	glColor3f(0.0f,1.0f,0.0f); // float, range [0.0f, 1.0f] green
	glBegin(GL_POLYGON);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(0.0f, -1.0f);
	glEnd();
	glPopMatrix(); //end of move

	//to rotate the pentagon
    glPushMatrix();    // saves existing top matrix
	glRotatef(pentagonDegrees, 0.0f, 0.0f, 1.0f);
	//display an orange pentagon //change to purple hexagon
	glColor3f(0.5f, 0.0f, 0.5f); // float, range [0.0f, 1.0f] purple
	glBegin(GL_POLYGON);
	glVertex2f(-0.5f, 0.0f);
	glVertex2f(0.0f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(1.0f, 0.0f); //add for hexagon.
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.0f, 0.5f);
	glEnd();
    glPopMatrix(); // restores matrix from glPushMatrix
	
	
	// ensure that all buffered OpenGL commands get done
	glFlush();	
}

