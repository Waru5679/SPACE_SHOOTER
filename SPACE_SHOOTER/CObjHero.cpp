//�g�p����w�b�_�[�t�@�C��
#include <stdlib.h>
#include <time.h>
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"
#include "CObjHero.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"

#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjHero::Init()
{
	//�ʒu�̏�����
	m_x=-10;
	m_y=WINDOW_SIZE_H/3.5f;
	
	//�ړ��ʂ̏�����
	m_vy=0.0f;
	m_move=3;

	//��]�̏�����
	m_r=0;
	m_rf=true;

	srand(time(NULL)); // �����_������������
	
	//�����u���b�N�̏�����-----------------------
	for(int i=0;i<4;i++)
	{
		m_npc[i]=rand() % 6;  // ���̂悤�ɋL�q�����npc�ɂ͂O�`5�܂ł̒l������܂�
	}
	//------------------------------------------

	m_bullet_count=0;//�u���b�N�J�E���g�̏�����

	//�u���b�N���m�̒��ԓ_�����߂�
	m_senter.x=BLOCK_SIZE+(BLOCK_SIZE/2);
	m_senter.y=(WINDOW_SIZE_H-8.0f)-(BLOCK_SIZE*2);

	//m_senter�ƕ`��̊�_�i���ォ�E���j�Ƃ̍��i��Βl�j
	m_drow.x=BLOCK_SIZE/2;
	m_drow.y=BLOCK_SIZE;

	//�e�����ʒu�ƐF�̕ۑ��p--------
	m_shot_x[0]=-1;
	m_shot_x[1]=-1;

	m_shot_y[0]=-1;
	m_shot_y[1]=-1;
	//----------------------------

	//�ړ��̐���t���O������
	m_down	= true;
	m_up	= true;

	//�X�^�[�g����----
	m_count_time=0;
	m_end_flag=false;

	//�Q�[�W�p���������˗p
	m_gauge_time = 360;

	//���ז��u���b�N���~�炷��
	ojm_num=0;

	m_f=true;//�u���b�N���Ƃ܂��Ă��邩�̃t���O�̏�����
	m_push_f = true;//�������j�~�p�̃t���O������
}

//�A�N�V����
void CObjHero::Action()
{
	m_count_time++;
	
	if(m_count_time >= 10000)//10000�𒴂��Ȃ��悤�ɂ���
		m_count_time=270;

	if(m_count_time)

	//�Q�[���I�[�o�[�Ȃ�
	if(m_end_flag==true) return;//2017-06-26

	//�}�b�v�I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	//�f�o�b�O�p---------------
	if(Input::GetVKey('M')==true)
	{
		obj->Enter(0,3,6);
		obj->FlagOn(0,3);
	}
	//-------------------------------

	//�X�^�[�g�J�E���g��������Ɛ���ł���悤�ɂ���
	if(m_count_time < 270) return;//2017-06-26

	//�Q�[�W��max�@���@���ז��������K�v�Ȃ�
	if(m_gauge_time==360 && ojm_num != 0)
	{
		if( obj->ShotCheck(true) ==	true)//���w�̃u���b�N�S�Ă��Ƃ܂��Ă��邩�m�F����
		{	
			//���w�̃u���b�N�S�Ă��Ƃ܂��Ă����
			obj->CreateIntervention(ojm_num,true);//���ז��u���b�N����
			ojm_num=0;//�������I�������0�ɂ���
				
			return;
		}
	}
	
	Shot_move();//�e�����A��]�A�ړ�����������֐�
	
}

