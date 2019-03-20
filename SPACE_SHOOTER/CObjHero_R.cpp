//�g�p����w�b�_�[�t�@�C��
#include <stdlib.h>
#include <time.h>
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"
#include "CObjHero_R.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjHero_R::Init()
{
	m_x=WINDOW_SIZE_W-54;
	m_y=WINDOW_SIZE_H/3.5f;
	m_f=true;
	m_vx=0.0f;
	m_vy=0.0f;
	m_move=3;
	m_r=0;
	m_rf=true;
	m_bullet_count=0;

	srand(time(NULL)); // �����_������������
	
	for(int i=0;i<4;i++)
	{
		m_npc[i]=rand() % 6;  // ���̂悤�ɋL�q�����npc�ɂ͂O�`5�܂ł̒l������܂�
	}

	//�u���b�N���m�̒��ԓ_�����߂�
	m_senter.x=WINDOW_SIZE_W-(BLOCK_SIZE+(BLOCK_SIZE/2));
	m_senter.y=(WINDOW_SIZE_H-8.0f)-(BLOCK_SIZE*2);

	//m_senter�ƕ`��̊�_�i���ォ�E���j�Ƃ̍��i��Βl�j
	m_drow.x=BLOCK_SIZE/2;
	m_drow.y=BLOCK_SIZE;
	
	//�e�����ʒu�̕ۑ��p--------
	m_shot_x[0]=-1;
	m_shot_x[1]=-1;

	m_shot_x[0]=-1;
	m_shot_x[1]=-1;
	//----------------------------


	//�ړ��̐���t���O������
	m_down	= true;
	m_up	= true;

	//�X�^�[�g����----
	m_count_time=0;

	//�Q�[���I�[�o�[�I�u�W�F�N�g�̗L���`�F�b�N
	m_end_flag=false;

	//�Q�[�W�p���������ː���p
	m_gauge_time=360;

	//���ז��u���b�N���~�炷��
	ojm_num=0;
	
	m_push_f=true;//����������̑j�~�p�̃t���O
}

//�A�N�V����
void CObjHero_R::Action()
{
	m_count_time++;
	
	if(m_count_time>=10000)
		m_count_time=270;

	//�Q�[���I�[�o�[���Ȃ����
	if(m_end_flag==true) return;
	
	//�}�b�v�I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);
	
	//�X�^�[�g�J�E���g������ꍇ
	if(m_count_time < 270) return;
			
	//�Q�[�W��max�@���@���ז��������K�v�Ȃ�
	if(m_gauge_time==360 && ojm_num != 0)
	{
		if( obj->ShotCheck(false) ==true)//���w�̃u���b�N�S�Ă��Ƃ܂��Ă��邩�m�F����
		{
				//���w�̃u���b�N�S�Ă��Ƃ܂��Ă����d
				obj->CreateIntervention(ojm_num,false);//���ז��u���b�N����
				ojm_num=0;//�������I�������0�ɂ���
				return;
		}
	}
	
	Shot_move();//�ړ��A��]�A�e��������������֐�
		
}

//�ړ��A��]�A�e�̔��˂�����֐�
void CObjHero_R::Shot_move()
{
	//�}�b�v�I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	//���w�̃u���b�N�S�Ă��~�܂��Ă��
	if( obj->ShotCheck(false) == true)
		m_f=true;//�e�����Ă�悤�ɂ���
	else
		m_f=false;//�u���b�N�������Ă���ΑłĂȂ��悤�ɂ���

	if(m_f == true)//�e�����Ă�󋵂Ȃ�
	{
		m_gauge_time-=2;//�������˃J�E���g��i�߂�
						
		if(m_gauge_time < 0)//0�����ɂȂ�΂����O�ɂ���
			m_gauge_time = 0;
	}

	Block_Pos_Save();//�e�̐����\��n�̕ۑ�

	//��l���@�̒e�۔���
	if(Input::GetVKey(VK_LEFT)==true )//���������ꂽ��
	{
		//�u���b�N���Ƃ܂��Ă��āA����������Ă��Ȃ��ꍇ
		if( m_f == true && m_push_f == true)
		{
			Shot();//�e���������̊֐����Ăт���
			m_push_f = false;//�������j�~�t���O���I�t�ɂ���
		}
	}
	else
	{
		m_push_f = true;//�������j�~�t���O���I���ɂ���
	}

	//�������˃V�X�e��-----------------------------------
	if(m_f == true)//�e�����Ă�󋵂Ȃ�
	{					
		if( m_gauge_time == 0)//�J�E���g��0�ɂȂ�΋����Ŕ���
		{
			Shot();//�e���������̊֐����Ăт���
		}
	}
	//---------------------------------------------------
				
	//��l���@�̈ړ��x�N�g���̏�����
	m_vx=0.0f;
	m_vy=0.0f;

	//�L�[�̓��͕����Ƀx�N�g���̑��x�������
	if(Input::GetVKey(VK_UP)==true)
	{
		if(m_up==true)
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
		m_up = true;
	}
				
	//�A�Ńo�O���p
	if(Input::GetVKey(VK_UP)!=true)
	{
		if(Input::GetVKey(VK_DOWN)==true)//�@���������ꂽ�Ƃ�
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
		else //���������ꂽ�Ƃ�
		{
			m_down = true;
		}
	}//�A�Ńo�O����@�����

	if(Input::GetVKey(VK_RIGHT)==true)
	{
		Revolution();//��]�����̊֐����Ăяo��
		m_rf=false;
	}
	else 
	{
		m_rf=true;
	}
	
	//�ړ��x�N�g�������W�ɉ��Z����
	m_x+=m_vx;
	m_y+=m_vy;
}


