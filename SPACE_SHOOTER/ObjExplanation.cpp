//�g�p����w�b�_�[
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjExplanation.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjExplanation::Init()
{
	m_key_flag=false;
}

//�A�N�V����
void CObjExplanation::Action()
{

	//���L�[��D�L�[�������Ď��̐�����ʂɈڍs����
	if(Input ::GetVKey(VK_RIGHT)==true || Input::GetVKey('D') == true)
	{
		if(m_key_flag==true)
		{
			//�����I�u�W�F�N�g3�쐬
			CObjExplanation3* obj=new CObjExplanation3();//�����I�u�W�F�N�g2�쐬
			Objs::InsertObj(obj,OBJ_EXPLANATION3,10);

			m_key_flag = false;

			this->SetStatus(false);//����1�I�u�W�F�N�g�j��
		}
	}
	//���L�[��A�L�[�������đO�̐�����ʂɈڍs����
	else if (Input::GetVKey(VK_LEFT) == true || Input::GetVKey('A') == true)
	{
		if (m_key_flag == true)
		{
			//�����I�u�W�F�N�g2�쐬
			CObjExplanation2* obj = new CObjExplanation2();//�����I�u�W�F�N�g2�쐬
			Objs::InsertObj(obj, OBJ_EXPLANATION3, 10);

			m_key_flag = false;

			this->SetStatus(false);//����1�I�u�W�F�N�g�j��
		}
	}
	else
	{
		m_key_flag=true;
	}

	
}

//�h���[
void CObjExplanation::Draw()
{
	float key[4]={1.0f,1.0f,1.0f,1.0f};//�e�L�[
	float moji[4]={1.0f,1.0f,1.0f,1.0f};//����
	float back[4]={0.9f,0.9f,0.9f,0.9f};//�w�i

	RECT_F src;//�`�挳�̐؂���ʒu
	RECT_F dst;//�`���̕\���ʒu

//�����\��-------------------------------------

	Font::StrDraw((wchar_t*)L"2/4",950,10,30,moji);
	//���@�̐���
	Font::StrDraw((wchar_t*)L"���@��",150,150,30,moji);
	Font::StrDraw((wchar_t*)L"��ړ�",375,210,25,moji);
	Font::StrDraw((wchar_t*)L"���ړ�",375,310,25,moji);
	Font::StrDraw((wchar_t*)L"�e����",375,410,25,moji);
	Font::StrDraw((wchar_t*)L"�e��](�E��])",375,510,25,moji);

	//�E�@�̐���
	Font::StrDraw((wchar_t*)L"�E�@��",530,150,30,moji);
	Font::StrDraw((wchar_t*)L"��ړ�",750,210,25,moji);
	Font::StrDraw((wchar_t*)L"���ړ�",750,310,25,moji);
	Font::StrDraw((wchar_t*)L"�e����",750,410,25,moji);
	Font::StrDraw((wchar_t*)L"�e��](�E��])",750,510,25,moji);

	Font::StrDraw((wchar_t*)L"Next Page   : �� / D", 360, 660, 32, moji);
	Font::StrDraw((wchar_t*)L"Back Page   : �� / A", 360, 692, 32, moji);

//�����\�������----------------------------------------------------
		
	//�؂���ʒu�̐ݒ�
	RectSet(0.0f,0.0f,470.0f,270.0f,src);
	
//�@�̕\��-----------------------------------------------------
	
	//���@�̂�\��

	//�؂���ʒu
	RectSet(1.0f,0.0f,32.0f,31.0f,src);

	//�\���ʒu�̐ݒ�
	RectSet(190.0f,150.0f,220.0f,260.0f,dst);

	Draw::Draw(21,&src,&dst,key,0.0f);//�`��

	//�E�@�̂�\��
	//�؂���ʒu�̐ݒ�
	RectSet(1.0f,32.0f,64.0f,31.0f,src);

	//�\���ʒu�̐ݒ�
	RectSet(190.0f,530.0f,600.0f,260.0f,dst);

	Draw::Draw(21,&src,&dst,key,0.0f);//�`��

//�@�̕\�������-----------------------------------------------------------------------

//��������L�[�\��-------------------------------------------------------------------------------	

	//�؂���ʒu�̐ݒ�
	RectSet(0.0f,0.0f,32.0f,32.0f,src);

	//--------------------------------------------------------------------------------------------------
	
	//W�L�[�\��

	//�\���ʒu�̐ݒ�
	RectSet(190.0f,275.0f,340.0f,250.0f,dst);

	Draw::Draw(13,&src,&dst,key,0.0f);//�`��
	
	//---------------------------------------------------------------------------------------------------

	//D�L�[�̕\��

	//�\���ʒu�̐ݒ�
	RectSet(390.0f,275.0f,340.0f,450.0f,dst);
	
	Draw::Draw(14,&src,&dst,key,0.0f);//�`��

	//-----------------------------------------------------------------------------------------------------
	
	//A�L�[�̕\��
	
	//�\���ʒu�̐ݒ�
	RectSet(490.0f,275.0f,340.0f,550.0f,dst);
	
	Draw::Draw(15,&src,&dst,key,0.0f);//�`��

	//-----------------------------------------------------------------------------------------------------
	
	//S�L�[�̕\��

	//�\���ʒu�̐ݒ�
	RectSet(290.0f,275.0f,340.0f,350.0f,dst);

	Draw::Draw(16,&src,&dst,key,0.0f);//�`��

	//----------------------------------------------------------------------------------------------

	//���L�[�̕\��

	//�\���ʒu�̐ݒ�
	RectSet(190.0f,650.0f,715.0f,256.0f,dst);

	Draw::Draw(17,&src,&dst,key,0.0f);//�`��

	//-----------------------------------------------------------------------------------------------------

	//���L�[�̕\��

	//�\���ʒu�̐ݒ�
	RectSet(290.0f,650.0f,715.0f,350.0f,dst);

	Draw::Draw(18,&src,&dst,key,0.0f);//�`��

	//--------------------------------------------------------------------------------------------------------

	//���L�[�̕\��

	//�\���ʒu�̐ݒ�
	RectSet(390.0f,650.0f,715.0f,450.0f,dst);

	Draw::Draw(19,&src,&dst,key,0.0f);//�`��

	//-----------------------------------------------------------------------------------------------------------

	//���L�[�̕\��

	//�\���ʒu�̐ݒ�
	RectSet(490.0f,650.0f,715.0f,550.0f,dst);

	Draw::Draw(20,&src,&dst,key,0.0f);//�`��

	//--------------------------------------------------------------------------------------------------------
}