//�e�����A��]�A�ړ��̏���������֐�
void CObjHero::Shot_move()
{
	//�}�b�v�I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	//���w�̃u���b�N�S�Ă��~�܂��Ă��
	if( obj->ShotCheck(true) ==true)
		m_f=true;//�e�����Ă�悤�ɂ���
	else
		m_f=false;//�u���b�N�������Ă���ΑłĂȂ��悤�ɂ���

	if(m_f==true)//�e�����Ă�󋵂Ȃ�
	{
		m_gauge_time-=2;//�������˃J�E���g��i�߂�

		if(m_gauge_time < 0)//����0�����ɂȂ낤�Ƃ��Ă�Ȃ�
			m_gauge_time=0;
	}

	//�u���b�N���ˈʒu(�o���\��ʒu)
	Block_Pos_Save();//�u���b�N�o���\��ʒu�ƐF�ۑ�
		
	//��l���@�̒e�۔���
	if(Input::GetVKey('D')==true )//D�L�[���������
	{
		//�u���b�N�������Ă��Ȃ��āA�{�^�������������Ă��Ȃ��ꍇ
		if( m_f == true && m_push_f == true)
		{
			Shot();//�e���������̊֐����Ăт���	
			m_push_f = false;//�g���K�[�p�̃t���O���I�t�ɂ���
		}
	}
	else
	{
		m_push_f=true;//�g���K�[�p�t���O���I���ɂ���
	}
				
	//�}�V���̎������˃V�X�e��----------------------------
	if(m_f == true)//�e�����Ă�󋵂Ȃ�
	{		
		if( m_gauge_time == 0)//�J�E���g��0�ɂȂ�΋����Ŕ���
		{
			Shot();//�e���������̊֐����Ăт���
		}
	}
	//---------------------------------------------------------
					
	//��l���@�̈ړ��x�N�g���̏�����
	m_vx=0.0f;
	m_vy=0.0f;

	//�L�[�̓��͕����Ƀx�N�g���̑��x�������
	//W�������ꂽ�Ƃ�
	if(Input::GetVKey('W')==true)
	{
		if(m_up==true)//�g���K�[�@�\
		{
			m_up = false;
			m_move--;//�ړ��̃J�E���g�����炷
			m_vy = -BLOCK_SIZE;
		
			//�O�ɐ��������Ȃ�J�E���g�ƈʒu���ێ�����悤�ɂ���
			if( m_move < 0 )
			{
				m_move=0;
				m_vy=0.0f;
			}
		}
	}
	else
	{
		//W��������ĂȂ��Ƃ�
		m_up = true;
	}

	//�A�Ńo�O���p�ɂ���������ĂȂ��Ƃ�����̏���������
	if(Input::GetVKey('W')!=true)
	{
		if(Input::GetVKey('S')==true)
		{
			if(m_down == true)
			{
				m_down = false;
				m_move++;//�ړ��̃J�E���g�𑝂₷
				m_vy=BLOCK_SIZE;

				//�O�ɐ��������Ȃ�J�E���g�ƈʒu���ێ�����悤�ɂ���
				if(m_move >6)
				{
					m_move=6;
					m_vy=0.0f;
				}
			}
		}
		else
		{
			m_down = true;
		}
	}

	if(Input::GetVKey('A')==true)
	{
		Revolution();//��]�����̊֐����Ăяo��
		m_rf=false;//�t���O���I�t�ɂ���
	}
	else 
	{
		m_rf=true;//�t���O���I���ɂ���
	}
			
	//�ړ��x�N�g�������W�ɉ��Z����
	m_x+=m_vx;
	m_y+=m_vy;
}

