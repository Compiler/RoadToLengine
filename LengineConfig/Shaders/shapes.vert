#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
//layout(location = 2) in vec2 vNormal;

out vec4 fColor;
//out vec2 fNormal;

uniform mat4 projMatrix;

void main(){
	
	gl_Position = projMatrix * vec4(vPosition.xyz, 1.0);
	
	fColor = vColor;
	
	//fNormal = vNormal;
}