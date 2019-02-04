//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBackground.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjBackground::Init()
{
	m_count_time=0;
}

//�A�N�V����
void CObjBackground::Action()
{
	m_count_time++;
}

//�h���[
void CObjBackground::Draw()
{
	//�`��J���[���@R=RED G=Green B=Blue A=alpha(���ߏ��)
	float c[4]={1.0f,1.0f,1.0f,0.8f};
	float c1[4]={1.0f,1.0f,1.0f,1.0f};
	RECT_F src;//�`�挳�̐؂���ʒu
	RECT_F dst;//�`���̕\���ʒu

	//�؂���ʒu�̐ݒ�
	RectSet(0.0f,0.0f,512.0f,512.0f,src);

	//�w�i�̕\���ʒu�̐ݒ�
	RectSet(0.0f,0.0f,WINDOW_SIZE_W,WINDOW_SIZE_H,dst);

	if(m_count_time<270)//�X�^�[�g�܂ł̃J�E���g��
	{
		Draw::Draw(7,&src,&dst,c,0.0f);//�g�Ȃ��w�i�̕`��
	}
	else//�J�E���g�I����
	{			
		Draw::Draw(8,&src,&dst,c,0.0f);//�g�L�w�i�̕`��
	}


}
