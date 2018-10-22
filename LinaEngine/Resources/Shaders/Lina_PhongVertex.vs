#version 330 core //This line states we are using core functionality of OpenGL 3.3

//As we stated in glVertexAttribPointer we declare position at the location 0.
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 texCoord0;
out vec3 normal0;
out vec3 worldPos0;

uniform mat4 model;
uniform mat4 modelViewProjection;


void main()
{	
	gl_Position =  modelViewProjection * vec4(position, 1.0);
	texCoord0 = texCoord;
	normal0 = (model * vec4(normal, 0.0)).xyz;
	worldPos0 = (model * vec4(position, 1.0)).xyz;
}