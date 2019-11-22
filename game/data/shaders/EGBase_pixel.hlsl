uniform float4 u_materialColor;

Texture2D u_colormap;
SamplerState u_samplerState;

float4 GetMaterialColor()
{
	return u_materialColor;
}

Texture2D GetColormap()
{
	return u_colormap;
}

SamplerState GetSamplerState()
{
	return u_samplerState;
}