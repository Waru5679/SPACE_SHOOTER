#pragma once

//�C���N���[�h�w�b�_
#include<math.h>
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

bool UnitVec(float* vx, float* vy);

//�̈�����ǂ������ׂ�ʒupos_(xy)��window_(xywh)�̓����O���𒲂ׂ�
bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h);


//�����ƕ����璼�p�O�p�`������Ɖ��肵���̊p�x�����߂�
float GetAtan2Angle(float w, float h);

//del�Œe�ۂ�RECT�⒅�eeffect��RECT(�A�j���[�V������RECT�j��Ԃ�
RECT_F GetBulletEffec(int* ani, int* ani_time, bool del, int timing);
