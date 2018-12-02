#pragma once

#define _USE_MATH_DEFINES

// GLEW to use GL types like GLuint
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <soil.h>

#include <iostream>
#include <cstddef> // To use NULL

#define MEMBER_OFFSET(s,m) ((char *)NULL + (offsetof(s,m)))
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// This values was calculated by the fly, but need to be recalculated in a good way ;@
constexpr auto SIZEVERTEXCUBE = 8;
constexpr auto SIZEINDEXCUBE = 24;

constexpr auto SIZEVERTEXCYLINDER = 128;
constexpr auto SIZEVERTEXCYLINDER_TOP_BOTTOM = 64;

constexpr auto SIZEVERTEXSPHERE = 882;

constexpr auto SIZEVERTEXPRISM = 722;
constexpr auto SIZEVERTEXPRISM_TOP_BOTTOM = 360;

// Vertex with a color for the primitives to use with VBO
struct VertexXYZColor{
	glm::vec3 m_Pos;
	glm::vec3 m_Color;
	glm::vec3 m_Normal;
	glm::vec2 m_TextureCoord;
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
	motGrid,
	motCamera,
	motRaytrace
};

enum EtypeOfMethodForRayTrace {
	// TypeOfMethod = tom
	tomForward = 0,
	tomBackward
};

class myMaterial{
public:
	myMaterial() {};
	myMaterial(
		glm::vec4 ambient, glm::vec4 diffuse,
		glm::vec4 specular, glm::vec4 emission,
		float shininess);
	~myMaterial() {};

	bool apply();

//private:
	glm::vec4 _ambient;
	glm::vec4 _diffuse;
	glm::vec4 _specular;
	glm::vec4 _emission;
	float  _shininess;
};

// Base class for the 3D objects
class myBaseObject {

public:
	myBaseObject();
	~myBaseObject();

	EmyObjectType getObjectType();

	virtual bool draw() { std::cout << "This object does not know how to be drawed!" << std::endl;  return false; };
	bool setPosition(GLfloat x, GLfloat y, GLfloat z);
	glm::vec3 getPosition();

protected:
	EmyObjectType _type;
	glm::vec3 _position;
};

class myLight : public myBaseObject{

public:
	myLight(GLenum LightID,
		glm::vec4 ambient,
		glm::vec4 diffuse,
		glm::vec4 specular,
		glm::vec4 position,
		glm::vec3 spotDirection,
		float  spotExponent,
		float  spotCutoff,
		float  constantAttenuation,
		float  linearAttenuation,
		float  quadraticAttenuation);
	~myLight();
	
	void activate();
	void deactivate();
	glm::vec4 position;
	glm::vec3 spotDirection;

private:
	GLenum _lightID;
	glm::vec4 _ambient;
	glm::vec4 _diffuse;
	glm::vec4 _specular;

	float  _spotExponent;
	float  _spotCutoff;
	float  _constantAttenuation;
	float  _linearAttenuation;
	float  _quadraticAttenuation;
};

class my3dObjectBase : public myBaseObject{

public:
	my3dObjectBase();
	~my3dObjectBase();

	//bool draw();

	bool setMaterial(myMaterial material);
	myMaterial getMaterial();

	bool loadTexture(std::string pathToTexture);
	bool bindTexture();
	bool unbindTexture();

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
	myMaterial _material;
	EmyTypeOfTexture _typeOfTexture;
	GLfloat _transparency;

	GLfloat _radius;
	GLfloat _width;
	GLfloat _height;
	GLint _sides;
	GLfloat _scale;

	// Data vertex and index
	VertexXYZColor _g_Vertices;
	GLuint _g_Indices;
	GLsizei _sizeVertex;
	GLsizei _sizeIndex;

	// IDs for the buffers
	GLuint _g_uiVerticesVBO = 0;
	GLuint _g_uiIndicesVBO = 0;
	GLenum _drawMode;

	GLuint _textureObject;
	int _textureWidth;
	int _textureHeight;
};

class myCube : public my3dObjectBase{
public:
	myCube();
	~myCube();
	bool draw();

private:
	// Define the 8 vertices of a unit cube
	VertexXYZColor _g_Vertices[SIZEVERTEXCUBE] = {
		{//1
			glm::vec3(1,  1,  1), // Coord
			glm::vec3(1, 1, 1),	// Color
			glm::normalize(glm::vec3(1,  1,  1)), // Normal
			glm::vec2(1,0)	// UV
		},
		{//2
			glm::vec3(-1,  1,  1), // Coord
			glm::vec3(0, 1, 1), // Color
			glm::normalize(glm::vec3(-1, 1, 1)), // Normal
			glm::vec2(0,0)	// UV
		},
		{//3
			glm::vec3(-1, -1,  1), // Coord
			glm::vec3(0, 0, 1),	// Color
			glm::normalize(glm::vec3(-1, -1, 1)), // Normal
			glm::vec2(0,1)
		},
		{//4
			glm::vec3(1, -1,  1), // Coord
			glm::vec3(1, 0, 1),	// Color
			glm::normalize(glm::vec3(1,  -1,  1)), // Normal
			glm::vec2(1,1) // UV
		},
		{//5
			glm::vec3(1, -1, -1), // Coord
			glm::vec3(1, 0, 0),	// Color
			glm::normalize(glm::vec3(1,  -1,  -1)), // Normal
			glm::vec2(0,0)	// UV
		},
		{//6
			glm::vec3(-1, -1, -1), // Coord
			glm::vec3(0, 0, 0),	// Color
			glm::normalize(glm::vec3(-1,  -1,  -1)), // Normal
			glm::vec2(0,0)	// UV
		},
		{//7
			glm::vec3(-1,  1, -1), // Coord
			glm::vec3(0, 1, 0),	// Color
			glm::normalize(glm::vec3(-1,1,-1)), // Normal
			glm::vec2(0,0)	// UV
		},
		{//8
			glm::vec3(1,  1, -1), // Coord
			glm::vec3(1, 1, 0),	// Color
			glm::normalize(glm::vec3(1,1,-1)), // Normal
			glm::vec2(0,0)	// UV
		},
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

class myGrid : public my3dObjectBase
{
public:
	myGrid(GLfloat sizeCell, GLfloat numCells);
	~myGrid();
	bool draw();
	bool draw2();

private:
	VertexXYZColor* _g_Vertices;
	GLuint* _g_Indices;

	GLfloat _sizeCell;
	GLfloat _numCells;
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