//�h���[
void CObjHero::Draw()
{
	//�`��J���[���@R=RED G=Green B=Blue A=alpha(���ߏ��)
	float c[4]={1.0f,1.0f,1.0f,1.0f};//�ʏ�
	float c1[4]={1.0f,1.0f,1.0f,0.5f};//�u���b�N�ʒu�\���p
	float str_c[4]={0.0f,0.0f,0.0f,1.0f};//�����\���p

	//�X�^�[�g�܂ł̃J�E���g���I����Ă����
	if(m_count_time>=270)
	{

//�@�̂̕\��--------------------------------

		//�؂���ʒu�̐ݒ�
		RectSet(1.0,0.0f,32.0f,31.0f,src);

		//�\���ʒu�̐ݒ�
		RectSet(0.0f + m_y ,0.0f + m_x, 0.0f + m_x + 60.0f , 0.0f + m_y +60.0f ,dst);
	
		//10�Ԗڂɓo�^�����O���t�B�b�N�̂�src.dst.c�̏������ɕ`��
		Draw::Draw(10,&src,&dst,c,0.0f);
	
//----------------------------------------------------------
	
//���ז��̐���\��------------------------------------------
	
	//�؂���ʒu���Z�b�g����
	RectSet(0.0f,0.0f,32.0f,32.0f,src);
		
	//�`��ʒu���Z�b�g����
	RectSet( 20.0f ,50.0f + BLOCK_SIZE ,
		50.0f + BLOCK_SIZE + BLOCK_SIZE , 20.0f + BLOCK_SIZE , dst);

	//10�Ԗڂɓo�^�����O���t�B�b�N�̂�src.dst.c�̏������ɕ`��
	Draw::Draw(6,&src,&dst,c,0.0f);
	
	//������p�ӂ��ĕ\������
	wchar_t str[128];
	swprintf_s(str, (wchar_t*)L"%d",ojm_num);

	Font::StrDraw((wchar_t*)L"x",50.0f + BLOCK_SIZE + BLOCK_SIZE,20.0f,BLOCK_SIZE,str_c);
	Font::StrDraw(str,75.0f + BLOCK_SIZE + BLOCK_SIZE,20.0f,BLOCK_SIZE,str_c);

//----------------------------------------------------------

//�Q�[�W----------------------------------------------------
			
			//�Q�[�W�p�w�i-----------------------------

			//�؂���ʒu	�D�F
			RectSet(0.0f,401.0f,402.0f,100.0f,src);
			//�`��ʒu
			RectSet(445.0f,59.0f,64.0f + 365,485.0f,dst);
			//�`�悷��
			Draw::Draw(15,&src,&dst,c,0.0f);

			//------------------------

			//�؂���ʒu	���F
			RectSet(0.0f,100.0f,101.0f,100.0f,src);
			//�`��ʒu
			RectSet(450.0f,64.0f,64.0f + 360.0f,480.0f,dst);
			//�`�悷��
			Draw::Draw(15,&src,&dst,c,0.0f);

			//�w�i�����------------------------------

			//�Q�[�W�{��---------------

			//�؂���ʒu
			RectSet(0.0f,1.0f,2.0f,99.0f,src);
			//�`��ʒu
			RectSet(450.0f,64.0f,64.0f+m_gauge_time,480.0f,dst);
			//�`�悷��
			Draw::Draw(15,&src,&dst,c,0.0f);

//�Q�[�W�\��-----------------------------------------------------------

		//�u���b�N�̐؂���ʒu�̐ݒ�
		RectSet(0.0f,0.0f,64.0f,64.0f,src);

//�u���b�N�̐����\��n�̕\��---------------------------------

		for(int i=0;i<2;i++)
		{
			//�\���ʒu�̐ݒ�
			RectSet(80.0f+m_shot_y[i]*BLOCK_SIZE,50.0f+m_shot_x[i]*BLOCK_SIZE,
				50.0f+m_shot_x[i]*BLOCK_SIZE+BLOCK_SIZE,80.0f+m_shot_y[i]*BLOCK_SIZE+BLOCK_SIZE,dst);
		
			
			
			Draw::Draw(m_npc[ (m_bullet_count+i)%4 ],&src,&dst,c1,0.0f);//�`��
		}
		
//-------------------------------------------------------------

//��̃u���b�N�\��-------------------------------------
		
		//1��̂Q��------------------------------------
		
		//�\���ʒu�̐ݒ�
		RectSet(m_senter.y-m_drow.y,m_senter.x-m_drow.x+20,
			m_senter.x-m_drow.x+20+BLOCK_SIZE,m_senter.y-m_drow.y+BLOCK_SIZE,dst);

		Draw::Draw(m_npc[m_bullet_count],&src,&dst,c,0.0f);//�`��
		
		//�\���ʒu�̐ݒ�
		RectSet( m_senter.y+m_drow.y-BLOCK_SIZE , m_senter.x+m_drow.x+20-BLOCK_SIZE ,
			m_senter.x+m_drow.x+20,m_senter.y+m_drow.y,dst);
		
		Draw::Draw(m_npc[(m_bullet_count+1)%4],&src,&dst,c,0.0f);//�`��
		
		//2���2��------------------------------------------------------------
		
		//�`��ʒu�̐ݒ�
		RectSet(m_senter.y,m_senter.x+17+BLOCK_SIZE*2-BLOCK_SIZE/2+3,
			m_senter.x+17+BLOCK_SIZE*2-BLOCK_SIZE/2+3+BLOCK_SIZE-20 ,m_senter.y+BLOCK_SIZE-20,dst);
			
		Draw::Draw(m_npc[(m_bullet_count+2)%4],&src,&dst,c,0.0f);//�`��
	
		//�`��ʒu�̐ݒ�
		RectSet(m_senter.y+BLOCK_SIZE-20,m_senter.x+17+BLOCK_SIZE*2-BLOCK_SIZE/2+3,
			m_senter.x+17+BLOCK_SIZE*2-BLOCK_SIZE/2+3+BLOCK_SIZE-20 ,m_senter.y+BLOCK_SIZE-20+BLOCK_SIZE-20,dst);

	
		Draw::Draw(m_npc[(m_bullet_count+3)%4],&src,&dst,c,0.0f);//�`��

//��̃u���b�N�\�������-----------------------------------------------------------------------------	

	}
}

