
#ifndef NOMAT
uniform float4 u_materialColor;
#endif

#ifndef NOTEXTURE
Texture2D u_colormap;
#endif

SamplerState u_samplerState;

#ifndef NOMAT
float4 GetMaterialColor()
{
	return u_materialColor;
}
#endif

#ifndef NOTEXTURE
Texture2D GetColormap()
{
	return u_colormap;
}
#endif

SamplerState GetSamplerState()
{
	return u_samplerState;
}