#include "Function.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"

//Rectに値をセットする関数
//引数　1～4：上下左右それぞれにセットしたい値
//引数　5	：値を入れたい場所
void RectSet(float top,float left,float right,float bottom,RECT_F &rect)
{
	rect.m_top		= top;
	rect.m_left		= left;
	rect.m_right	= right;
	rect.m_bottom	= bottom;
}

//色セット用
void ColorSet(float Color[4],float R, float G, float B, float A)
{
	Color[0] = R;
	Color[1] = G;
	Color[2] = B;
	Color[3] = A;
}
