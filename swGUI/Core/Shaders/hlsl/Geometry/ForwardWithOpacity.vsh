

// ================================ //
//
float4			GeometryFunctionPos		( float4 pos, float2 maskUV, float2 tex )
{
	return pos;
}

// ================================ //
//
float2			GeometryFunctionAtlas	( float4 pos, float2 maskUV, float2 tex )
{
    return maskUV;
}

// ================================ //
//
float2			GeometryFunctionTex		( float4 pos, float2 maskUV, float2 tex )
{
    return tex;
}



