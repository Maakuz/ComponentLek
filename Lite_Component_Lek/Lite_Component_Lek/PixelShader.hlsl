struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 wPos : WORLD_POS;
    float3 normal : NORMAL;
    float3 color : COLOR;
};

cbuffer directionalLights : register (b0)
{
    int nrOfLights;
    int otherint;
    float4 dir[10];
    float4 color[10];
}

float4 main(VS_OUT input) : SV_TARGET
{
    float3 diffuse = 0;

    for (int i = 0; i < min(nrOfLights, 10); i++)
    {
        diffuse += (dot(dir[i].xyz, input.normal.xyz) * color[i].xyz);
    }
        
    return float4(input.color.xyz * saturate(diffuse).xyz, 1);
}