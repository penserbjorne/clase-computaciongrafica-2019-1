// Standar C++ libraries
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <ctime>

// Standar GL libraries
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

// OpenGL callback functions
void InitGL(int argc, char* argv[]);
void DisplayGL();	//	Render function for GLUT
void IdleGL();	//	Background processing - Update methods
void KeyboardGL(unsigned char c, int x, int y);
void MouseGL(int button, int state, int x, int y);
void MotionGL(int x, int y);	//	Invoked when the mouse moves within the window while one or more mouse buttons are pressed.
void PassiveMotionGL(int x, int y);		//	Invoked when the mouse moves within the window while no one button is pressed.
void ReshapeGL(int w, int h);

// To draw some primitives
void DrawRectangle(float width, float height);
void DrawCircle(float radius, int numSides = 8);
void DrawTriangle(float2 p1, float2 p2, float2 p3);

// Clean up resources
void Cleanup(int exitCode, bool bExit = true);

// Render functions from the different scenes
// Render a simple scene with 2D primitives
void RenderScene1();
// Render a slightly more complex scene using different colors
void RenderScene2();
// Render a scene with animated transformations
void RenderScene3();
// Render a scene with 3D objects that perform rotations on all 3 axis.
void RenderScene4();

// Drawer!
void DisplayGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	g_fRotate1 += (fRotationRate * fDeltaTime);
	g_fRotate1 = fmodf(g_fRotate1, 360.0f);

	g_fRotate2 += (fRotationRate * fDeltaTime);
	g_fRotate2 = fmodf(g_fRotate2, 360.0f);

	g_fRotate3 += (fRotationRate * fDeltaTime);
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
}

int main(int argc, char* argv[]){

	// Capture the previous time to calculate the delta time on the next frame
	g_PreviousTicks = std::clock();

	InitGL(argc, argv);
	glutMainLoop();
}

// Primitive functions
void DrawTriangle(float2 p1, float2 p2, float2 p3){

	glBegin(GL_TRIANGLES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glVertex2f(p3.x, p3.y);
	glEnd();
}

void DrawRectangle(float width, float height){

	const float w = width / 2.0f;
	const float h = height / 2.0f;

	glBegin(GL_QUADS);
	glVertex2f(-w, h);   // Top-Left
	glVertex2f(w, h);   // Top-Right
	glVertex2f(w, -h);   // Bottom-Right
	glVertex2f(-w, -h);   // Bottom-Left
	glEnd();

}

void DrawCircle(float radius, int numSides /* = 8 */){

	const float step = M_PI / numSides;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for (float angle = 0.0f; angle < (2.0f * M_PI); angle += step)
	{
		glVertex2f(radius * sinf(angle), radius * cosf(angle));
	}
	glVertex2f(0.0f, radius); // One more vertex to close the circle
	glEnd();
}

// Draw functions
void RenderScene1(){

	glMatrixMode(GL_MODELVIEW);                                           // Switch to modelview matrix mode
	glLoadIdentity();                                                       // Load the identity matrix

	glTranslatef(-1.5f, 1.0f, -6.0f);                                     // Translate our view matrix back and a bit to the left.
	glColor3f(1.0f, 0.0f, 0.0f);                                          // Set Color to red
	DrawTriangle(float2(0.0f, 1.0f), float2(-1.0f, -1.0f), float2(1.0f, -1.0f));

	glTranslatef(3.0f, 0.0f, 0.0f);                                       // Shift view 3 units to the right
	glColor3f(0.0f, 0.0f, 1.0f);                                          // Set Color to blue
	DrawRectangle(2.0f, 2.0f);

	glTranslatef(-1.5f, -3.0f, 0.0f);                                     // Back to center and lower screen
	glColor3f(1.0f, 1.0f, 0.0f);                                          // Set color to yellow
	DrawCircle(1.0f, 16);
}

void RenderScene2(){

	glMatrixMode(GL_MODELVIEW);                                           // Switch to modelview matrix mode
	glLoadIdentity();                                                       // Load the identity matrix

	glTranslatef(-1.5f, 1.0f, -6.0f);                                     // Translate back and to the left
	// Draw a triangle with different colors on each vertex
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);                                      // Red
	glVertex2f(0.0f, 1.0f);                                           // Top-Center

	glColor3f(0.0f, 1.0f, 0.0f);                                      // Green
	glVertex2f(-1.0f, -1.0f);                                         // Bottom-Left

	glColor3f(0.0f, 0.0f, 1.0f);                                      // Blue
	glVertex2f(1.0f, -1.0f);                                          // Bottom-Right
	glEnd();

	glTranslatef(3.0f, 0.0f, 0.0f);                                       // Translate right
	// Draw a rectangle with different colors on each vertex
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);                                      // Red
	glVertex2f(-1.0f, 1.0f);                                          // Top-Left

	glColor3f(0.0f, 1.0f, 0.0f);                                      // Green
	glVertex2f(1.0f, 1.0f);                                           // Top-Right

	glColor3f(0.0f, 0.0f, 1.0f);                                      // Blue
	glVertex2f(1.0f, -1.0f);                                          // Bottom-Right

	glColor3f(1.0f, 1.0f, 1.0f);                                      // White
	glVertex2f(-1.0f, -1.0f);                                         // Bottom-Left
	glEnd();

	glTranslatef(-1.5f, -3.0f, 0.0f);                                     // Back to center and lower screen

	// Draw a circle with blended red/blue vertices.
	const float step = M_PI / 16;
	const float radius = 1.0f;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	for (float angle = 0.0f; angle < (2.0f * M_PI); angle += step){

		float fSin = sinf(angle);
		float fCos = cosf(angle);

		glColor3f((fCos + 1.0f) * 0.5f, (fSin + 1.0f) * 0.5f, 0.0f);
		glVertex2f(radius * fSin, radius * fCos);
	}
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(0.0f, radius); // One more vertex to close the circle
	glEnd();
}

