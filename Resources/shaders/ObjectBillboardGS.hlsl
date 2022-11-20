#include "ObjectBillboard.hlsli"

//struct GSOutput
//{
//	float4 pos : SV_POSITION;
//};

//[maxvertexcount(1)]
//void main(
//	point VSOutput input[1] : SV_POSITION, 
//	inout PointStream< GSOutput > output
//)
//{
//	for (uint i = 0; i < 3; i++)
//	{
//		GSOutput element;
//		element.svpos = input[i].svpos;
//        element.normal = input[i].normal;
//		element.uv = input[i].uv;
//		output.Append(element);
//	}
//}

//�l�p�`�̒��_��
static const uint vnum = 4;

static const float2 uv_array[vnum] =
{
    float2(0, 1),
	float2(0, 0),
	float2(1, 1),
	float2(1, 0)
};

//�Z���^�[����̃I�t�Z�b�g
static const float4 offset_array[vnum] =
{
    float4(-0.5f, -0.5f, 0, 0),
	float4(-0.5f, +0.5f, 0, 0),
	float4(+0.5f, -0.5f, 0, 0),
	float4(+0.5f, +0.5f, 0, 0),
};
	
[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION,
	inout TriangleStream<GSOutput> output
)
{
    GSOutput element;
	//4�_����
    for (uint i = 0; i < vnum; i++)
    {
		////���S����̃I�t�Z�b�g���r���{�[�h��](���f�����W)
        float4 offset = mul(matBillboard, offset_array[i]);
		////�I�t�Z�b�g�����炷(���[���h���W)
        element.svpos = input[0].pos + offset;
		//���[���h���W�x�[�X�ł��炷
        //element.svpos = input[0].pos + offset_array[i];
		//�r���[�A�ˉe�ϊ�
        element.svpos = mul(mat, element.svpos);
        //element.uv = float2(0.5f, 0.5f);
        element.uv = uv_array[i];
        output.Append(element);
    }
	
}
