#version 330 core

layout(location = 0) out vec4 color;

in vertData
{
	vec4 position;
	vec4 vertColour;
	vec2 texCoords;
	float texID;
} inVertexData;

struct Material
{
	sampler2D u_fTexSampler[32];
};

uniform Material u_Material;

void main()
{
	vec4 pixelColor = (inVertexData.texID > 0.5) ? 
		texture(u_Material.u_fTexSampler[int(inVertexData.texID - 0.5f)], inVertexData.texCoords) : 
		inVertexData.vertColour;

	if(pixelColor.a < 0.01)
	{
        discard;
	}

	color = pixelColor;
}