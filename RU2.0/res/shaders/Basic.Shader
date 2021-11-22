#shader vertex
#version 330 core 

layout(location = 0) in vec4 position; 
layout(location = 1) in vec2 texCoord; 
layout(location = 2) in vec4 color; 
layout(location = 3) in float texIndex;

out vec2 v_TexCoord;
out float v_TexIndex;
out vec4 v_Color;
uniform mat4 u_MVP;

void main() 
{ 
	v_TexCoord = texCoord;
	v_TexIndex = texIndex;
	v_Color = color;
    gl_Position = u_MVP * position;
  
};


#shader fragment
#version 330 core 

layout(location = 0) out vec4 color; 

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TexIndex;
uniform sampler2D u_Texture[32];

void main() 
{ 
	int index = int(round(v_TexIndex));
	
	vec4 texColor = texture(u_Texture[index], v_TexCoord) * v_Color;
	color = texColor;
	//color = vec4(index, index, index, 1.0f);
};