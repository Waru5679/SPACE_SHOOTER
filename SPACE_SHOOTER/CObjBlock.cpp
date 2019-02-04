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
#include "CObjBlock.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBlock::CObjBlock(float x,float y,int color,bool lr,bool sk )
{
	m_px=x;
	m_py=y;
	m_color=color;
	m_lr=lr;
	m_skip=sk;
}

//�C�j�V�����C�Y
void CObjBlock::Init()
{
	if(m_lr==true)
	{
		//���@�̂�����ꂽ�u���b�N
		m_vx=1.0f;
	}
	else
	{
		//�E�@�̂�����ꂽ�u���b�N
		m_vx=-1.0f;
	}

	srand(time(NULL)); // �����_������������

	m_time=0;//�^�C���̏�����
	
	m_stop_flag=false;//�X�g�b�v�t���O

	m_Processing_flag=false;//��������Ԃɂ���

	//���ŏ����֘A�̏�����------------
	m_eff.m_top	  = 32;
	m_eff.m_left  =  0;
	m_eff.m_right = 32;
	m_eff.m_bottom= 64;
	m_ani=0;
	m_ani_time=0;
	m_del=false;
	//--------------------------------

	m_se=true;//SE�p�̃t���O�̏�����
	
	m_gemeover_check=false;//�Q�[���I�[�o�[�`�F�b�N�t���O�̏�����

	//�f�o�b�O�p�@����pHitBox���쐬
	Hits::SetHitBox(this,m_px*BLOCK_SIZE+60.0f,m_py*BLOCK_SIZE+80.0f,BLOCK_SIZE/2,BLOCK_SIZE/2,ELEMENT_NULL,OBJ_BLOCK,1);
	
	move_check = true;
}
//�A�N�V����
void CObjBlock::Action()
{
	//���C���I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	//�Q�[���I�[�o�[�I�u�W�F�N�g�̗L���𒲂ׂ�
	m_gemeover_check = obj->ReturnFlag();

	//�Q�[���I�[�o�[�I�u�W�F�N�g�������
	if(m_gemeover_check == true)	return ;
	
	m_time++;
	
	if(m_time>1000)//1000�𒴂��Ȃ��悤�ɂ���
		m_time=0;

	//Block����~�����Ƃ��i1��̂݁j--------------------------------
	//�ړ������̌ォ�炱���Ɉړ��������i2017-06-23�j
	if(m_stop_flag==true)
	{
		if(m_Processing_flag==false)//���������s����Ă��Ȃ��Ȃ�
		{
			Disappear();//���ŏ����֐��̌Ăяo���ȂǁA�u���b�N���Ƃ܂����Ƃ��̏���������֐�
		}
	}
	//-----------------------------------------------------------------------
		
	//���ŏ���-----------------------------------------
	if(obj->Return_Num(m_px,m_py)==98)//98�������Ă����
	{
		m_del=true; //���ŏ����̃t���O�𗧂Ă�
	}

	if(m_del==true)//���ŏ����̃t���O�������Ă����
	{
		DeleteAnimetion();//���łƃA�j���[�V�����̏���������
		return;
	}
	//---------------------------------------
		
	Check();//�ړ��ł��邩�`�F�b�N����	

	if(move_check == true)//�ړ��\�Ȃ�
	{
		//10f��1�񏈗�����-----------------
		if(m_time%10==0)
		{
			Move();//�ړ�����������
		}
		//------------------------------------
		m_se=true;//se�Ǘ��t���O�I��

		Check();//���Ɉړ��ł��邩���ׂ�(��d�`�F�b�N)

		if( move_check == true )//���Ɉړ��ł��
		{
			m_stop_flag = false;//�X�g�b�v�t���O���I�t�ɂ���
		}
		else
		{
			m_stop_flag = true;//���g�̃X�g�b�v�t���O���I���ɂ���
		}					
	}
	else//�ړ��s��
	{
		if(m_se==true)
		{
			Audio::Start(2);//SE��炷
			m_se=false;//�t���O���I�t�ɂ���
		}
		m_stop_flag = true;
	}			
	
	//�}�b�v�\���̂̍X�V-----------------------------
	//���ŏ������łȂ����
	if(m_del==false)
		obj->Enter(m_px,m_py,m_color);//�ړ���̈ʒu�Ɏ����̐F������
	
	//�X�g�b�v�t���O�X�V
	obj->Enter_Stop_flag(m_px,m_py,m_stop_flag);
	//�����t���O�X�V
	obj->Processflag(m_px,m_py,m_Processing_flag);
	//-------------------------------------------------

	//hitbox�̍X�V
	CHitBox* hit=Hits::GetHitBox(this); 
	hit->SetPos(m_px*BLOCK_SIZE+60.0f,m_py*BLOCK_SIZE+80.0f);
}


