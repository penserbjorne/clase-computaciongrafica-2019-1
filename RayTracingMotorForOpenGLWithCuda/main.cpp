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
int g_iWindowWidth = 800;
int g_iWindowHeight = 640;
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

myMaterial *matAmbient;
myMaterial *mat1, *mat2, *mat3;
myLight *pointLight;
myLight *spotLight;
myCube *unCubo;
myCylinder *unCilindro;
mySphere *unaEsfera;
myPrism *unPrisma3;
myPrism *unPrisma5;
myPrism *unPrisma7;
myPrism *unPrisma9;
myPlane *unPlano;
myGrid *unGrid;
my3dObjectBase *unObjeto1;
my3dObjectBase *unObjeto2;
my3dObjectBase *unObjeto3;

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

	//g_fRotate1 += 0.1;

	glPushMatrix();

		camara.setViewMatrix();
		
		pointLight->activate();
		// Cube to reference light0
		glPushMatrix();
			glRotatef((double)g_fRotate1, 1.0, 0.0, 0.0);
			glTranslatef(pointLight->position[0], pointLight->position[1], pointLight->position[2]);
			glDisable(GL_LIGHTING);
			glColor3f(0.0, 0.0, 1.0);
			glutWireCube(0.1);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		spotLight->activate();
		// Cube to reference light1
		glPushMatrix();
			glTranslatef(spotLight->position[0], spotLight->position[1], spotLight->position[2]);
			glDisable(GL_LIGHTING);
			glColor3f(0.0, 1.0, 0.0);
			glutWireCube(0.1);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		// Cube to reference light1
		glPushMatrix();
			glTranslatef(spotLight->spotDirection[0], spotLight->spotDirection[1], spotLight->spotDirection[2]);
			glDisable(GL_LIGHTING);
			glColor3f(0.0, 1.0, 1.0);
			glutWireCube(0.1);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		// Grid
		glPushMatrix();
			glTranslatef(0.0, -0.5, 0.0);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			//glDisable(GL_LIGHTING);
			glColor3f(1.0, 0.0, 0.0);
			unGrid->draw2();
			//glEnable(GL_LIGHTING);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-10.0, 0.0, -3.0f);
			//glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unCubo->bindTexture();
			mat1->apply();
			unCubo->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-7.0, 0.0, -3.0f);
			//glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unaEsfera->bindTexture();
			mat2->apply();
			unaEsfera->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-4.0, 0.0, -3.0f);
			//glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unCilindro->bindTexture();
			mat3->apply();
			unCilindro->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.0, 0.0, -3.0f);
			//glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unPlano->bindTexture();
			mat1->apply();
			unPlano->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.0, 0.0, -3.0f);
			//glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unPrisma3->bindTexture();
			mat2->apply();
			unPrisma3->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(5.0, 0.0, -3.0f);
			//glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unPrisma5->bindTexture();
			mat3->apply();
			unPrisma5->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(8.0, 0.0, -3.0f);
			//glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unPrisma7->bindTexture();
			mat1->apply();
			unPrisma7->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(11.0, 0.0, -3.0f);
			//glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unPrisma9->bindTexture();
			mat2->apply();
			unPrisma9->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		// Otros ;v
			glPushMatrix();
			glTranslatef(-1.0, 0.0, 3.0f);
			//glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unObjeto1->bindTexture();
			mat3->apply();
			unCubo->draw();
			//glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.0, 0.0, 3.0f);
			//glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unObjeto2->bindTexture();
			mat1->apply();
			unaEsfera->draw();
			//glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(5.0, 0.0, 3.0f);
			//glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f);
			unObjeto3->bindTexture();
			mat2->apply();
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

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepthf(1.0f);

	matAmbient = new myMaterial(
		glm::vec4(1.0, 1.0, 1.0, 1.0 ), // ambient
		glm::vec4(1.0, 1.0, 1.0, 1.0), // diffuse
		glm::vec4(1.0, 1.0, 1.0, 1.0), // specular
		glm::vec4(0.1, 0.1, 0.1, 1.0), // emission
		1.0 // shininess
	);

	matAmbient->apply();

	// Specify a global ambient
	GLfloat globalAmbient[] = { 0.1, 0.1, 0.1, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE); // Renormalize scaled normals so that lighting still works properly.
	glEnable(GL_LIGHT_MODEL_LOCAL_VIEWER);

	pointLight = new myLight(
		GL_LIGHT0, // Light
		glm::vec4(0.0, 0.0, 1.0, 1.0), // ambient
		glm::vec4(1.0, 1.0, 1.0, 1.0), // diffuse
		glm::vec4(1.0, 1.0, 1.0, 1.0), // specular
		glm::vec4(0.0, 1.0, 0.0, 1.0), // position
		glm::vec4(), //spotPosition = 0
		0.0, // spotExponent
		180.0, // spotCutoff
		1.5, // constantAttenuation
		0.5, // linearAttenuation
		0.2	// quadraticAttenuation
		);
	spotLight = new myLight(
		GL_LIGHT1, // Light
		glm::vec4(0.0, 1.0, 0.0, 1.0), // ambient
		glm::vec4(1.0, 1.0, 1.0, 1.0), // diffuse
		glm::vec4(1.0, 1.0, 1.0, 1.0), // specular
		glm::vec4(-1.0, 1.0, -3.0, 1.0), // position
		glm::vec4(-1.0, 0.0, -3.0, 1.0), //spotPosition = 0
		2.0, // spotExponent
		45.0, // spotCutoff
		1.5, // constantAttenuation
		0.5, // linearAttenuation
		0.2	// quadraticAttenuation
	);
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

	mat1 = new myMaterial(
		glm::vec4(0.5, 0.5, 0.5, 1), // ambient
		glm::vec4(1, 1, 1, 1),	// diffuse
		glm::vec4(1, 1, 1, 1),	// specular
		glm::vec4(0.2, 0.2, 0.2, 1.0),	// emissive
		10	// shininess
	);
	mat2 = new myMaterial(
		glm::vec4(0.2, 0.2, 0.2, 1.0),	// ambient
		glm::vec4(0.5, 0.5, 0.5, 1),	//diffuse
		glm::vec4(1, 1, 1, 1),	// specular
		glm::vec4(0, 0, 0, 1),	// emissive
		50	// shininess
	);
	mat3 = new myMaterial(
		glm::vec4(0.1, 0.1, 0.1, 1.0),	// ambient
		glm::vec4(1, 1, 1, 1),	// diffuse
		glm::vec4(0.2, 0.2, 0.2, 1),	// specular
		glm::vec4(0, 0, 0, 1),	// emissive
		30	// shininess
	);

	unCubo->loadTexture("./textures/uno.png");
	unaEsfera->loadTexture("./textures/dos.png");
	unCilindro->loadTexture("./textures/tres.png");
	unPlano->loadTexture("./textures/mario.png");
	unPrisma3->loadTexture("./textures/cinco.png");
	unPrisma5->loadTexture("./textures/seis.png");
	unPrisma7->loadTexture("./textures/siete.png");
	unPrisma9->loadTexture("./textures/uno.png");
	unObjeto1->loadTexture("./textures/mario.png");
	unObjeto2->loadTexture("./textures/paper.jpg");
	unObjeto3->loadTexture("./textures/grunge.jpg");
}

int main(int argc, char* argv[]){

	// Capture the previous time to calculate the delta time on the next frame
	g_PreviousTicks = std::clock();

	InitGL(argc, argv);
	glutMainLoop();
}
