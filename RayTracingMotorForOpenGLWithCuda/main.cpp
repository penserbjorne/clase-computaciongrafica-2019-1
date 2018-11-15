// Standar C++ libraries
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <ctime>

// Standar GL libraries
#include <GL/glew.h>
#include <GL/glut.h>

// My unhappy Code :D
#include "myObjectTypes.h"

// GL variables to use with GLUT
int g_iWindowWidth = 512;
int g_iWindowHeight = 512;
int g_iGLUTWindowHandle = 0;
int g_iErrorCode = 0;

// Global parameters to track current rotation
float g_fRotate1 = 0.0f;
float g_fRotate2 = 0.0f;
float g_fRotate3 = 0.0f;

// To store the number os ticks between frames
std::clock_t g_PreviousTicks;
std::clock_t g_CurrentTicks;

// Test
myCube* unCubo;

// OpenGL callback functions
void InitGL(int argc, char* argv[]);
void DisplayGL();	//	Render function for GLUT
void IdleGL();	//	Background processing - Update methods
void KeyboardGL(unsigned char c, int x, int y);
void MouseGL(int button, int state, int x, int y);
void MotionGL(int x, int y);	//	Invoked when the mouse moves within the window while one or more mouse buttons are pressed.
void PassiveMotionGL(int x, int y);		//	Invoked when the mouse moves within the window while no one button is pressed.
void ReshapeGL(int w, int h);

// Clean up resources
void Cleanup(int exitCode, bool bExit = true);

// Render a scene with 3D objects that perform rotations on all 3 axis.
void RenderScene();

// Drawer!
void DisplayGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	RenderScene();

	// Render Stuff
	glutSwapBuffers();
	glutPostRedisplay();
}

// To update the logic of our demo :D
void IdleGL(){
	// Update our simulation
	g_CurrentTicks = std::clock();
	float deltaTicks = (g_CurrentTicks - g_PreviousTicks);
	g_PreviousTicks = g_CurrentTicks;

	float fDeltaTime = deltaTicks / (float)CLOCKS_PER_SEC;

	// Rate of rotation in (degrees) per second
	const float fRotationRate = 50.0f;

	// Update our rotation parameters
	g_fRotate1 += ((fRotationRate + 10) * fDeltaTime);
	g_fRotate1 = fmodf(g_fRotate1, 360.0f);

	g_fRotate2 += ((fRotationRate + 5) * fDeltaTime);
	g_fRotate2 = fmodf(g_fRotate2, 360.0f);

	g_fRotate3 += ((fRotationRate + 20) * fDeltaTime);
	g_fRotate3 = fmodf(g_fRotate3, 360.0f);

	glutPostRedisplay();
}

void KeyboardGL(unsigned char c, int x, int y){

	switch (c){
		case '1':{
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);                         // White background
		}
		break;
		case '2':{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                         // Black background
		}
		break;
		case '3':{
			glClearColor(0.27f, 0.27f, 0.27f, 1.0f);                      // Dark-Gray background
		}
		break;
		case '4':{
			glClearColor(0.73f, 0.73f, 0.73f, 1.0f);                      // Light-Gray background
		}
		break;
		case 's':
		case 'S':{
			std::cout << "Shade Model: GL_SMOOTH" << std::endl;
			// Switch to smooth shading model
			glShadeModel(GL_SMOOTH);
		}
		break;
		case 'f':
		case 'F':{
			std::cout << "Shade Model: GL_FLAT" << std::endl;
			// Switch to flat shading model
			glShadeModel(GL_FLAT);
		}
		break;
		case 'r':
		case 'R':{
			std::cout << "Reset Parameters..." << std::endl;
			g_fRotate1 = g_fRotate2 = g_fRotate3 = 0.0f;
		}
		break;
		case '\033': // escape quits
		case '\015': // Enter quits
		case 'Q':    // Q quits
		case 'q':    // q (or escape) quits
		{
			// Cleanup up and quit
			Cleanup(0);
		}
		break;
	}

	glutPostRedisplay();
}

