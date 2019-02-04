//�g�p����w�b�_�[�t�@�C��
#include <stdio.h>
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjScore.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�f�X�g���N�^
CObjScore::~CObjScore()
{
}

//�C�j�V�����C�Y
void CObjScore::Init()
{
	//�o�͂����镶���̃O���t�B�b�N
	Font::SetStrTex((wchar_t*)L"0123456789");
	Font::SetStrTex((wchar_t*)L"1UP HIGH SCORE");
	m_score_L=0;
	m_score_R=0;
	m_high_score=0;
		
}

//�A�N�V����
void CObjScore::Action()
{
}

//�h���[
void CObjScore::Draw()
{
	//�`��J���[���
	float c[4]={1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//�؂���
	RECT_F dst;//�\����

		
	wchar_t score_L[10];
	swprintf_s(score_L,L"%d",m_score_L,4*10);
	Font::StrDraw(score_L,(WINDOW_SIZE_W/6) ,10,60.0f,c);

	wchar_t	score_R[10];
	swprintf_s(score_R,L"%d",m_score_R,4*10);
	Font::StrDraw(score_R,(WINDOW_SIZE_W/6)*4,10,60.0f,c);

	
}

//�X�R�A�ǉ��֐�
//�����P�@bool true:���@false:�E
//�����Q�@int  �������u���b�N�̐�
void CObjScore::ScorePlus(bool LorR,int num)
{
	if(LorR==true)
		m_score_L+=100*num;
	else
		m_score_R+=100*num;
}
