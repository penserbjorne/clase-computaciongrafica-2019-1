#pragma once

// GLEW to use GL types like GLuint
#include <GL/glew.h>


// Struct to define vector type objects for 2D and 3D space
struct float2{
	float2(GLfloat _x = 0.0f, GLfloat _y = 0.0f) : x(_x), y(_y) {}

	GLfloat x;
	GLfloat y;
};

struct float3{
	float3(GLfloat _x = 0.0f, GLfloat _y = 0.0f, GLfloat _z = 0.0f) : x(_x), y(_y), z(_z) {}

	GLfloat x;
	GLfloat y;
	GLfloat z;
};

// Vertex with a color for the primitives to use with VBO
struct VertexXYZColor{
	float3 m_Pos;
	float3 m_Color;
};

struct myMaterial {
	// Pendiente de implementar y definir
};

struct myTexture{
	// Pendiente de implementar y definir
};

enum EmyTypeOfTexture {
	// MyTypeOfTexture = mtot
	mtotReflective = 0,
	mtotRefractice
};

// Enum to clasify objects
enum EmyObjectType {
	// MyObjecttype = mot
	motBase = 0,
	mot3dBase,
	motSpotlight,
	motPointlight,
	motCylinder,
	motSphere,
	motPrism,
	motOBJModel,
	motPlane,
	motCamera,
	motRaytrace
};

enum EtypeOfMethodForRayTrace {
	// TypeOfMethod = tom
	tomForward = 0,
	tomBackward
};

// Base class for the 3D objects
class myBaseObject {

public:
	myBaseObject();
	~myBaseObject();

	EmyObjectType getObjectType();

	virtual bool draw() { return false; };
	bool setPosition(GLfloat x, GLfloat y, GLfloat z);
	float3 getPosition();

protected:
	EmyObjectType _type;
	float3 _position;
};

class mySpotlight : public myBaseObject{

public:
	mySpotlight();
	~mySpotlight();

private:

};

class myPointlight : public myBaseObject{

public:
	myPointlight();
	~myPointlight();

private:

};

class my3dObjectBase : public myBaseObject{

public:
	my3dObjectBase();
	~my3dObjectBase();

	bool setMaterial(struct myMaterial material);
	struct myMaterial getMaterial();

	bool setTexture(struct myTexture texture);
	struct myTexture getTexture();

	bool setTypeOfTexture(EmyTypeOfTexture typeOfTexture);
	EmyTypeOfTexture getTypeOfTexture();

	bool setTransparency(GLfloat transparency);
	GLfloat getTransparency();

	bool setRaidus(GLfloat radius);
	GLfloat getRadius();

	bool setWidth(GLfloat width);
	GLfloat getWidth();

	bool setHeight(GLfloat height);
	GLfloat getHeight();

	bool setSides(GLint sides);
	GLint getSides();

	bool setScale(GLfloat scale);
	GLfloat getScale();

protected:
	struct myMaterial _material;
	struct myTexture _texture;
	EmyTypeOfTexture _typeOfTexture;
	GLfloat _transparency;

	GLfloat _radius;
	GLfloat _width;
	GLfloat _height;
	GLint _sides;
	GLfloat _scale;
};

class myCube : public my3dObjectBase{
public:
	myCube();
	~myCube();
	bool draw();

private:
	// Define the 8 vertices of a unit cube
	VertexXYZColor _g_Vertices[8] = {
		{ float3(1,  1,  1), float3(1, 1, 1) }, // 0
		{ float3(-1,  1,  1), float3(0, 1, 1) }, // 1
		{ float3(-1, -1,  1), float3(0, 0, 1) }, // 2
		{ float3(1, -1,  1), float3(1, 0, 1) }, // 3
		{ float3(1, -1, -1), float3(1, 0, 0) }, // 4
		{ float3(-1, -1, -1), float3(0, 0, 0) }, // 5
		{ float3(-1,  1, -1), float3(0, 1, 0) }, // 6
		{ float3(1,  1, -1), float3(1, 1, 0) }, // 7
	};

	// Define the vertex indices for the cube.
	GLuint _g_Indices[24] = {
		0, 1, 2, 3,                 // Front face
		7, 4, 5, 6,                 // Back face
		6, 5, 2, 1,                 // Left face
		7, 0, 3, 4,                 // Right face
		7, 6, 1, 0,                 // Top face
		3, 2, 5, 4,                 // Bottom face
	};

	// IDs for the buffers
	GLuint _g_uiVerticesVBO = 0;
	GLuint _g_uiIndicesVBO = 0;
};

class myCylinder : public my3dObjectBase{

public:
	myCylinder();
	myCylinder(GLfloat radius, GLfloat height);
	~myCylinder();

	bool draw();

protected:
	VertexXYZColor _g_Vertices[128];
	GLuint _g_Indices[128];
	GLuint _g_IndicesTapa[64];
	GLuint _g_IndicesFondo[64];

	// IDs for the buffers
	GLuint _g_uiVerticesVBO = 0;
	GLuint _g_uiIndicesVBO = 0;
	GLuint _g_uiIndicesVBOTapa = 0;
	GLuint _g_uiIndicesVBOFondo = 0;
};

class mySphere : public my3dObjectBase{

public:
	mySphere(GLfloat radius, GLfloat lats, GLfloat longs);
	~mySphere();

	bool draw();

private:
	GLfloat _lats;
	GLfloat _longs;

	VertexXYZColor _g_Vertices[882];
	GLuint _g_Indices[882];

	// IDs for the buffers
	GLuint _g_uiVerticesVBO = 0;
	GLuint _g_uiIndicesVBO = 0;
};

class myPrism : public my3dObjectBase{

public:
	myPrism(GLfloat radius, GLfloat height, GLint sides);
	~myPrism();
	bool draw();

private:
	VertexXYZColor _g_Vertices[722];
	GLuint _g_Indices[722];
	GLuint _g_IndicesTapa[360];
	GLuint _g_IndicesFondo[360];

	// IDs for the buffers
	GLuint _g_uiVerticesVBO = 0;
	GLuint _g_uiIndicesVBO = 0;
	GLuint _g_uiIndicesVBOTapa = 0;
	GLuint _g_uiIndicesVBOFondo = 0;

	int _size1;
	int _size2;
};

class myOBJModel : public my3dObjectBase{

public:
	myOBJModel();
	~myOBJModel();

private:

};
 
class myPlane : public my3dObjectBase{

public:
	myPlane();
	~myPlane();

private:

};

class myCamera : public my3dObjectBase
{
public:
	myCamera();
	~myCamera();

	bool setLookAt(GLfloat x, GLfloat y, GLfloat z);
	float3 getLookAt();

private:
	float3 _lookAt;
};

class myRaytrace
{
public:
	myRaytrace();
	~myRaytrace();

	bool setOrder(GLint order);
	GLint getOrder();

	bool setMethod(EtypeOfMethodForRayTrace method);
	EtypeOfMethodForRayTrace getTypeOfMethod();

private:
	EmyObjectType _type;
	GLint _order;
	EtypeOfMethodForRayTrace _method;
};