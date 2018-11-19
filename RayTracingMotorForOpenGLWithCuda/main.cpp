// Standar C++ libraries
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <ctime>

// Standar GL libraries
#include <GL/glew.h>
#include <GL/glut.h>

// My unhappy Code >;v
#include "myObjectTypes.h"
#include "myCameraFPS.h"

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
float deltaTicks, fDeltaTime;

// Test
myCameraFPS camara;
float lastX = 0.0, lastY = 0.0;

myCube* unCubo;
myCylinder* unCilindro;
mySphere* unaEsfera;
myPrism* unPrisma3;
myPrism* unPrisma5;
myPrism* unPrisma7;
myPrism* unPrisma9;
myPlane* unPlano;
void RenderScene();
void RenderScene1();

// OpenGL callback functions
void InitGL(int argc, char* argv[]);
void DisplayGL();	//	Render function for GLUT
void IdleGL();	//	Background processing - Update methods
void KeyboardGL(unsigned char c, int x, int y);
void SpecialFunc(int key, int x, int y);
void MouseGL(int button, int state, int x, int y);
void MotionGL(int x, int y);	//	Invoked when the mouse moves within the window while one or more mouse buttons are pressed.
void PassiveMotionGL(int x, int y);		//	Invoked when the mouse moves within the window while no one button is pressed.
void ReshapeGL(int w, int h);
void Cleanup(int exitCode, bool bExit = true);

// Drawer!
void DisplayGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE); // Renormalize scaled normals so that lighting still works properly.
	glMatrixMode(GL_MODELVIEW);	// Switch to modelview matrix mode

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	camara.setViewMatrix();
	glTranslatef(0, 0, 0);

	unCilindro->draw();
	RenderScene();
	//RenderScene1();

	// Render Stuff
	glutSwapBuffers();
	glutPostRedisplay();
}

// To update the logic of our demo :D
void IdleGL(){
	// Update our simulation
	g_CurrentTicks = std::clock();
	deltaTicks = (g_CurrentTicks - g_PreviousTicks);
	g_PreviousTicks = g_CurrentTicks;
	fDeltaTime = deltaTicks / (float)CLOCKS_PER_SEC;

	// Rate of rotation in (degrees) per second
	const float fRotationRate = 25.0f;

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
		case 'w':
		case 'W': {
			camara.processKeyboard(Camera_Movement::C_FORWARD, fDeltaTime);
		}
		break;
		case 's':
		case 'S':{
			camara.processKeyboard(Camera_Movement::C_BACKWARD, fDeltaTime);
		}
		break;
		case 'd':
		case 'D': {
			camara.processKeyboard(Camera_Movement::C_RIGHT, fDeltaTime);
		}
		break;
		case 'a':
		case 'A': {
			camara.processKeyboard(Camera_Movement::C_LEFT, fDeltaTime);
		}
		break;
		case 'f':
		case 'F':{
			//std::cout << "Shade Model: GL_FLAT" << std::endl;
			// Switch to flat shading model
			//glShadeModel(GL_FLAT);
			// Switch to smooth shading model
			//glShadeModel(GL_SMOOTH);
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

	//glutPostRedisplay();
}

void SpecialFunc(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		camara.processKeyboard(Camera_Movement::C_FORWARD, fDeltaTime);
		break;
	case GLUT_KEY_DOWN:
		camara.processKeyboard(Camera_Movement::C_BACKWARD, fDeltaTime);
		break;
	case GLUT_KEY_LEFT:
		camara.processKeyboard(Camera_Movement::C_LEFT, fDeltaTime);
		break;
	case GLUT_KEY_RIGHT:
		camara.processKeyboard(Camera_Movement::C_RIGHT, fDeltaTime);
		break;
	}
}

void MouseGL(int button, int state, int x, int y){
	std::cout << "MouseGL; Boton:" << button << " X:"<< x << " Y:" << y << std::endl;
}

void MotionGL(int x, int y){
	float xoffset = lastX - x;
	float yoffset = lastY - y;

	std::cout << "MotionGL; X:" << x << " Y:" << y << std::endl;

	camara.processMouseMovement(-xoffset, yoffset, true);
	lastX = x;
	lastY = y;
}