void RenderScene3(){

	glMatrixMode(GL_MODELVIEW);                                           // Switch to modelview matrix mode
	glLoadIdentity();                                                       // Load the identity matrix

	glTranslatef(-1.5f, 1.0f, -6.0f);                                     // Translate back and to the left
	glPushMatrix();                                                         // Push the current transformation onto the matrix stack
	glRotatef(g_fRotate1, 0.0f, 0.0f, 1.0f);
	// Draw a triangle with different colors on each vertex
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);                                      // Red
	glVertex2f(0.0f, 1.0f);                                           // Top-Center

	glColor3f(0.0f, 1.0f, 0.0f);                                      // Green
	glVertex2f(-1.0f, -1.0f);                                         // Bottom-Left

	glColor3f(0.0f, 0.0f, 1.0f);                                      // Blue
	glVertex2f(1.0f, -1.0f);                                          // Bottom-Right
	glEnd();
	glPopMatrix();

	glTranslatef(3.0f, 0.0f, 0.0f);                                       // Translate right
	glPushMatrix();
	glRotatef(g_fRotate2, 0.0f, 0.0f, 1.0f);
	// Draw a rectangle with different colors on each vertex
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);                                      // Red
	glVertex2f(-1.0f, 1.0f);                                          // Top-Left

	glColor3f(0.0f, 1.0f, 0.0f);                                      // Green
	glVertex2f(1.0f, 1.0f);                                           // Top-Right

	glColor3f(0.0f, 0.0f, 1.0f);                                      // Blue
	glVertex2f(1.0f, -1.0f);                                          // Bottom-Right

	glColor3f(1.0f, 1.0f, 1.0f);                                      // White
	glVertex2f(-1.0f, -1.0f);                                         // Bottom-Left
	glEnd();
	glPopMatrix();

	glTranslatef(-1.5f, -3.0f, 0.0f);                                     // Back to center and lower screen
	glPushMatrix();
	glRotatef(g_fRotate3, 0.0f, 0.0f, 1.0f);
	// Draw a circle with blended red/blue vertecies
	const float step = M_PI / 16;
	const float radius = 1.0f;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	for (float angle = 0.0f; angle < (2.0f * M_PI); angle += step){

		float fSin = sinf(angle);
		float fCos = cosf(angle);

		glColor3f((fCos + 1.0f) * 0.5f, (fSin + 1.0f) * 0.5f, 0.0f);
		glVertex2f(radius * fSin, radius * fCos);
	}
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(0.0f, radius); // One more vertex to close the circle
	glEnd();
	glPopMatrix();
}