//�h���[
void CObjBlock::Draw()
{
	//�`��J���[���
	float c[4]={1.0f,1.0f,1.0f,1.0f};

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu���Z�b�g����
	RectSet(0.0f,0.0f,64.0f,64.0f,src);
	
	//�`��ʒu���Z�b�g����
	RectSet( 80.0f + m_py * BLOCK_SIZE ,50.0f + m_px * BLOCK_SIZE ,
		50.0f + m_px * BLOCK_SIZE + BLOCK_SIZE , 80.0f + m_py * BLOCK_SIZE + BLOCK_SIZE , dst);

	//�u���b�N�̕`��
	Draw::Draw(m_color,&src,&dst,c,0.0f);

	if(m_del==true)//���������t���O���I���Ȃ�
	{
		//���j�A�j���[�V��������
		Draw::Draw(10,&m_eff,&dst,c,0.0f);
	}
}

//�ړ������̊֐�
void CObjBlock::Move()
{
	//���C���I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	if(m_lr==true)
	{
		//��

		obj->Enter(m_px,m_py,99);//�ړ��O�̈ʒu��99�ɂ���
		obj->StopFlag_OFF(m_px,m_py);//�ړ��O�̈ʒu�̃X�g�b�v�t���O���I�t�ɂ���
				
		m_px+=m_vx;//�ʒu�̍X�V
	}
	else
	{
		//�E

		if(m_skip!=true )//�X�L�b�v�u���b�N(�E���ŉ������ɑł����ꍇ�̍����ɗ���u���b�N�j�łȂ����
		{	
			obj->Enter(m_px,m_py,99);//�ړ��O�̈ʒu��99�ɂ���
		}
		obj->StopFlag_OFF(m_px,m_py);//�ړ��O�̈ʒu�̃X�g�b�v�t���O���I�t�ɂ���
				
		m_px+=m_vx;//�ʒu�̍X�V
	}
}

//�ړ��ł��邩�̃`�F�b�N
void CObjBlock::Check()
{
	if(m_px<9||m_px>10)//�������C���̂����ׂł͂Ȃ��Ȃ�
	{
		move_check=MoveCheck(m_px+m_vx,m_py);//�ړ���̊m�F
	}
	else//���łɒ����̈ʒu�ɂ���ꍇ
	{
		move_check = false;//�ړ��s��
	}
}

//�ړ���̃`�F�b�N�֐�
//����1�F���ׂ�ʒu��x���W�im_px+m_vx�j
//����2�F���ׂ�ʒu��y���W
//�ړ��\�Ȃ�true���A�����Ȃ�false��Ԃ�
bool CObjBlock::MoveCheck(int x,int y)
{
	int  num_check;//���l�̊m�F
	bool stop_check;//�X�g�b�v�t���O�̊m�F
			
	//���C���I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	num_check  = obj->Return_Num(x,y);//���̐��������Ă���
	stop_check = obj->Return_Stop_Flag(x,y);//���̃X�g�b�v�t���O�������Ă���

	//������悪�J���[�u���b�N�Ȃ�i�������6�܂ށj
	if( (0 <= num_check ) && ( num_check <= 6 ) )
	{
		if( stop_check == false )//�X�g�b�v�t���O���I�t�Ȃ�
		{
			return true;//�ړ��\
		}
		else
		{
			return false;//�ړ��s��
		}
	}
	else 
	{
		if( num_check == 98 )//���ŏ�����
		{
			return false;
		}
		else if( num_check == 99 )//��
		{
			return true;
		}
	}
}

