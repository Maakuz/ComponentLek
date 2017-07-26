struct Particle
{
    float3 pos;
    float3 velocity;
    float3 color;
    float time;
};

AppendStructuredBuffer<Particle> NewState : register(u0);
ConsumeStructuredBuffer<Particle> CurrentState : register(u1);

cbuffer ParticleCount : register(b0)
{
    uint nrOfParticles;
};

cbuffer Parameters : register(b1)
{
    float deltaTime;
};



[numthreads(512, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    uint id = DTid.x + DTid.y * 512 + DTid.z * 512 * 512;

	if (id < nrOfParticles)
    {
        Particle p = CurrentState.Consume();

        p.pos.xyz += p.velocity * deltaTime;

        NewState.Append(p);

		//TODO: TA BORT OM GAMLA
    }	
}