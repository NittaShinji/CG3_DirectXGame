#include "Object.hlsli"

VSOutput main(float4 pos : POSITION)
{
    VSOutput output; // �s�N�Z���V�F�[�_�[�ɓn���l
    //output.svpos = mul(mat, pos);
    //output.normal = normal;
    //output.uv = uv;
    
    output.pos = pos;
    return output;
}