void PassiveMotionGL(int x, int y){
	std::cout << "PassiveMotionGL; X:" << x << " Y:" << y << std::endl;

	lastX = x;
	lastY = y;
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

Light g_SunLight(GL_LIGHT0, glm::vec4(0, 0, 0, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), glm::vec4(0, 0, 0, 1));

// Material properties
Material g_SunMaterial(glm::vec4(0, 0, 0, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1));
Material g_EarthMaterial(glm::vec4(0.2, 0.2, 0.2, 1.0), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), glm::vec4(0, 0, 0, 1), 50);
Material g_MoonMaterial(glm::vec4(0.1, 0.1, 0.1, 1.0), glm::vec4(1, 1, 1, 1), glm::vec4(0.2, 0.2, 0.2, 1), glm::vec4(0, 0, 0, 1), 10);

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

	g_iGLUTWindowHandle = glutCreateWindow("Ray Tracing Motor for OpenGL with CUDA by Penserbjorne");

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
	glutSpecialFunc(SpecialFunc);
	glutReshapeFunc(ReshapeGL);

	// Setup initial GL State
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black light
	glClearDepth(1.0f);

	std::cout << "Initialise OpenGL: Success!" << std::endl;

	// Specify a global ambient
	GLfloat globalAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

	unCubo = new myCube();
	unCilindro = new myCylinder(1.0f, 1.0f);
	unaEsfera = new mySphere(1.0f, 20.0f, 20.0f);
	unPrisma3 = new myPrism(1.0f, 1.0f, 3);
	unPrisma5 = new myPrism(1.0f, 1.0f, 5);
	unPrisma7 = new myPrism(1.0f, 1.0f, 7);
	unPrisma9 = new myPrism(1.0f, 1.0f, 9);
	unPlano = new myPlane();
}

int main(int argc, char* argv[]){

	// Capture the previous time to calculate the delta time on the next frame
	g_PreviousTicks = std::clock();

	InitGL(argc, argv);
	glutMainLoop();
}

void RenderScene1()
{
	glMatrixMode(GL_MODELVIEW);	// Switch to modelview matrix mode
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();

	// Move the scene
	glTranslatef(0.0f, 0.0f, -100.0f);

	// Sun
	glPushMatrix();
		glRotatef(g_fRotate1, 0.0f, -1.0f, 0.0f);
		glTranslatef(60.0f, 0.0f, 0.0f);
		g_SunLight.Activate();
		unCilindro->loadTexture("./textures/paper.jpg");
		g_SunMaterial.Apply();
		unCilindro->draw();
	glPopMatrix();

	// Earth
	glPushMatrix();
		glRotatef(g_fRotate2, 0.0f, 0.0f, -1.0f); // Rotate the earth around it's axis
		glScalef(12.756f, 12.756f, 12.756f);  // The earth's diameter is about 12,756 Km
		unaEsfera->loadTexture("./textures/mario.png");
		g_EarthMaterial.Apply();
		unaEsfera->draw();
	glPopMatrix();

	// Moon
	glPushMatrix();
		glRotatef(g_fRotate2, 0.0f, 0.0f, -1.0f);// Rotate the moon around it's axis
		glTranslatef(50.0f, 0.0f, 0.0f); // Translate the moon away from the earth
		glScalef(3.476f, 3.476f, 3.476f);
		unCubo->loadTexture("./textures/grunge.jpg");
		g_MoonMaterial.Apply();
		unaEsfera->draw();
	glPopMatrix();
}

void RenderScene(){

	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);
	glLoadIdentity();

	glPushMatrix();

	glTranslatef(-1.5f, 4.5f, -12.0f);
	glPushMatrix();
		glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
		unCubo->loadTexture("./textures/uno.png");
		g_EarthMaterial.Apply();
		unCubo->draw();
	glPopMatrix();

	
	glTranslatef(3.0f, 0.0f, 0.0f);
	glPushMatrix();
		glRotatef(g_fRotate2, 1.0f, 1.0f, 1.0f);
		unCilindro->loadTexture("./textures/dos.png");
		g_EarthMaterial.Apply();
		unCilindro->draw();
	glPopMatrix();

	
	glTranslatef(-3.0f, -3.0f, 0.0f);
	glPushMatrix();
		glRotatef(g_fRotate3, 1.0f, 1.0f, 1.0f);
		unaEsfera->loadTexture("./textures/tres.png");
		g_EarthMaterial.Apply();
		unaEsfera->draw();
	glPopMatrix();
	
	glTranslatef(3.0f, 0.0f, 0.0f);
	glPushMatrix();
		glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
		unPlano->loadTexture("./textures/cuatro.png");
		g_EarthMaterial.Apply();
		unPlano->draw();
	glPopMatrix();

	glTranslatef(-3.0f, -3.0f, 0.0f);
	glPushMatrix();
		glRotatef(g_fRotate2, 1.0f, 1.0f, 1.0f);
		unPrisma3->loadTexture("./textures/cinco.png");
		unPrisma3->draw();
	glPopMatrix();

	glTranslatef(3.0f, 0.0f, 0.0f);
	glPushMatrix();
		glRotatef(g_fRotate3, 1.0f, 1.0f, 1.0f);
		unPrisma5->loadTexture("./textures/seis.png");
		unPrisma5->draw();
	glPopMatrix();

	glTranslatef(-3.0f, -3.0f, 0.0f);
	glPushMatrix();
		glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
		unPrisma7->loadTexture("./textures/siete.png");
		unPrisma7->draw();
	glPopMatrix();

	glTranslatef(3.0f, 0.0f, 0.0f);
	glPushMatrix();
		glRotatef(g_fRotate2, 1.0f, 1.0f, 1.0f);
		unPrisma9->loadTexture("./textures/uno.png");
		unPrisma9->draw();
	glPopMatrix();
	
	glPopMatrix();
}
