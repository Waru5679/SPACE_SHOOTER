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
#include "SceneTitle.h"
#include "GameHead.h"
#include"GameL\DrawTexture.h"
#include "GameL\Audio.h"


//�R���X�g���N�^
CSceneTitle::CSceneTitle()
{
	
}
//�f�X�g���N�^
CSceneTitle::~CSceneTitle()
{

}

//�Q�[�����C�����������\�b�h
void CSceneTitle::InitScene()
{
	//�o�͂����镶���̃O���t�B�b�N���쐬
	Font::SetStrTex((wchar_t*)L"GameStart : PushEnterKey");
	Font::SetStrTex((wchar_t*)L"�^�C�g��");
	//Font::SetStrTex(L"����");

	Draw::LoadImage((wchar_t*)L"TitleBackground.png",6,TEX_SIZE_512);//�^�C�g���w�i
	Draw::LoadImage((wchar_t*)L"Title.png",7,TEX_SIZE_512);//�^�C�g�����S
	Draw::LoadImage((wchar_t*)L"Intervention.png", 10, TEX_SIZE_32);//���ז��u���b�N
	Draw::LoadImage((wchar_t*)L"W_key.png" , 13 , TEX_SIZE_32);//W�L�[
	Draw::LoadImage((wchar_t*)L"D_key.png" , 14 , TEX_SIZE_32);//D�L�[
	Draw::LoadImage((wchar_t*)L"A_key.png" , 15 , TEX_SIZE_32);//A�L�[
	Draw::LoadImage((wchar_t*)L"S_key.png" , 16 , TEX_SIZE_32);//S�L�[
	Draw::LoadImage((wchar_t*)L"UP_key.png" , 17 , TEX_SIZE_32);//���L�[
	Draw::LoadImage((wchar_t*)L"DOWN_key.png" , 18 , TEX_SIZE_32);//���L�[
	Draw::LoadImage((wchar_t*)L"LEFT_key.png" , 19 , TEX_SIZE_32);//���L�[
	Draw::LoadImage((wchar_t*)L"RIGHT_key.png" , 20 , TEX_SIZE_32);//���L�[
	Draw::LoadImage((wchar_t*)L"image.png",21,TEX_SIZE_512);//�@�̂Ɣ����̃G�t�F�N�g
	Draw::LoadImage((wchar_t*)L"slide.png",22,TEX_SIZE_1024);//�X���C�h
	Draw::LoadImage((wchar_t*)L"gauge.png",23,TEX_SIZE_600);//�Q�[�W

	 //�^�C�������Ƃ��ז�����
	Draw::LoadImage((wchar_t*)L"time.png", 24, TEX_SIZE_512);
	Draw::LoadImage((wchar_t*)L"bomb.png", 25, TEX_SIZE_512);

	
	Audio::LoadAudio(9, (wchar_t*)L"Title.wav" , BACK_MUSIC);//�^�C�g���~���[�W�b�N
	Audio::LoadAudio(10, (wchar_t*)L"Exp.wav" , BACK_MUSIC);//������ʎ��̃~���[�W�b�N

	//�u���b�N 0~5 & 6
	Draw::LoadImage((wchar_t*)L"ColorBlue.png"  ,0,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorRed.png"   ,1,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorGreen.png" ,2,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorYellow.png",3,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorPink.png"  ,4,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorPurple.png" ,5,TEX_SIZE_64);

	//�o�b�N�~���[�W�b�N�X�^�[�g
	float Volume = Audio::VolumeMaster(-0.8f);
	Audio::Start(9);

	//�^�C�g���I�u�W�F�N�g�쐬
	CObjTitle* obj=new CObjTitle();//�^�C�g���I�u�W�F�N�g�쐬
	Objs::InsertObj(obj,OBJ_TITLE,10);//�^�C�g���I�u�W�F�N�g�쐬
}

//�Q�[�����C�����s���̃��\�b�h
void CSceneTitle::Scene()
{

}


