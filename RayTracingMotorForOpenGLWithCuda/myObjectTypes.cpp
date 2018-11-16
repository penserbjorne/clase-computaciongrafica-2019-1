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
	this->_sizeVertex = 0;
	this->_sizeIndex = 0;
	this->_textureObject = 0;
}

my3dObjectBase::~my3dObjectBase(){
	if (this->_g_uiIndicesVBO != 0) {
		glDeleteBuffersARB(1, &this->_g_uiIndicesVBO);
		this->_g_uiIndicesVBO = 0;
	}
	if (this->_g_uiVerticesVBO != 0) {
		glDeleteBuffersARB(1, &this->_g_uiVerticesVBO);
		this->_g_uiVerticesVBO = 0;
	}
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

bool my3dObjectBase::loadTexture(std::string pathToTexture){
	if (this->_textureObject = SOIL_load_OGL_texture(pathToTexture.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS)) {
		glBindTexture(GL_TEXTURE_3D, this->_textureObject);
		return true;
	}
	return false;
}

bool my3dObjectBase::setTransparency(GLfloat transparency){
		this->_transparency = transparency;
	return false;
}

GLfloat my3dObjectBase::getTransparency(){
	return this->_transparency;
}

bool my3dObjectBase::setRadius(GLfloat radius){
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
	this->_type = EmyObjectType::motCube;
	// Create VBO's ID
	glGenBuffersARB(1, &(this->_g_uiVerticesVBO));
	glGenBuffersARB(1, &(this->_g_uiIndicesVBO));
	this->_sizeVertex = SIZEVERTEXCUBE;
	this->_sizeIndex = SIZEINDEXCUBE;
}

myCube::~myCube(){
}

bool myCube::draw(){

	// Copy the vertex data to the VBO
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->_g_uiVerticesVBO);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(this->_g_Vertices), this->_g_Vertices, GL_STATIC_COPY_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Copy the index data to the VBO
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(this->_g_Indices), this->_g_Indices, GL_STATIC_COPY_ARB);
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
	glDrawElements(GL_QUADS, this->_sizeIndex, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Unbind buffers so client-side vertex arrays still work.
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Disable the client side arrays again.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	return true;
}

// myCylinder class definitions

myCylinder::myCylinder(){
	// This shoul be empty always, dont modify ;@
}

myCylinder::myCylinder(GLfloat radius, GLfloat height){
	this->_type = EmyObjectType::motCylinder;
	this->_sizeVertex = SIZEVERTEXCYLINDER;
	this->_sizeIndex = SIZEVERTEXCYLINDER;
	this->_sizeIndex_Top_Bottom = SIZEVERTEXCYLINDER_TOP_BOTTOM;
	this->_radius = radius;
	this->_height = height;

	GLfloat x = 0.0f, y = 0.0f;
	GLfloat angle = 0.0f, angle_stepsize = 0.1f;
	int index = 0, index2 = 0;

	while (angle < 2 * M_PI) {
		x = this->_radius * cos(angle);
		y = this->_radius * sin(angle);

		this->_g_Indices[index] = index;
		this->_g_IndicesT[index2] = index;
		this->_g_Vertices[index] = {
			float3(x, y, this->_height), // Coord
			float3(x, y, this->_height) // Color
		};
		index++;

		this->_g_Indices[index] = index;
		this->_g_IndicesB[index2] = index;
		this->_g_Vertices[index] = {
			float3(x, y, 0.0f), // Coord
			float3(x, y, 0.0f) // Position
		};
		index++;

		angle += angle_stepsize;
		index2++;
	}

	this->_g_Indices[index] = index;
	this->_g_IndicesT[index2] = index;
	this->_g_Vertices[index] = {
		float3(this->_radius, 0.0, this->_height), // Coord
		float3(this->_radius, 0.0, this->_height) // Position
	};
	index++;

	this->_g_Indices[index] = index;
	this->_g_IndicesB[index2] = index;
	this->_g_Vertices[index] = {
		float3(this->_radius, 0.0, 0.0), // Coord
		float3(this->_radius, 0.0, 0.0) // Position
	};

	// Create VBO's ID's
	glGenBuffersARB(1, &(this->_g_uiVerticesVBO));
	glGenBuffersARB(1, &(this->_g_uiIndicesVBO));
	glGenBuffersARB(1, &(this->_g_uiIndicesVBO_Top));
	glGenBuffersARB(1, &(this->_g_uiIndicesVBO_Bottom));
}

