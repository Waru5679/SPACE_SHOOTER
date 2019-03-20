//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjMain.h"

#include <stdlib.h>
#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMain::Init()
{
	//MAP�\���̂̏�����
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<20;j++)
		{
			m_map[i][j].Num = 99;
			m_map[i][j].BeforeNum = 99;
			m_map[i][j].StopTime = 0;
			m_map[i][j].ObjTime = 0;
			m_map[i][j].bCreate	= false;
			m_map[i][j].bStop = false;
			m_map[i][j].bProcess = true;
		}
	}

	//��������t���O������
	m_bLeftWin=false;
	m_bRightWin-false;

	//�X�^�[�g�J�E���g�_�E��
	m_CountTime=0;

	//�������傫���Ȃ鎞��
	m_FontBigTime=0;

	//�����L���O�p�^�C���̏�����
	m_Time = 0;

	//�Q�[���I�[�o�[�Ǘ�
	m_bGameOver = false;

	//AI�p
	for(int i=0;i<7;i++)
	{
		m_BlockStopPoint[i]=19;//�u���b�N�̎~�܂�ʒu
	}
}

//�A�N�V����
void CObjMain::Action()
{
	//�������I����Ă���΂Ȃɂ����Ȃ�
	if (m_bGameOver == true) return;

	m_CountTime++;

	//�X�^�[�g�̕\�����I����Ă����
	if (m_CountTime > 270)
	{
		//�����L���O�p�̃^�C���v��
		if ((m_CountTime - 270) % 60 == 0)
			m_Time++;				
	}

	//�q�[���[�I�u�W�F�N�g�̌Ăяo��
	CObjHero * obj_h =(CObjHero*)Objs ::GetObj(OBJ_HERO);		
	CObjHero_R * obj_hr =(CObjHero_R*)Objs ::GetObj(OBJ_HERO_R);
	
	//�}�b�v���X�V
	MapUpdate();

	//���s����
	m_bLeftWin=VictoryCheck(true);//��
	m_bRightWin=VictoryCheck(false);//�E
	
	if(m_bGameOver == false)
	{
		VictoryProcess(m_bCpBattle);//����������݂����Ă��邩���ׁA�������Ă���Ώ���������
	}
}

//�}�b�v�X�V
void CObjMain::MapUpdate()
{
	//Map���X�V
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			//�O��̏������Ɠ������l�������Ă����
			if (m_map[i][j].Num == m_map[i][j].BeforeNum)
				m_map[i][j].StopTime++;//�X�g�b�v�^�C���𑝂₷
			else
				m_map[i][j].StopTime = 0;//�X�g�b�v�^�C����0�ɖ߂�

			//�F�u���b�N�������Ă����
			if (m_map[i][j].Num < 6)
			{
				//�I�u�W�F�N�g�����t���O���I���Ȃ�
				if (m_map[i][j].bCreate == true)
				{
					//����ȃP�[�X�@�E�[ �������̂Ƃ�
					//18�Ԗڂ�19�Ԗڂɂ��u���b�N�������Ă���ꍇ�i�E���ŉ������ɂ������Ƃ�
					if (j == 18 && (m_map[i][19].Num < 6))
					{
						//�u���b�N�쐬
						CObjBlock* obj_b = new CObjBlock(j, i, m_map[i][j].Num, false, true);
						Objs::InsertObj(obj_b, OBJ_BLOCK, 10);

						m_map[i][j].bCreate = false;	//�I�u�W�F�N�g�����t���O���I�t�ɂ���
						m_map[i][j].bStop = false;	//�u���b�N�����ʒu�̃X�g�b�v�t���O���I�t�ɂ���
						m_map[i][j].ObjTime = 0;		//�I�u�W�F�N�g�����^�C�������Z�b�g����
					}
					//���ʂ̃P�[�X
					else
					{
						//�����p�̃u���b�N����
						if (j <= 9)
						{
							CObjBlock* obj_b = new CObjBlock(j, i, m_map[i][j].Num, true, false);
							Objs::InsertObj(obj_b, OBJ_BLOCK, 10);
						}
						//�E���p�̃u���b�N����
						else if (j >= 10)
						{
							CObjBlock* obj_b = new CObjBlock(j, i, m_map[i][j].Num, false, false);
							Objs::InsertObj(obj_b, OBJ_BLOCK, 10);
						}

						m_map[i][j].bCreate = false;//�I�u�W�F�N�g�����t���O���I�t�ɂ���
						m_map[i][j].bStop = false;	//�u���b�N�����ʒu�̃X�g�b�v�t���O���I�t�ɂ���
						m_map[i][j].ObjTime = 0;		//�I�u�W�F�N�g�����^�C�������Z�b�g����
					}
				}
			}
			//���ז��u���b�N
			if (m_map[i][j].Num == 6)
			{
				//�I�u�W�F�N�g�����t���O���I���Ȃ�
				if (m_map[i][j].bCreate == true)
				{
					//�����p�̃u���b�N����
					if (j <= 9)
					{
						CObjIntervention* obj_i = new CObjIntervention(j, i, true);
						Objs::InsertObj(obj_i, OBJ_INTERVENTION, 10);
					}
					//�E���p�̃u���b�N����
					else if (j >= 10)
					{
						CObjIntervention* obj_i = new CObjIntervention(j, i, false);
						Objs::InsertObj(obj_i, OBJ_INTERVENTION, 10);
					}

					m_map[i][j].bCreate = false;//�I�u�W�F�N�g�����t���O���I�t�ɂ���
					m_map[i][j].bStop = false;	//�u���b�N�����ʒu�̃X�g�b�v�t���O���I�t�ɂ���
					m_map[i][j].ObjTime = 0;	//�I�u�W�F�N�g�����^�C�������Z�b�g����
				}
			}
			//���ŃA�j���[�V�����@
			if (m_map[i][j].Num == 98)
			{
				//���ŏ����̔��肪�A�j���[�V�����̎��Ԃ�蒷���Ƃǂ܂��Ă�����//�󔒂ɂ��ǂ�
				if (m_map[i][j].StopTime >= 5)
					m_map[i][j].Num = 99;
			}
			//�� 99
			if (m_map[i][j].Num == 99)
			{
				//�����σt���O���I���ɂ���
				m_map[i][j].bProcess = true;
			}

			//�ԍ���ۑ�����
			m_map[i][j].BeforeNum = m_map[i][j].Num;

			//�I�u�W�F�N�g�̃^�C���X�V
			m_map[i][j].ObjTime++;
			if (m_map[i][j].ObjTime > 10000)
				m_map[i][j].ObjTime = 10;
		}
	}
}

