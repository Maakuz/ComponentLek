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
    float4 dir[10];
    float4 color[10];
}

cbuffer pointLights : register(b1)
{
    int nrOfPointLights;
    float3 positions[30];
    float radiuses[30];
    
}

float4 main(VS_OUT input) : SV_TARGET
{
    float3 diffuse = 0;

    for (int i = 0; i < min(nrOfLights, 10); i++)
    {
        diffuse += saturate(dot(-dir[i].xyz, input.normal.xyz) * color[i].xyz);
    }

    for (int i = 0; i < min(nrOfPointLights, 30); i++)
    {
        float3 posToLight = positions[i].xyz - input.wPos.xyz;
        //float attenuation = saturate((1.f / (0.01 * max(1, pow(length(posToLight.xyz), 2)))));
        //float attenuation = pow(1.f / (length(posToLight / radiuses[i]) + 1), 2);
        float attenuation = saturate((radiuses[i] - length(posToLight.xyz)) / (radiuses[i] * 0.5f));
        diffuse += saturate(dot(normalize(posToLight), input.normal.xyz) * attenuation);
    }
        
        return float4(input.color.xyz * saturate(diffuse).xyz, 1);
}