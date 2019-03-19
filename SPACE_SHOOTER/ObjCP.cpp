//�g�p����w�b�_�[�t�@�C��
#include <stdlib.h>
#include <time.h>
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"
#include "ObjCP.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//������
void CObjCP::Init()
{
	//�ʒu
	m_Pos.x = WINDOW_SIZE_W - 54;
	m_Pos.y = WINDOW_SIZE_H / 3.5f;

	//m_f=true;

	//�ړ�
	m_Move.x = 0.0f;
	m_Move.y = 0.0f;

	//�ړ��̐���
	m_MoveCheck = 3;

	//��]
	m_RotNum = 0;

	m_bRot = true;

	//���ˉ�
	m_BulletCount = 0;

	//�ړ������t���O
	m_bMove = true;

	//�����_������������(0-6)
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		m_Npc[i] = rand() % 6;
	}

	//�u���b�N���m�̒��ԓ_�����߂�
	m_Senter.x = WINDOW_SIZE_W - (BLOCK_SIZE + (BLOCK_SIZE / 2));
	m_Senter.y = (WINDOW_SIZE_H - 8.0f) - (BLOCK_SIZE * 2);

	//m_senter�ƕ`��̊�_�i���ォ�E���j�Ƃ̍��i��Βl�j
	m_Drow.x = BLOCK_SIZE / 2;
	m_Drow.y = BLOCK_SIZE;

	//�e�����ʒu�̕ۑ��p
	m_Shot[0].x = -1;
	m_Shot[0].y = -1;
	m_Shot[1].x = -1;
	m_Shot[1].y = -1;

	//�ړ��̐���t���O������
	m_bDown = true;
	m_bUp = true;

	//�X�^�[�g����
	m_Time = 0;

	//�Q�[���I�[�o�[�I�u�W�F�N�g�̗L���`�F�b�N
	m_bEnd = false;

	//�Q�[�W�p���������ː���p
	m_GaugeTime = 360;

	//���ז��u���b�N���~�炷��
	m_OjmNum = 0;

	//���ː���
	m_ShootTime = 360; 
	
	//AI������
	AiInit();

	//�`��J���[
	ColorSet(m_fNomalColor, 1.0f, 1.0f, 1.0f, 1.0f);
	ColorSet(m_fPreBlockColor, 1.0f, 1.0f, 1.0f, 0.5f);
	ColorSet(m_fFontColor, 0.0f, 0.0f, 0.0f, 1.0f);

}

//AI�֘A�̏��̏�����
void CObjCP::AiInit()
{
	m_DeleteCount = 0;
	for (int i = 0; i < DELETE_INFO_MAX; i++)
	{
		DeleteInfo[i].Pos.x = -1;
		DeleteInfo[i].Pos.y = -1;
		DeleteInfo[i].Num = -1;
		DeleteInfo[i].Rot = -1;
	}
}


//�A�N�V����
void CObjCP::Action()
{
	//�J�E���^�X�V
	m_Time++;
	if(m_Time>=10000)
		m_Time=270;

	//Ai�̏�����
	AiInit();
	
	//�Q�[���I�[�o�[�Ȃ炱���ŏI���
	if( m_bEnd == true) return;
	
	//�}�b�v�I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);
	
	//�X�^�[�g�܂ł̃J�E���g
	if(m_Time < 270) return;
			
	//�Q�[�W��MAX�ɂȂ������ɂ��ז��������K�v�Ȃ�
	if(m_GaugeTime==360 && m_OjmNum != 0)
	{
		//���w�̃u���b�N�S�Ă��Ƃ܂��Ă����΂��ז�����
		if( obj->ShotCheck(false) ==true)
		{
			obj->CreateIntervention(m_OjmNum,false);
			m_OjmNum=0;
			
			return;
		}
	}
	
	//�ړ��A��]�A�e��������������֐�
	ShotMove();
}

