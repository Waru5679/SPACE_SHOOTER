//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneVsCP.h"
#include "GameHead.h"

//�Q�[�����C���̏��������\�b�h
void CSceneVsCP::InitScene()
{
	//���y�̓ǂݍ��ݐ錾
	Audio::LoadAudio(2, (wchar_t*)L"Hit.WAV",EFFECT);	       //�u���b�N�ƃu���b�N�A�u���b�N�ƈ�ԍŏ��̐^�񒆂ł��������Ƃ��̉�
	Audio::LoadAudio(3, (wchar_t*)L"bomb.WAV",EFFECT);        //������
	Audio::LoadAudio(4, (wchar_t*)L"Ojama.WAV",EFFECT);       //���ז����ˉ�
	Audio::LoadAudio(5, (wchar_t*)L"SetOjama.WAV",EFFECT);    //���ז��ݒu��
	Audio::LoadAudio(7, (wchar_t*)L"Win.wav"   ,BACK_MUSIC);  //�������������ɗ����
	Audio::LoadAudio(8, (wchar_t*)L"Fight.wav" , BACK_MUSIC); //�퓬�~���[�W�b�N

	Audio::LoadAudio(9, (wchar_t*)L"Start1.wav" , EFFECT);     //�J�E���g�_�E��(3-1)
	Audio::LoadAudio(10, (wchar_t*)L"Start0.wav" , EFFECT);    //�X�^�[�g(start)
	
	//�퓬�~���[�W�b�N�J�n
	Audio::Start(8);

	//�{�����[���ݒ�
	float Volume2 = Audio::Volume(-0.4f,2);		//�ݒu��
	float Volume3 = Audio::Volume(-0.7f,3);		//������
	float Volume4 = Audio::Volume(1.0f,4);		//���ז����ˉ�
	float Volume5 = Audio::Volume(1.0f,5);		//���ז��ݒu��
	float Volume7 = Audio::Volume(-0.2f,7);		//������
	float Volume8 = Audio::Volume(-0.6f,8);		//�퓬BGM
	float Volume9 = Audio::Volume(-0.3f,9);		//�X�^�[�g�V�O�i��
	float Volume10 = Audio::Volume(-0.3f,10);	//�X�^�[�g�V�O�i��
	
	//�u���b�N
	Draw::LoadImage((wchar_t*)L"ColorBlue.png"	,0,TEX_SIZE_64);	//��
	Draw::LoadImage((wchar_t*)L"ColorRed.png"   ,1,TEX_SIZE_64);	//��
	Draw::LoadImage((wchar_t*)L"ColorGreen.png" ,2,TEX_SIZE_64);	//��
	Draw::LoadImage((wchar_t*)L"ColorYellow.png",3,TEX_SIZE_64);	//���F
	Draw::LoadImage((wchar_t*)L"ColorPink.png"  ,4,TEX_SIZE_64);	//�s���N
	Draw::LoadImage((wchar_t*)L"ColorPurple.png" ,5,TEX_SIZE_64);	//��
	Draw::LoadImage((wchar_t*)L"Intervention.png",6,TEX_SIZE_32);	//���ז��u���b�N

	//�w�i
	Draw::LoadImage((wchar_t*)L"background1.png",7,TEX_SIZE_512);	//�w�i
	Draw::LoadImage((wchar_t*)L"background2.png",8,TEX_SIZE_512);	//�w�i�g�L
	Draw::LoadImage((wchar_t*)L"blueback.png"	,9,TEX_SIZE_512);	//�}�b�v�̘g��

	//��l��&�����G�t�F�N�g 9
	Draw::LoadImage((wchar_t*)L"image.png",10,TEX_SIZE_512);

	//�J�E���g�_�E���p�����@���@START
	Draw::LoadImage((wchar_t*)L"3.png",11,TEX_SIZE_256);
	Draw::LoadImage((wchar_t*)L"2.png",12,TEX_SIZE_256);
	Draw::LoadImage((wchar_t*)L"1.png",13,TEX_SIZE_256);
	Draw::LoadImage((wchar_t*)L"START.png",14,TEX_SIZE_256);
	
	//�Q�[�W
	Draw::LoadImage((wchar_t*)L"gauge.png",15,TEX_SIZE_600);

	//��l���I�u�W�F�N�g�쐬
	CObjHero*obj=new CObjHero();
	Objs::InsertObj(obj,OBJ_HERO,10);

	//CP�I�u�W�F�N�g�쐬
	CObjCP*obj_cp=new CObjCP();
	Objs::InsertObj(obj_cp,OBJ_CP,10);
	
	//�w�i�I�u�W�F�N�g�쐬
	CObjBackground *obj_b=new CObjBackground();
	Objs::InsertObj(obj_b,OBJ_BACK_GROUND,1);

	//�}�b�v�I�u�W�F�N�g
	CObjMain* p=new CObjMain(true);
	Objs::InsertObj(p,OBJ_MAIN,5);
}



