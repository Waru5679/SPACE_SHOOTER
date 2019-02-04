//�g�p����w�b�_�[
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include"GameL\DrawTexture.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjRanking.h"
#include"ObjBackground.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRanking::CObjRanking(int rank)
{
	m_rank = rank; //�����Ă������ʂ�ۑ�
}

//�C�j�V�����C�Y
void CObjRanking::Init()
{
	m_key_flag = false;//�L�[�t���O

	for (int i = 0; i <= 10; i++)
	{
		//���Ԃɏ����l9999�������Ă����ꍇtrue
		if (((UserData*)Save::GetData())->mRankingTimeData[i] == SET_TIME)
		{
			time_set_flag[i] = true;
		}
	}
}

//�A�N�V����
void CObjRanking::Action()
{
	//�G���^�[�L�[�������ꂽ��
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			if (m_rank <= 10)	//10�ʈȓ��Ȃ�
			{
				//���O���̓V�[���ֈړ�
				Scene::SetScene(new CSceneNameInput(m_rank));
			}
			else//�����L���O�O�Ȃ�
			{
				//���[�h�Z���N�g��
				CObjModeChoice* obj = new CObjModeChoice();
				Objs::InsertObj(obj, OBJ_MODE_CHOICE, 10);

				m_key_flag = false;

				this->SetStatus(false);//�����L���O�j��
			}
		}
	}
	else
	{
		m_key_flag = true;
	}
}

//�h���[
void CObjRanking::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float yellow[4] = { 1.0f,1.0f,0.0f,1.0f };
	wchar_t str_time[256];

	//�����L���O
	Font::StrDraw((wchar_t*)L"�����L���O",350,30,60,c);

	int j;

	//�����N�擾��10�ʈȏ�Ȃ�11�ʕ\�������Ȃ�
	if (m_rank > 10)
		j = 10;
	else
		j = 9;

	for (int i = 0; i <= j; i++)
	{
		//�^�C���\��-----------------------------------------------
		//�����l9999�������Ă���ꍇ
		if (time_set_flag[i] == true)
		{
			if (j == 9)
			{
				swprintf_s(str_time, L"%2d��     --:--", i + 1);
				Font::StrDraw(str_time, 250, 130 + 55 * i, 40, c);				
			}
			else if (j == 10 && i < 10)
			{
				swprintf_s(str_time, L"%2d��     --:--", i + 1);
				Font::StrDraw(str_time, 250, 130 + 55 * i, 40, c);
			}
		}
		//�����l9999�������Ă��Ȃ��ꍇ
		else
		{
			//10�ʈȏ�Ȃ�11�ʕ\�����Ȃ�
			if (j == 9 && ((UserData*)Save::GetData())->mRankingTimeData[0] == SET_TIME)
			{
				swprintf_s(str_time, L"%2d��     %02d:%02d", i + 1, ((UserData*)Save::GetData())->mRankingTimeData[i] / 60, ((UserData*)Save::GetData())->mRankingTimeData[i] % 60);
				Font::StrDraw(str_time, 250, 130 + 55 * i, 40, c);
			}
			//�f�[�^��0�Ԗڂɏ����l�������ĂȂ��ꍇ
			else if (j == 9 && ((UserData*)Save::GetData())->mRankingTimeData[0] != SET_TIME)
			{
				swprintf_s(str_time, L"%2d��     %02d:%02d", i + 1, ((UserData*)Save::GetData())->mRankingTimeData[i] / 60, ((UserData*)Save::GetData())->mRankingTimeData[i] % 60);
				Font::StrDraw(str_time, 135, 110 + 55 * i, 60, yellow);
			}
			//�����Ă���ꍇ
			else if (((UserData*)Save::GetData())->mRankingTimeData[0] != SET_TIME && i == 0)
			{
				swprintf_s(str_time, L"%2d��     %02d:%02d", i + 1, ((UserData*)Save::GetData())->mRankingTimeData[i] / 60, ((UserData*)Save::GetData())->mRankingTimeData[i] % 60);
				Font::StrDraw(str_time, 135, 110 + 55 * i, 60, yellow);
			}
			//10�ʈȉ��Ȃ�11�ʕ\��
			else if (j == 10 && i == 10)
			{
				swprintf_s(str_time, L"         %02d:%02d",((UserData*)Save::GetData())->mRankingTimeData[i] / 60, ((UserData*)Save::GetData())->mRankingTimeData[i] % 60);
				Font::StrDraw(str_time, 225, 140 + 55 * i, 45, c);
			}
			//1�`10�ʕ\��
			else if (j == 10 && i < 10 && i > 0)
			{
				swprintf_s(str_time, L"%2d��     %02d:%02d", i + 1, ((UserData*)Save::GetData())->mRankingTimeData[i] / 60, ((UserData*)Save::GetData())->mRankingTimeData[i] % 60);
				Font::StrDraw(str_time, 250, 130 + 55 * i, 40, c);
			}
			
		}
	}
	//-----------------------------------------------------------------------------

	//���O�\��----------------------------------------
	for (int i = 0; i < 10; i++)
	{
		wchar_t str_name[256];
		char name[6];
		strcpy_s(name, ((UserData*)Save::GetData())->mRankingNameData[i]);

		//char ����wchar_t�@�Ɂ@�w�肵���T�C�Y���R�s�[
		size_t* size = nullptr;
		mbstowcs_s(size, str_name, 12, name, 12);
			   
		if(((UserData*)Save::GetData())->mRankingNameData[0] == SET_NAME && i == 0)//�l�[���ɏ��������������Ă���ꍇ��1��
			Font::StrDraw(str_name, 660, 130 + 55 * i, 40, c);
		else if (i == 0 && ((UserData*)Save::GetData())->mRankingTimeData[0] != SET_TIME)//�����Ă��Ȃ��ꍇ��1��
			Font::StrDraw(str_name, 700, 110 + 55 * i, 60, yellow);
		else
			Font::StrDraw(str_name, 660, 130 + 55 * i, 40, c);//����ȊO�̏���
	}
	//-------------------------------------------------
}