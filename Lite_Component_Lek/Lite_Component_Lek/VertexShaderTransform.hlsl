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

cbuffer transformBuffer : register(b1)
{
    matrix transform;
};


VS_OUT main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;

    output.pos = float4(input.pos, 1);

    output.pos = mul(output.pos, transform);
    output.wPos = output.pos;
    output.pos = mul(output.pos, VP);

    output.normal = input.normal;
    output.normal = normalize(mul(float4(output.normal.xyz, 0), transform));
    output.color = input.color;

    return output;
}