void RenderScene4(){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	glTranslatef(-1.5f, 1.0f, -6.0f);                                     // Translate back and to the left

	glPushMatrix();                                                         // Push the current modelview matrix on the matrix stack
	glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);                               // Rotate on all 3 axis
	glBegin(GL_TRIANGLES);                                                // Draw a pyramid
	glColor3f(1.0f, 0.0f, 0.0f);                                      // Red
	glVertex3f(0.0f, 1.0f, 0.0f);                                     // Top of front face
	glColor3f(0.0f, 1.0f, 0.0f);                                      // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);                                   // Left of front face
	glColor3f(0.0f, 0.0f, 1.0f);                                      // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);                                    // Right of front face

	glColor3f(1.0f, 0.0f, 0.0f);                                      // Red
	glVertex3f(0.0f, 1.0f, 0.0f);                                     // Top of right face
	glColor3f(0.0f, 0.0f, 1.0f);                                      // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);                                    // Left of right face
	glColor3f(0.0f, 1.0f, 0.0f);                                      // Green
	glVertex3f(1.0f, -1.0f, -1.0f);                                   // Right of right face

	glColor3f(1.0f, 0.0f, 0.0f);                                      // Red
	glVertex3f(0.0f, 1.0f, 0.0f);                                     // Top of back face
	glColor3f(0.0f, 1.0f, 0.0f);                                      // Green
	glVertex3f(1.0f, -1.0f, -1.0f);                                   // Left of back face
	glColor3f(0.0f, 0.0f, 1.0f);                                      // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);                                  // Right of back face

	glColor3f(1.0f, 0.0f, 0.0f);                                      // Red
	glVertex3f(0.0f, 1.0f, 0.0f);                                     // Top of left face
	glColor3f(0.0f, 0.0f, 1.0f);                                      // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);                                  // Left of left face
	glColor3f(0.0f, 1.0f, 0.0f);                                      // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);                                   // Right of left face
	glEnd();

	// Render a quad for the bottom of our pyramid
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);                                      // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);                                   // Left/right of front/left face
	glColor3f(0.0f, 0.0f, 1.0f);                                      // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);                                    // Right/left of front/right face
	glColor3f(0.0f, 1.0f, 0.0f);                                      // Green
	glVertex3f(1.0f, -1.0f, -1.0f);                                   // Right/left of right/back face
	glColor3f(0.0f, 0.0f, 1.0f);                                      // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);                                  // Left/right of right/back face
	glEnd();
	glPopMatrix();

	glTranslatef(3.0f, 0.0f, 0.0f);                                        // Translate right
	glPushMatrix();                                                         // Push the current modelview matrix on the matrix stack
	glRotatef(g_fRotate2, 1.0f, 1.0f, 1.0f);                              // Rotate the primitive on all 3 axis
	glBegin(GL_QUADS);
	// Top face
	glColor3f(0.0f, 1.0f, 0.0f);                                   // Green
	glVertex3f(1.0f, 1.0f, -1.0f);                                   // Top-right of top face
	glVertex3f(-1.0f, 1.0f, -1.0f);                                   // Top-left of top face
	glVertex3f(-1.0f, 1.0f, 1.0f);                                   // Bottom-left of top face
	glVertex3f(1.0f, 1.0f, 1.0f);                                   // Bottom-right of top face

	// Bottom face
	glColor3f(1.0f, 0.5f, 0.0f);                                  // Orange
	glVertex3f(1.0f, -1.0f, -1.0f);                                  // Top-right of bottom face
	glVertex3f(-1.0f, -1.0f, -1.0f);                                  // Top-left of bottom face
	glVertex3f(-1.0f, -1.0f, 1.0f);                                  // Bottom-left of bottom face
	glVertex3f(1.0f, -1.0f, 1.0f);                                  // Bottom-right of bottom face

	// Front face
	glColor3f(1.0f, 0.0f, 0.0f);                                  // Red
	glVertex3f(1.0f, 1.0f, 1.0f);                                  // Top-Right of front face
	glVertex3f(-1.0f, 1.0f, 1.0f);                                  // Top-left of front face
	glVertex3f(-1.0f, -1.0f, 1.0f);                                  // Bottom-left of front face
	glVertex3f(1.0f, -1.0f, 1.0f);                                  // Bottom-right of front face

	// Back face
	glColor3f(1.0f, 1.0f, 0.0f);                                 // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);                                 // Bottom-Left of back face
	glVertex3f(-1.0f, -1.0f, -1.0f);                                 // Bottom-Right of back face
	glVertex3f(-1.0f, 1.0f, -1.0f);                                 // Top-Right of back face
	glVertex3f(1.0f, 1.0f, -1.0f);                                 // Top-Left of back face

	// Left face
	glColor3f(0.0f, 0.0f, 1.0f);                                   // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);                                   // Top-Right of left face
	glVertex3f(-1.0f, 1.0f, -1.0f);                                   // Top-Left of left face
	glVertex3f(-1.0f, -1.0f, -1.0f);                                   // Bottom-Left of left face
	glVertex3f(-1.0f, -1.0f, 1.0f);                                   // Bottom-Right of left face

	// Right face
	glColor3f(1.0f, 0.0f, 1.0f);                                   // Violet
	glVertex3f(1.0f, 1.0f, 1.0f);                                   // Top-Right of left face
	glVertex3f(1.0f, 1.0f, -1.0f);                                   // Top-Left of left face
	glVertex3f(1.0f, -1.0f, -1.0f);                                   // Bottom-Left of left face
	glVertex3f(1.0f, -1.0f, 1.0f);                                   // Bottom-Right of left face
	glEnd();
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