//���ŏ����֐��̌Ăяo���ȂǁA�u���b�N���Ƃ܂����Ƃ��̏���������֐�
void CObjBlock::Disappear()
{			
	//���C���I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	bool stop_check_flag = obj->StopCheck(m_py,m_lr);//���w�̂��̒i���S�ĂƂ܂��Ă��邩���וۑ�����
	
	//���̒i�̎��w���S�Ď~�܂��Ă���Ȃ�
	if( stop_check_flag == true)// ; ->  2017-06-26
	{
		switch(m_lr)
		{
			case true://�����v���[���[
			{
				Left_Dis();//�����̏��ŏ������Ăяo���O�̒���������֐�
			}
			break;

			case false://�E���v���[���[
			{
				Right_Dis();//�E���̏��ŏ������Ăяo���O�̒���������֐�
			}
			break;
		}
	}
}


//�����̏��ŏ������Ăяo���O�̒���������֐�
void CObjBlock::Left_Dis()
{
	//���C���I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	int n=obj->Return_Num(m_px-1,m_py);//����̃}�X�̐��l��ۑ�����
	
	static int lplayerblockcheck=0;
	bool m_wh;//�u���b�N�̌�����ۑ��@true:���@false:�c
	
	m_wh = CheckWH(n,lplayerblockcheck);//�u���b�N�̌����𒲂ׂ�
	
	//�����ɉ����ď���������---------------------------------------------------
	if(m_wh == false)
	{
		//�c����
		obj->CheckMap(m_px,m_py,m_lr);//���ŏ����֐����Ăяo��	
		//�����ς݃t���O�𗧂Ă�
		m_Processing_flag=true;
	}
	else 
	{
		//������
		//��2�A�u���b�N�̃`�F�b�N 2017-05-26
		switch(lplayerblockcheck)
		{
			case 0://����
			{
				m_delete_check[0] = obj->BlockDeleteCheck( m_px		, m_py ,m_lr );//�����̏�����
				m_delete_check[1] = obj->BlockDeleteCheck( m_px - 1	, m_py ,m_lr );//�O���̏�����

				//�����̏������̕������� 
				if( m_delete_check[0]>m_delete_check[1] )
					obj->CheckMap( m_px , m_py , m_lr );//���ŏ����֐����Ăяo��				
							
				lplayerblockcheck=1;//static�ϐ����X�V

				//�����ς݃t���O�𗧂Ă�
				m_Processing_flag=true;								
			}
			break;
			case 1://�O��
			{
				m_delete_check[0] = obj->BlockDeleteCheck( m_px + 1 , m_py , m_lr );//�����̏�����
				m_delete_check[1] = obj->BlockDeleteCheck( m_px		, m_py , m_lr );//�O���̏�����

				//�O���̏������̕��������ꍇ �܂��́@�O���Ɠ����̏�����������(0�ȊO)�̏ꍇ
				if( ( m_delete_check[0] < m_delete_check[1] ) || ( m_delete_check[0] == m_delete_check[1] ) && m_delete_check[0] != 0 )
					obj->CheckMap( m_px , m_py , m_lr );//�ŏ����֐����Ăяo��
				
				lplayerblockcheck=0;//static�ϐ����X�V

				//�����ς݃t���O�𗧂Ă�
				m_Processing_flag=true;																
			}
			break;
		}
	}
	//-----------------------------------------------------------------------
}

