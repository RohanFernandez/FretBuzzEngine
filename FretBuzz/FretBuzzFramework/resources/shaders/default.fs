#version 330 core

layout(location = 0) out vec4 color;

in vertData
{
	vec4 position;
	vec4 vertColour;
	vec2 texCoords;
	float texID;
} inVertexData;

uniform sampler2D textureSampler[32];

void main()
{
	vec4 pixelColor = (inVertexData.texID > 0.5) ? 
		texture(textureSampler[int(inVertexData.texID - 0.5f)], inVertexData.texCoords) : 
		inVertexData.vertColour;

	if(pixelColor.a < 0.01)
	{
        discard;
	}

	color = pixelColor;
}