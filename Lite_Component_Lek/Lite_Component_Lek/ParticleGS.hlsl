struct GS_IN
{
    float4 pos : POSITION;
	float3 color : COLOR;
};

struct GS_OUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
};

cbuffer VP : register(b0)
{
	matrix VP;
};

float3 camPos : register(b1);


[maxvertexcount(4)]
void main(point GS_IN input[1] : SV_POSITION, inout TriangleStream<GS_OUT> output)
{
	float3 camToPos = input[0].pos.xyz - camPos.xyz;
    float3 right = normalize(cross(camToPos, float3(0, 1, 0))) * 0.02f;
    float3 up = normalize(cross(camToPos, right)) * 0.02f;
    float4 pos;

    GS_OUT element;
    pos = float4(input[0].pos.xyz - up - right, 1);
    element.pos = mul(pos, VP);
    element.color = input[0].color;
	output.Append(element);

    pos = float4(input[0].pos.xyz + up - right, 1);
    element.pos = mul(pos, VP);
    element.color = input[0].color;
    output.Append(element);

    pos = float4(input[0].pos.xyz - up + right, 1);
    element.pos = mul(pos, VP);
    element.color = input[0].color;
    output.Append(element);

    pos = float4(input[0].pos.xyz + up + right, 1);
    element.pos = mul(pos, VP);
    element.color = input[0].color;
    output.Append(element);
}