

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
	linear			float4 Pos : SV_Position;
	noperspective	float2 Tex : TEXCOORD;
};

// ================================ //
//
cbuffer RenderingSystemConsts : register( b0 )
{
	float2		_RenderingSystemConsts_ViewportSize;
}

// ================================ //
//
cbuffer VisualConsts : register( b1 )
{
	float2		_VisualConstants_Offset;
}

// ================================ //
//
float4			TransformVertex		( float2 pos )
{
	// GUI uses coordinates system with y-axis directed to bottom.
	// We have to inverse offset for directX.
	float2 offset = _VisualConstants_Offset;
	offset.y = -offset.y;

	float2 offsetedPos = pos + offset;

	// Rescale object from screen size to [-1.0, 1.0] range.
	float2 halfViewportSize = _RenderingSystemConsts_ViewportSize;

	float4 vertex = { 0.0, 0.0, 0.5, 1.0 };
	vertex.xy = offsetedPos / halfViewportSize;
	vertex.z = 0.5;
	vertex.w = 1.0;

	// Move top left corner to point [-1.0, 1.0].
	vertex.xy = vertex.xy + float2( -1.0, 1.0 );

	return vertex;
}


// ================================ //
//
OutputVS		main	( InputVS input )
{
	OutputVS output = (OutputVS)0;

	output.Pos = GeometryFunctionPos( input.Pos, input.Tex );
	output.Tex = GeometryFunctionTex( input.Pos, input.Tex );

	output.Pos = TransformVertex( output.Pos.xy );

	return output;
}
