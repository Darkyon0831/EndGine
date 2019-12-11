#include "EGBase_pixel.hlsl"

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

float4 main(PixelInput pIn) : SV_TARGET
{
	float4 TexColor = GetColormap().Sample(GetSamplerState(), pIn.uv);
	TexColor *= pIn.color;
	TexColor *= GetMaterialColor();

	return TexColor;
}