//�h���[
void CObjMain::Draw()
{
	//�`��J���[���
	float c[4]={1.0f,1.0f,1.0f,1.0f};
	float start[4]={1.0f,1.0f,0.0f,1.0f};

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu
	
	wchar_t str[10];//0:���@1:�b

	//�X�^�[�g�̃J�E���g���I����Ă����
	if(m_CountTime>=270)
	{
		//�X�R�A�\��
		swprintf_s(str, L"%02d:%02d",m_Time/60, m_Time % 60);
		Font::StrDraw(str, 430.0f, 20.0f, 60.0f, c);

		//��������u���b�N�\��-----------
		for(int y=0;y<7;y++)
		{
			for(int x=0;x<20;x++)
			{
				//�\���ʒu�̐ݒ�
				RectSet(80.0f+y*BLOCK_SIZE,50.0f+x*BLOCK_SIZE,
					50.0f+x*BLOCK_SIZE+BLOCK_SIZE,80.0f+y*BLOCK_SIZE+BLOCK_SIZE,dst);
				
				//�g�\��
				if(x==9)
				{
					//���E�B���h�E
					//�؂���ʒu�̐ݒ�
					RectSet(46.0f,320.0f,320.0f+64.0f,46.0f+64.0f,src);
					
					Draw::Draw(9,&src,&dst,c,0.0f);//�`��
				}
				else if(x==10)
				{
					//���E�B���h�E
					//�؂���ʒu�̐ݒ�
					RectSet(46.0f,255.0f,255.0f+64.0f,46.0f+64.0f,src);
					
					Draw::Draw(9,&src,&dst,c,0.0f);//�`��
				}
				else if(m_map[y][x].Num==99)
				{
					//�����E�B���h�E
					//�؂���ʒu�̐ݒ�
					RectSet(111.0f,255.0f,255.0f+64.0f,111.0f+64.0f,src);
					
					Draw::Draw(9,&src,&dst,c,0.0f);//�`��
				}
			}
		}
	}

	//�؂���ʒu�̐ݒ�
	RectSet(0.0f,0.0f,256.0f,256.0f,src);

	//3
	if(m_CountTime<=70)
	{
		if(m_CountTime ==5)
			Audio::Start(9);//���ʉ�

		m_FontBigTime++;

		//font_big_time��������ɂ�ĕ\������鐔�����傫���Ȃ�
		//�`��ʒu�̐ݒ�
		RectSet(200-m_FontBigTime,420-m_FontBigTime,570+m_FontBigTime,400+ m_FontBigTime,dst);
		
		Draw::Draw(11,&src,&dst,c,0.0f);//�`��
		
	}

	//2
	if(m_CountTime>70&&m_CountTime<=140)
	{
		if(m_CountTime ==75)
			Audio::Start(9);//���ʉ�

		m_FontBigTime++;

		RectSet(200- m_FontBigTime,420- m_FontBigTime,570+ m_FontBigTime,400+ m_FontBigTime,dst);

		Draw::Draw(12,&src,&dst,c,0.0f);//�`��
	}

	//1
	if(m_CountTime>140&&m_CountTime<=210)
	{
		if(m_CountTime ==145)
			Audio::Start(9);//���ʉ�

		m_FontBigTime++;

		RectSet(200- m_FontBigTime,420- m_FontBigTime,570+ m_FontBigTime,400+ m_FontBigTime,dst);

		Draw::Draw(13,&src,&dst,c,0.0f);//�`��

	}

	//START
	if(m_CountTime>210&&m_CountTime<=260)
	{
		if(m_CountTime ==215)
			Audio::Start(10);//���ʉ�

		RectSet(100.0f,300.0f,700.0f,400.0f,dst);

		Draw::Draw(14,&src,&dst,start,0.0f);//�`��
	}

	//�J�E���g��70�����Ƃ��Ɍ��̃T�C�Y�ɖ߂�
	if(m_FontBigTime ==70)
		m_FontBigTime =0;
}

