struct Particle
{
    float3 pos;
    float3 velocity;
    float3 color;
    float time;
};

StructuredBuffer<Particle> SimulationState;

struct VS_OUT
{
    float4 pos : POSITION;
    float3 color : COLOR;
};

VS_OUT main(uint vertexID : SV_VertexID)
{
    VS_OUT output;

    output.pos.xyz = float4(SimulationState[vertexID].pos.xyz, 1);
    output.color = SimulationState[vertexID].color;
	return output;
}