myCylinder::~myCylinder(){
	if (this->_g_uiIndicesVBO_Top != 0) {
		glDeleteBuffersARB(1, &this->_g_uiIndicesVBO_Top);
		this->_g_uiIndicesVBO_Top = 0;
	}
	if (this->_g_uiIndicesVBO_Bottom != 0) {
		glDeleteBuffersARB(1, &this->_g_uiIndicesVBO_Bottom);
		this->_g_uiIndicesVBO_Bottom = 0;
	}
}

bool myCylinder::draw(){

	// Copy the vertex data to the VBO
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->_g_uiVerticesVBO);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(this->_g_Vertices), this->_g_Vertices, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Copy the index data to the VBO
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(this->_g_Indices), this->_g_Indices, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO_Top);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(this->_g_IndicesT), this->_g_IndicesT, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO_Bottom);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(this->_g_IndicesB), this->_g_IndicesB, GL_STATIC_DRAW_ARB);
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
	glDrawElements(GL_QUAD_STRIP, this->_sizeVertex, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO_Top);
	glDrawElements(GL_POLYGON, this->_sizeIndex_Top_Bottom, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO_Bottom);
	glDrawElements(GL_POLYGON, this->_sizeIndex_Top_Bottom, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Unbind buffers so client-side vertex arrays still work.
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Disable the client side arrays again.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	return true;
}

// mySphere class definitions

mySphere::mySphere(GLfloat radius, GLfloat lats, GLfloat longs){
	this->_type = EmyObjectType::motSphere;
	this->_sizeVertex = SIZEVERTEXSPHERE;
	this->_sizeIndex = SIZEVERTEXSPHERE;

	this->_radius = radius;
	this->_lats = lats;
	this->_longs = longs;

	double user_theta = 0;
	double user_height = 0;

	double lat0, z0, zr0;
	double lat1, z1, zr1;

	double lng, x, y;

	int i, j, index = 0;

	for (i = 0; i <= this->_lats; i++) {
		lat0 = M_PI * (-0.5 + (double)(i - 1) / this->_lats);
		z0 = sin(lat0);
		zr0 = cos(lat0);
		lat1 = M_PI * (-0.5 + (double)i / this->_lats);
		z1 = sin(lat1);
		zr1 = cos(lat1);
		for (j = 0; j <= this->_longs; j++) {
			lng = 2 * M_PI * (double)(j - 1) / this->_longs;
			x = cos(lng);
			y = sin(lng);
			this->_g_Indices[index] = index;
			this->_g_Vertices[index] = {
				float3(x * zr0, y * zr0, z0), // Coord
				float3(x * zr0, y * zr0, z0) // Position
			};
			index++;
			this->_g_Indices[index] = index;
			this->_g_Vertices[index] = {
				float3(x * zr1, y * zr1, z1), // Coord
				float3(x * zr1, y * zr1, z1) // Position
			};
			index++;
		}
	}

	// Create VBO's ID's
	glGenBuffersARB(1, &(this->_g_uiVerticesVBO));
	glGenBuffersARB(1, &(this->_g_uiIndicesVBO));
}

mySphere::~mySphere(){
}

