#define NOINPUT

#include "EGBase_vertex.hlsl"

struct VertexInput
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD0;
	float3 instancePosition : TEXCOORD1;
	float3 instanceScale : TEXCOORD2;
	uint instanceID : SV_InstanceID;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	uint instanceID : SV_InstanceID;
	float2 uv : TEXCOORD;
};

PixelInput main(VertexInput vIn)
{
	PixelInput vOut;

	vIn.position.x *= vIn.instanceScale.x;
	vIn.position.y *= vIn.instanceScale.y;
	vIn.position.z *= vIn.instanceScale.z;

	vIn.position.x += vIn.instancePosition.x;
	vIn.position.y += vIn.instancePosition.y;
	vIn.position.z += vIn.instancePosition.z;

	float4 result = GetScreenPosition(vIn.position);

	vOut.position = result;
	vOut.color = vIn.color;
	vOut.instanceID = vIn.instanceID;
	vOut.uv = vIn.uv;

	return vOut;
}