//�g�p����w�b�_�[
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"

#include "GameHead.h"
#include "ObjExplanation2.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjExplanation2::Init()
{
	m_key_flag=false;
}

//�A�N�V����
void CObjExplanation2::Action()
{
	//���L�[��D�L�[�������Ď��̐�����ʂɈڍs����
	if (Input::GetVKey(VK_RIGHT) == true || Input::GetVKey('D') == true)
	{
		if (m_key_flag == true)
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplanation* obj = new CObjExplanation();//�����I�u�W�F�N�g2�쐬
			Objs::InsertObj(obj, OBJ_EXPLANATION, 10);

			m_key_flag = false;

			this->SetStatus(false);//����1�I�u�W�F�N�g�j��
		}
	}
	//���L�[��A�L�[�������đO�̐�����ʂɈڍs����
	else if (Input::GetVKey(VK_LEFT) == true || Input::GetVKey('A') == true)
	{
		if (m_key_flag == true)
		{
			CObjModeChoice* obj = new CObjModeChoice();
			Objs::InsertObj(obj, OBJ_MODE_CHOICE, 10);

			m_key_flag = false;

			this->SetStatus(false);//�����I�u�W�F�N�g3�j��
		}
	}
	else
	{
		m_key_flag = true;
	}
}

//�h���[
void CObjExplanation2::Draw()
{
	float c[4]={1.0f,1.0f,1.0f,1.0f};

	RECT_F src;
	RECT_F dst;
	
	//�؂���ʒu
	RectSet(0.0f,0.0f,1024.0f,1024.0f,src);

	//�\���ʒu
	RectSet(0.0f,0.0f,1024.0f,768.0f,dst);
	
	Draw::Draw(22,&src,&dst,c,0.0f);//�`��


	Font::StrDraw((wchar_t*)L"1/4",950,10,30,c);

	Font::StrDraw((wchar_t*)L"Next Page   : �� / D", 360, 660, 32, c);
	Font::StrDraw((wchar_t*)L"Mode Select : �� / A", 360, 692, 32, c);
}