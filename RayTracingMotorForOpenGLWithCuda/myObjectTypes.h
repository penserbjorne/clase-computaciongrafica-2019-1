#pragma once

// GLEW to use GL types like GLuint
#include <GL/glew.h>


// Struct to define vector type objects for 2D and 3D space
struct float2{
	float2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

	float x;
	float y;
};

struct float3{
	float3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : x(_x), y(_y), z(_z) {}

	float x;
	float y;
	float z;
};

// Vertex with a color for the primitives to use with VBO
struct VertexXYZColor
{
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

	bool setPosition(float x, float y, float z);
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

	bool setTransparency(float transparency);
	float getTransparency();

	bool setRaidus(float radius);
	float getRadius();

	bool setWidth(float width);
	float getWidth();

	bool setHeight(float height);
	float getHeight();

	bool setSides(int sides);
	int getSides();

	bool setScale(float scale);
	float getScale();

private:
	struct myMaterial _material;
	struct myTexture _texture;
	EmyTypeOfTexture _typeOfTexture;
	float _transparency;

	float _radius;
	float _width;
	float _height;
	int _sides;
	float _scale;
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
	~myCylinder();

private:

};

class mySphere : public my3dObjectBase{

public:
	mySphere();
	~mySphere();

private:

};

class myPrism : public my3dObjectBase{

public:
	myPrism();
	~myPrism();

private:

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

	bool setLookAt(float x, float y, float z);
	float3 getLookAt();

private:
	float3 _lookAt;
};

class myRaytrace
{
public:
	myRaytrace();
	~myRaytrace();

	bool setOrder(int order);
	int getOrder();

	bool setMethod(EtypeOfMethodForRayTrace method);
	EtypeOfMethodForRayTrace getTypeOfMethod();

private:
	EmyObjectType _type;
	int _order;
	EtypeOfMethodForRayTrace _method;
};
