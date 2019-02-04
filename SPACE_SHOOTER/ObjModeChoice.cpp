//�g�p����w�b�_�[
#include <time.h>
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjModeChoice.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjModeChoice::Init()
{
	m_key_flag = false;
	select = 1;

	//���[�h�Z���N�g��ʂɈړ���11�ʂ̂ݏ�����
	((UserData*)Save::GetData())->mRankingTimeData[10] = SET_TIME;

}

//�A�N�V����
void CObjModeChoice::Action()
{
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if(m_key_flag == true)
		{
			//�������I�����ꂽ�Ȃ�Ȃ�
			if(select == 1)
			{
				//�����I�u�W�F�N�g1�쐬
				CObjExplanation2* obj=new CObjExplanation2();//�����I�u�W�F�N�g2�쐬
				Objs::InsertObj(obj,OBJ_EXPLANATION2,10);

				this->SetStatus(false);
				m_key_flag = false;

			}
			//COM�ΐ킪�I�����ꂽ�Ȃ�
			if(select == 2)
			{
				//COM�ΐ탁�C���ڍs
				Scene::SetScene(new CSceneVsCP());
				m_key_flag = false;
			}
			//�ΐ�(�I�t���C��)���I�����ꂽ�Ȃ�
			if(select == 3)
			{
				//�ΐ�(�I�t���C��)�Ɉڍs
				Scene::SetScene(new CSceneMain());
				m_key_flag = false;
			}
			//�����L���O���I�����ꂽ�Ȃ�
			if(select == 4)
			{
				//�����L���O�ֈڍs
				Scene::SetScene(new CSceneRanking(99));

				m_key_flag = false;
			}
		}
	}

	else
	{
		m_key_flag = true;;
	}

	
	//���L�[����D�L�[�������Ƒΐ탂�[�h(�I�t���C��)�E�ΐ탂�[�h(�I�����C��)�Ɉړ�
	if (Input::GetVKey('D') == true || Input::GetVKey(VK_RIGHT) == true)
	{
		//������ʂ��I������Ă���Ƃ�
		if (select == 1)
		{
			//COM�ΐ�Ɉړ�
			select += 1;
		}
		//�ΐ�(�I�t���C��)���I������Ă���Ƃ�
		if (select == 3)
		{
			//�ΐ�(�I�����C��)�Ɉړ�
			select += 1;
		}
			
	}

	//���L�[���͍���������COM�ΐ탂�[�h�E������ʂɈړ�
	if(Input::GetVKey('A') == true || Input::GetVKey(VK_LEFT) == true)
	{
		//COM�ΐ킪�I������Ă���Ƃ�
		if(select == 2)
		{
			//�����Ɉړ�
			select -= 1;
		}
		//�ΐ�(�I�����C��)���I�΂�Ă���Ƃ�
		if(select == 4)
		{
			//�ΐ�(�I�t���C��)�Ɉړ�
			select -=1;
		}
	}

	//���L�[����S�L�[�������Ɛ����E�ΐ탂�[�h(�I�����C��)�Ɉړ�
	if(Input::GetVKey('S') == true || Input::GetVKey(VK_DOWN) == true)
	{
		//�������I������Ă���Ƃ�
		if(select == 1)
		{
			//�ΐ�(�I�t���C��)�Ɉړ�
			select += 2;
		}
		//COM�ΐ�)���I�΂�Ă���Ƃ�
		if(select == 2)
		{
			//�ΐ�(�I�����C��)�Ɉړ�����
			select += 2;
		}
	}

	//���L�[����W�L�[��������COM�ΐ탂�[�h�E�ΐ탂�[�h(�I�t���C��)�Ɉړ�
	if(Input::GetVKey('W') == true || Input::GetVKey(VK_UP) == true)
	{
		//�ΐ�(�I�t���C��)���I������Ă���Ƃ�
		if(select == 3)
		{
			//�����Ɉړ�����
			select -= 2;
		}
		//�ΐ�(�I�����C��)���I������Ă���Ƃ�
		if(select == 4)
		{
			//COM�ΐ�Ɉړ�����B
			select -= 2;
		}
	}

}
//�h���[
void CObjModeChoice::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float red[4] = { 0.0f , 0.5f , 1.0f , 1.0f };

	Font::StrDraw((wchar_t*)L"���L�[�Ń��[�h��I������Enter�L�[�������Ă�������", 50, 200, 35,c);
	if(select == 1)
	{
		Font::StrDraw((wchar_t*)L"�������", 200, 400, 50, red);
	}
	else
	{
		Font::StrDraw((wchar_t*)L"�������", 200, 400, 30, c);
	}

	if(select == 2)
	{
		Font::StrDraw((wchar_t*)L"COM�ΐ�", 600, 400, 50, red);
	}
	else
	{
		Font::StrDraw((wchar_t*)L"COM�ΐ�", 600, 400, 30, c);
	}

	if(select == 3)
	{
		Font::StrDraw((wchar_t*)L"�ΐ�",200,550,50,red);
		Font::StrDraw((wchar_t*)L"(�I�t���C��)",300,560,30,red);
	}
	else
	{
		Font::StrDraw((wchar_t*)L"�ΐ�(�I�t���C��)",200,550,30,c);
	}

	if(select == 4)
	{
		Font::StrDraw((wchar_t*)L"�����L���O", 600, 550, 50, red);
	}
	else
	{
		Font::StrDraw((wchar_t*)L"�����L���O", 600, 550, 30, c);
	}

}