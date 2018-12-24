

// ================================ //
//
struct InputVS
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

// ================================ //
//
struct OutputVS
{
	float4 Pos : POSITIONT;
	float2 Tex : TEXCOORD;
};

// ================================ //
//
cbuffer RenderingSystemConsts : register(b0)
{
	float2		Offset;
}


// ================================ //
//
OutputVS		main	( InputVS input )
{
	OutputVS output = (OutputVS)0;

	output.Pos = GeometryFunctionPos( input.Pos, input.Tex );
	output.Tex = GeometryFunctionTex( input.Pos, input.Tex );

	output.Pos.xy = output.Pos.xy + RenderingSystemConsts.Offset;

	return out;
}