//�Ȃ����Ă���u���b�N�̐��𐔂��Ă�����Ȃ���ŏ���������֐�
//����1 :�v�f�ԍ�X
//����2 :�v�f�ԍ�Y
//����3 :���E�`�F�b�N�i�ǂ��瑤���痈�Ă�u���b�N���j
void CObjMain::CheckMap(int x, int y,bool lr)
{
	int pos[2];
	int number=0;	//�Ȃ����Ă���u���b�N�̐��J�E���g
	int OjmCount=0;	//���ז��u���b�N�̐��J�E���g
	int Color=m_map[y][x].Num;	//�����Ώۂ̐F��ۑ�

	pos[0]=x;
	pos[1]=x;

	//������Player�������� ���@Block��~���
	if(lr==true) 	
	{
		//�z��I���܂ŒT��
		for(int i=x; i<20; i++)
		{ 
			//�F���o
			if(m_map[y][i].Num==Color)
			{
				pos[1]=i;//�ꏊ���L�^
				
			}
			//�T�����ɋ󔒂ɂ��������炻���ŒT���I��
			if(m_map[y][i].Num==99)
				break;
		}
			
	}
	//�E����Player���������@���@Block��~���
	else
	{
		//�z��I���܂ŒT��
		for(int i=x; i>0; i--)
		{ 
			//�F���o
			if(m_map[y][i].Num==Color)
			{
				pos[1]=i;//�ꏊ���L�^
			}

			//�T�����ɋ󔒂ɂ��������炻���ŒT���I��
			if(m_map[y][i].Num==99)
				break;
		}
	}

	//�Ȃ����Ă��鐔(���ז��Ɨ��T�C�h����)�����߂�
	number=abs(pos[1]-pos[0])+1;

	//�����v���[���[
	if(lr==true)
	{
		//�����͈͓��ɂ��ז��������邩�J�E���g����
		for(int i=x; i<pos[1]; i++)
		{
			if(m_map[y][i].Num==6)
				OjmCount++;
		}
	}
	//�E���v���C���[
	else 
	{
		//�����͈͓��ɂ��ז��������邩�J�E���g����
		for(int i=x; i>pos[1]; i--)
		{
			if(m_map[y][i].Num==6)
				OjmCount++;
		}
	}
	
	//�F�u���b�N�݂̂̐�(�Ȃ����Ă��鐔 - ���ז��̐�)
	int BlockNum = number - OjmCount;
	
	//�F�u���b�N�̐���4�ȏ�Ȃ�
	if(BlockNum >= 4)
	{
		for(int i=0 ; i<number;i++)
		{
			//�}�b�v�ɔ��������p�̐���(98)�������
			if(lr==true)
				m_map[y][x+i].Num=98;
			else
				m_map[y][x-i].Num=98;
		}
	}

	//���ז��������ď���������5�ȏ�Ȃ�
	if(BlockNum>=5)
	{
		//�v���C���[�̌Ăяo��
		CObjHero * obj_h =(CObjHero*)Objs ::GetObj(OBJ_HERO);

		//����Player
		if(lr==true)
		{
			//CP��
			if(m_bCpBattle == true)
			{
				//���ז��̐�������ݒ�
				CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);//CP
				obj_cp->SetOjmNum(BlockNum-4);//�������邨�ז��̐���ۑ�
			}
			//2P��
			else
			{
				//���ז��̐�������ݒ�
				CObjHero_R * obj_hr =(CObjHero_R*)Objs ::GetObj(OBJ_HERO_R);
				obj_hr->SetOjmNum(BlockNum-4);
			}
		}

		//�E��Player
		else
		{
			//���ז��̐�������ݒ�
			obj_h->SetOjmNum(BlockNum-4);
		}	
	}
}

