

struct InputVS
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct OutputVS
{
	float4 Pos : SV_POSITION;
};

OutputVS		main	( InputVS input )
{
	OutputVS output = (OutputVS)0;
	return output;
}
