#pragma once

#define _USE_MATH_DEFINES

// GLEW to use GL types like GLuint
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <soil.h>

#include <iostream>
#include <cstddef> // To use NULL
#include <cmath>

#define MEMBER_OFFSET(s,m) ((char *)NULL + (offsetof(s,m)))
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

constexpr auto SIZEVERTEXCUBE = 8;
constexpr auto SIZEINDEXCUBE = 24;

constexpr auto SIZEVERTEXCYLINDER = 128;
constexpr auto SIZEVERTEXCYLINDER_TOP_BOTTOM = 64;

constexpr auto SIZEVERTEXSPHERE = 882;

constexpr auto SIZEVERTEXPRISM = 722;
constexpr auto SIZEVERTEXPRISM_TOP_BOTTOM = 360;

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

struct float4 {
	float4(GLfloat _x = 0.0f, GLfloat _y = 0.0f, GLfloat _z = 0.0f, GLfloat _w = 0.0f) : x(_x), y(_y), z(_z), w(_w) {}

	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
};

struct color4 {
	color4(GLfloat _r = 0.0f, GLfloat _g = 0.0f, GLfloat _b = 0.0f, GLfloat _a = 0.0f) : r(_r), g(_g), b(_b), a(_a) {}

	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
};

// Vertex with a color for the primitives to use with VBO
struct VertexXYZColor{
	float3 m_Pos;
	float3 m_Color;
};

struct Light
{
	Light(GLenum lightID = GL_LIGHT0
		, color4 ambient = color4(1.0, 1.0, 1.0, 1.0)
		, color4 diffuse = color4(.3, .3, .3, 1.0)
		, color4 specular = color4(1.0, 1.0, 1.0, 1.0)
		, float4 position = float4(0.0, 0.0, 1.0, 0.0)
		, float3 spotDirection = float3(0.0, 0.0, 1.0)
		, float  spotExponent = 0.0
		, float  spotCutoff = 180.0f
		, float  constantAttenuation = 1.0
		, float  linearAttenuation = 0.0
		, float  quadraticAttenuation = 0.0)
		: m_LightID(lightID)
		, m_Ambient(ambient)
		, m_Diffuse(diffuse)
		, m_Specular(specular)
		, m_Position(position)
		, m_SpotDirection(spotDirection)
		, m_SpotExponent(spotExponent)
		, m_SpotCutoff(spotCutoff)
		, m_ConstantAttenuation(constantAttenuation)
		, m_LinearAttenuation(linearAttenuation)
		, m_QuadraticAttenuation(quadraticAttenuation)
	{}

	void Activate()
	{
		glEnable(m_LightID);
		glLightfv(m_LightID, GL_AMBIENT, &(m_Ambient.r));
		glLightfv(m_LightID, GL_DIFFUSE, &(m_Diffuse.r));
		glLightfv(m_LightID, GL_SPECULAR, &(m_Specular.r));
		glLightfv(m_LightID, GL_POSITION, &(m_Position.x));
		glLightfv(m_LightID, GL_SPOT_DIRECTION, &(m_SpotDirection.x));
		glLightf(m_LightID, GL_SPOT_EXPONENT, m_SpotExponent);
		glLightf(m_LightID, GL_SPOT_CUTOFF, m_SpotCutoff);
		glLightf(m_LightID, GL_CONSTANT_ATTENUATION, m_ConstantAttenuation);
		glLightf(m_LightID, GL_LINEAR_ATTENUATION, m_LinearAttenuation);
		glLightf(m_LightID, GL_QUADRATIC_ATTENUATION, m_QuadraticAttenuation);
	}

	void Deactivate()
	{
		glDisable(m_LightID);
	}

	GLenum m_LightID;
	color4 m_Ambient;
	color4 m_Diffuse;
	color4 m_Specular;

	float4 m_Position;
	float3 m_SpotDirection;
	float  m_SpotExponent;
	float  m_SpotCutoff;
	float  m_ConstantAttenuation;
	float  m_LinearAttenuation;
	float  m_QuadraticAttenuation;
};

