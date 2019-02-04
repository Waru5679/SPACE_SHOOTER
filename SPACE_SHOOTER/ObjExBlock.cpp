//---------------------------------------------
// Color Block Move Check
// Collision Check
// 2017-06-12 Monday Released
// By �J���X�A�Q�n
//---------------------------------------------
#include <time.h>

#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjExBlock.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjExBlock::CObjExBlock(int color)
{
	m_color = color;
}

//�C�j�V�����C�Y
void CObjExBlock::Init()
{
	srand(time(NULL)); // �����_������������
	m_color= rand()%6; // �����_���ɐF�����߂�

	m_vx = 2.0f;
	m_px= 700.0f;
	m_py= 470.0f;
}

//�A�N�V����
void CObjExBlock::Action()
{
	//���C���I�u�W�F�N�g�̌Ăяo��
	CObjExplanation3 * obj_e3 = (CObjExplanation3*)Objs ::GetObj(OBJ_EXPLANATION3);

	m_px += m_vx;

	if(m_px >= 850.0f || Input::GetVKey('D') == true || Input::GetVKey('A') == true
		|| Input::GetVKey(VK_LEFT) == true || Input::GetVKey(VK_RIGHT) == true)//270�܂ňړ���A�܂���D�L�[�������Ə�����B
	{
		obj_e3->Updata();//�Q�[�W������������
		this->SetStatus(false);//���g���폜����
	}

}


//�h���[
void CObjExBlock::Draw()
{
	//�`��J���[���
	float c[4]={1.0f,1.0f,1.0f,1.0f};

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	RectSet(0.0f,0.0f,64.0f,64.0f,src);

	//�\���ʒu�̐ݒ�
	RectSet(m_py,m_px,m_px+30.0f,m_py+30.0f,dst);

	//�u���b�N�̕`��
	Draw::Draw(m_color,&src,&dst,c,0.0f);
}
