#include "myPrimitives.h"

// myMaterial class definitions

myMaterial::myMaterial(
	glm::vec4 ambient, glm::vec4 diffuse, 
	glm::vec4 specular, glm::vec4 emission, 
	float shininess){

	this->_ambient = ambient;
	this->_diffuse = diffuse;
	this->_specular = specular;
	this->_emission = emission;
	this->_shininess = shininess;
}

bool myMaterial::apply(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &(this->_ambient[0]));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &(this->_diffuse[0]));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &(this->_specular[0]));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &(this->_emission[0]));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->_shininess);
	return true;
}



// myBaseObject class definitions

myBaseObject::myBaseObject(){
	this->_type = EmyObjectType::motBase;
	this->_position = glm::vec3(0.0f, 0.0f, 0.0f);
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

glm::vec3 myBaseObject::getPosition(){
	return this->_position;
}

// myLight

myLight::myLight(GLenum lightID,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,
	glm::vec4 position, glm::vec3 spotDirection,
	float spotExponent, float spotCutoff,
	float constantAttenuation, float linearAttenuation, float quadraticAttenuation) {

	this->_lightID = lightID;
	this->_ambient = ambient;
	this->_diffuse = diffuse;
	this->_specular = specular;
	this->position = position;
	this->spotDirection = spotDirection;
	this->_spotExponent = spotExponent;
	this->_spotCutoff = spotCutoff;
	this->_constantAttenuation = constantAttenuation;
	this->_linearAttenuation = linearAttenuation;
	this->_quadraticAttenuation = quadraticAttenuation;
}

void myLight::activate() {
	glEnable(this->_lightID);
	glLightfv(this->_lightID, GL_AMBIENT, &(this->_ambient[0]));
	glLightfv(this->_lightID, GL_DIFFUSE, &(this->_diffuse[0]));
	glLightfv(this->_lightID, GL_SPECULAR, &(this->_specular[0]));
	glLightfv(this->_lightID, GL_POSITION, &(this->position[0]));
	glLightfv(this->_lightID, GL_SPOT_DIRECTION, &(this->spotDirection[0]));
	glLightf(this->_lightID, GL_SPOT_EXPONENT, this->_spotExponent);
	glLightf(this->_lightID, GL_SPOT_CUTOFF, this->_spotCutoff);
	glLightf(this->_lightID, GL_CONSTANT_ATTENUATION, this->_constantAttenuation);
	glLightf(this->_lightID, GL_LINEAR_ATTENUATION, this->_linearAttenuation);
	glLightf(this->_lightID, GL_QUADRATIC_ATTENUATION, this->_quadraticAttenuation);
}

void myLight::deactivate() {
	glDisable(this->_lightID);
}

// my3dObjectBase class definitions

my3dObjectBase::my3dObjectBase(){
	this->_type = EmyObjectType::mot3dBase;
	this->_sizeVertex = 0;
	this->_sizeIndex = 0;
	this->_textureObject = 0;

	this->_radius = 0;
	this->_width = 0;
	this->_height = 0;
	this->_sides = 0;
	this->_scale = 0;
	this->_transparency = 0;

	// Create VBO's ID
	glGenBuffersARB(1, &(this->_g_uiVerticesVBO));
	glGenBuffersARB(1, &(this->_g_uiIndicesVBO));
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
	if (this->_textureObject != 0) {
		glDeleteTextures(1, &this->_textureObject);
	}
}

bool my3dObjectBase::setMaterial(myMaterial material){
	this->_material = material;
	return true;
}

myMaterial my3dObjectBase::getMaterial(){
	return this->_material;
}

bool my3dObjectBase::loadTexture(std::string pathToTexture){
	unsigned char* image = SOIL_load_image(pathToTexture.c_str(), &this->_textureWidth, &this->_textureHeight, NULL, SOIL_LOAD_RGBA);
	
	glGenTextures(1, &this->_textureObject);
	glBindTexture(GL_TEXTURE_2D, this->_textureObject);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	if (image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_textureWidth,
			this->_textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Se cargo la textura " << pathToTexture.c_str() << "" << std::endl;
	} else {
		std::cout << "No se cargo la textura " << pathToTexture.c_str() << "" << std::endl;
		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image);
		return false;
	}

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return true;
}

