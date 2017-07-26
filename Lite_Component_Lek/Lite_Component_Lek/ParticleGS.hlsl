struct GS_IN
{
	float4 pos : SV_POSITION;
	float3 color : COLOR;
};

struct GS_OUT
{
	float4 pos : SV_POSITION;
};

cbuffer VP : register(b0)
{
	matrix VP;
};

float4 camPos : register(b1);


[maxvertexcount(4)]
void main(
	point GS_IN input[1] : SV_POSITION, 
	inout TriangleStream<GS_OUT> output
)
{
	for (uint i = 0; i < 3; i++)
	{
		GSOutput element;
		element.pos = input[i];
		output.Append(element);
	}
}