//�ړ��A��]�A�e�̔��˂�����֐�
void CObjCP::ShotMove()
{
	//�}�b�v�I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	//5�t���[�����ɉ�]�ƈړ����ł���悤�ɂ���
	if(m_Time % 5 == 0)
	{
		m_bRot  = true;
		m_bMove = true;
	}

	m_DeleteCount=0;
	
	//�����̃u���b�N���Ƃ܂��Ă���ꍇ
	if( obj->ShotCheck(false) ==true)
	{
		m_ShootTime-=2;

		if(m_ShootTime <0)
			m_ShootTime =0;
	}

	//�S�Ă̌����ŏ����邩�ǂ����̃`�F�b�N������
	obj->AiDeleteCheck_H(m_Npc[m_BulletCount], m_Npc[m_BulletCount+1],0);
	obj->AiDeleteCheck_W(m_Npc[m_BulletCount], m_Npc[m_BulletCount+1],1);
	obj->AiDeleteCheck_H(m_Npc[m_BulletCount], m_Npc[m_BulletCount + 1], 2);
	obj->AiDeleteCheck_W(m_Npc[m_BulletCount], m_Npc[m_BulletCount + 1], 3);

	//���˃��~�b�g�ňʒu�����܂��Ă��Ȃ��Ȃ�
	//��ԓ����Ŏ~�܂�ʒu���烉���_���łƂ肾��
	if(m_ShootTime ==0 && DeleteInfo[0].Pos.y == -1)
	{
		DeleteInfo[0].Pos.y = obj->InSideCheck();
	}
				
	//�����̃u���b�N���Ƃ܂��Ă���ꍇ
	if( obj->ShotCheck(false) ==true)
	{
		//������ʒu������΂���
		if(DeleteInfo[0].Pos.y!=-1)
		{
			//�����ꏊ�ɂȂ����ꍇ
			if(DeleteInfo[0].Pos.y == m_MoveCheck)
			{
				//�u���b�N�̉�]�����Ȃ�
				if(m_RotNum != DeleteInfo[0].Rot)
				{
					Shot();//����
					
					//���˂܂ł̎��Ԃ�������	
					m_ShootTime = 360; 
					
					//��]����������
					m_RotNum=0;
				}
				else
				{
					Revolution();//�u���b�N����]������		
				}
			}
		
			//y��艺�Ȃ��Ɉړ�
			if(DeleteInfo[0].Pos.y < m_MoveCheck)
			{
				m_MoveCheck--;
				if (m_MoveCheck < 0)
					m_MoveCheck = 0;

				m_Pos.y += -BLOCK_SIZE;
				m_bMove=false;	
			}
			//y����Ȃ牺�Ɉړ�
			else
			{
				m_MoveCheck++;
				if (m_MoveCheck > 6)
					m_MoveCheck = 6;

				m_Pos.y += BLOCK_SIZE;
				m_bMove =false;
			}
		}
	}
}


//�`��
void CObjCP::Draw()
{
	//�X�^�[�g�܂ł̃J�E���g���I����Ă����
	if(m_Time>=270)
	{
		//�@�̂̕`��
		AircraftDraw();
		
		//���ז��̐���\��
		OjmNumDraw();

		//�Q�[�W�`��
		GaugeDraw();

		//��̃u���b�N�`��
		AfterBloackDraw();
	}
}

//�@�̂̕`��
void CObjCP::AircraftDraw()
{
	//�؂���ʒu�̐ݒ�
	RectSet(1.0f, 32.0f, 64.0f, 31.0f, m_Src);

	//�\���ʒu�̐ݒ�
	RectSet(m_Pos.y, 60.0f + m_Pos.x,m_Pos.x, 60.0f + m_Pos.y, m_Dst);

	//�`��
	Draw::Draw(10, &m_Src, &m_Dst, m_fNomalColor, 0.0f);
}

//���ז��̐���`��
void CObjCP::OjmNumDraw()
{
	//�؂���ʒu���Z�b�g����
	RectSet(0.0f, 0.0f, 32.0f, 32.0f, m_Src);

	//�`��ʒu���Z�b�g����
	RectSet(20.0f, WINDOW_SIZE_W - (50.0f + BLOCK_SIZE * 4),
		WINDOW_SIZE_W - (50.0f + BLOCK_SIZE * 3), 20.0f + BLOCK_SIZE, m_Dst);

	//���ז��u���b�N�`��
	Draw::Draw(6, &m_Src, &m_Dst, m_fNomalColor, 0.0f);

	//������p��
	wchar_t str[128];
	swprintf_s(str, L"%d", m_OjmNum);

	//�����`��
	Font::StrDraw((wchar_t*)L"x", WINDOW_SIZE_W - (50.0f + BLOCK_SIZE * 3), 20.0f, BLOCK_SIZE, m_fFontColor);
	Font::StrDraw(str, WINDOW_SIZE_W - (50.0f + BLOCK_SIZE * 3) + 30.0f, 20.0f, BLOCK_SIZE, m_fFontColor);
}

