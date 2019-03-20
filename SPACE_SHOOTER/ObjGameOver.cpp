//�g�p����w�b�_�[
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include"GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjGameOver.h"
#include "ObjBackground.h"
#include "GameL\UserData.h"
#include "ObjCP.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGameOver::CObjGameOver(int p)
{
	m_pattern=p; //�Q�[�������p�^�[����ObjMain���玝���Ă��āAm_pattern�ɑ��
}

//�C�j�V�����C�Y
void CObjGameOver::Init()
{
	//�ʒu�̏�����
	m_y = 900.0f;
	m_yy = 800.0f;

	count=0;
	ranking = 0;
	
	//�}�b�v�I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	m_cp_flag=obj->ReturnCPflag();
	
	//�퓬�ȃX�g�b�v
	Audio::Stop(8);

	//���s�~���[�W�b�N�J�n
	Audio::Start(7);
}

//�A�N�V����
void CObjGameOver::Action()
{	
	count++;//�J�E���g�𑝂₵�Ă���

	if( count > 300)//300�𒴂��Ȃ��悤�ɂ���
		count = 300;

	//�G���^�[�L�[�������ꂽ��
	if(Input ::GetVKey(VK_RETURN)==true)
	{
		//�}�X�^�[�{�����[����1.0�ɖ߂�
		float v =Audio::VolumeMaster( 0 );
		v =Audio::VolumeMaster( (1.0f-v) );

		//CP��@���@���v���C���[�̏����Ȃ�
		if (m_cp_flag == true && m_pattern == 1)
		{
			//�}�b�v�I�u�W�F�N�g�̌Ăяo��
			CObjMain * obj_main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
			
			//�����L���O�̍ŉ��ʂɍ���̃^�C���Ɩ��O��ۑ�
			((UserData*)Save::GetData())->mRankingTimeData[10] = obj_main->ReturnTime();
			strcpy_s( ((UserData*)Save::GetData())->mRankingNameData[10],NO_NAME);

			//�����L���O���\�[�g���āA����̏��ʂ𒲂ׂ�
			ranking = RankingSort(((UserData*)Save::GetData())->mRankingTimeData, ((UserData*)Save::GetData())->mRankingNameData);

			//�����L���O�ֈڍs
			Scene::SetScene(new CSceneRanking(ranking));
		}
		else
		{
			//�^�C�g���ֈڍs
			Scene::SetScene(new CSceneTitle);
		}
	}
}

//�h���[
void CObjGameOver::Draw()
{
	float c[4]={1.0f,1.0f,1.0f,1.0f};//�J���[
		
	Result();//���ʂ�\������
	Font::StrDraw((wchar_t*)L"EnterKey�Ń^�C�g���ɖ߂�",223,m_y - count,50,c);
	
}

//�p�^�[���ɉ�����
void CObjGameOver::Result()
{
	CObjCP* obj_cp=(CObjCP*)Objs::GetObj(OBJ_CP);
	float c[4]={1.0f,1.0f,1.0f,1.0f};//�J���[
	
	switch(m_pattern)
	{
		case 0:
		{
			//���������\��
			Font::StrDraw((wchar_t*)L"DROW",400,m_yy - count,100,c);
			break;
		}
		case 1:
		{
			if (obj_cp != nullptr)
			{
				//CPU����
				Font::StrDraw((wchar_t*)L"YOU WIN", 350, m_yy - count, 100, c);
				break;
			}
			else//2�l�ΐ펞
			{
				//1Pwin�\��
				Font::StrDraw((wchar_t*)L"1P WIN", 350, m_yy - count, 100, c);
				break;
			}
		}
		case 2:
		{
			if (obj_cp != nullptr)//CPU�ΐ킩�ۂ�����
			{
				//CPU����
				Font::StrDraw((wchar_t*)L"YOU LOSE", 350, m_yy - count, 100, c);
				break;
			}
			else//2�l�ΐ펞
			{
				//2Pwin�\��
				Font::StrDraw((wchar_t*)L"2P WIN", 350, m_yy - count, 100, c);
				break;
			}
		}
	}
}

//�Ⴂ���Ń\�[�g���s��
//����1:�^�C���z��
//����2:���O�z��
//�߂�l�F����̏���
int CObjGameOver::RankingSort(int time[],char name[][6])
{
	int w;		//�^�C�������p�ϐ�
	int ranking;//����̏��ʕۑ��p
	char n[6];	//���O�����p�z��

	//�\�[�g
	for (int i = 10; i >= 1; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (time[i] <= time[j])
			{
				//�^�C���̌���
				w = time[i];
				time[i] = time[j];
				time[j]= w;

				//���O�̌���
				strcpy_s(n, name[i]);
				strcpy_s(name[i], name[j]);
				strcpy_s(name[j], n);
			}
		}
	}

	//�����̖͂��O�ӏ���T���č���̏��ʂ𒲂ׂ�
	for (int i = 0; i < 11; i++)
	{
		//���O�������͂Ȃ�
		if (strcmp(name[i], NO_NAME) == 0)
		{
			ranking = i + 1; //���ʕۑ�
			break;
		}
	}

	return ranking;
}