bool my3dObjectBase::bindTexture(){
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->_textureObject);
	return true;
}

bool my3dObjectBase::unbindTexture(){
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

bool my3dObjectBase::setTypeOfTexture(EmyTypeOfTexture typeOfTexture){
	this->_typeOfTexture = typeOfTexture;
	return true;
}

EmyTypeOfTexture my3dObjectBase::getTypeOfTexture(){
	return this->_typeOfTexture;
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
	
	this->_sizeVertex = SIZEVERTEXCUBE;
	this->_sizeIndex = SIZEINDEXCUBE;
	this->_drawMode = GL_QUADS;
}

myCube::~myCube(){
}

bool myCube::draw(){

	// Copy the vertex data to the VBO
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->_g_uiVerticesVBO);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(this->_g_Vertices) * this->_sizeVertex, this->_g_Vertices, GL_STATIC_COPY_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Copy the index data to the VBO
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(this->_g_Indices) * this->_sizeIndex, this->_g_Indices, GL_STATIC_COPY_ARB);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	// We need to enable the client stats for the vertex attributes we want 
	// to render even if we are not using client-side vertex arrays.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Bind the vertices's VBO
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->_g_uiVerticesVBO);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Pos));
	glColorPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Color));
	glNormalPointer(GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Normal));
	glTexCoordPointer(2, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_TextureCoord));

	// Bind the indices's VBO
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO);
	glDrawElements(this->_drawMode, this->_sizeIndex, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Unbind buffers so client-side vertex arrays still work.
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Disable the client side arrays again.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

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
	float uSteep = 1.0 / (float)((float)SIZEVERTEXCYLINDER / 2.0);
	float u = 0;

	GLfloat x = 0.0f, y = 0.0f;
	GLfloat angle = 0.0f, angle_stepsize = 0.1f;
	int index = 0, index2 = 0;

	while (angle < 2 * M_PI) {

		x = this->_radius * cos(angle);
		y = this->_radius * sin(angle);

		// Top vertex
		this->_g_Indices[index] = index;
		this->_g_IndicesT[index2] = index;
		this->_g_Vertices[index] = {
			glm::vec3(x, y, this->_height), // Coord
			glm::vec3(x, y, this->_height), // Color
			glm::normalize(glm::vec3(x, y, this->_height)), // Normal
			glm::vec2(u,0)	// UV
		};
		index++;

		// Bottom vertex
		this->_g_Indices[index] = index;
		this->_g_IndicesB[index2] = index;
		this->_g_Vertices[index] = {
			glm::vec3(x, y, 0.0f), // Coord
			glm::vec3(x, y, 0.0f), // Color
			glm::normalize(glm::vec3(x, y, 0.0f)), // Normal
			glm::vec2(u,1)	// UV
		};
		index++;

		angle += angle_stepsize;
		index2++;
		u += uSteep;
	}

	// Top
	this->_g_Indices[index] = index;
	this->_g_IndicesT[index2] = index;
	this->_g_Vertices[index] = {
		glm::vec3(this->_radius, 0.0, this->_height), // Coord
		glm::vec3(this->_radius, 0.0, this->_height), // Color
		glm::normalize(glm::vec3(this->_radius, 0.0, this->_height)), // Normal
		glm::vec2(u,0)	// UV
	};
	index++;

	// Bottom
	this->_g_Indices[index] = index;
	this->_g_IndicesB[index2] = index;
	this->_g_Vertices[index] = {
		glm::vec3(this->_radius, 0.0, 0.0), // Coord
		glm::vec3(this->_radius, 0.0, 0.0), // Color
		glm::normalize(glm::vec3(this->_radius, 0.0, 0.0)), // Normal
		glm::vec2(u,1)	// UV
	};

	// Create VBO's ID's
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
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Bind the vertices's VBO
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->_g_uiVerticesVBO);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Pos));
	glColorPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Color));
	glNormalPointer(GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Normal));
	glTexCoordPointer(2, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_TextureCoord));

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
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	return true;
}