//���ז��u���b�N�̗ʌv�Z�Ɛ���
//����1�F�������邨�ז��u���b�N�̐��@�@�@
//����2�F�u���b�N�𐶐��������
void CObjMain::CreateIntervention(int number,bool lr)
{
	int y;//�������邨�ז��̍����ۑ��p

    //Debug�p�@�����ς݂��ז��L�����̐�
    int SpawnBombCnt=0;

	int Dec=0x0000000;//����ʒu
	int Sch=0x0000000;//�\��ʒu�@�V�r�b�g�ŊǗ�����
		
	int j=0;//�u���b�N������v�f���[���牽�Ԗڂ��J�E���g
		
	//�������邨�ז��̐������܂킷
	for(int i = 0; i < number ; i++)
	{
		do
		{
			//7�Ԗڂ̂��ז��Ȃ�
			if(i==7)
			{
				Dec=0x0000000;//�������������
				j++;//�����ʒu��������ɂ��炷
			}

			y = rand() % 7;//�����_���ňʒu�����߂�
			Sch = 1 << y;

		}while((Dec & Sch ) != 0x0000000);//�����\��n������ψʒu�Ƃ��Ԃ��Ă��Ȃ���Δ�����
			
		//���肵���ʒu�ɂ͂P������
		Dec += (1 << y);

		//�����ɍ~�炷��
		if(lr==true)
		{
			Enter(0+j,y,6);	//�}�b�v�ɓ����
			FlagOn(0+j,y);	//�I�u�W�F�N�g�����t���O���I���ɂ���				
		}
		//�E���ɍ~�炷��
		else
		{
			Enter(19-j,y,6);//�}�b�v�ɓ����
			FlagOn(19-j,y);	//�I�u�W�F�N�g�����t���O���I���ɂ���
		}		
	}
}

//�E�����܂��͍������̃u���b�N�S�Ă��~�܂��Ă��邩���ׂ�
//�����F�ǂ��瑤�𒲂ׂ邩������킷�Bture�Ȃ獶�Afalse�Ȃ�E
//�߂�l:�͈͂̑S�Ă��~�܂��Ă����true:�Ⴆ��false��Ԃ�
bool CObjMain::ShotCheck(bool lr)
{
	for(int i=0;i<7;i++)
	{
		//StopCheck�֐���p���Ĉ�i�����ׂĂ���
		if( StopCheck(i,lr)==false )
			return false;
	}
	return true;
}

//�w�肵���i�̎w�肵���͈́i�E�����܂��͍������j�̃I���ɂȂ��Ă���X�g�b�v�t���O�̐��𐔂���֐�
//�����P�F���ׂ����i
//�����Q�F���ׂ�������
//�߂�l�F�S�ăI���Ȃ�true:�P�ł��I�t�������false��Ԃ�
bool CObjMain::StopCheck(int y,bool lr)//�w�肵���i�̑S�Ẵu���b�N���Ƃ܂��Ă����
{
	int count=0;//�X�g�b�v�t���O�̃J�E���g�p
	
	//����
	if(lr==true)
	{
		for(int i=0;i<=9;i++)
		{
			//���̈ʒu�ɐF�u���b�N�܂��͂��ז��u���b�N�������Ă����
			if( ( 0<=m_map[y][i].Num) && (m_map[y][i].Num <= 6 ) )  
			{
				//�X�g�b�v�t���O���I�t�Ȃ�
				if(m_map[y][i].bStop==false)	
				{	
					//���̃u���b�N�������Ă�����
					return false;
				}
			}
		}
	}
	//�E��
	else
	{	for(int i=10;i<=19;i++)
		{
			//���̈ʒu�ɐF�u���b�N�܂��͂��ז��u���b�N�������Ă����
			if( ( 0<=m_map[y][i].Num) && (m_map[y][i].Num <= 6 ) )  
			{
				//�X�g�b�v�t���O���I�t�Ȃ�
				if(m_map[y][i].bStop==false)	
				{
					//���̃u���b�N�������Ă�����
					return false;
				}
			}
		}
	}
	return true;
}

//���s�̔���p�̊֐�
//����1:���E�������t���O
//��Ԓ[�Ƀu���b�N�͓����Ă��āA������50�t���[���ȏ�Ƃǂ܂��Ă����true�B����ȊO�Ȃ�false
bool CObjMain::VictoryCheck(bool lr)
{
	//��Ԓ[��x�����̗v�f��
	int SideIndex;

	for(int i=0;i<7;i++)
	{
		//��
		if(lr==true)
			SideIndex =0;
		//�E
		else
			SideIndex =19;

		//�F�u���b�N�����ז��u���b�N�������Ă���Ȃ�
		if( 0<=m_map[i][SideIndex].Num && m_map[i][SideIndex].Num<=6)
		{
			//������50�t���[���ȏ�Ƃǂ܂��Ă���Ȃ�
			if(m_map[i][SideIndex].StopTime >= 50)
				return true;
		}
	}
	return false;
}

