#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameHead.h"

#define DELETE_INFO_MAX 20

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�u���b�N��������Ƃ��̏���ۑ����邽�߂̍\����
struct BlockDelete
{
	Point Pos;	//�u���b�N��������Ƃ��̏�܂��͍��ɗ���u���b�N�̈ʒu
	int Num;	//���̂Ƃ��ɏ����鐔��ۑ�
	int Rot;	//���̂Ƃ��̉�]����ۑ�
};

//�I�u�W�F�N�g:CP
class CObjCP:public CObj
{
public:
	void Init();	//������
	void Action();	//�X�V
	void Draw();	//�`��
	void ShotMove();//�ړ��A��]�A�e�̔��˂�����֐�
	void Shot();	//�e��ł֐�

	void BlockPosSave();//�u���b�N�𐶐�����\��ʒu�̕ۑ�
	void Revolution();	//�u���b�N�̉�]�����̊֐�
	
	void EndFlagON(){ m_bEnd = true; }		//�Q�[���I�u�W�F�N�g�t���O���I���ɂ���
	int ReturnMove(){ return m_MoveCheck; }	//�ړ��̈ʒu��Ԃ��֐�
	void SetOjmNum(int n){ m_OjmNum += n; }	//���ז��u���b�N�̐��������Z�b�g����֐�

	//AI�֘A�̊֐�
	void SetDeletePoint(Point Pos, int Num, int Rot);//�u���b�N�̏�������Z�b�g����֐�

private:
	//AI�֘A�̏��̏�����
	void AiInit();

	//�@�̕`��
	void AircraftDraw();

	//���ז��̐��`��
	void OjmNumDraw();

	//�Q�[�W�`��
	void GaugeDraw();

	//��̃u���b�N�`��
	void AfterBloackDraw();

	Point m_Pos;	//�ʒu
	Point m_Move;	//�ړ�
	Point m_Senter;	//2�̃u���b�N���m�̒��S�_
	Point m_Drow;	//m_senter�Ɗ�_�i���ォ�E���j�ɂȂ�_�Ƃ̍�(��Βl
	Point m_Shot[2];//�}�b�v�ɓ����Ƃ��̈ʒu�ۑ��p

	BlockDelete DeleteInfo[DELETE_INFO_MAX];	//�u���b�N��������Ƃ��̏��

	int m_Npc[4];		//�����_���L��
	int m_BulletCount;	//�ʂ̔��ˉ�
	int m_RotNum;		//�u���b�N�̉�]��(0-3�j
	int m_MoveCheck;	//�ړ��̃`�F�b�N�p
	int m_Time;			//�X�^�[�g����p
	int m_GaugeTime;	//�Q�[�W�p�^�C��
	int m_OjmNum;		//���ז��u���b�N���~�炷��
	int m_ShootTime;	////���u���̋������˂܂ł̎���
	int m_DeleteCount;//�u���b�N�������֐��̌Ăяo���񐔂��J�E���g����

	bool m_bShot;	//�e�ۂ̔��ː���p
	bool m_bRot;	//��]�̐���
	bool m_bDis;	//���ł����邩
	bool m_bUp;		//��̈ړ��`�F�b�N�p
	bool m_bDown;	//���̈ړ��`�F�b�N�p
	bool m_bEnd;	//�Q�[���I�[�o�[�̃`�F�b�N
	bool m_bMove;	//�ړ������̃t���O

	//�`��֘A
	RECT_F m_Src;				//�`�挳�̐؂���ʒu
	RECT_F m_Dst;				//�`���̕\���ʒu
	float m_fNomalColor[4];		//�ʏ�̐F
	float m_fPreBlockColor[4];	//�\���u���b�N�̐F
	float m_fFontColor[4];		//�����\���F�̐F

	
};