//�Q�[�W�`��
void CObjCP::GaugeDraw()
{
//�Q�[�W�p�w�i-------------------
	//�؂���ʒu�Z�b�g �D�F
	RectSet(0.0f, 401.0f, 402.0f, 99.0f, m_Src);
	
	//�`��ʒu���Z�b�g
	RectSet(445.0f, 960.0f, 950.0f - 360, 485.0f, m_Dst);
	
	//�`�悷��
	Draw::Draw(15, &m_Src, &m_Dst,m_fNomalColor, 0.0f);
	
	//�؂���ʒu�Z�b�g ���F
	RectSet(0.0f, 100.0f, 101.0f, 99.0f, m_Src);
	
	//�`��ʒu���Z�b�g
	RectSet(450.0f, 955.0f, 955.0f - 360.0f, 480.0f, m_Dst);
	
	//�`�悷��
	Draw::Draw(15, &m_Src, &m_Dst, m_fNomalColor, 0.0f);
//�w�i�����----------------------

//�Q�[�W�{��----------------------
	//�؂���ʒu
	RectSet(0.0f, 1.0f, 2.0f, 99.0f, m_Src);

	//�`��ʒu
	RectSet(450.0f, 955.0f, 955.0f - m_ShootTime, 480.0f, m_Dst);
	
	//�`��
	Draw::Draw(15, &m_Src, &m_Dst, m_fNomalColor, 0.0f);
//�Q�[�W�����-----------------------------------------------------------
}

//��̃u���b�N�`��
void CObjCP::AfterBloackDraw()
{
//1��̂Q��------------------------------------
	//�؂���ʒu�̐ݒ�
	RectSet(0.0f, 0.0f, 64.0f, 64.0f, m_Src);

	//�\���ʒu�̐ݒ�
	RectSet(m_Senter.y - m_Drow.y, m_Senter.x - m_Drow.x - 6,
		m_Senter.x - m_Drow.x - 6 + BLOCK_SIZE, m_Senter.y - m_Drow.y + BLOCK_SIZE, m_Dst);

	//�`��
	Draw::Draw(m_Npc[m_BulletCount], &m_Src, &m_Dst, m_fNomalColor, 0.0f);

	//�`��ʒu��ݒ�
	RectSet(m_Senter.y + m_Drow.y - BLOCK_SIZE, m_Senter.x + m_Drow.x - 6 - BLOCK_SIZE,
		m_Senter.x + m_Drow.x - 6, m_Senter.y + m_Drow.y, m_Dst);

	//�`��
	Draw::Draw(m_Npc[(m_BulletCount + 1) % 4], &m_Src, &m_Dst, m_fNomalColor, 0.0f);

//2���2��-----------------------------------------
	
	//�`��ʒu�̐ݒ�
	RectSet(m_Senter.y, m_Senter.x + 17 - BLOCK_SIZE * 2 - BLOCK_SIZE / 2 - 4,
		m_Senter.x + 17 - BLOCK_SIZE * 2 - BLOCK_SIZE / 2 - 4 + BLOCK_SIZE - 20, m_Senter.y + BLOCK_SIZE - 20, m_Dst);

	//�`��
	Draw::Draw(m_Npc[(m_BulletCount + 2) % 4], &m_Src, &m_Dst, m_fNomalColor, 0.0f);

	//�`��ʒu�̐ݒ�
	RectSet(m_Senter.y + BLOCK_SIZE - 20, m_Senter.x + 17 - BLOCK_SIZE * 2 - BLOCK_SIZE / 2 - 4,
		m_Senter.x + 17 - BLOCK_SIZE * 2 - BLOCK_SIZE / 2 - 4 + BLOCK_SIZE - 20, m_Senter.y + BLOCK_SIZE - 20 + BLOCK_SIZE - 20, m_Dst);

	//�`��
	Draw::Draw(m_Npc[(m_BulletCount + 3) % 4], &m_Src, &m_Dst, m_fNomalColor, 0.0f);
}

