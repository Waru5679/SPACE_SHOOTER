#pragma once

//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjGameOver:public CObj
{
public:
	CObjGameOver(int p);
	~CObjGameOver(){};
	void Init();//�C�j�V�����C�Y
	void Action();//�A�N�V����
	void Draw();//�h���[
	void Result();//�p�^�[���ɉ����Č��ʂ̕����������֐�
	int RankingSort(int time[],char name[][6]);//�����L���O���\�[�g���ď��ʂ�Ԃ��֐�
private:
	int m_pattern;	//���s�p�^�[��
	float m_y;		//������y�ʒu
	float m_yy;		//������y�ʒu
	int count;		//���������炷���߂̃J�E���g
	int ranking;	//����̏��ʂ�ۑ�����
	bool m_cp_flag;	//CP�킩�ǂ����������t���O
};