//�w�肵���͈͂Ɏw��u���b�N�����邩���ׂ�֐�
//����1�@y	�F�i��
//����2�@lr	�F�E�������̃t���O
//����3�@n	�F���ׂ�����
//�߂�l�@����������Ԃ�
int CObjMain::BlockCheck(int y,bool lr,int n)
{
	int count=0;//���������J�E���g�p

	for(int i=0;i<=9;i++)
	{
		//��
		if(lr==true)
		{
			if(m_map[y][i].Num == n)
				count++;
		}
		//�E
		else
		{
			if(m_map[y][i+10].Num == n)
				count++;
		}
	}
	
	return count;
}

//�Ȃ����Ă���u���b�N�̐��𐔂��Ă��̐���Ԃ��֐�
//����1 :�v�f�ԍ�X
//����2 :�v�f�ԍ�Y
//����3 :���E�`�F�b�N
int CObjMain::BlockDeleteCheck(int x,int y,bool lr)
{
	int Pos[2];
	int Number = 0;		//�Ȃ����Ă���u���b�N�̐��J�E���g
	int OjmCount = 0;	//���ז��u���b�N�̐��J�E���g
	int Color = m_map[y][x].Num;	//�����Ώۂ̐F��ۑ�

	Pos[0] = x;
	Pos[1] = x;

	//������Player�������� ���@Block��~���
	if (lr == true)
	{
		//�z��I���܂ŒT��
		for (int i = x; i < 20; i++)
		{
			//�F���o
			if (m_map[y][i].Num == Color)
			{
				Pos[1] = i;//�ꏊ���L�^

			}
			//�T�����ɋ󔒂ɂ��������炻���ŒT���I��
			if (m_map[y][i].Num == 99)
				break;
		}

	}
	//�E����Player���������@���@Block��~���
	else
	{
		//�z��I���܂ŒT��
		for (int i = x; i > 0; i--)
		{
			//�F���o
			if (m_map[y][i].Num == Color)
			{
				Pos[1] = i;//�ꏊ���L�^
			}

			//�T�����ɋ󔒂ɂ��������炻���ŒT���I��
			if (m_map[y][i].Num == 99)
				break;
		}
	}

	//�Ȃ����Ă��鐔(���ז��Ɨ��T�C�h����)�����߂�
	Number = abs(Pos[1] - Pos[0]) + 1;

	//�����v���[���[
	if (lr == true)
	{
		//�����͈͓��ɂ��ז��������邩�J�E���g����
		for (int i = x; i < Pos[1]; i++)
		{
			if (m_map[y][i].Num == 6)
				OjmCount++;
		}
	}
	//�E���v���C���[
	else
	{
		//�����͈͓��ɂ��ז��������邩�J�E���g����
		for (int i = x; i > Pos[1]; i--)
		{
			if (m_map[y][i].Num == 6)
				OjmCount++;
		}
	}

	//�F�u���b�N�݂̂̐�(�Ȃ����Ă��鐔 - ���ז��̐�)
	int BlockNum = Number - OjmCount;
	
	//�Ȃ����Ă��鐔-���ז��̐���4�ȏ�Ȃ�
	if(BlockNum >=4)
	{		
		return BlockNum;
	}
	else
		return 0;
}

//���ꂼ��̒i�̂ǂ��Ńu���b�N���Ƃ܂邩�𒲂ׂ�֐�
void CObjMain::StopPointCheck()
{
	//�E���璲�ׂău���b�N�̎~�܂�ł��낤�ʒu��T��-----
	for(int i=0;i<7;i++)
	{
		for(m_BlockStopPoint[i]=19;m_BlockStopPoint[i]>=10;m_BlockStopPoint[i]--)
		{
			//�󔒂Ȃ�
			if(m_map[i][ m_BlockStopPoint[i] ].Num == 99)
			{
				;//�Ȃɂ����Ȃ�
			}
			//����ȊO�Ȃ�
			else
			{
					break;//���[�v�𔲂���
			}
		}

		//���̂Ƃ�BlockStopPoint�͉E������݂ď��߂ău���b�N�������Ă���ӏ��ɂȂ�
		//�u���b�N������̂͂��̈�E�ׂȂ̂ł�����E�̒l���~����
		m_BlockStopPoint[i]++;//BlockStopPoint�̒l������₷
	}
}

