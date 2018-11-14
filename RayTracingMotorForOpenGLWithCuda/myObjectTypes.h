#pragma once

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