bool mySphere::draw(){

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
	glDrawElements(GL_QUAD_STRIP, this->_sizeIndex, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Unbind buffers so client-side vertex arrays still work.
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Disable the client side arrays again.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	return true;
}

// myPrism class definitions

myPrism::myPrism(GLfloat radius, GLfloat height, GLint sides){
	this->_type = EmyObjectType::motPrism;
	this->_sizeVertex = SIZEVERTEXPRISM;

	this->_radius = radius;
	this->_height = height;
	this->_sides = sides;
	if (this->_sides > 360) {
		this->_sides = 360;
	}

	GLfloat x = 0.0f, y = 0.0f;
	GLfloat angle = 0.0f, angle_stepsize = 0.0f;
	int index = 0, index2 = 0;
	angle_stepsize = 360 / this->_sides;

	for(index = 0, index2 = 0; index < (this->_sides*2); index++, index2++) {
		x = this->_radius * cos((angle/180) * M_PI);
		y = this->_radius * sin((angle / 180) * M_PI);

		this->_g_Indices[index] = index;
		this->_g_IndicesT[index2] = index;
		this->_g_Vertices[index] = {
			float3(x, y, this->_height), // Coord
			float3(x, y, this->_height) // Color
		};
		index++;

		this->_g_Indices[index] = index;
		this->_g_IndicesB[index2] = index;
		this->_g_Vertices[index] = {
			float3(x, y, 0.0f), // Coord
			float3(x, y, 0.0f) // Position
		};

		angle += angle_stepsize;
	}
	this->_g_Indices[index] = index;
	this->_g_IndicesT[index2] = index;
	this->_g_Vertices[index] = {
		float3(this->_radius, 0.0, this->_height), // Coord
		float3(this->_radius, 0.0, this->_height) // Position
	};
	index++;

	this->_g_Indices[index] = index;
	this->_g_IndicesB[index2] = index;
	this->_g_Vertices[index] = {
		float3(this->_radius, 0.0, 0.0), // Coord
		float3(this->_radius, 0.0, 0.0) // Position
	};
	index++;
	index2++;
	
	// Here assign the index because the prism has a variable number 'cause the sides ;@
	this->_sizeIndex = index;
	this->_sizeIndex_Top_Bottom = index2;

	// Create VBO's ID's
	glGenBuffersARB(1, &(this->_g_uiVerticesVBO));
	glGenBuffersARB(1, &(this->_g_uiIndicesVBO));
	glGenBuffersARB(1, &(this->_g_uiIndicesVBO_Top));
	glGenBuffersARB(1, &(this->_g_uiIndicesVBO_Bottom));
}

myPrism::~myPrism(){
}

bool myPrism::draw(){

	// Copy the vertex data to the VBO
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->_g_uiVerticesVBO);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(this->_g_Vertices), this->_g_Vertices, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Copy the index data to the VBO
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(this->_g_Indices), this->_g_Indices, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO_Top);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(this->_g_IndicesT), this->_g_IndicesT, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO_Bottom);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(this->_g_IndicesB), this->_g_IndicesB, GL_STATIC_DRAW_ARB);
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
	glDrawElements(GL_QUAD_STRIP, this->_sizeIndex, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO_Top);
	glDrawElements(GL_POLYGON, this->_sizeIndex_Top_Bottom, GL_UNSIGNED_INT, BUFFER_OFFSET(1));

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO_Bottom);
	glDrawElements(GL_POLYGON, this->_sizeIndex_Top_Bottom, GL_UNSIGNED_INT, BUFFER_OFFSET(2));

	// Unbind buffers so client-side vertex arrays still work.
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Disable the client side arrays again.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	return true;
}

// myOBJModel class definitions

myOBJModel::myOBJModel(std::string pathToFile){
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

bool myPlane::draw(){
	glPushMatrix();
		glScalef(1.0f, 0.05f, 1.0f);	
		this->_cubeBase.draw();
	glPopMatrix();
	return true;
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

bool myRaytrace::setOrder(GLint order){
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
