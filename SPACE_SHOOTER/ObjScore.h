#pragma once 

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�}�b�v
class CObjScore:public CObj
{
public:
	CObjScore(){};
	~CObjScore();

	void ScorePlus(bool LorR,int num );//�X�R�A�ǉ��֐�
	void Init();//�C�j�V�����C�Y
	void Action();//�A�N�V����
	void Draw();//�h���[
private:
	int m_score_L;//���̃v���C���[�̃X�R�A
	int m_score_R;//�E�̃v���C���[�̃X�R�A
	int m_high_score;
};
