#pragma once

//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjRanking :public CObj
{
public:
	CObjRanking(int rank);
	~CObjRanking() {};
	void Init();//�C�j�V�����C�Y
	void Action();//�A�N�V����
	void Draw();//�h���[
private:
	int	 m_rank;	//�����L���O�̏���
	bool m_key_flag;//�L�[�t���O
	bool time_set_flag[11];//�^�C���Z�b�g�t���O
						  //�����l�������Ă邩�ǂ������ׂ�p
};