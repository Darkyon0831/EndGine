////////////////////////////////////////
// Containes helper functions to be used in different shaders
///////////////////////////////////////

float4 GetScreenPosition(float4 localPosition, float4x4 worldViewProjection)
{
	localPosition.w = 1.0;

	return mul(worldViewProjection, localPosition);
}
