#include "myObjectTypes.h"

// myBaseObject class definitions

myBaseObject::myBaseObject(){
	this->_type = EmyObjectType::motBase;
}

myBaseObject::~myBaseObject(){
}

EmyObjectType myBaseObject::getObjectType(){
	return this->_type;
}

bool myBaseObject::setPosition(float x, float y, float z){
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

float my3dObjectBase::getTransparency(){
	return this->_transparency;
}

bool my3dObjectBase::setRaidus(float radius){
	this->_radius = radius;
	return true;
}

float my3dObjectBase::getRadius(){
	return this->_radius;
}

bool my3dObjectBase::setWidth(float width){
	this->_width = width;
	return true;
}

float my3dObjectBase::getWidth(){
	return this->_width;
}

bool my3dObjectBase::setHeight(float height){
	this->_height = height;
	return true;
}

float my3dObjectBase::getHeight(){
	return this->_height;
}

bool my3dObjectBase::setSides(int sides){
	this->_sides = sides;
	return true;
}

int my3dObjectBase::getSides(){
	return this->_sides;
}

bool my3dObjectBase::setScale(float scale){
	this->_scale = scale;
	return true;
}

float my3dObjectBase::getScale(){
	return this->_scale;
}

// myCylinder class definitions

myCylinder::myCylinder(){
	this->_type = EmyObjectType::motCylinder;
}

myCylinder::~myCylinder(){
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

bool myCamera::setLookAt(float x, float y, float z){
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

int myRaytrace::getOrder(){
	return this->_order;
}

bool myRaytrace::setMethod(EtypeOfMethodForRayTrace method){
	this->_method = method;
	return true;
}

EtypeOfMethodForRayTrace myRaytrace::getTypeOfMethod(){
	return this->_method;
}
