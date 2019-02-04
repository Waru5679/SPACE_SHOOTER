#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameHead.h"

#define D_POINT_MAX 20

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g:CP
class CObjCP:public CObj
{
public:
	CObjCP(){};
	~CObjCP(){};
	void Init();//�C�j�V�����C�Y
	void Action();//�A�N�V����
	void Draw();//�h���[
	void Shot_move();//�ړ��A��]�A�e�̔��˂�����֐�
	
	void EndFlag_ON(){m_end_flag=true;}//�Q�[���I�u�W�F�N�g�t���O���I���ɂ���
	
	void Block_Pos_Save();//�u���b�N�𐶐�����\��ʒu�̕ۑ�
	void Shot();//�e��ł֐�
	void Revolution();//�u���b�N�̉�]�����̊֐�

	int ReturnMove(){return m_move;}//�ړ��̈ʒu��Ԃ��֐�
	void SetOjmNum(int n){ ojm_num += n; }//���ז��u���b�N�̐��������Z�b�g����֐�

	//AI�֘A�̊֐�
	void SetDeletePoint(Point d,int n,int rad);//�u���b�N�̏�������Z�b�g����֐�

private:
	float m_x;//��l���̂������ړ��p�ϐ�
	float m_y;//��l���̂������ړ��p�ϐ�
	bool m_f;//�e�ۂ̔��ː���p
	float m_vx;//��l���@�̂������ړ��x�N�g���p�ϐ�
	float m_vy;//��l���@�̂������ړ��x�N�g���p�ϐ�
	int m_npc[4];//�����_���L��
	int m_bullet_count;//�ʂ̔��ˉ�
	int m_r;//�ʂ̉�]��(0-3�j
	bool m_rf;//��]�̐���
	Point m_senter;//�ҋ@���̃u���b�N���m�̒��S�_
	Point m_drow;//m_senter�Ɗ�_�i���ォ�E���j�ɂȂ�_�Ƃ̍�(��Βl

	int m_shot_x[2];//�}�b�v�ɓ����x�ʒu�̕ۑ��p
	int m_shot_y[2];//�}�b�v�ɓ����y�ʒu�̕ۑ��p

	bool m_pf;//���ł̏��������邩�ǂ����𒲂ׂ�t���O�i�j
	int m_move;//�ړ��̃`�F�b�N�p

	bool m_up;//��̈ړ��`�F�b�N�p
	bool m_down;//���̈ړ��`�F�b�N�p

	int m_count_time;//�X�^�[�g����p
	bool m_end_flag;//�Q�[���I�[�o�[�I�u�W�F�N�g�̗L���`�F�b�N

	float m_shoot_count;//���u���̋������˂܂ł̎���

	int m_gauge_time;//�Q�[�W�p�^�C��
		
	int ojm_num; //���ז��u���b�N���~�炷��

	bool m_move_f;//�ړ������̃t���O
	
	//�u���b�N��������Ƃ��̏���ۑ����邽�߂̍\����------
	struct BlockDeleteCheck
	{
		Point Delete;//�u���b�N��������Ƃ��̏�܂��͍��ɗ���u���b�N�̈ʒu
		int num;//���̂Ƃ��ɏ����鐔��ۑ�
		int rad;//���̂Ƃ��̉�]����ۑ�
	};
	//------------------------------------------------------
	
	BlockDeleteCheck D_Point[D_POINT_MAX];//�u���b�N��������Ƃ��̏���ۑ����邽�߂̍\����

	int d_count;//D_point�̌Ăяo���񐔂��J�E���g����
	int m_shoot_time;	//���܂ł̎���(3�b�҂��Č���)
};
