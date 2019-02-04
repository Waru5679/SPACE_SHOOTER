//�r�s�k�f�o�b�O�@�\���n�e�e�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "SceneGameOver.h"
#include "GameHead.h"
#include"GameL\DrawTexture.h"
#include "GameL\Audio.h"


//�R���X�g���N�^
CSceneGameOver::CSceneGameOver(int p)
{
	m_pattern=p;
}

//�f�X�g���N�^
CSceneGameOver::~CSceneGameOver()
{

}

//�Q�[�����C�����������\�b�h
void CSceneGameOver::InitScene()
{

	//�o�͂����镶���̃O���t�B�b�N���쐬
	Font::SetStrTex((wchar_t*)L"�PP�@WIN");
	Font::SetStrTex((wchar_t*)L"�QP�@WIN");
	Font::SetStrTex((wchar_t*)L"DROW");
	//���y���̓ǂݍ���


	//�o�b�N�~���[�W�b�N�X�^�[�g
	

	//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
	CObjGameOver* obj=new CObjGameOver(m_pattern);//�^�C�g���I�u�W�F�N�g�쐬
	Objs::InsertObj(obj,OBJ_GAME_OVER,10);//�^�C�g���I�u�W�F�N�g�쐬
}

//�Q�[�����C�����s���̃��\�b�h
void CSceneGameOver::Scene()
{

}