//�e�����֐�
void CObjCP::Shot()
{
	//�}�b�v�I�u�W�F�N�g�̌Ăяo��
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);
	
	//�e�̐����\��n�̕ۑ�
	BlockPosSave();

	//�u���b�N������ʒu�����ז��u���b�N�Ƃ̏d�����Ȃ����̃`�F�b�N
	bool check,check2;
	check = (obj->Return_Num(m_Shot[0].x,m_Shot[0].y) == 99 );
	check2= (obj->Return_Num(m_Shot[1].x,m_Shot[1].y) == 99 );
	
	//�Q�̃u���b�N�������ɑłĂ�󋵂Ȃ�
	if(check==true && check2==true)
	{
		//2�̃u���b�N����
		for(int i=0;i<2;i++)
		{
			//�L���������z��̈ʒu�̗v�f��ύX����
			obj->Enter(m_Shot[i].x,m_Shot[i].y,m_Npc[m_BulletCount]);

			//�g�p�����ʒu�̃����_�����̍X�V
			m_Npc[(m_BulletCount++)%4]=rand() % 6;

			//�I�u�W�F�N�g�����t���O���I���ɂ���
			obj->FlagOn(m_Shot[i].x,m_Shot[i].y);
		}
	
		//��]���̃��Z�b�g--------------------------
		m_RotNum = 0;
		m_Drow.x = BLOCK_SIZE/2;
		m_Drow.y = BLOCK_SIZE;
	
		//�J�E���^�X�V(0-3���J��Ԃ��j
		m_BulletCount %= 4;

		//�Q�[�W�̏�����
		m_GaugeTime = 360;
	}		
}

//�u���b�N����]������֐�
void CObjCP::Revolution()
{
	if(m_bRot==true)
	{
		//��]
		m_RotNum++;
		if(m_RotNum==4)
			m_RotNum=0;

		//��_�̒����i���Ƃ��̓���ւ��j
		float num	= m_Drow.x;
		m_Drow.x	= m_Drow.y;
		m_Drow.y	= num;
			
		//��]��������ڂȂ�
		if(m_RotNum ==1|| m_RotNum ==3)
		{
			//��������ւ�
			int tmp=m_Npc[m_BulletCount];
			m_Npc[m_BulletCount]=m_Npc[(m_BulletCount+1)%4];
			m_Npc[(m_BulletCount+1)%4]=tmp;
		}
	}
}

//�e�̐����\��n�̕ۑ�
void CObjCP::BlockPosSave()
{
	//�v���C���[�̒��S�ʒu����u���b�N������ׂ��z��̗v�f�������߂�
	int index = m_MoveCheck;
			
	//�u���b�N���c���i������]�j�Ȃ�
	if(m_RotNum%2==0)
	{	
		//��Ԃ����̒i�őłƂ��Ƃ����ꍇ�͂ЂƂ���ɂ��炷
		if(index==6)
			index--;

		//�㑤�̃u���b�N�̈ʒu���L��
		m_Shot[0].x=19;
		m_Shot[0].y=index;
		//�����̃u���b�N�̈ʒu���L��
		m_Shot[1].x = 19;
		m_Shot[1].y = index+1;
	}
	else 
	{

		//�����̃u���b�N�̈ʒu���L��
		m_Shot[0].x=18;
		m_Shot[0].y=index;
		
		//�E���̃u���b�N�̈ʒu���L��
		m_Shot[1].x=19;
		m_Shot[1].y=index;
	}
}

//�u���b�N�̏�������Z�b�g����֐�
void CObjCP::SetDeletePoint(Point Pos,int Num,int Rot)
{
	DeleteInfo[m_DeleteCount].Pos = Pos;	//���W������
	DeleteInfo[m_DeleteCount].Num = Num;	//�����鐔���Z�b�g
	DeleteInfo[m_DeleteCount].Rot = Rot;	//��]�����Z�b�g
	
	//�J�E���^�X�V
	m_DeleteCount++;
	if(m_DeleteCount >= DELETE_INFO_MAX)
		m_DeleteCount =0;
}
