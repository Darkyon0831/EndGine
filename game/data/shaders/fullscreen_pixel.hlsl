#define NOMAT
#define NOTEXTURE

Texture2DArray textureArray;

#include "EGBase_pixel.hlsl"

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	uint instanceID : SV_InstanceID;
	float2 uv : TEXCOORD;
};

float4 main(PixelInput pIn) : SV_TARGET
{
	const int index = pIn.instanceID;

	float3 uvz = float3(pIn.uv.x, pIn.uv.y, index);
	
	float4 TexColor = textureArray.Sample(GetSamplerState(), uvz);
	TexColor *= pIn.color;

	return TexColor;
}