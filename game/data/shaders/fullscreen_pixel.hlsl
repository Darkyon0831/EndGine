#define NOMAT
#define NOTEXTURE

Texture2D textures[10];

#include "EGBase_pixel.hlsl"

struct PixelInput
{
	float4 position : SV_POSITION;
	int instanceID : SV_InstanceID;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

float4 main(PixelInput pIn) : SV_TARGET
{
	Texture2D currentTexture = textures[0];
	float4 TexColor = currentTexture.Sample(GetSamplerState(), pIn.uv);
	TexColor *= pIn.color;

	return TexColor;
}