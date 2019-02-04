#pragma once

//インクルードヘッダ
#include<math.h>
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
//使用するネームスペース
using namespace GameL;

bool UnitVec(float* vx, float* vy);

//領域内かどうか調べる位置pos_(xy)がwindow_(xywh)の内か外かを調べる
bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h);


//高さと幅から直角三角形があると仮定しその角度を求める
float GetAtan2Angle(float w, float h);

//delで弾丸のRECTや着弾effectのRECT(アニメーションのRECT）を返す
RECT_F GetBulletEffec(int* ani, int* ani_time, bool del, int timing);
