#include "Function.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"

//Rect�ɒl���Z�b�g����֐�
//�����@1�`4�F�㉺���E���ꂼ��ɃZ�b�g�������l
//�����@5	�F�l����ꂽ���ꏊ
void RectSet(float top,float left,float right,float bottom,RECT_F &rect)
{
	rect.m_top		= top;
	rect.m_left		= left;
	rect.m_right	= right;
	rect.m_bottom	= bottom;
}

//�F�Z�b�g�p
void ColorSet(float Color[4],float R, float G, float B, float A)
{
	Color[0] = R;
	Color[1] = G;
	Color[2] = B;
	Color[3] = A;
}
