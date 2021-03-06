#include "Sprite.h"



Sprite::Sprite(){
}


Sprite::Sprite(GLfloat positionX, GLfloat positionY, GLfloat width, GLfloat height, const char* filePath){
	
	vertex[PositionTuples::BOTTOM_LEFT].setPosition(positionX, positionY);
	vertex[PositionTuples::BOTTOM_LEFT].setNormal(1.0f, 1.0f);

	vertex[PositionTuples::TOP_LEFT].setPosition(positionX, positionY + height);
	vertex[PositionTuples::TOP_LEFT].setNormal(1.0f, 1.0f);

	vertex[PositionTuples::TOP_RIGHT].setPosition(positionX + width, positionY + height);
	vertex[PositionTuples::TOP_RIGHT].setNormal(1.0f, 1.0f);

	vertex[PositionTuples::BOTTOM_RIGHT].setPosition(positionX + width, positionY);
	vertex[PositionTuples::BOTTOM_RIGHT].setNormal(1.0f, 1.0f);

	shader.create("Shaders/passthrough.vert", fragName);
	
	//LoadBMP(filePath);

}

void Sprite::init(GLfloat positionX, GLfloat positionY, GLfloat width, GLfloat height, const char* filePath) {

	vertex[PositionTuples::BOTTOM_LEFT].setPosition(positionX, positionY);
	vertex[PositionTuples::BOTTOM_LEFT].setUV(0.0f, 0.0f);
	vertex[PositionTuples::BOTTOM_LEFT].setNormal((positionX + width) - positionX, 1.0f);
	vertex[PositionTuples::BOTTOM_LEFT].setColor(255, 255, 255, 255);

	vertex[PositionTuples::TOP_LEFT].setPosition(positionX, positionY + height);
	vertex[PositionTuples::TOP_LEFT].setUV(0.0f, 1.0f);
	vertex[PositionTuples::TOP_LEFT].setNormal(-1.0f, 1.0f);
	vertex[PositionTuples::TOP_LEFT].setColor(255, 255, 255, 255);

	vertex[PositionTuples::TOP_RIGHT].setPosition(positionX + width, positionY + height);
	vertex[PositionTuples::TOP_RIGHT].setUV(1.0f, 1.0f);
	vertex[PositionTuples::TOP_RIGHT].setNormal(1.0f, -1.0f);
	vertex[PositionTuples::TOP_RIGHT].setColor(255, 255, 255, 255);

	vertex[PositionTuples::BOTTOM_RIGHT].setPosition(positionX + width, positionY);
	vertex[PositionTuples::BOTTOM_RIGHT].setUV(1.0f, 0.0f);
	vertex[PositionTuples::BOTTOM_RIGHT].setNormal(1.0f, 0.0f);
	vertex[PositionTuples::BOTTOM_RIGHT].setColor(255, 255, 255, 255);


	//using namespace lml;
	Vector3 edge1 = Vector3(vertex[PositionTuples::TOP_LEFT].pos.x, vertex[PositionTuples::TOP_LEFT].pos.y, 1.0f) -
		Vector3(vertex[PositionTuples::BOTTOM_RIGHT].pos.x, vertex[PositionTuples::BOTTOM_RIGHT].pos.y, -1.0f);
	std::cout << "\n" << edge1.x << ", " << edge1.y;
	Vector3 edge2 = Vector3(vertex[PositionTuples::BOTTOM_RIGHT].pos.x, vertex[PositionTuples::BOTTOM_RIGHT].pos.y, 1.0f) -
		Vector3(vertex[PositionTuples::BOTTOM_LEFT].pos.x, vertex[PositionTuples::BOTTOM_LEFT].pos.y, 1.0f);
	std::cout << "\n" << edge2.x << ", " << edge2.y;
	Vector3 normals = ::crossProduct(edge2, edge1);
	normals.normalize();
	std::cout << "~" << normals.x;
	vertex[PositionTuples::BOTTOM_LEFT].setNormal(-normals.x, normals.y);
	vertex[PositionTuples::BOTTOM_RIGHT].setNormal(normals.x, -normals.y);
	vertex[PositionTuples::TOP_LEFT].setNormal(normals.x, normals.y);
	vertex[PositionTuples::TOP_RIGHT].setNormal(normals.x, normals.y);
	
	shader.create("Shaders/passthrough.vert", fragName);

	

	glGenVertexArrays(1, &vertexID);

	glGenBuffers(1, &bufferID);
	glGenBuffers(1, &eboID);
	
	glBindVertexArray(vertexID);

	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STREAM_DRAW);


	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexNorm), reinterpret_cast<GLvoid *>(offsetof(VertexNorm, pos)));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexNorm), reinterpret_cast<GLvoid *>(offsetof(VertexNorm, color)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexNorm), reinterpret_cast<GLvoid *>(offsetof(VertexNorm, uv)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexNorm), reinterpret_cast<GLvoid *>(offsetof(VertexNorm, normal)));



	unsigned long myWidth, myHeight;
	LoadBMP(filePath, myWidth, myHeight, textureID);
}



void Sprite::render(const OrthographicCamera &camera){
	shader.useProgram();
	
	glUniform3f(glGetUniformLocation(shader.getProgramID(), "lightColor"), 200, 220, 220);
	glUniform3f(glGetUniformLocation(shader.getProgramID(), "lightPosition"), 0.5, 1, 1.0);

	glBindVertexArray(vertexID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	camera.sendToShader(shader.getProgramID());

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);


	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader.unuseProgram();
}


void Sprite::translate(GLfloat xAmount, GLfloat yAmount){
	vertex[PositionTuples::BOTTOM_LEFT].setPosition(vertex[PositionTuples::BOTTOM_LEFT].pos.x + xAmount,
		vertex[PositionTuples::BOTTOM_LEFT].pos.y + yAmount);
	vertex[PositionTuples::BOTTOM_RIGHT].setPosition(vertex[PositionTuples::BOTTOM_RIGHT].pos.x + xAmount,
		vertex[PositionTuples::BOTTOM_RIGHT].pos.y + yAmount);
	vertex[PositionTuples::TOP_LEFT].setPosition(vertex[PositionTuples::TOP_LEFT].pos.x + xAmount,
		vertex[PositionTuples::TOP_LEFT].pos.y + yAmount);
	vertex[PositionTuples::TOP_RIGHT].setPosition(vertex[PositionTuples::TOP_RIGHT].pos.x + xAmount,
		vertex[PositionTuples::TOP_RIGHT].pos.y + yAmount);

	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);

}

Sprite::~Sprite(){
}