void MouseGL(int button, int state, int x, int y){

}

void MotionGL(int x, int y){

}

void PassiveMotionGL(int x, int y){

}

// Only destroy the render window we have created.
void Cleanup(int errorCode, bool bExit){

	if (g_iGLUTWindowHandle != 0){
		glutDestroyWindow(g_iGLUTWindowHandle);
		g_iGLUTWindowHandle = 0;
	}

	if (bExit){
		exit(errorCode);
	}
}

void ReshapeGL(int w, int h){

	std::cout << "ReshapGL( " << w << ", " << h << " );" << std::endl;

	if (h == 0){                                    // Prevent a divide-by-zero error
		h = 1;                                      // Making Height Equal One
	}

	g_iWindowWidth = w;
	g_iWindowHeight = h;

	glViewport(0, 0, g_iWindowWidth, g_iWindowHeight);

	// Setup the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)g_iWindowWidth / (GLdouble)g_iWindowHeight, 0.1, 100.0);

	glutPostRedisplay();
}

// Setup the OpenGL and GLUt cotnext
void InitGL(int argc, char* argv[]){

	std::cout << "Initialise OpenGL..." << std::endl;

	glutInit(&argc, argv);
	int iScreenWidth = glutGet(GLUT_SCREEN_WIDTH);
	int iScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition((iScreenWidth - g_iWindowWidth) / 2,
		(iScreenHeight - g_iWindowHeight) / 2);
	glutInitWindowSize(g_iWindowWidth, g_iWindowHeight);

	g_iGLUTWindowHandle = glutCreateWindow("OpenGL");

	// Init GLEW
	if (glewInit() != GLEW_OK){
		std::cerr << "Failed to initialize GLEW." << std::endl;
		exit(-1);
	}

	// is VBO supported?
	if (!glewIsSupported("GL_VERSION_2_0") && !glewIsSupported("GL_ARB_vertex_buffer_object"))
	{
		std::cerr << "ARB_vertex_buffer_object not supported!" << std::endl;
		exit(-2);
	}
	
	// Register GLUT callbacks
	glutDisplayFunc(DisplayGL);
	glutIdleFunc(IdleGL);
	glutMouseFunc(MouseGL);
	glutMotionFunc(MotionGL);
	glutPassiveMotionFunc(PassiveMotionGL);
	glutKeyboardFunc(KeyboardGL);
	glutReshapeFunc(ReshapeGL);

	// Setup initial GL State
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);

	glShadeModel(GL_SMOOTH);
	std::cout << "Initialise OpenGL: Success!" << std::endl;

	unCubo = new myCube();
}

int main(int argc, char* argv[]){

	// Capture the previous time to calculate the delta time on the next frame
	g_PreviousTicks = std::clock();

	InitGL(argc, argv);
	glutMainLoop();
}

void RenderScene(){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	glTranslatef(-1.5f, 1.0f, -6.0f);                                     // Translate back and to the left
	glPushMatrix();                                                         // Push the current modelview matrix on the matrix stack
	glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);                               // Rotate on all 3 axis
	unCubo->draw();
	glPopMatrix();

	glTranslatef(3.0f, 0.0f, 0.0f);                                        // Translate right
	glPushMatrix();
	glRotatef(g_fRotate2, 1.0f, 1.0f, 1.0f);
	unCubo->draw();
	glPopMatrix();

	glTranslatef(-1.5f, -3.0f, 0.0f);                                     // Back to center and lower screen
	glPushMatrix();
	glRotatef(g_fRotate3, 1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);                                          // Yellow
	glutSolidSphere(1.0f, 16, 16);                                        // Use GLUT to draw a solid sphere
	glScalef(1.01f, 1.01f, 1.01f);
	glColor3f(1.0f, 0.0f, 0.0f);                                          // Red
	glutWireSphere(1.0f, 16, 16);                                         // Use GLUT to draw a wireframe sphere
	glPopMatrix();
}