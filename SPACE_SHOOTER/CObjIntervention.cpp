//---------------------------------------------
// Intervention Block Move Check
// Collision Check
// 2017-06-12 Monday Released
// By �J���X�A�Q�n
//---------------------------------------------
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "CObjIntervention.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjIntervention::CObjIntervention(float x,float y,bool lr)
{
	m_px=x;
	m_py=y;
	m_lr=lr;
}

//�C�j�V�����C�Y
void CObjIntervention::Init()
{
	if(m_lr==true)
	{
		m_vx=1.0f;
	}
	else
	{
		m_vx=-1.0f;
	}
	//����pHitBox���쐬
	Hits::SetHitBox(this,m_px*BLOCK_SIZE+60.0f,m_py*BLOCK_SIZE+80.0f,BLOCK_SIZE/2,BLOCK_SIZE/2,ELEMENT_NULL,OBJ_BLOCK,1);
	m_time=0;

	m_Processing_flag=false;
	m_se=true;
	m_gameover_check=false;
	m_stop_flag=false; // ==�ɂȂ��Ă����̂��C��(2017-06-28)
	move_check=true;
}
//�A�N�V���� ���ז��L�����̈ړ�
void CObjIntervention::Action()
{
	//���C���I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	//�Q�[���I�[�o�[�I�u�W�F�N�g�̗L���𒲂ׂ�
	m_gameover_check = obj->ReturnFlag();
	
	//�Q�[���I�[�o�[�I�u�W�F�N�g�������
	if(m_gameover_check==true) return;
	
	m_time++;
		
	if(m_time>1000)//1000�𒴂��Ȃ��悤�ɂ���
		m_time = 0;

	Check();//�ړ��ł��邩�`�F�b�N����

	//�ړ��\�̏ꍇ
	if(move_check == true)
	{
		//10f�ɂP�񏈗�����--------------------------------
		if(m_time%10==0)
		{
			Move();//�ړ��̃`�F�b�N�ƈړ�������
		}
		//------------------------------------------------

		Check();//���̂Ƃ��ړ��ł��邩�`�F�b�N����(��d�`�F�b�N)

		if( move_check ==true)
		{
			//�ړ��\�Ȃ�
			m_stop_flag = false;//�X�g�b�v�t���O���I�t�ɂ���	
		}
		else
		{
			//�ړ��s��
			m_stop_flag=true;//�X�g�b�v�t���O���I���ɂ���
		}
	}
	else//�ړ��s�i�u���b�N������j
	{
		m_Processing_flag=true;//�����ς݃t���O�𗧂Ă�
		m_stop_flag = true;//�X�g�b�v�t���O���I���ɂ���
	}
		
	//�}�b�v�\���̂̍X�V
	obj->Enter(m_px,m_py,6);//���ז��u���b�N��6�Ԃɐݒ�
	obj->Enter_Stop_flag(m_px,m_py,m_stop_flag);//�X�g�b�v�t���O���}�b�v�\���̂ɓ����
	obj->Processflag(m_px,m_py,m_Processing_flag);//���ŏ����p�̃t���O���}�b�v�ɓ����

	//hitbox�̍X�V
	CHitBox* hit = Hits::GetHitBox(this); 
	hit->SetPos( m_px * BLOCK_SIZE + 60.0f , m_py * BLOCK_SIZE + 80.0f );
}

//�h���[
void CObjIntervention::Draw()
{
	//�`��J���[���
	float c[4]={1.0f,1.0f,1.0f,1.0f};

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	RectSet(0.0f,0.0f,32.0f,32.0f,src);

	//�\���ʒu�̐ݒ�
	RectSet(80.0f+m_py*BLOCK_SIZE,50.0f+m_px*BLOCK_SIZE,
		50.0f+m_px*BLOCK_SIZE+BLOCK_SIZE,80.0f+m_py*BLOCK_SIZE+BLOCK_SIZE,dst);

	Draw::Draw(6,&src,&dst,c,0.0f);//�`��
}

//�ړ������̊֐�
void CObjIntervention::Move()
{
	//���C���I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	if(m_lr==true)
	{
		//��
		if( m_px+m_vx<=9 )//�ړ��悪������荶�ł��ړ��\�Ȃ�
		{
			obj->Enter(m_px,m_py,99);//�ړ��O�̈ʒu��99�ɂ���
			obj->StopFlag_OFF(m_px,m_py);//�ړ��O�̈ʒu�̃X�g�b�v�t���O���I�t�ɂ���
		
			m_px+=m_vx;//�ʒu���X�V
		}
		if(m_se==true)
		{
			Audio::Start(4);//���ˉ��Đ�
			m_se=false;
		}
	}
	else
	{
		//�E
		if( m_px+m_vx>=10 )//�ړ��悪�������E�ł��ړ��\�Ȃ�
		{
			obj->Enter(m_px,m_py,99);//�ړ��O�̈ʒu��99�ɂ���
			obj->StopFlag_OFF(m_px,m_py);//�ړ��O�̈ʒu�̃X�g�b�v�t���O���I�t�ɂ���
			
			m_px+=m_vx;//�ʒu���X�V
		}
		if(m_se==true)
		{
			Audio::Start(4);//���ˉ��Đ�
			m_se=false;
		}
	}
}

//�ړ��ł��邩�ǂ����̃`�F�b�N�p
void CObjIntervention::Check()
{
	//�u���b�N�I�u�W�F�N�g�̌Ăяo��
	CObjBlock * obj_b =(CObjBlock*)Objs ::GetObj(OBJ_BLOCK);

	if(m_px<9 || m_px>10)//�ړ��ł���\��������ʒu�Ȃ�
	{			
		move_check = obj_b->MoveCheck(m_px+m_vx,m_py);//�ړ��ł��邩�̃`�F�b�N�֐����Ăяo��
	}
	else//���łɒ����̈ʒu�ɂ���ꍇ
		move_check=false;
}