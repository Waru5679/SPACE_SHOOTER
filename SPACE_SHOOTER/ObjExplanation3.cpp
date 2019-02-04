//�g�p����w�b�_�[
#include <time.h>
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjExplanation3.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^

//�C�j�V�����C�Y
void CObjExplanation3::Init()
{
	m_key_flag=false;

	m_gauge_time = 180;

	srand(time(NULL)); // �����_������������
	
	m_f=true;//�u���b�N�����̃t���O

	m_color = rand() % 6;
	
	
}

//�A�N�V����
void CObjExplanation3::Action()
{
	//�u���b�N�I�u�W�F�N�g�̌Ăяo��
	CObjBlock * obj_b =(CObjBlock*)Objs ::GetObj(OBJ_BLOCK);

	m_gauge_time--;

	if(m_gauge_time < 0)//0�ȉ��ɂȂ�Ȃ��悤�ɂ���
		m_gauge_time=0;

	//���L�[��D�L�[�������ă��[�h�Z���N�g�̐�����ʂɈڍs����
	if (Input::GetVKey(VK_RIGHT) == true || Input::GetVKey('D') == true)
	{
		if (m_key_flag == true)
		{
			//����4�Ɉړ�
			CObjExplanation4* obj = new CObjExplanation4();
			Objs::InsertObj(obj, OBJ_EXPLANATION4, 10);

			m_key_flag = false;

			this->SetStatus(false);//����1�I�u�W�F�N�g�j��
		}
	}
	//���L�[��A�L�[�������đO�̐�����ʂɈڍs����
	else if (Input::GetVKey(VK_LEFT) == true || Input::GetVKey('A') == true)
	{
		if (m_key_flag == true)
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplanation* obj = new CObjExplanation();//�����I�u�W�F�N�g2�쐬
			Objs::InsertObj(obj, OBJ_EXPLANATION3, 10);

			m_key_flag = false;

			this->SetStatus(false);//�����I�u�W�F�N�g3�j��
		}
	}
	else
	{
		m_key_flag = true;
	}

	if(m_gauge_time == 0)
	{
		if(m_f == true)
		{
			m_color = rand() % 6;

			//�����u���b�N�I�u�W�F�N�g�쐬
			CObjExBlock* obj = new CObjExBlock(m_color);
			Objs::InsertObj(obj, OBJ_EX_BLOCK, 20);

			m_f=false;

		}
	}

}

//�h���[
void CObjExplanation3::Draw()
{
	float c[4]={1.0f,1.0f,1.0f,1.0f};
	float c2[4]={2.5f,2.5f,2.5f,1.0f};

	RECT_F src;//�`�挳�̐؂���ʒu
	RECT_F dst;//�`���̕\���ʒu

//�����\��--------------------------------------------------------------------------------------

	//����3�J�n
	Font::StrDraw((wchar_t*)L"3/4",950,10,30,c);
	Font::StrDraw((wchar_t*)L"x0", 770, 110, 60, c);

	Font::StrDraw((wchar_t*)L"�@�E���ז��u���b�N",100,160,40,c);
	Font::StrDraw((wchar_t*)L"    �������Ƃ̂ł��Ȃ��u���b�N�B", 150, 210 , 28, c);
	Font::StrDraw((wchar_t*)L"    ���̐����͎��ɍ~���Ă��邨�ז��̐���", 150, 240, 28, c);
	Font::StrDraw((wchar_t*)L"    �\�����Ă��܂��B", 150, 270, 28, c);

	//�Q�[�W�̐���
	Font::StrDraw((wchar_t*)L"�@�E�Q�[�W",100,380,40,c);
	Font::StrDraw((wchar_t*)L"    �ԐF�̃Q�[�W���Ȃ��Ȃ��",150,440,28,c);
	Font::StrDraw((wchar_t*)L"    �e������ɔ��˂����B",150,470,28,c);

	////��������̐���
	//Font::StrDraw(L"�@�E���s�ɂ���", 100, 430, 40, c);
	//Font::StrDraw(L"�@  1P�E2P�̒[�̃}�X�����܂�A�����Ȃ���ԂɂȂ��", 150, 490, 28, c);
	//Font::StrDraw(L"�@�@�Q�[���I���B����̒[�̃}�X�Ƀu���b�N�𖄂߂��", 150, 520, 28, c);
	//Font::StrDraw(L"�@�@�����ƂȂ�" , 150 , 550 , 28 , c);

	Font::StrDraw((wchar_t*)L"Next Page   : �� / D", 360, 660, 32, c);
	Font::StrDraw((wchar_t*)L"Back Page   : �� / A", 360, 692, 32, c);

//�����\�������--------------------------------------------------------------------------------------------

//���ז��u���b�N��\��---------------------------------------

	//�؂���ʒu�̐ݒ�
	RectSet(0.0f,0.0f,32.0f,32.0f,src);

	//�\���ʒu�̐ݒ�
	RectSet(110.0f,700.0f,770.0f,170.0f,dst);

	Draw::Draw(10, &src, &dst, c2, 0.0f);//�`��



//���ז��u���b�N��\�������------------------------------------------

//�Q�[�W�\��------------------------------------------------------

	//�Q�[�W�p�w�i----------------------

	//�؂���ʒu �D�F
	RectSet(0.0f,401.0f,402.0f,99.0f,src);
	//�`��ʒu
	RectSet(395.0f,695.0f,885.0f,425.0f,dst);
	//�`�悷��
	Draw::Draw(23,&src,&dst,c,0.0f);

	//---------------------------

	//�؂���ʒu ���F
	RectSet(0.0f,100.0f,101.0f,99.0f,src);
	//�`��ʒu
	RectSet(400.0f,700.0f,880.0f,420.0f,dst);
	//�`�悷��
	Draw::Draw(23,&src,&dst,c,0.0f);

	//�w�i�I�����----------------------

	//�Q�[�W�{��------------------

	//�؂���ʒu
	RectSet(0.0f,1.0f,2.0f,99.0f,src);

	//�\���ʒu
	RectSet(400.0f,700.0f,700.0f+m_gauge_time,420.0f,dst);

	Draw::Draw(23,&src,&dst,c,0.0f);//�`��

//�Q�[�W�\�������--------------------------------------------------------

//�@�̂̕\��---------------------------------------------------
	
	//�؂���ʒu�̐ݒ�
	RectSet(1.0f,1.0f,32.0f,31.0f,src);

	//�`��ʒu
	RectSet(460.0f,640.0f,690.0f,510.0f,dst);
	
	Draw::Draw(21,&src,&dst,c,0.0f);//�`��

//�@�̕\�������------------------------------------------------------------
}