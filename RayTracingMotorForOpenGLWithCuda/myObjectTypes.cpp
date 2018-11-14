#include "myObjectTypes.h"

// myBaseObject class definitions

myBaseObject::myBaseObject()
{
}

myBaseObject::~myBaseObject()
{
}

EmyObjectType myBaseObject::getObjectType()
{
	return EmyObjectType();
}

bool myBaseObject::setPsotion(float x, float y, float z)
{
	return false;
}

float3 myBaseObject::getPosition()
{
	return float3();
}

// mySpotlight class definitions

mySpotlight::mySpotlight()
{
}

mySpotlight::~mySpotlight()
{
}

// myPointlight class definitions

myPointlight::myPointlight()
{
}

myPointlight::~myPointlight()
{
}

// my3dObjectBase class definitions

my3dObjectBase::my3dObjectBase()
{
}

my3dObjectBase::~my3dObjectBase()
{
}

bool my3dObjectBase::setMaterial(myMaterial material)
{
	return false;
}

myMaterial my3dObjectBase::getMaterial()
{
	return myMaterial();
}

bool my3dObjectBase::setTexture(myTexture texture)
{
	return false;
}

myTexture my3dObjectBase::getTexture()
{
	return myTexture();
}

bool my3dObjectBase::setTypeOfTexture(EmyTypeOfTexture typeOfTexture)
{
	return false;
}

EmyTypeOfTexture my3dObjectBase::getTypeOfTexture()
{
	return EmyTypeOfTexture();
}

bool my3dObjectBase::setTransparency(float transparency)
{
	return false;
}

float my3dObjectBase::getTransparency()
{
	return 0.0f;
}

bool my3dObjectBase::setRaidus(float radius)
{
	return false;
}

float my3dObjectBase::getRadius()
{
	return 0.0f;
}

bool my3dObjectBase::setWidth(float width)
{
	return false;
}

float my3dObjectBase::getWidth()
{
	return 0.0f;
}

bool my3dObjectBase::setHeight(float height)
{
	return false;
}

float my3dObjectBase::getHeight()
{
	return 0.0f;
}

bool my3dObjectBase::setSides(int sides)
{
	return false;
}

int my3dObjectBase::getSides()
{
	return 0;
}

bool my3dObjectBase::setScale(float scale)
{
	return false;
}

float my3dObjectBase::getScale()
{
	return 0.0f;
}

// myCylinder class definitions

myCylinder::myCylinder()
{
}

myCylinder::~myCylinder()
{
}

// mySphere class definitions

mySphere::mySphere()
{
}

mySphere::~mySphere()
{
}

// myPrism class definitions

myPrism::myPrism()
{
}

myPrism::~myPrism()
{
}

// myOBJModel class definitions

myOBJModel::myOBJModel()
{
}

myOBJModel::~myOBJModel()
{
}

// myPlane class definitions

myPlane::myPlane()
{
}

myPlane::~myPlane()
{
}

// myCamera class definitions

myCamera::myCamera()
{
}

myCamera::~myCamera()
{
}

bool myCamera::setLookAt(float x, float y, float z)
{
	return false;
}

float3 myCamera::getLookAt()
{
	return float3();
}

// myRaytrace class definitions

myRaytrace::myRaytrace()
{
}

myRaytrace::~myRaytrace()
{
}

bool myRaytrace::setOrder(int order)
{
	return false;
}

int myRaytrace::getOrder()
{
	return 0;
}

bool myRaytrace::setMethod(EtypeOfMethodForRayTrace method)
{
	return false;
}

EtypeOfMethodForRayTrace myRaytrace::getTypeOfMethod()
{
	return EtypeOfMethodForRayTrace();
}
