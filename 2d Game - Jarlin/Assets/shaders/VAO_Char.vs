#version 420 core
 layout (location = 0) in vec3 position; 
 layout (location = 1) in vec3 color; 
 layout (location = 2) in vec2 texCoord;

out vec3 outColor; 
out vec2 TexCoord;

uniform mat4 transform; 

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;
uniform mat4 world;

void main(void)
{ 
	gl_Position = world * projection * view *  model * vec4(position, 1.0);
	outColor = color;
	TexCoord = texCoord;
 }