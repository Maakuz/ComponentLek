struct VS_IN
{
	float3 pos : POSITION;
    float3 normal : NORMAL;
	float3 color : COLOR;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
    float4 wPos : WORLD_POS;
    float3 normal : NORMAL;
	float3 color : COLOR;
};

cbuffer VP : register(b0)
{
    matrix VP;
};


VS_OUT main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	output.pos = float4(input.pos, 1);

    output.wPos = output.pos;
    output.normal = normalize(input.normal.xyz);

    output.pos = mul(output.pos, VP);

	output.color = input.color;

	return output;
}