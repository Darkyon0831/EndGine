
#ifndef NOMATRIX
float4x4 worldMatrix;
float4x4 viewMatrix;
float4x4 projectionMatrix;

float4 GetScreenPosition(float4 pos)
{
	float4 result;

	pos.w = 1.0;
	result = mul(pos, worldMatrix);
	result = mul(result, viewMatrix);
	result = mul(result, projectionMatrix);

	return result;
}
#endif

#ifndef NOINPUT
struct VertexInput
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};
#endif