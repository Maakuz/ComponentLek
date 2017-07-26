struct GS_OUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
};

float4 main(GS_OUT input) : SV_TARGET
{
	return float4(input.color, 1);
}