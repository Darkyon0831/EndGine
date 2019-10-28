#include "helpers.hlsl"

float4x4 world;
float4x4 view;
float4x4 projection;

struct VertexInput
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR; 
	float2 uv : TEXCOORD;
};

PixelInput main(VertexInput input)
{
	PixelInput output;

	input.position.w = 1.0;

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	output.color = input.color;
	output.uv = input.uv;

	return output;
}