// Standar C++ libraries
#define _USE_MATH_DEFINES
#include <iostream>
#include <ctime>

// Standar GL libraries
#include <GL/glew.h>
#include <GL/glut.h>

// My unhappy Code >;v
#include "myPrimitives.h"
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
myGrid* unGrid;
my3dObjectBase* unObjeto1;
my3dObjectBase* unObjeto2;
my3dObjectBase* unObjeto3;

// Sun light
Light g_SunLight(GL_LIGHT0, glm::vec4(0, 0, 0, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), glm::vec4(0, 0, 0, 1));

// Material properties
Material g_SunMaterial(glm::vec4(0, 0, 0, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1));
Material g_EarthMaterial(glm::vec4(0.2, 0.2, 0.2, 1.0), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), glm::vec4(0, 0, 0, 1), 50);
Material g_MoonMaterial(glm::vec4(0.1, 0.1, 0.1, 1.0), glm::vec4(1, 1, 1, 1), glm::vec4(0.2, 0.2, 0.2, 1), glm::vec4(0, 0, 0, 1), 10);

GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };

/*This is for the properties of the point light*/
GLfloat light_ambient[] = { 1.0, 0.0, 0.2, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 0.0, 0.0, 1.5, 1.0 };

/*This is for the properties of the spot light*/
GLfloat light1_ambient[] = { 0.0, 1.0, 0.2, 1.0 };
GLfloat light1_diffuse[] = { 0.0, 1.0, 1.0, 1.0 };
GLfloat light1_specular[] = { 0.0, 1.0, 1.0, 1.0 };
GLfloat light1_position[] = { -2.0, 0.0, -0.5, 1.0 };
GLfloat spot_direction[] = { 1.0, 0.0, 0.0 };

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
	glMatrixMode(GL_MODELVIEW);	// Switch to modelview matrix mode

	if (g_fRotate1 > 360.0)
		g_fRotate1 -= 360;

	//g_fRotate1 += 0.1;

	glPushMatrix();

		camara.setViewMatrix();

		// Cube to reference light0
		glPushMatrix();
			glRotatef((double)g_fRotate1, 1.0, 0.0, 0.0);
			glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			glTranslatef(light_position[0], light_position[1], light_position[2]);
			//glDisable(GL_LIGHTING);
			//glColor3f(1.0, 1.0, 1.0);
			glutWireCube(0.1);
			//glEnable(GL_LIGHTING);
		glPopMatrix();

		// Cube to reference light1
		glPushMatrix();
			glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
			glTranslatef(light1_position[0], light1_position[1], light1_position[2]);
			//glDisable(GL_LIGHTING);
			//glColor3f(1.0, 1.0, 1.0);
			glutWireCube(0.1);
			//glEnable(GL_LIGHTING);
		glPopMatrix();

		// Grid
		glPushMatrix();
			glTranslatef(0.0, -0.5, 0.0);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			//glDisable(GL_LIGHTING);
			unGrid->draw2();
			//glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
			//glDisable(GL_LIGHTING);
			glTranslatef(-10.0, 0.0, -5.0f);
			glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unCubo->bindTexture();
			//g_EarthMaterial.Apply();
			unCubo->draw();
			//glutSolidSphere(0.5, 20, 20);
			//glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-7.0, 0.0, -5.0f);
			glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unaEsfera->bindTexture();
			unaEsfera->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-4.0, 0.0, -5.0f);
			glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unCilindro->bindTexture();
			unCilindro->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.0, 0.0, -5.0f);
			glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unPlano->bindTexture();
			unPlano->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.0, 0.0, -5.0f);
			glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unPrisma3->bindTexture();
			unPrisma3->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(5.0, 0.0, -5.0f);
			glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unPrisma5->bindTexture();
			unPrisma5->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(8.0, 0.0, -5.0f);
			glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unPrisma7->bindTexture();
			unPrisma7->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(11.0, 0.0, -5.0f);
			glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unPrisma9->bindTexture();
			unPrisma9->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		// Otros ;v
			glPushMatrix();
			glTranslatef(-1.0, 0.0, 5.0f);
			glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unObjeto1->bindTexture();
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.0, 0.0, 5.0f);
			glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unObjeto2->bindTexture();
			glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(5.0, 0.0, 5.0f);
			glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unObjeto3->bindTexture();
			glutSolidTeapot(1);
		glPopMatrix();

	glPopMatrix();
	// Render Stuff
	glutSwapBuffers();
	glBindTexture(GL_TEXTURE_2D, 0);
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

// Setup the OpenGL and GLUt cotnext
void InitGL(int argc, char* argv[]){

	std::cout << "Initialise OpenGL..." << std::endl;
	// Window
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

	std::cout << "Initialise OpenGL: Success!" << std::endl;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	/*This is for spot light*/
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

	glClearDepthf(1.0f);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	/*This is for point light*/
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE); // Renormalize scaled normals so that lighting still works properly.

	unCubo = new myCube();
	unCilindro = new myCylinder(1.0f, 1.0f);
	unaEsfera = new mySphere(1.0f, 20.0f, 20.0f);
	unPrisma3 = new myPrism(1.0f, 1.0f, 3);
	unPrisma5 = new myPrism(1.0f, 1.0f, 5);
	unPrisma7 = new myPrism(1.0f, 1.0f, 7);
	unPrisma9 = new myPrism(1.0f, 1.0f, 9);
	unPlano = new myPlane();
	unGrid = new myGrid(0.3f, 20.0);
	unObjeto1 = new my3dObjectBase();
	unObjeto2 = new my3dObjectBase();
	unObjeto3 = new my3dObjectBase();

	unCubo->loadTexture("./textures/uno.png");
	unaEsfera->loadTexture("./textures/dos.png");
	unCilindro->loadTexture("./textures/tres.png");
	unPlano->loadTexture("./textures/cuatro.png");
	unPrisma3->loadTexture("./textures/cinco.png");
	unPrisma5->loadTexture("./textures/seis.png");
	unPrisma7->loadTexture("./textures/siete.png");
	unPrisma9->loadTexture("./textures/uno.png");
	unObjeto1->loadTexture("./textures/paper.jpg");
	unObjeto2->loadTexture("./textures/mario.jpg");
	unObjeto3->loadTexture("./textures/grunge.jpg");
}

int main(int argc, char* argv[]){

	// Capture the previous time to calculate the delta time on the next frame
	g_PreviousTicks = std::clock();

	InitGL(argc, argv);
	glutMainLoop();
}
