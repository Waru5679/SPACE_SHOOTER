#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�u���b�N
class CObjBlock:public CObj
{
	public:
		CObjBlock(float x,float y,int color,bool lr,bool sk);//�R���X�g���N�^
		~CObjBlock(){};//�f�X�g���N�^
		void Init();	//�C�j�V�����C�Y
		void Action();	//�A�N�V����
		void Draw();	//�`��

		void Move();//�ړ�

		//�u���b�N��~���̏����֘A
		void Disappear();//�u���b�N���Ƃ܂����Ƃ��̏���������֐�
		void Left_Dis();//�u���b�N���Ƃ܂����Ƃ��̍���
		void Right_Dis();//�u���b�N���Ƃ܂����Ƃ��̉E��
		
		//�`�F�b�N�֘A
		bool CheckWH(int n,int staticnum );//�u���b�N�̌����𒲂ׂĕԂ��֐�
		void Check();//�ړ��ł��邩�̃`�F�b�N
		bool MoveCheck(int x,int y);//�ړ���̃`�F�b�N�֐�
		
		void DeleteAnimetion();//���Ł��A�j���[�V�����̏���������֐�
	private:
		//���W�֘A
		float m_vx;//�ړ���
		float m_px;//�ʒuX
		float m_py;//�ʒuY

		//���g�̏�Ԃ̊Ǘ��֘A
		bool m_stop_flag;//�u���b�N�������Ă邩�Ƃ܂��Ă��邩�̊Ǘ�

		int m_color;//�F
		int m_time;//���Ԃ̊Ǘ��p
		bool m_lr;//�ǂ��瑤����ł��ꂽ�u���b�N���̊Ǘ��@true�F�� false�F�E
		bool m_skip;//true�̂Ƃ��݈̂ړ����ɋ󔒂����鏈�����΂�
		bool m_Processing_flag;//�����̎��s�ς݂��̊Ǘ��@true�F�ρ@false�F��
		
		//�u���b�N�̏����p
		int m_delete_check[2];//�폜���ۑ�

		bool m_se;//SE����p
		bool m_gemeover_check;//�Q�[���I�[�o�[�I�u�W�F�N�g�̗L���𒲂ׂ�
		
		//�����Ə��Ŋ֘A
		int    m_ani;		//���j�A�j���[�V�����p
		int	   m_ani_time;	//���j�A�j���[�V�����Ԋu
		bool   m_del;		//�폜�`�F�b�N
		RECT_F m_eff;		//�폜�G�t�F�N�g�`��p

		bool move_check;//�ŏI�I�Ȉړ��ł��邩�̔���p
};