struct Particle
{
    float3 pos;
    float3 velocity;
    float3 color;
    float time;
};

AppendStructuredBuffer<Particle> NewState : register(u0);

cbuffer Parameters : register(b1)
{
    float3 emitterLocation;
};

[numthreads(8, 1, 1)]
void main( uint3 GTid : SV_GroupThreadID )
{
    Particle p;

    p.pos.xyz = emitterLocation.xyz;
    p.velocity = float3(0, 0.03f, 0);
    p.time = 0.0f;
    p.color = float3(1, 0, 0);

    NewState.Append(p);

}