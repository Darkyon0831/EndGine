Texture2D shaderTexture;
SamplerState samplerState;

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

float4 main(PixelInput input) : SV_TARGET
{
	float4 TexColor = shaderTexture.Sample(samplerState, input.uv);

	return TexColor;
}