//�g�p����w�b�_�[
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include"GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "ObjTitle.h"
#include"ObjBackground.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjTitle::Init()
{
	m_key_flag=false;
	m_time = 0;

	//�Q�[�������s���Ĉ��̂�
	static bool init_point = false;
	if (init_point == false)
	{
		//�����L���O���̏�����
		for (int i = 0; i < 11; i++)
		{
			((UserData*)Save::GetData())->mRankingTimeData[i] = SET_TIME;				//�^�C��
			strcpy_s(((UserData*)Save::GetData())->mRankingNameData[i], SET_NAME);		//���O			
	
			//�f�o�b�O�p---------------------------------------
			wchar_t str[256];
			swprintf_s(str, L"mRankingTimeData[i]:%d", ((UserData*)Save::GetData())->mRankingTimeData[i]);
			OutputDebugStringW(str);
			//--------------------------------------------------------
		}

		Save::Open();//�����L���O���̃��[�h
		
		for (int i = 0; i < 11; i++)
		{
			//��񂪑���Ȃ��ꍇ
			if (((UserData*)Save::GetData())->mRankingTimeData[i] <= 0)
			{
				((UserData*)Save::GetData())->mRankingTimeData[i] = SET_TIME;			//�^�C��
				strcpy_s(((UserData*)Save::GetData())->mRankingNameData[i], SET_NAME);	//���O
			}
		}

		((UserData*)Save::GetData())->mRankingTimeData[10] = SET_TIME; //���[�h��11�ʂ̂ݏ�����

		//�f�o�b�O�p--------------------------------------
		int i = 0;
		while (i < 11)
		{
			wchar_t str[256];
			swprintf_s(str, L"���[�h��[%d]:%d",i, ((UserData*)Save::GetData())->mRankingTimeData[i]);
			OutputDebugStringW(str);
			i++;
		}
		//�f�o�b�O�p---------------------------------------

		init_point = true;
	}

}

//�A�N�V����
void CObjTitle::Action()
{
	//W�L�[�������Đ����ɂɈڍs����
	if(Input ::GetVKey(VK_RETURN)==true)
	{
		if(m_key_flag==true)
		{
			//���[�h�I����ʈړ�
			CObjModeChoice* obj=new CObjModeChoice();//�����I�u�W�F�N�g�쐬
			Objs::InsertObj(obj,OBJ_MODE_CHOICE,10);//�^�C�g���I�u�W�F�N�g�쐬

			this->SetStatus(false);//�^�C�g���I�u�W�F�N�g�폜

			//�^�C�g�����X�g�b�v
			Audio::Stop(9);
			//�������̃~���[�W�b�N�J�n
			Audio::Start(10);
			
			m_key_flag=false;
		}
	}
	else
	{
		m_key_flag=true;
	}

}

//�h���[
void CObjTitle::Draw()
{
	float c[4]={1.0f,1.0f,1.0f,1.0f};
	RECT_F src;//�`�挳�̐؂���ʒu
	RECT_F dst;//�`���̕\���ʒu

//�w�i�̕`��-------------------------------------------------

	//�؂���ʒu�̐ݒ�
	RectSet(0.0f,0.0f,512.0f,512.0f,src);

	//�w�i�̕\���ʒu�̐ݒ�
	RectSet(0.0f,0.0f,WINDOW_SIZE_W,WINDOW_SIZE_H,dst);

	//�`��
	Draw::Draw(6,&src,&dst,c,0.0f);

//�w�i�̕`�您���------------------------------------------------------------

//�^�C�g�����S�`��-----------------------------------

	//�؂���ʒu�̐ݒ�
	RectSet(0.0f,0.0f,512.0f,512.0f,src);

	//�w�i�̕\���ʒu�̐ݒ�
	RectSet(150.0f,200.0f,812.0f,362.0f,dst);

	Draw::Draw(7,&src,&dst,c,0.0f);//�`��

//�^�C�g�����S�����--------------------------------

//�����\��-------------------------------------------
	m_time++;

	if (m_time >= 0 && m_time < 40)
	{
		Font::StrDraw((wchar_t*)L"PushEnterKey", 340, 540, 60, c);
	}
	else if (m_time >= 80)
	{
		m_time = 0;
	}

}