//AI�p�u���b�N��������ʒu��T���֐�(�u���b�N�c�o�[�W����)
//�����P�F�F�P(�㑤�z��)
//�����Q�F�F�Q(�����z��)
//�����R�F��]�̏��
void CObjMain::AiDeleteCheck_H(int color1,int color2,int r)
{
	//CP�I�u�W�F�N�g�̌Ăяo��
	CObjCP * ObjCp =(CObjCP*)Objs ::GetObj(OBJ_CP);
	
	//�F1,2�����F�̈ʒu��ۑ�����
	int PointColor[2];	
	
	int DeleteNum = -1;	//�ŏI�I�ȏ����鐔

	int DeleteNumColor1[7];	//���ꂼ��̒i�ŐF�P�̏����鐔
	int DeleteNumColor2[7];	//���ꂼ��̒i�ŐF�Q�̏����鐔
	
	int OjmCount[7];//���ז��u���b�N�̃J�E���g

	//������
	for(int i=0;i<7;i++)
	{
		DeleteNumColor1[i]=-1;
		DeleteNumColor2[i]=-1;
		OjmCount[i]=0;
	}

	//������ʒu�̕ۑ��p
	Point DeletePoint;
	DeletePoint.x=-1;
	DeletePoint.y=-1;
	
	//�u���b�N�̎~�܂�ł��낤�ʒu��T��
	StopPointCheck();
	
	//�ォ���i���F1,2�ŏ����鐔�𒲂ׂĂ���
	for(int y=0;y<7;y++)
	{
		//�����l�ɖ߂�
		PointColor[0] = -1;
		PointColor[1] = -1;

		//�u���b�N���~�܂�ʒu�̈�����珇�Ɍ��Ă���
		for(int i=m_BlockStopPoint[y]-1;i>0;i--)
		{
			//�󔒂Ȃ炻��ȏ㌩��K�v���Ȃ��̂Ń��[�v�𔲂���
			if( m_map[y][i].Num == 99 )
			{
				break;
			}

			//�F1�Ɠ����F�Ȃ炻�̈ʒu��ۑ�����
			if( m_map[y][i].Num == color1)
			{
				PointColor[0]=i;
			}

			//�F2�Ɠ����F�Ȃ炻�̈ʒu��ۑ�����
			if( m_map[y][i].Num == color2)
			{
				PointColor[1] = i;
			}

			//���ז��u���b�N�Ȃ炨�ז��̃J�E���g�𑝂₷
			if(m_map[y][i].Num==6)
			{
				OjmCount[y]++;
			}
		}

		//���̒i�ŐF�P���������Ă���Ώ����鐔���X�V����
		if(PointColor[0] != -1)
		{
			DeleteNumColor1[y] = abs( m_BlockStopPoint[y] - PointColor[0]) + 1 - 4 - OjmCount[y];
		}

		if(PointColor[1] != -1)//���̒i�ŐF2���������Ă���Ώ����鐔���X�V����
		{
			DeleteNumColor2[y] = abs( m_BlockStopPoint[y] - PointColor[1]) + 1 - 4 - OjmCount[y];
		}
	}
	
	//���ꂼ��̏ڍ׏������߂đ���
	for(int y=0;y<7;y++)
	{	
		//�F1�̏����鐔��0�ȏ�Ȃ�
		if(DeleteNumColor1[y] >= 0)
		{
			if(y < 6)//��Ԃ����̒i�ŐF�Q�������邱�Ƃ͂Ȃ��̂ŏȂ�
			{
				//����̒i�̂ŐF2��������
				if(DeleteNumColor2[y+1] >= 0)
				{
					//���̒i�ŐF�P�������鐔�{����1���ŐF�Q�������鐔�̍��v��ۑ�
					DeleteNum = DeleteNumColor1[y]+DeleteNumColor2[y+1];
				}
				//�F�P������������ꍇ
				else
				{
					//���̒i�ŐF�P�������鐔��ۑ�
					DeleteNum = DeleteNumColor1[y];
				}
				
				//������|�C���g��ۑ�����
				DeletePoint.x=m_BlockStopPoint[y];
				DeletePoint.y=y;

				//������|�C���g�A���A��]���𑗂�
				ObjCp->SetDeletePoint(DeletePoint,DeleteNum,r);
			}
		}
		
		//�F2�̏����鐔��0�ȏ�Ȃ�
		if( DeleteNumColor2[y] >= 0)
		{
			if(y >= 1)//��ԏ�̒i�ŐF2�������邱�Ƃ͂Ȃ��̂ŏȂ�
			{
				//�F1�������ĐF2��������ꍇ
				if(DeleteNumColor2[y-1] >=0 )
				{
				
					//�F1�ŏ����鐔�{�F2�ŏ����鐔
					DeleteNum = DeleteNumColor2[y]+ DeleteNumColor1[y];
				}
				//�F�P�͏����Ȃ��ĐF�Q����������ꍇ
				else
				{
					//���̒i�ŐF2�������鐔
					DeleteNum = DeleteNumColor2[y];
				}

				//������|�C���g��ۑ�����
				DeletePoint.x = m_BlockStopPoint[y - 1];
				DeletePoint.y = y - 1;
				
				//������|�C���g�A���A��]���𑗂�
				ObjCp->SetDeletePoint(DeletePoint,DeleteNum,r);	
			}
		}
	}
}

