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
	glm::vec2 m_TextureCoord;
};

struct Light
{
	Light(GLenum lightID = GL_LIGHT0
		, glm::vec4 ambient = glm::vec4(1.0, 0.0, 0.2, 1.0)
		, glm::vec4 diffuse = glm::vec4(1.0, 1.0, 1.0, 1.0)
		, glm::vec4 specular = glm::vec4(1.0, 1.0, 1.0, 1.0)
		, glm::vec4 position = glm::vec4(0.0, 1.0, 0.0, 0.0)
		, glm::vec3 spotDirection = glm::vec3(0.0, 0.0, 1.0)
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
		glLightfv(m_LightID, GL_AMBIENT, &(m_Ambient[0]));
		glLightfv(m_LightID, GL_DIFFUSE, &(m_Diffuse[0]));
		glLightfv(m_LightID, GL_SPECULAR, &(m_Specular[0]));
		glLightfv(m_LightID, GL_POSITION, &(m_Position[0]));
		glLightfv(m_LightID, GL_SPOT_DIRECTION, &(m_SpotDirection[0]));
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
	glm::vec4 m_Ambient;
	glm::vec4 m_Diffuse;
	glm::vec4 m_Specular;

	glm::vec4 m_Position;
	glm::vec3 m_SpotDirection;
	float  m_SpotExponent;
	float  m_SpotCutoff;
	float  m_ConstantAttenuation;
	float  m_LinearAttenuation;
	float  m_QuadraticAttenuation;
};

struct Material
{
	Material(glm::vec4 ambient = glm::vec4(0.2, 0.2, 0.2, 1.0)
		, glm::vec4 diffuse = glm::vec4(0.8, 0.8, 0.8, 1.0)
		, glm::vec4 specular = glm::vec4(0.0, 0.0, 0.0, 1.0)
		, glm::vec4 emission = glm::vec4(0.0, 0.0, 0.0, 1.0)
		, float shininess = 0)
		: m_Ambient(ambient)
		, m_Diffuse(diffuse)
		, m_Specular(specular)
		, m_Emission(emission)
		, m_Shininess(shininess)
	{}

	void Apply()
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &(m_Ambient[0]));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &(m_Diffuse[0]));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &(m_Specular[0]));
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &(m_Emission[0]));
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_Shininess);
	}

	glm::vec4 m_Ambient;
	glm::vec4 m_Diffuse;
	glm::vec4 m_Specular;
	glm::vec4 m_Emission;
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
	motGrid,
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

	virtual bool draw() { std::cout << "This object does not know how to be drawed!" << std::endl;  return false; };
	bool setPosition(GLfloat x, GLfloat y, GLfloat z);
	glm::vec3 getPosition();

protected:
	EmyObjectType _type;
	glm::vec3 _position;
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

	//bool draw();

	bool setMaterial(struct myMaterial material);
	struct myMaterial getMaterial();

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
	struct myMaterial _material;
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
			glm::vec2(1,0)	// UV
		},
		{//2
			glm::vec3(-1,  1,  1), // Coord
			glm::vec3(0, 1, 1), // Color
			glm::vec2(0,0)	// UV
		},
		{//3
			glm::vec3(-1, -1,  1), // Coord
			glm::vec3(0, 0, 1),	// Color
			glm::vec2(0,1)
		},
		{//4
			glm::vec3(1, -1,  1), // Coord
			glm::vec3(1, 0, 1),	// Color
			glm::vec2(1,1) // UV
		},
		{//5
			glm::vec3(1, -1, -1), // Coord
			glm::vec3(1, 0, 0),	// Color
			glm::vec2(0,0)	// UV
		},
		{//6
			glm::vec3(-1, -1, -1), // Coord
			glm::vec3(0, 0, 0),	// Color
			glm::vec2(0,0)	// UV
		},
		{//7
			glm::vec3(-1,  1, -1), // Coord
			glm::vec3(0, 1, 0),	// Color
			glm::vec2(0,0)	// UV
		},
		{//8
			glm::vec3(1,  1, -1), // Coord
			glm::vec3(1, 1, 0),	// Color
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