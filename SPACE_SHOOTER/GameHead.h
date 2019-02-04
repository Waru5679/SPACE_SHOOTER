#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_HERO,
	OBJ_BLOCK,
	OBJ_HERO_R,
	OBJ_BULLET,
	OBJ_BACK_GROUND,
	OBJ_TITLE,
	OBJ_EXPLANATION,
	OBJ_MAIN,
	OBJ_INTERVENTION,
	OBJ_EXPLANATION2,
	OBJ_GAME_OVER,
	OBJ_EXPLANATION3,
	OBJ_EX_BLOCK,
	OBJ_MODE_CHOICE,
	OBJ_CP,
	OBJ_EXPLANATION4,
	OBJ_NAME_INPUT,
	OBJ_RANKING,
};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
};
//------------------------------------------------

//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	char mRankingNameData[11][6];	//���O�f�[�^
	int mRankingTimeData[11];		//�^�C���f�[�^
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E�񋓁E�֐�--

//�E�B���h�E�T�C�Y
#define WINDOW_SIZE_W	(1024)
#define WINDOW_SIZE_H	(768)

//�u���b�N�T�C�Y
#define BLOCK_SIZE (46)

//�����L���O�֘A�̏����l
#define SET_NAME	"+++++"
#define SET_TIME	(9999)

//�Q�[���N���A��̖��O�����͂̏�Ԃɉ��ŃZ�b�g����
#define NO_NAME		"-----"

//���ԓ_�̈ʒu�Ǘ��p
struct Point 
{
	float x;
	float y;
};

//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------
#include "ObjTitle.h"
#include "ObjExplanation.h"
#include "CObjBlock.h"
#include "CObjHero.h"
#include "CobjHero_R.h"
#include "ObjBackground.h"
#include "ObjMain.h"
#include "CObjIntervention.h"
#include "ObjExplanation2.h"
#include "ObjGameOver.h"
#include "ObjExplanation3.h"
#include "ObjExBlock.h"
#include "Function.h"
#include "ObjModeChoice.h"
#include "ObjCP.h"
#include "ObjNameInput.h"
#include "ObjExplanation4.h"
#include "ObjRanking.h"
//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneVsCP.h"
#include "SceneNameInput.h"
#include "SceneRanking.h"
//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START  CSceneTitle
//-----------------------------------------------