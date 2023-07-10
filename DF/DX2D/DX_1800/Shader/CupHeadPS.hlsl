Texture2D resource : register(t0);
SamplerState samp : register(s0);

cbuffer ReverseBuffer : register(b0)
{
	int isReverse;
	int paddint[3];
}

cbuffer ActionBuffer : register(b1)
{
	float2 startPos;
	float2 size;
	float2 imageSize;
	int padding[2];
};

cbuffer FilterBuffer : register(b2)
{
	int selected;
	int value1;
	int value2;
	int value3;

	float2 imageSize_;
	float2 radialCenter;
}

float4 Mosaic(float2 uv)
{
	// 0 ~ 1 * 10 .. 0.5 => 5 , 0.55 => 5
	float x = floor(uv.x * value1); // floor : 소수뒷자리 날리는 함수
	float y = floor(uv.y * value1);

	float2 temp;
	temp.x = x / value1; // 0.5
	temp.y = y / value1;

	return resource.Sample(samp, temp);
}

float4 Blur(float2 uv)
{
	float4 result = 0;

	if (value2 == 0)
		return resource.Sample(samp, uv);

	for (int i = 0; i < value2; i++)
	{
		float divX = (i + 1) / imageSize.x;
		float divY = (i + 1) / imageSize.y;

		result += resource.Sample(samp, float2(uv.x + divX, uv.y));
		result += resource.Sample(samp, float2(uv.x - divX, uv.y));
		result += resource.Sample(samp, float2(uv.x, uv.y + divY));
		result += resource.Sample(samp, float2(uv.x, uv.y - divY));
	}

	result /= 4 * value2;

	return result;
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
		float2 resultUV;
	// input.x ... 0 ~ 1
	// startPos (0,520)
	// ImageSize(1200, 1040)
	// 
	if (isReverse == 1)
		input.uv.x = 1 - input.uv.x;
	
	resultUV.x = (startPos.x) / (imageSize.x) + input.uv.x * (size.x / imageSize.x);
	resultUV.y = (startPos.y) / (imageSize.y) + input.uv.y * (size.y / imageSize.y);
	
	float4 color = resource.Sample(samp, resultUV);

	if(selected == 1)
		return Blur(resultUV);
	
	return color;
}