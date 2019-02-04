#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g:�e��
class CObjBullet:public CObj
{
public:
	CObjBullet(float x,float y,bool s,int n);//�R���X�g���N�^
	~CObjBullet(){};
	void Init();//�C�j�V�����C�Y
	void Action();//�A�N�V����
	void Draw();//�h���[

	float GetX(){return m_px;}
	float GetY(){return m_py;}

void  BlockHit(
	float *x,bool* left,bool* right,float* vx,int* bt
	);


private:
	float m_px;//�ʒu
	float m_py;
	float m_x;//�e�ۂ�x�����̈ʒu�p�ϐ�
	float m_y;//�e�ۂ�y�����̈ʒu�p�ϐ�
	float m_vx;//�e�ۂ̂������̑��x�p�ϐ�
	int m_ani;//���e�A�j���[�V�����p
	int m_ani_time;//���e�A�j���[�V�����Ԋu�^�C��
	bool m_del;//�폜�`�F�b�N
	RECT_F m_eff;//���e�G�t�F�N�g�`��p
	
	bool m_check;//�ړ������邩�ǂ����̔���p
	bool m_s;//���E�ǂ��瑤�̋@�̂����ʗp�@true �E�Ffalse ��
	int npc;
};
