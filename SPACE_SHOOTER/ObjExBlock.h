#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�����p�u���b�N
class CObjExBlock:public CObj
{
	public:
		CObjExBlock(int color);//�R���X�g���N�^
		~CObjExBlock(){};//�f�X�g���N�^
		void Init();	//�C�j�V�����C�Y
		void Action();	//�A�N�V����
		void Draw();	//�`��
	private:
		//���W�֘A
		float m_vx;//�ړ���
		float m_px;//�ʒuX
		float m_py;//�ʒuY

		int m_color;//�F
};