struct Material
{
	Material(color4 ambient = color4(0.2, 0.2, 0.2, 1.0)
		, color4 diffuse = color4(0.8, 0.8, 0.8, 1.0)
		, color4 specular = color4(0.0, 0.0, 0.0, 1.0)
		, color4 emission = color4(0.0, 0.0, 0.0, 1.0)
		, float shininess = 0)
		: m_Ambient(ambient)
		, m_Diffuse(diffuse)
		, m_Specular(specular)
		, m_Emission(emission)
		, m_Shininess(shininess)
	{}

	void Apply()
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &(m_Ambient.r));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &(m_Diffuse.r));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &(m_Specular.r));
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &(m_Emission.r));
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_Shininess);
	}

	color4 m_Ambient;
	color4 m_Diffuse;
	color4 m_Specular;
	color4 m_Emission;
	float  m_Shininess;

};

struct myMaterial {
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
	motCube,
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

	bool loadTexture(std::string pathToTexture);
	bool unloadTexture();

	bool setTypeOfTexture(EmyTypeOfTexture typeOfTexture);
	EmyTypeOfTexture getTypeOfTexture();

	bool setTransparency(GLfloat transparency);
	GLfloat getTransparency();

	bool setRadius(GLfloat radius);
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
	EmyTypeOfTexture _typeOfTexture;
	GLfloat _transparency;

	GLfloat _radius;
	GLfloat _width;
	GLfloat _height;
	GLint _sides;
	GLfloat _scale;

	// IDs for the buffers
	GLuint _g_uiVerticesVBO = 0;
	GLuint _g_uiIndicesVBO = 0;

	GLsizei _sizeVertex;
	GLsizei _sizeIndex;

	GLuint _textureObject;
};

class myCube : public my3dObjectBase{
public:
	myCube();
	~myCube();
	bool draw();

private:
	// Define the 8 vertices of a unit cube
	VertexXYZColor _g_Vertices[SIZEVERTEXCUBE] = {
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
	GLuint _g_Indices[SIZEINDEXCUBE] = {
		0, 1, 2, 3,                 // Front face
		7, 4, 5, 6,                 // Back face
		6, 5, 2, 1,                 // Left face
		7, 0, 3, 4,                 // Right face
		7, 6, 1, 0,                 // Top face
		3, 2, 5, 4,                 // Bottom face
	};
};

class myCylinder : public my3dObjectBase{

public:
	myCylinder();
	myCylinder(GLfloat radius, GLfloat height);
	~myCylinder();

	bool draw();

protected:
	VertexXYZColor _g_Vertices[SIZEVERTEXCYLINDER];
	GLuint _g_Indices[SIZEVERTEXCYLINDER];
	GLuint _g_IndicesT[SIZEVERTEXCYLINDER_TOP_BOTTOM];
	GLuint _g_IndicesB[SIZEVERTEXCYLINDER_TOP_BOTTOM];

	// IDs for the buffers
	GLuint _g_uiIndicesVBO_Top = 0;	// Top - Tapa
	GLuint _g_uiIndicesVBO_Bottom = 0;	// Bottom - Base

	GLsizei _sizeIndex_Top_Bottom;
};

class mySphere : public my3dObjectBase{

public:
	mySphere(GLfloat radius, GLfloat lats, GLfloat longs);
	~mySphere();

	bool draw();

private:
	GLfloat _lats;
	GLfloat _longs;

	VertexXYZColor _g_Vertices[SIZEVERTEXSPHERE];
	GLuint _g_Indices[SIZEVERTEXSPHERE];
};

class myPrism : public my3dObjectBase{

public:
	myPrism(GLfloat radius, GLfloat height, GLint sides);
	~myPrism();
	bool draw();

private:
	VertexXYZColor _g_Vertices[SIZEVERTEXPRISM];
	GLuint _g_Indices[SIZEVERTEXPRISM];
	GLuint _g_IndicesT[SIZEVERTEXPRISM_TOP_BOTTOM];
	GLuint _g_IndicesB[SIZEVERTEXPRISM_TOP_BOTTOM];

	// IDs for the buffers
	GLuint _g_uiIndicesVBO_Top = 0;
	GLuint _g_uiIndicesVBO_Bottom = 0;

	GLsizei _sizeIndex_Top_Bottom;
};

class myOBJModel : public my3dObjectBase{

public:
	myOBJModel(std::string pathToFile);
	~myOBJModel();

private:
};
 
class myPlane : public my3dObjectBase{

public:
	myPlane();
	~myPlane();
	bool draw();

private:
	myCube _cubeBase;
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