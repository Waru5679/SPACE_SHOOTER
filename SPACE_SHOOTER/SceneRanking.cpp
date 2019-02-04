//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "SceneRanking.h"
#include "GameHead.h"


//�R���X�g���N�^�@�iCP�ΐ�@�I����p�j
CSceneRanking::CSceneRanking(int rank)
{
	m_rank = rank;
}

//�Q�[�����������\�b�h
void CSceneRanking::InitScene()
{
	//�����L���O�\���I�u�W�F�N�g�쐬
	CObjRanking* ranking = new CObjRanking(m_rank);
	Objs::InsertObj(ranking, OBJ_RANKING, 5);
}

//�Q�[�����s�����\�b�h
void CSceneRanking::Scene()
{
	
}