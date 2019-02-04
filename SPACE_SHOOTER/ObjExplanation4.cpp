//�g�p����w�b�_�[
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include"ObjExplanation4.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjExplanation4::Init()
{
	m_key_flag = false;

}

//�A�N�V����
void CObjExplanation4::Action()
{
	//����D�L�[�������ƃ��[�h�Z���N�g�ֈڍs
	if (Input::GetVKey(VK_RIGHT) == true || Input::GetVKey('D') == true)
	{
		if (m_key_flag == true)
		{
			CObjModeChoice* obj = new CObjModeChoice();
			Objs::InsertObj(obj, OBJ_MODE_CHOICE, 10);

			m_key_flag = false;

			this->SetStatus(false);

		}
	}
	//����A�L�[�������Ɛ���3�Ɉڍs����
	else if (Input::GetVKey(VK_LEFT) == true || Input::GetVKey('A') == true)
	{
		if (m_key_flag == true)
		{
			CObjExplanation3* obj = new CObjExplanation3();
			Objs::InsertObj(obj,OBJ_EXPLANATION3, 10);

			m_key_flag = false;

			this->SetStatus(false);
		}
	}

	else
	{
		m_key_flag = true;
	}
}

//�h���[
void CObjExplanation4::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float c2[4] = { 1.0f,1.0f,1.0f,2.0f };
	float moji[4] = { 1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//�`�挳�̐؂���ʒu
	RECT_F dst;//�`���̕\���ʒu

//-----------�����\��-----------------------------
	Font::StrDraw((wchar_t*)L"4/4", 950, 10, 30, moji);

	//�^�C���\��
	Font::StrDraw((wchar_t*)L"00:41", 100, 210, 50, moji);

	//�^�C���̐�����
	Font::StrDraw((wchar_t*)L"��^�C���̐���",270,120,40,moji);

	Font::StrDraw((wchar_t*)L"�^�C���͑ΐ�J�n���猈������܂ł̎��Ԃł��B", 280, 190, 30, moji);
	Font::StrDraw((wchar_t*)L"�^�C���̑������10�l�������L���O��", 280, 240, 30, moji);
	Font::StrDraw((wchar_t*)L"�\����L�^����܂��B", 280, 290, 30, moji);

	//Font::StrDraw(L"����ז��u���b�N�̐���", 270, 300, 40, c);
	//Font::StrDraw(L"���ז��u���b�N���Ԃɋ��ށA����", 280, 370, 30, c);
	//Font::StrDraw(L"���ז���[�ŋ���ł�", 280, 420, 30, c);
	//Font::StrDraw(L"�������Ƃ͂ł��Ȃ��B", 280, 470, 30, c);


	////���ז��̐���
	//Font::StrDraw(L"x0",130,550,80,moji);

	//Font::StrDraw(L"����ז��u���b�N�̐���2",270,540,40,moji);
	//Font::StrDraw(L"���ɍ~���Ă��邨�ז��̐���\�����Ă��܂��B", 280, 590, 30, moji);

	//��������̐���
	Font::StrDraw((wchar_t*)L"����s�ɂ���", 270, 390, 40, c);
	Font::StrDraw((wchar_t*)L"����̒[�̃}�X�����܂�A��莞�Ԃ��o�߂����", 280, 460, 28, c);
	Font::StrDraw((wchar_t*)L"�����ƂȂ�B", 280, 510, 28, c);


	Font::StrDraw((wchar_t*)L"Mode Select : �� / D", 360, 660, 32, c);
	Font::StrDraw((wchar_t*)L"Back Page   : �� / A", 360, 692, 32, c);


//-----------�G�̕\��-----------------------------
	


}