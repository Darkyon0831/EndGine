struct VertexInput
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
	float4 world1 : WORLD0;
	float4 world2 : WORLD1;
	float4 world3 : WORLD2;
	float4 world4 : WORLD3;
	float4 view1 : VIEW0;
	float4 view2 : VIEW1;
	float4 view3 : VIEW2;
	float4 view4 : VIEW3;
	float4 projection1 : PROJECTION0;
	float4 projection2 : PROJECTION1;
	float4 projection3 : PROJECTION2;
	float4 projection4 : PROJECTION3;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

PixelInput main(VertexInput vIn)
{
	PixelInput vOut;

	float4x4 world =
	{
		vIn.world1.x, vIn.world1.y, vIn.world1.z, vIn.world1.w,
		vIn.world2.x, vIn.world2.y, vIn.world2.z, vIn.world2.w,
		vIn.world3.x, vIn.world3.y, vIn.world3.z, vIn.world3.w,
		vIn.world4.x, vIn.world4.y, vIn.world4.z, vIn.world4.w
	};

	float4x4 view =
	{
		vIn.view1.x, vIn.view1.y, vIn.view1.z, vIn.view1.w,
		vIn.view2.x, vIn.view2.y, vIn.view2.z, vIn.view2.w,
		vIn.view3.x, vIn.view3.y, vIn.view3.z, vIn.view3.w,
		vIn.view4.x, vIn.view4.y, vIn.view4.z, vIn.view4.w
	};

	float4x4 projection =
	{
		vIn.projection1.x, vIn.projection1.y, vIn.projection1.z, vIn.projection1.w,
		vIn.projection2.x, vIn.projection2.y, vIn.projection2.z, vIn.projection2.w,
		vIn.projection3.x, vIn.projection3.y, vIn.projection3.z, vIn.projection3.w,
		vIn.projection4.x, vIn.projection4.y, vIn.projection4.z, vIn.projection4.w
	};

	float4 result;
	result = mul(vIn.position, world);
	result = mul(result, view);
	result = mul(result, projection);

	vOut.position = result;
	vOut.color = vIn.color;
	vOut.uv = vIn.uv;

	return vOut;
}