//AI�p�u���b�N��������ʒu��T���֐�(�u���b�N���o�[�W����)
//�����P�F�F�P(�����z��)
//�����Q�F�F�Q(�E���z��)
//�����R�F��]�̏��
void CObjMain::AiDeleteCheck_W(int color1,int color2,int r)
{
	//CP�I�u�W�F�N�g�̌Ăяo��
	CObjCP * ObjCp =(CObjCP*)Objs ::GetObj(OBJ_CP);
	
	//�F1,2�����F�̈ʒu��ۑ�����
	int PointColor[2];

	int DeleteNum = -1;	//�ŏI�I�ȏ����鐔

	int DeleteNumColor1[7];	//���ꂼ��̒i�ŐF�P�̏����鐔
	int DeleteNumColor2[7];	//���ꂼ��̒i�ŐF�Q�̏����鐔

	int OjmCount[7];//���ז��u���b�N�̃J�E���g

	//������
	for(int i=0;i<7;i++)
	{
		DeleteNumColor1[i]=-1;
		DeleteNumColor2[i]=-1;
		OjmCount[i]=0;
	}

	//������ʒu�̕ۑ��p
	Point DeletePoint;
	DeletePoint.x=-1;
	DeletePoint.y=-1;
	
	//�u���b�N�̎~�܂�ł��낤�ʒu��T��
	StopPointCheck();
	
	//�ォ���i���F1,2�ŏ����邩���𒲂ׂĂ���
	for(int y=0;y<7;y++)
	{
		//�����l�ɖ߂�
		PointColor[0] = -1;
		PointColor[1] = -1;

		//�u���b�N���~�܂�ʒu�̈�����珇�Ɍ��Ă���
		for(int i=m_BlockStopPoint[y]-1;i>0;i--)
		{
			//�󔒂Ȃ炻��ȏ㌩��K�v���Ȃ��̂Ń��[�v�𔲂���
			if( m_map[y][i].Num == 99 )
			{
				break;
			}

			//�F1�Ɠ����F�Ȃ炻�̈ʒu��ۑ�����
			if( m_map[y][i].Num == color1)
			{
				PointColor[0]=i;
			}

			//�F2�Ɠ����F�Ȃ炻�̈ʒu��ۑ�����
			if( m_map[y][i].Num == color2)
			{
				PointColor[1] = i;
			}

			//���ז��u���b�N�Ȃ炨�ז��J�E���g�𑝂₷
			if(m_map[y][i].Num==6)
			{
				OjmCount[y]++;
			}

			//���̒i�ŐF1���������Ă���Ώ����鐔���X�V����
			if(PointColor[0] != -1)
			{
				DeleteNumColor1[y] = abs( m_BlockStopPoint[y] - PointColor[0]) + 1 - 4 - OjmCount[y];		
			}

			//���̒i�ŐF2���������Ă���Ώ����鐔���X�V����
			if (PointColor[1] != -1)
			{
				DeleteNumColor2[y] = abs(m_BlockStopPoint[y] - PointColor[1]) + 1 - 4 - OjmCount[y];
			}
		}
	}
	
	//���ꂼ��̏ڍ׏������߂đ���
	//�������̏ꍇ�͐F1��2�̂ɂ���Ĉʒu�̕ω��͖����̂ŏ����鐔�������ׂ�΂���
	for(int y=0;y<7;y++)
	{
		//�F1���F2�̏����鐔��0��肨���������
		if( DeleteNumColor1[y] >= 0 || DeleteNumColor2[y] >= 0)
		{
			//������|�C���g��ۑ�����
			DeletePoint.x=m_BlockStopPoint[y];
			DeletePoint.y=y;

			//�F�P�ƂQ�ŏ����鐔�̑傫�����𒲂ׂđ���

			//�F1�̕�������������ꍇ
			if(DeleteNumColor1[y] >=DeleteNumColor2[y])	
			{
				ObjCp->SetDeletePoint(DeletePoint,DeleteNumColor1[y],r);				
			}
			//�F2�̕�������������ꍇ
			else
			{
				ObjCp->SetDeletePoint(DeletePoint,DeleteNumColor2[y],r);
			}
		}	
	}
}

