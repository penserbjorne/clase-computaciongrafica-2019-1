#define _USE_MATH_DEFINES
#include "myObjectTypes.h"
#include <cstddef> // To use NULL
#include <cmath>

#define MEMBER_OFFSET(s,m) ((char *)NULL + (offsetof(s,m)))
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// myBaseObject class definitions

myBaseObject::myBaseObject(){
	this->_type = EmyObjectType::motBase;
}

myBaseObject::~myBaseObject(){
}

EmyObjectType myBaseObject::getObjectType(){
	return this->_type;
}

bool myBaseObject::setPosition(GLfloat x, GLfloat y, GLfloat z){
	this->_position.x = x;
	this->_position.y = y;
	this->_position.z = z;
	return true;
}

float3 myBaseObject::getPosition(){
	return this->_position;
}

// mySpotlight class definitions

mySpotlight::mySpotlight(){
	this->_type = EmyObjectType::motSpotlight;
}

mySpotlight::~mySpotlight(){
}

// myPointlight class definitions

myPointlight::myPointlight(){
	this->_type = EmyObjectType::motPointlight;
}

myPointlight::~myPointlight(){
}

// my3dObjectBase class definitions

my3dObjectBase::my3dObjectBase(){
	this->_type = EmyObjectType::mot3dBase;
}

my3dObjectBase::~my3dObjectBase(){
}

bool my3dObjectBase::setMaterial(myMaterial material){
	this->_material = material;
	return true;
}

myMaterial my3dObjectBase::getMaterial(){
	return this->_material;
}

bool my3dObjectBase::setTexture(myTexture texture){
	this->_texture = texture;
	return true;
}

myTexture my3dObjectBase::getTexture(){
	return this->_texture;
}

bool my3dObjectBase::setTypeOfTexture(EmyTypeOfTexture typeOfTexture){
	this->_typeOfTexture = typeOfTexture;
	return true;
}

EmyTypeOfTexture my3dObjectBase::getTypeOfTexture(){
	return this->_typeOfTexture;
}

bool my3dObjectBase::setTransparency(float transparency){
	this->_transparency = transparency;
	return true;
}

GLfloat my3dObjectBase::getTransparency(){
	return this->_transparency;
}

bool my3dObjectBase::setRaidus(GLfloat radius){
	this->_radius = radius;
	return true;
}

GLfloat my3dObjectBase::getRadius(){
	return this->_radius;
}

bool my3dObjectBase::setWidth(GLfloat width){
	this->_width = width;
	return true;
}

GLfloat my3dObjectBase::getWidth(){
	return this->_width;
}

bool my3dObjectBase::setHeight(GLfloat height){
	this->_height = height;
	return true;
}

GLfloat my3dObjectBase::getHeight(){
	return this->_height;
}

bool my3dObjectBase::setSides(GLint sides){
	this->_sides = sides;
	return true;
}

GLint my3dObjectBase::getSides(){
	return this->_sides;
}

bool my3dObjectBase::setScale(GLfloat scale){
	this->_scale = scale;
	return true;
}

GLfloat my3dObjectBase::getScale(){
	return this->_scale;
}

// myCube class definitions

myCube::myCube(){
	
}

myCube::~myCube(){
}

bool myCube::draw(){
	// Create VBO's
	glGenBuffersARB(1, &(this->_g_uiVerticesVBO));
	glGenBuffersARB(1, &(this->_g_uiIndicesVBO));

	// Copy the vertex data to the VBO
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->_g_uiVerticesVBO);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(this->_g_Vertices), this->_g_Vertices, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Copy the index data to the VBO
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(this->_g_Indices), this->_g_Indices, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	// We need to enable the client stats for the vertex attributes we want 
	// to render even if we are not using client-side vertex arrays.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// Bind the vertices's VBO
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->_g_uiVerticesVBO);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Pos));
	glColorPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Color));

	// Bind the indices's VBO
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Unbind buffers so client-side vertex arrays still work.
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Disable the client side arrays again.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	return true;
}

// myCylinder class definitions

myCylinder::myCylinder(GLfloat radius, GLfloat height){
	this->_type = EmyObjectType::motCylinder;
	this->_radius = radius;
	this->_height = height;
}

myCylinder::~myCylinder(){
}

bool myCylinder::draw(){
	GLfloat x = 0.0f, y = 0.0f;
	GLfloat angle = 0.0f, angle_stepsize = 0.1f;

	glBegin(GL_QUAD_STRIP);
	while (angle < 2 * M_PI) {
		x = this->_radius * cos(angle);
		y = this->_radius * sin(angle);
		glVertex3f(x, y, this->_height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(this->_radius, 0.0, this->_height);
	glVertex3f(this->_radius, 0.0, 0.0);
	glEnd();

	/** Draw the circle on top of cylinder */
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * M_PI) {
		x = this->_radius * cos(angle);
		y = this->_radius * sin(angle);
		glVertex3f(x, y, this->_height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(this->_radius, 0.0, this->_height);
	glEnd();
	return true;
}

// mySphere class definitions

mySphere::mySphere(){
	this->_type = EmyObjectType::motSphere;
}

mySphere::~mySphere(){
}

// myPrism class definitions

myPrism::myPrism(){
	this->_type = EmyObjectType::motPrism;
}

myPrism::~myPrism(){
}

// myOBJModel class definitions

myOBJModel::myOBJModel(){
	this->_type = EmyObjectType::motOBJModel;
}

myOBJModel::~myOBJModel(){
}

// myPlane class definitions

myPlane::myPlane(){
	this->_type = EmyObjectType::motPlane;
}

myPlane::~myPlane(){
}

// myCamera class definitions

myCamera::myCamera(){
	this->_type = EmyObjectType::motCamera;
}

myCamera::~myCamera(){
}

bool myCamera::setLookAt(GLfloat x, GLfloat y, GLfloat z){
	this->_lookAt.x = x;
	this->_lookAt.y = y;
	this->_lookAt.z = z;
	return true;
}

float3 myCamera::getLookAt(){
	return this->_lookAt;
}

// myRaytrace class definitions

myRaytrace::myRaytrace(){
	this->_type = EmyObjectType::motRaytrace;
}

myRaytrace::~myRaytrace(){
}

bool myRaytrace::setOrder(int order){
	this->_order = order;
	return true;
}

GLint myRaytrace::getOrder(){
	return this->_order;
}

bool myRaytrace::setMethod(EtypeOfMethodForRayTrace method){
	this->_method = method;
	return true;
}

EtypeOfMethodForRayTrace myRaytrace::getTypeOfMethod(){
	return this->_method;
}
