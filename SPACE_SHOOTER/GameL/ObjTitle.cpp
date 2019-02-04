//�g�p����w�b�_�[
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjTitle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTitle::Init()
{
	m_key_flag=false;
}

//�A�N�V����
void CObjTitle::Action()
{
	//�G���^�[�L�[�������ăV�[���F�Q�[�����C���Ɉڍs����
	if(Input ::GetVKey(VK_RETURN)==true)
	{
		if(m_key_flag==true)
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplanation* obj=new CObjExplanation();//�����I�u�W�F�N�g�쐬
			Objs::InsertObj(obj,OBJ_EXPLANATION,10);//�^�C�g���I�u�W�F�N�g�쐬

			this->SetStatus(false);//�^�C�g���I�u�W�F�N�g�폜

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
	Font::StrDraw((wchar_t*)L"�^�C�g��",130,100,80,c);
	Font::StrDraw((wchar_t*)L"GameStart : PushEnterKey",200,400,32,c);
}