#pragma once

//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F����
class CObjExplanation3:public CObj
{
public:
	CObjExplanation3(){};
	~CObjExplanation3(){};
	void Init();//�C�j�V�����C�Y
	void Action();//�A�N�V����
	void Draw();//�h���[

	void Updata(){ m_gauge_time = 180; m_f=true;}//�Q�[�W�^�C�����X�V����֐�

private:
	float m_x;
	float m_y;
	bool m_key_flag;//�L�[�t���O

	float m_gauge_time;//�Q�[�W�p�^�C��
	bool m_f;//�u���b�N�����̃t���O
	bool flag;

	int m_color;//�F�Ǘ��p
};