// mySphere class definitions

mySphere::mySphere(GLfloat radius, GLfloat lats, GLfloat longs){
	this->_type = EmyObjectType::motSphere;
	this->_sizeVertex = SIZEVERTEXSPHERE;
	this->_sizeIndex = SIZEVERTEXSPHERE;
	/*
	this->_g_Vertices = new VertexXYZColor[this->_sizeVertex];
	this->_g_Indices = new GLuint[this->_sizeIndex];
	*/

	this->_radius = radius;
	this->_lats = lats;
	this->_longs = longs;

	double user_theta = 0;
	double user_height = 0;

	double lat0, z0, zr0;
	double lat1, z1, zr1;

	double lng, x, y;

	double uSteep, vSteep;
	double u = 0, v = 0;

	int i, j, index = 0;

	uSteep = 1 / this->_longs;
	vSteep = 1 / this->_lats;
	for (i = 0; i <= this->_lats; i++) {
		lat0 = M_PI * (-0.5 + (double)(i - 1) / this->_lats);
		z0 = sin(lat0);
		zr0 = cos(lat0);
		lat1 = M_PI * (-0.5 + (double)i / this->_lats);
		z1 = sin(lat1);
		zr1 = cos(lat1);
		u = 0;
		for (j = 0; j <= this->_longs; j++) {
			lng = 2 * M_PI * (double)(j - 1) / this->_longs;
			x = cos(lng);
			y = sin(lng);
			this->_g_Indices[index] = index;
			this->_g_Vertices[index] = {
				glm::vec3(x * zr0, y * zr0, z0), // Coord
				glm::vec3(x * zr0, y * zr0, z0), // Color
				glm::normalize(glm::vec3(x * zr0, y * zr0, z0)), // Normal
				glm::vec2(u, v)	// UV
			};
			index++;
			this->_g_Indices[index] = index;
			this->_g_Vertices[index] = {
				glm::vec3(x * zr1, y * zr1, z1), // Coord
				glm::vec3(x * zr1, y * zr1, z1), // Color
				glm::normalize(glm::vec3(x * zr1, y * zr1, z1)), // Normal
				glm::vec2(u, v)	// UV
			};
			index++;
			u += uSteep;
		}
		v += vSteep;
	}

	this->_drawMode = GL_QUAD_STRIP;
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
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Bind the vertices's VBO
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->_g_uiVerticesVBO);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Pos));
	glColorPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Color));
	glNormalPointer(GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Normal));
	glTexCoordPointer(2, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_TextureCoord));

	// Bind the indices's VBO
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO);
	glDrawElements(this->_drawMode, this->_sizeIndex, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Unbind buffers so client-side vertex arrays still work.
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Disable the client side arrays again.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

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

	float u = 0;
	float uSteep;
	uSteep = 1.0f / (float)this->_sides;

	for(index = 0, index2 = 0; index < (this->_sides*2); index++, index2++) {
		x = this->_radius * cos((angle/180) * M_PI);
		y = this->_radius * sin((angle / 180) * M_PI);

		this->_g_Indices[index] = index;
		this->_g_IndicesT[index2] = index;
		this->_g_Vertices[index] = {
			glm::vec3(x, y, this->_height), // Coord
			glm::vec3(x, y, this->_height), // Color
			glm::normalize(glm::vec3(x, y, this->_height)), // Normal
			glm::vec2(u, 0)	// UV
		};
		index++;

		this->_g_Indices[index] = index;
		this->_g_IndicesB[index2] = index;
		this->_g_Vertices[index] = {
			glm::vec3(x, y, 0.0f), // Coord
			glm::vec3(x, y, 0.0f), // Color
			glm::normalize(glm::vec3(x, y, 0.0f)), // Normal
			glm::vec2(u, 1)	// UV
		};

		angle += angle_stepsize;
		u += uSteep;
	}
	this->_g_Indices[index] = index;
	this->_g_IndicesT[index2] = index;
	this->_g_Vertices[index] = {
		glm::vec3(this->_radius, 0.0, this->_height), // Coord
		glm::vec3(this->_radius, 0.0, this->_height), // Color
		glm::normalize(glm::vec3(this->_radius, 0.0, this->_height)), // Normal
		glm::vec2(0, 0)	// UV
	};
	index++;

	this->_g_Indices[index] = index;
	this->_g_IndicesB[index2] = index;
	this->_g_Vertices[index] = {
		glm::vec3(this->_radius, 0.0, 0.0), // Coord
		glm::vec3(this->_radius, 0.0, 0.0), // Color
		glm::normalize(glm::vec3(this->_radius, 0.0, 0.0)), // Normal
		glm::vec2(1, 1)	// UV
	};
	index++;
	index2++;
	
	// Here assign the index because the prism has a variable number 'cause the sides ;@
	this->_sizeIndex = index;
	this->_sizeIndex_Top_Bottom = index2;

	// Create VBO's ID's
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
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_2D_ARRAY);

	// Bind the vertices's VBO
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->_g_uiVerticesVBO);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Pos));
	glColorPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Color));
	glNormalPointer(GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Normal));
	glTexCoordPointer(2, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_TextureCoord));

	// Bind the indices's VBO
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO);
	glDrawElements(GL_QUAD_STRIP, this->_sizeIndex, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

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
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_2D_ARRAY);

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

