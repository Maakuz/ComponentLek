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

float3 camPos : register(b1);


[maxvertexcount(4)]
void main(point GS_IN input[1] : SV_POSITION, inout TriangleStream<GS_OUT> output)
{
	GS_OUT element;

	float3 camToPos = input[0].pos.xyz - camPos.xyz;

	element.pos = input[0].pos;
	output.Append(element);
}