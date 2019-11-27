#include "EGBase_vertex.hlsl"

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

PixelInput main(VertexInput vIn)
{
	PixelInput vOut;

	vOut.position = GetScreenPosition(vIn.position);
	vOut.color = vIn.color;
	vOut.uv = vIn.uv;

	return vOut;
}