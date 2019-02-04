#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���ז��u���b�N
class CObjIntervention:public CObj
{
	public:
		CObjIntervention(float x,float y,bool lr);
		~CObjIntervention(){};
		void Init();	//�C�j�V�����C�Y
		void Action();	//�A�N�V����
		void Draw();	//�`��

		void Move();	//�ړ������̊֐�
		void Check();	//�ړ��̃`�F�b�N�p�̊֐�
	
private:
		float m_vx;
		float m_vy;

		float m_px;
		float m_py;
		int m_time;

		bool m_lr;//true���� false���E
		bool m_se;//SE����p
		bool m_Processing_flag;//�����p�̃t���O
		bool m_gameover_check;//�Q�[���I�[�o�[�̗L��������ׂ�
		bool m_stop_flag;//���g�����܂��Ă��邩�ǂ����̃t���O
		bool move_check;//�ړ��ł��邩�ǂ����̃`�F�b�N�p�t���O
};