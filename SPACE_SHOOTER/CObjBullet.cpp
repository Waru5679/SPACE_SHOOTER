//�g�p����w�b�_�[�t�@�C��
#include <stdlib.h>
#include <time.h>
#include"GameHead.h"
#include"GameL\HitBoxManager.h"
#include"CObjBullet.h"
#include"GameL\DrawTexture.h"
#include"UtilityModule.h"
#include"GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBullet::CObjBullet(float x,float y,bool s,int n)
{
	m_x=x;
	m_y=y;
	m_s=s;
	npc=n;

}

//�C�j�V�����C�Y
void CObjBullet::Init()
{
	m_eff.m_top=32;
	m_eff.m_left=0;
	m_eff.m_right=32;
	m_eff.m_bottom=64;
	m_ani=0;
	m_ani_time=0;
	m_del=false;
	m_check=true;



	if(m_s==true)
		m_vx=-3.0f;
	else
		m_vx=+3.0f;

	
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this,m_x,m_y,45,45,ELEMENT_NULL,OBJ_BULLET,1);



}

//�A�N�V����
void CObjBullet::Action()
{
	////��l���̈ʒu���擾
	//CObjHero* hero = (CObjHero*) Objs::GetObj(OBJ_HERO);
	//float hx = hero->GetX();
	//float hy = hero->GetY();

	//Resorces�̕`�敨��RECT
	m_eff =GetBulletEffec(&m_ani,&m_ani_time,m_del,2);

	//�e�ۏ��ŏ���
	if(m_del==true)
	{
			//���e�A�j���[�V�����I���Ŗ{���ɃI�u�W�F�N�g�j��
			if(m_ani==4)
			{
				this->SetStatus(false);
				Hits::DeleteHitBox(this);
			}

		return;//���ł������̓R�R�ŃA�N�V�������\�b�h���I��������
	}
		
	//�e�ۂ�HitBox�s�i�p�|�C���^�[�擾
	CHitBox*hit=Hits::GetHitBox(this);
	hit->SetPos(m_x,m_y);//HitBox�̈ʒu��e�ۂ̈ʒu�ɍX�V

	//�̈�̔���
	if(m_s==true)//�E�@��
		m_check=CheckWindow(m_x,m_y,WINDOW_SIZE_W/2,0.0f,WINDOW_SIZE_W,WINDOW_SIZE_H);
	else//���@��
		m_check=CheckWindow(m_x+32.0f,m_y,0.0f,0.0f,WINDOW_SIZE_W/2,WINDOW_SIZE_H);

	if(m_check==true)
	{
		//�ړ�
		m_x+=m_vx;
	}


	if(hit->CheckObjNameHit(OBJ_BULLET) != nullptr&&m_vx!=0.0f)
	{

		//���g��HitBox�������Ă���
		CHitBox* hit=Hits::GetHitBox(this);
		//�G�Ɠ������Ă��邩�m�F
		if(hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
		{
			//��l�����G�Ƃǂ̊p�x�œ������Ă��邩�m�F
			HIT_DATA** hit_data;								//�����������ׂ̍��ȏ�������邽�߂̍\����
			hit_data=hit->SearchObjNameHit(OBJ_BULLET);			//hit_data��l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������

			for(int i=0; i<hit->GetCount(); i++)
			{

				//�G�̍��E�ɓ���������
				float r=hit_data[0]->r;
				if((r<45 && r>=0) || r>315)
				{
					m_x -=1.0f;//���Ɉړ�������

				}

				if(r>135 && r<225)
				{
					m_x+=1.0f;//�E�Ɉړ�������
				}
			}

		}

		m_vx = 0.0f;
			
	}
		
}

//�h���[
void CObjBullet::Draw()
{
	//�`��J���[���@R=RED G=Green B=Blue A=alpha(���ߏ��)
	float c[4]={1.0f,1.0f,1.0f,1.0f};
	RECT_F dst;//�`���̕\���ʒu
	RECT_F src;


	
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = npc * 100.0f;
	src.m_right  = src.m_left + 100.0f;
	src.m_bottom = 32.0f;

	if(m_s==false)
	{
		//�\���ʒu�̐ݒ�
		dst.m_top    = 0.0f+m_y;
		dst.m_left   = 0.0f+m_x;
		dst.m_right  = 45.0f+m_x;
		dst.m_bottom = 45.0f+m_y;
	}
	else 
	{
		//�\���ʒu�̐ݒ�
		dst.m_top    = 0.0f+m_y;
		dst.m_left   = 45.0f+m_x;
		dst.m_right  = 0.0f+m_x;
		dst.m_bottom = 45.0f+m_y;
	}
	if(m_del==true)
	{
		////2�Ԗڂɓo�^�����O���t�B�b�N�̂�src.dst.c�̏������ɕ`��
		//Draw::Draw(2,&m_eff,&dst,c,0.0f);	
	}
	else
	{
		////2�Ԗڂɓo�^�����O���t�B�b�N�̂�src.dst.c�̏������ɕ`��
		//Draw::Draw(2,&src,&dst,c,0.0f);	
	}

}


////BlockHit�֐�
////����1		float* x			:������s��object��X�ʒu
////����2		float* y			:������s��object��Y�ʒu
////����3		bool	scroll_on	:������s��object�̓X�N���[���̉e���^���邩�ǂ���(true=�^����@false=�^���Ȃ�)
////����4		bool*   up			:�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
////����5		bool*	down		:�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
////����6		bool*	left		:�㉺���E����̍������ɓ������Ă��邩�ǂ�����Ԃ�
////����7		bool*	right		:�㉺���E����̉E�����ɓ������Ă��邩�ǂ�����Ԃ�
////����8		float*	vx			:���E���莞�̔����ɂ��ړ������E�͂̒l�ς��ĕԂ�
////����9		float*	vy			:�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l�ς��ĕԂ�
////����10	int*	bt			:���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
////������s��object�ƃu���b�N64X64����ŁA�����蔻��Ə㉺���E������s��
////���̌��ʂ͈�����4�`10�ɕԂ�
//void  CObjBullet ::BlockHit(
//	float *x,bool* left,bool* right,float* vx,int* bt
//	)
//{
//	//��l���̏Փˏ�Ԋm�F�p�t���O�̏�����
//	*left	= false;
//	*right	= false;
//
//					//�㉺���E����
//
//					//vector�̍쐬
//					float rvx = *x - bx;
//
//					//���������߂�
//					float len = sqrt( rvx*rvx);
//
//					//�p�x�����߂�
//					float r=atan2(rvx);
//					r = r * 180.0f / 3.14f;
//
//					if(r <= 0.0f)
//						r = abs(r);
//					else
//						r = 360.0f-abs(r);
//
//					//len��������̒����̂��Z���ꍇ����ɓ���
//					if(len<88.0f)
//					{
//
//					//�p�x�ŏ㉺���E�𔻒�
//
//
//					if((r<45 && r>0) || r>315)
//					{
//						//�E
//						*right = true;//��l���̍��������Փ˂��Ă���
//						*x = bx + 64.0f;//�u���b�N�̈ʒu+��l���̕�
//						*vx = -(*vx) * 0.1f;;//-VX*�����W��
//					}
//
//					if(r>135 && r<225)
//					{
//						//��
//						*left = true;//��l���̉E�̕������Փ˂��Ă���B
//						*x = bx - 64.0f;//�u���b�N�̈ʒu-��l���̕�
//						*vx = -(*vx) * 0.1f;;//-VX*�����W��
//					}
//
//					}
//
//				}
//
//			}
//		}
//	}
//
//	
//}
