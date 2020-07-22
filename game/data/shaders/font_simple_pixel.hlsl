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
	TexColor.g = TexColor.r;
	TexColor.b = TexColor.r;
	TexColor.a = TexColor.r;
	TexColor *= pIn.color;
	TexColor *= GetMaterialColor();



	//if (TexColor.r == 0.0f && TexColor.g == 0.0f && TexColor.b == 0.0f) TexColor.a = 0.0f;


	return TexColor;
}