//�e��ł����̊֐�
void CObjHero::Shot()
{
	//�}�b�v�I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);
	
	Block_Pos_Save();//�u���b�N�̐����\��n�̕ۑ�
		
	//���ז��u���b�N�Ƃ̏d��������邽�߂̃`�F�b�N-----------------------------------------------------------------
	bool check,check2;
	check = (obj->Return_Num(m_shot_x[0],m_shot_y[0]) == 99 );//1�ڂ̃u���b�N������\��̈ʒu���󔒂��ǂ������ׂ�
	check2= (obj->Return_Num(m_shot_x[1],m_shot_y[1]) == 99 );//2�ڂ̃u���b�N������\��̈ʒu���󔒂��ǂ������ׂ�
	//------------------------------------------------------------------------------------------------------------
			
	if(check==true && check2==true)//�Q�̃u���b�N�������ɑłĂ�󋵂Ȃ�
	{
		//��̃u���b�N�����̏���--------------
		for(int i=0;i<2;i++)
		{
			obj->Enter(m_shot_x[i],m_shot_y[i],m_npc[m_bullet_count]);//�L���������z��̈ʒu�̗v�f��ύX����
			m_npc[(m_bullet_count++)%4]=rand() % 6;//�g�p�����ʒu�̃����_�����̍X�V
			obj->FlagOn(m_shot_x[i],m_shot_y[i]);//�I�u�W�F�N�g�����t���O���I���ɂ���
		}
		//---------------------------------------
		//��]���̃��Z�b�g--------------------------
		m_r=0;

		m_drow.x=BLOCK_SIZE/2;
		m_drow.y=BLOCK_SIZE;
		//------------------------------------------
		m_bullet_count%=4;//bullet_count��0-3���J��Ԃ��悤�ɂ���

		//�Q�[�W�̏�����
		m_gauge_time=360;
	}			
}

//�u���b�N�̉�]�����̊֐�
void CObjHero::Revolution()
{
	if(m_rf==true)
	{
		m_r++;

		if(m_r==4)
			m_r=0;

		//��_�̒����i���Ƃ��̓���ւ��j
		float num	= m_drow.x;
		m_drow.x	= m_drow.y;
		m_drow.y	= num;
			
		//��]��������ڂȂ�
		if(m_r==1||m_r==3)
		{
			//��������ւ�
			int tmp=m_npc[m_bullet_count];
			m_npc[m_bullet_count]=m_npc[(m_bullet_count+1)%4];
			m_npc[(m_bullet_count+1)%4]=tmp;
		}
		m_rf=false;
	}
}

//�u���b�N�̐����\��n�̕ۑ����s���֐�
void CObjHero::Block_Pos_Save()
{
	//�v���C���[�̒��S�ʒu����u���b�N������ׂ��z��̗v�f�������߂�
	int t = m_move;

	//�u���b�N���c���i������]�j�Ȃ�
	if(m_r%2==0)
	{	
		//��Ԃ����̒i�őłƂ��Ƃ����ꍇ�͂ЂƂ���ɂ��炷
		if(t==6)
			t--;

		//�㑤�̃u���b�N�̈ʒu���L��
		m_shot_x[0]=0;
		m_shot_y[0]=t;
		//�����̃u���b�N�̈ʒu���L��
		m_shot_x[1]=0;
		m_shot_y[1]=t+1;
	}
	else 
	{
		//�����̃u���b�N�̈ʒu���L��
		m_shot_x[0]=0;
		m_shot_y[0]=t;
		//�E���̃u���b�N�̈ʒu���L��
		m_shot_x[1]=1;
		m_shot_y[1]=t;
	}

}
