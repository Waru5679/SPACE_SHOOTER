#pragma once

//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[��:�l�[������
class CSceneNameInput :public CScene
{
public:
	CSceneNameInput() {	m_rank = 0;	}//debag
	CSceneNameInput(int rank);
	~CSceneNameInput() {};
	void InitScene();//�Q�[�����C���̏������̃��\�b�h
	void Scene();//�Q�[�����C���̎��s���̃��\�b�h
private:
	int m_rank;	//���ʂ�ۑ�
};
