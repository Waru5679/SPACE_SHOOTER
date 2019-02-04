#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g:��l��
class CObjHero:public CObj
{
public:
	CObjHero(){};//�R���X�g���N�^
	~CObjHero(){};//�f�X�g���N�^
	void Init();//�C�j�V�����C�Y
	void Action();//�A�N�V����
	void Draw();//�h���[

	void Shot();		//�e��ł֐�
	void Shot_move();	//�ړ��Ɖ�]�A�e��������������֐�

	void EndFlag_ON(){m_end_flag=true;}//�Q�[���I�u�W�F�N�g�t���O���I���ɂ���
	
	void Block_Pos_Save();//�u���b�N�𐶐�����\��ʒu�̕ۑ�
	
	void Revolution();//�u���b�N�̉�]����������֐�

	int ReturnMove(){return m_move;}//�ړ��̈ʒu��Ԃ��֐�
	void SetOjmNum(int n){ ojm_num +=n ;}//���ז��u���b�N�̐��������Z�b�g����֐�

private:
	float m_x;//��l���̂������ړ��p�ϐ�
	float m_y;//��l���̂������ړ��p�ϐ�
		
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

	int m_move;//�ړ��̃`�F�b�N�p
	bool m_down;//���ړ��̊Ǘ�
	bool m_up;//��ړ��̊Ǘ�

	int m_count_time;//�X�^�[�g����p
	bool m_end_flag;//�Q�[���I�[�o�[�I�u�W�F�N�g�̗L���`�F�b�N
	float m_shoot_count;//���u���̋������˂܂ł̎���

	int m_gauge_time;//�Q�[�W�p�^�C��
	int ojm_num;//���ז��u���b�N���~�炷��

	//�f�o�b�O�p
	bool m_f2;//���ז��u���b�N�̃e�X�g�p
	
	bool m_f;//�����Ă�u���b�N�̗L���ۑ��p
	bool m_push_f;//����������̑j�~�p�̃t���O

	RECT_F src;//�`�挳�̐؂���ʒu
	RECT_F dst;//�`���̕\���ʒu


};