//�h���[
void CObjHero_R::Draw()
{
	//�`��J���[���@R=RED G=Green B=Blue A=alpha(���ߏ��)
	float c[4]={1.0f,1.0f,1.0f,1.0f};//�ʏ�
	float c1[4]={1.0f,1.0f,1.0f,0.5f};//�u���b�N�ʒu�\���p
	float str_c[4]={0.0f,0.0f,0.0f,1.0f};//�����\���p

	RECT_F src;//�`�挳�̐؂���ʒu
	RECT_F dst;//�`���̕\���ʒu

	//�X�^�[�g�܂ł̃J�E���g���I����Ă����
	if(m_count_time>=270)
	{

//�@�̂̕\��---------------------------------------------------
		
		//�؂���ʒu�̐ݒ�
		RectSet(1.0f,32.0f,64.0f,31.0f,src);
		
		//�\���ʒu�̐ݒ�
		RectSet(0.0f+m_y,60.0f+m_x,0.0f+m_x,60.0f+m_y,dst);

		//10�Ԗڂɓo�^�����O���t�B�b�N�̂�src.dst.c�̏������ɕ`��
		Draw::Draw(10,&src,&dst,c,0.0f);
//----------------------------------------------------------------

//���ז��̐���\��------------------------------------------
	
	//�؂���ʒu���Z�b�g����
	RectSet(0.0f,0.0f,32.0f,32.0f,src);
		
	//�`��ʒu���Z�b�g����
	RectSet( 20.0f ,WINDOW_SIZE_W-(50.0f + BLOCK_SIZE*4) ,
		WINDOW_SIZE_W-(50.0f + BLOCK_SIZE*3) , 20.0f + BLOCK_SIZE , dst);

	//10�Ԗڂɓo�^�����O���t�B�b�N�̂�src.dst.c�̏������ɕ`��
	Draw::Draw(6,&src,&dst,c,0.0f);
	
	//������p�ӂ��ĕ\������
	wchar_t str[128];
	swprintf_s(str,L"%d",ojm_num);

	Font::StrDraw((wchar_t*)L"x",WINDOW_SIZE_W-(50.0f + BLOCK_SIZE*3),20.0f,BLOCK_SIZE,str_c);
	Font::StrDraw(str,WINDOW_SIZE_W-(50.0f + BLOCK_SIZE*3)+30.0f,20.0f,BLOCK_SIZE,str_c);

//----------------------------------------------------------

//�Q�[�W----------------------------------------------------

		//�Q�[�W�p�w�i-------------------

		//�؂���ʒu�Z�b�g �D�F
		RectSet(0.0f,401.0f,402.0f,99.0f,src);
		//�`��ʒu���Z�b�g
		RectSet(445.0f,960.0f,950.0f-360,485.0f,dst);
		//�`�悷��
		Draw::Draw(15,&src,&dst,c,0.0f);

		//-------------------------

		//�؂���ʒu�Z�b�g ���F
		RectSet(0.0f,100.0f,101.0f,99.0f,src);
		//�`��ʒu���Z�b�g
		RectSet(450.0f,955.0f,955.0f-360.0f,480.0f,dst);
		//�`�悷��
		Draw::Draw(15,&src,&dst,c,0.0f);

		//�w�i�����----------------------

		//�Q�[�W�{��----------------------

		//�؂���ʒu
		RectSet(0.0f,1.0f,2.0f,99.0f,src);

		
		//�`��ʒu
		RectSet(450.0f,955.0f,955.0f- m_gauge_time,480.0f,dst);

		Draw::Draw(15,&src,&dst,c,0.0f);//�`��

//�Q�[�W�����-----------------------------------------------------------

		//�؂���ʒu�̐ݒ�
		RectSet(0.0f,0.0f,64.0f,64.0f,src);
		
//�u���b�N�̐����\��n�̕\��---------------------------------------------

		for(int i=0;i<2;i++)
		{
			//�\���ʒu�̐ݒ�
			RectSet(80.0f+m_shot_y[i]*BLOCK_SIZE,50.0f+m_shot_x[i]*BLOCK_SIZE,
				50.0f+m_shot_x[i]*BLOCK_SIZE+BLOCK_SIZE,80.0f+m_shot_y[i]*BLOCK_SIZE+BLOCK_SIZE,dst);
			
			Draw::Draw(m_npc[ (m_bullet_count+i)%4 ],&src,&dst,c1,0.0f);//�`��
		}

//�u���b�N�̐����\��n�����-----------------------------------------------

//��̃u���b�N�\��----------------------------------------------------------
		
	//1��̂Q��------------------------------------
	
		//�\���ʒu�̐ݒ�
		RectSet(m_senter.y-m_drow.y,m_senter.x-m_drow.x-6,
			m_senter.x-m_drow.x-6+BLOCK_SIZE,m_senter.y-m_drow.y+BLOCK_SIZE,dst);//�`��

		Draw::Draw(m_npc[m_bullet_count],&src,&dst,c,0.0f);//�`��
	
		//�`��ʒu��ݒ�
		RectSet(m_senter.y+m_drow.y-BLOCK_SIZE,m_senter.x+m_drow.x-6-BLOCK_SIZE,
			m_senter.x+m_drow.x-6,m_senter.y+m_drow.y,dst);
	
		Draw::Draw(m_npc[(m_bullet_count+1)%4],&src,&dst,c,0.0f);//�`��
	
	//2���2��-----------------------------------------
		//�؂���ʒu�̐ݒ�

		//�`��ʒu�̐ݒ�
		RectSet(m_senter.y,m_senter.x+17-BLOCK_SIZE*2-BLOCK_SIZE/2-4,
			m_senter.x+17-BLOCK_SIZE*2-BLOCK_SIZE/2-4+BLOCK_SIZE-20,m_senter.y+BLOCK_SIZE-20,dst);
	
		Draw::Draw(m_npc[(m_bullet_count+2)%4],&src,&dst,c,0.0f);//�`��
	
		//�\��
		//�`��ʒu
		RectSet(m_senter.y+BLOCK_SIZE-20 ,m_senter.x+17-BLOCK_SIZE*2-BLOCK_SIZE/2-4,
			m_senter.x+17-BLOCK_SIZE*2-BLOCK_SIZE/2-4+BLOCK_SIZE-20,m_senter.y+BLOCK_SIZE-20+BLOCK_SIZE-20,dst);

		Draw::Draw(m_npc[(m_bullet_count+3)%4],&src,&dst,c,0.0f);//�`��

//��̃u���b�N�\��----------------------------------------------------------

	}
}

