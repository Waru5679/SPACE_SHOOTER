#pragma once

#include "GameL\DrawTexture.h"
using namespace GameL;

// Rect_fのメンバーをセットする関数
void RectSet(float top,float left,float right,float bottom, RECT_F &rect);	

//色セット用
void ColorSet(float Color[4],float r, float g, float b, float a);