// myGrid class definitions

myGrid::myGrid(GLfloat sizeCell, GLfloat numCells) {

	this->_type = EmyObjectType::motGrid;
	this->_sizeCell = sizeCell;
	this->_numCells = numCells;

	int size = ((this->_numCells) + 1) * 2;	// Because we are taking from -numCells to numCells

	this->_g_Vertices = new VertexXYZColor[size];
	this->_g_Indices = new GLuint[size];

	GLuint index = 0;
	for (int i = 0; i <= this->_numCells; i++) {

	}
	this->_sizeVertex = index;
	this->_sizeIndex = index;
}

myGrid::~myGrid()
{
}

bool myGrid::draw(){
	// Copy the vertex data to the VBO
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->_g_uiVerticesVBO);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(this->_g_Vertices) * this->_sizeVertex, this->_g_Vertices, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Copy the index data to the VBO
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(this->_g_Indices) * this->_sizeIndex, this->_g_Indices, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	// We need to enable the client stats for the vertex attributes we want 
	// to render even if we are not using client-side vertex arrays.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// Bind the vertices's VBO
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->_g_uiVerticesVBO);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Pos));
	glColorPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Color));
	glNormalPointer(GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Normal));

	// Bind the indices's VBO
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->_g_uiIndicesVBO);
	glDrawElements(GL_LINES, this->_sizeIndex, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Unbind buffers so client-side vertex arrays still work.
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Disable the client side arrays again.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	
	return true;
}

bool myGrid::draw2(){
	glBegin(GL_LINES);
	for (int i = -this->_numCells; i <= this->_numCells; i++) {
		glVertex3f((float)i * this->_sizeCell, (float)this->_numCells * this->_sizeCell, 0.0f);
		glVertex3f((float)i * this->_sizeCell, -(float)this->_numCells * this->_sizeCell, 0.0f);
		glVertex3f((float)this->_numCells * this->_sizeCell, (float)i * this->_sizeCell, 0.0f);
		glVertex3f(-(float)this->_numCells * this->_sizeCell, (float)i * this->_sizeCell, 0.0f);
	}
	glEnd();
	return true;
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

EtypeOfMethodForRayTrace myRaytrace::getTypeOfMethod() {
	return this->_method;
}
