#pragma once

//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�����L���O
class CSceneRanking : public CScene
{
public:
	CSceneRanking() { m_rank = -1; };
	CSceneRanking(int rank);
	~CSceneRanking() {};
	void InitScene();//���������\�b�h
	void Scene();//���s�����\�b�h
private:
	int m_rank;	//�����L���O����
};