//�E���̏��ŏ������Ăяo���O�̒���������֐�
void CObjBlock::Right_Dis()
{
	//���C���I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);
	
	// 2017-06-26 (m_px-1 -> m_px+1)
	int n=obj->Return_Num(m_px+1,m_py);//��E�̃}�X�̐��l���L������

	bool m_wh;//true�F���@false�F�c
	static int rplayerblockcheck=0;
	
	m_wh = CheckWH(n,rplayerblockcheck);//�u���b�N�̏�Ԃ��c�������ǂ������ׂ�	
		
	//�����ɉ����ď���������---------------------------------------------------------------------
	if(m_wh == false)
	{
		//�c����
		obj->CheckMap(m_px,m_py,m_lr);//���ŏ����֐����Ăяo��
		//�����ς݃t���O�𗧂Ă�
		m_Processing_flag=true;
	}
	else 
	{
		//������
		//��2�A�u���b�N�̃`�F�b�N 2017-05-26
		switch(rplayerblockcheck)
		{
			case 0://����
			{
				m_delete_check[0] = obj->BlockDeleteCheck( m_px		, m_py , m_lr );//�����̏�����
				m_delete_check[1] = obj->BlockDeleteCheck( m_px + 1 , m_py , m_lr );//�O���̏�����

				//�����̏������̕����O���̏�������葽���@
				if( m_delete_check[0] > m_delete_check[1] )
					obj->CheckMap( m_px , m_py , m_lr );//���ŏ����֐����Ăяo��				
				
				//�����ς݃t���O�𗧂Ă�
				m_Processing_flag=true;					

				rplayerblockcheck=1;//static�ϐ����X�V����
			}
			break;
			case 1://�O��
			{
				m_delete_check[0] = obj->BlockDeleteCheck( m_px - 1 , m_py , m_lr );//�����̏�����
				m_delete_check[1] = obj->BlockDeleteCheck( m_px		, m_py , m_lr );//�O���̏�����

				//�O���̏������̕������� �܂��́@������������(0�ȊO)�Ȃ�
				if( ( m_delete_check[0] < m_delete_check[1] ) || ( m_delete_check[0] == m_delete_check[1] ) && m_delete_check[0] != 0 )
					obj->CheckMap( m_px , m_py , m_lr );//���ŏ����֐����Ăяo��
				
				//�����ς݃t���O�𗧂Ă�
				m_Processing_flag=true;
				
				rplayerblockcheck=0;//static�ϐ����X�V����
			}
			break;
		}
	}
	//-------------------------------------------------------------------------
}

//�u���b�N�̌����𒲂ׂĕԂ��֐�
//����1�Fstatic�ϐ��������Ă���
//����2�F�P�O���̂����W�������Ă���
//�߂�l�F�@true�F���@false�F�c�@
bool CObjBlock::CheckWH(int n,int staticnum )
{
	//�u���b�N��static�ϐ����P�Ȃ�
	if( staticnum ==1)
	{
		return true;//��
	}
	else if( n >= 0 && n <=5 )//�P�O���Ƀu���b�N�������
	{
		return true;//��
	}
	else //����ȊO
	{
		return false;//�c
	}
}

//���Ł��A�j���[�V����������֐�
void CObjBlock::DeleteAnimetion()
{
	//���C���I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	//�A�j���[�V����RECT���
	RECT_F ani_src[4] = 
	{
		{ 32,  0, 32, 64},
		{ 32, 32, 64, 64},
		{ 32, 64, 96, 64},
		{ 32, 96,128, 64},
	};
	//�@05/26 14:04-------------------------------------
	m_ani_time++;
	//�A�j���[�V�����̃R�}�Ԋu����
	if(m_ani_time>2)
	{
		m_ani_time=0;
		m_ani++;			//�A�j���[�V�����̃R�}���P�i�߂�
				
		//���j�A�j���[�V�����I���ŃI�u�W�F�N�g�j��
		if(m_ani==4)
		{
			m_ani=0;
			Audio::Start(3);//�������Đ�
			m_del=false;
			obj->Enter(m_px,m_py,99);//���ŃA�j�����I���΋󔒂ɂ���
										//�������A�Z���̕\���́A�c���Ă���̂ŗv����
										//���̂��Ƃ́A�����Ńu���b�N�͈ړ������Ȃ�����
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
		else
		{		
			m_eff=ani_src[m_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT�����擾
		}
	}
}