//�e�����֐�
void CObjHero_R::Shot()
{
	//�}�b�v�I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);
		
	Block_Pos_Save();//�e�̐����\��n�̕ۑ�

	//���ז��u���b�N�Ƃ̏d��������邽�߂̃`�F�b�N-----------------------------------------------------------------
	bool check,check2;
	check = (obj->ReturnNum(m_shot_x[0],m_shot_y[0]) == 99 );//1�ڂ̃u���b�N������\��̈ʒu���󔒂��ǂ������ׂ�
	check2= (obj->ReturnNum(m_shot_x[1],m_shot_y[1]) == 99 );//2�ڂ̃u���b�N������\��̈ʒu���󔒂��ǂ������ׂ�
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

//�u���b�N����]������֐�
void CObjHero_R::Revolution()
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
	}
}

//�e�̐����\��n�̕ۑ�
void CObjHero_R::Block_Pos_Save()
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
			m_shot_x[0]=19;
			m_shot_y[0]=t;
			//�����̃u���b�N�̈ʒu���L��
			m_shot_x[1]=19;
			m_shot_y[1]=t+1;
		}
		else 
		{
			//�����̃u���b�N�̈ʒu���L��
			m_shot_x[0]=18;
			m_shot_y[0]=t;
			//�E���̃u���b�N�̈ʒu���L��
			m_shot_x[1]=19;
			m_shot_y[1]=t;
		}
}