//�u���b�N���~�܂�ʒu�̂Ȃ����ԏ������ʒu��T���A��������΂��̒����烉���_���łP���߂�֐�
int CObjMain::InSideCheck()
{
	int i = 0;		//���[�v�p�i���p�j
	int npc;	//�����_���p
	int count=0;//�ォ�牽�Ԗڂ̍ŏ��l���J�E���g����
	
	int BlockStopPointCopy[7];//��r�p�ɃR�s�[���ĕۑ��p

	//�����_������������
	srand(time(NULL)); 

	//�R�s�[������
	for( i=0;i<7;i++)
	{
		BlockStopPointCopy[i] = m_BlockStopPoint[i];
	}

	//�l�L���p
	int num;
	
	//�R�s�[���\�[�g����
	for( i=0;i<6;i++)
	{
		for(int j=i+1;j<7;j++)
		{
			//�����l���傫����Γ���ւ���
			if(BlockStopPointCopy[i] >BlockStopPointCopy[j])
			{
				num =BlockStopPointCopy[i];
				BlockStopPointCopy[i] = BlockStopPointCopy[j];
				BlockStopPointCopy[j] = num;
			}
		}
	}

	//�ŏ��l��ۑ�
	num=BlockStopPointCopy[0];

	for( i=1 ;i < 7 ; i++)
	{
		//�ŏ��l�������Ȃ�
		if( BlockStopPointCopy[i] != num)
		{
			break;
		}
	}

	//0-num�ň�l���i��
	npc = rand() % i;

	for(i=0;i<7;i++)
	{
		if(m_BlockStopPoint[i]==num)
		{
			//count�Ɨ�������v�����
			if(count==npc)
				return i;

			//�J�E���g�𑝂₷
			count++;
		}
	}
	return 0;
}

//�������莞�̃Q�[���I�[�o�[�쐬�Ȃǂ̏���������֐�
//����1: �Qp�킩�����킩���ʂ��邽�߂̃t���O
void CObjMain::VictoryProcess(bool vs_CP)
{
	//�q�[���[�I�u�W�F�N�g�̌Ăяo��
	CObjHero * obj_h =(CObjHero*)Objs ::GetObj(OBJ_HERO);		
	CObjHero_R * obj_hr =(CObjHero_R*)Objs ::GetObj(OBJ_HERO_R);
	
	// �������s�k�����𖞂����Ă���Ȃ��������
	if(m_bLeftWin==true && m_bRightWin==true )
	{ 
		if(vs_CP==false)
		{
			//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
			CObjGameOver* obj_win_lose = new CObjGameOver(0);
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);

			//�@�̂��s���s�\�ɂ���
			obj_h->EndFlagON();
			obj_hr->EndFlagON();
		}
		if(vs_CP==true)
		{
			CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);//CP�I�u�W�F�N�g�̌Ăяo��
	
			//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
			CObjGameOver* obj_win_lose = new CObjGameOver(0);
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);

			//�@�̂��s���s�\�ɂ���
			obj_h->EndFlagON();
			obj_cp->EndFlagON();
		}
		m_bGameOver = true;
	}
	//�E�����s�k�����𖞂����Ă���Ȃ獶�̏���(1P)
	else if(m_bRightWin==true)
	{
		//�Qp��Ȃ�
		if(vs_CP==false)
		{
			//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
			CObjGameOver* obj_win_lose = new CObjGameOver(1);
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);
			
			//�@�̂��s���s�\�ɂ���
			obj_h->EndFlagON();
			obj_hr->EndFlagON();
		}
		if(vs_CP==true)//CP��
		{
			//CP�I�u�W�F�N�g�̌Ăяo��
			CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);
	
			//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
			CObjGameOver* obj_win_lose = new CObjGameOver(1);
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);
	
			//�@�̂��s���s�\�ɂ���
			obj_h->EndFlagON();
			obj_cp->EndFlagON();
		}
		m_bGameOver = true;
	}
	//�������s�k�����𖞂����Ă���Ȃ�E�̏���
	else if(m_bLeftWin==true)
	{
		//2P��
		if(vs_CP==false)
		{
			//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
			CObjGameOver* obj_win_lose = new CObjGameOver(2);
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);

			//�@�̂��s���s�\�ɂ���
			obj_h->EndFlagON();
			obj_hr->EndFlagON();
		}
		//CP��
		if(vs_CP==true)
		{
			//CP�I�u�W�F�N�g�̌Ăяo��
			CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);
	
			//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
			CObjGameOver* obj_win_lose = new CObjGameOver(2);
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);
			
			//�@�̂��s���s�\�ɂ���
			obj_h->EndFlagON();
			obj_cp->EndFlagON();
		}
		m_bGameOver = true;
	}
}