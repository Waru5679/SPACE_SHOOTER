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
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<20;j++)
		{
			//MAP�\���̂̏�����
			m_map[i][j].num=99;
			m_map[i][j].obj_check=false;
			m_map[i][j].obj_time=0;
			m_map[i][j].stop_flag=false;
			m_map[i][j].process_check=true;
			m_map[i][j].before_num=99;
			m_map[i][j].stop_time=0;
		}
	}

	//��������t���O������
	m_vc_r=false;
	m_vc_l-false;

	//�X�^�[�g�J�E���g�_�E��
	m_count_time=0;

	//�������傫���Ȃ鎞��
	font_big_time=0.0f;

	//�����L���O�p�^�C���̏�����
	m_time = 0;

	//�Q�[���I�[�o�[�Ǘ�
	flag = false;

	//AI�p
	for(int i=0;i<7;i++)
	{
		BlockStopPoint[i]=19;//�u���b�N�̎~�܂�ʒu
	}
}

//�A�N�V����
void CObjMain::Action()
{
	//�������I����Ă���΂Ȃɂ����Ȃ�
	if (flag == true) return;

	m_count_time++;

	if (m_count_time > 270)//�X�^�[�g�̕\�����I����Ă����
	{
		if ((m_count_time - 270) % 60 == 0)	//60f��(1�b����)��
			m_time++;				//�����L���O�p�̃^�C���̍X�V
	}

	//�q�[���[�I�u�W�F�N�g�̌Ăяo��
	CObjHero * obj_h =(CObjHero*)Objs ::GetObj(OBJ_HERO);		//��
	CObjHero_R * obj_hr =(CObjHero_R*)Objs ::GetObj(OBJ_HERO_R);//�E
	
	//-----------------------------------------
	//�e�[�u���q�b�g�A���`�F�b�N
	// �V�s�Q�O��
	//-----------------------------------------
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<20;j++)
		{
			//�O��̏������Ɠ������l�������Ă����
			if(m_map[i][j].num == m_map[i][j].before_num)
				m_map[i][j].stop_time++;//�X�g�b�v�^�C���𑝂₷
			else
				m_map[i][j].stop_time=0;//�X�g�b�v�^�C�����O�ɖ߂�
			
			//�F�u���b�N�������Ă����
			if( m_map[i][j].num < 6)
			{
				//�I�u�W�F�N�g�����t���O���I���Ȃ�
				if(m_map[i][j].obj_check==true)
				{
					//����ȃP�[�X�@�E�[ �������̂Ƃ�
					if(j==18 && ( m_map[i][19].num < 6) )//18�Ԗڂ�19�Ԗڂɂ��u���b�N�������Ă���ꍇ�i�E���ŉ������ɂ������Ƃ�
					{
						CObjBlock* obj_b=new CObjBlock(j,i,m_map[i][j].num,false,true);
						Objs::InsertObj(obj_b,OBJ_BLOCK,10);
						m_map[i][j].obj_check=false;//�I�u�W�F�N�g�����t���O���I�t�ɂ���
						m_map[i][j].stop_flag=false;//�u���b�N�����ʒu�̃X�g�b�v�t���O���I�t�ɂ���
						m_map[i][j].obj_time=0;//�I�u�W�F�N�g�����^�C�������Z�b�g����
					}
					else//���ʂ̃P�[�X
					{
						if(j<=9) //�����p�̃u���b�N����
						{
							CObjBlock* obj_b=new CObjBlock(j,i,m_map[i][j].num,
										true,false);
							Objs::InsertObj(obj_b,OBJ_BLOCK,10);
						
						}
						else if(j>=10) //�E���p�̃u���b�N�����@//2017-05-26 ���� > -> >=
						{
							CObjBlock* obj_b=new CObjBlock(j,i,m_map[i][j].num,
										false,false);
							Objs::InsertObj(obj_b,OBJ_BLOCK,10);					
						}
						m_map[i][j].obj_check=false;//�I�u�W�F�N�g�����t���O���I�t�ɂ���
						m_map[i][j].stop_flag=false;//�u���b�N�����ʒu�̃X�g�b�v�t���O���I�t�ɂ���
						m_map[i][j].obj_time=0;//�I�u�W�F�N�g�����^�C�������Z�b�g����
					}
				}//�����t���b�O�I���@ENDif	
			}
			//---------------------------------
			//���ז��u���b�N�@6
			//---------------------------------
			if(m_map[i][j].num==6)
			{
				//�I�u�W�F�N�g�����t���O���I���Ȃ�
				if(m_map[i][j].obj_check==true)
				{
					if(j<10)
					{
						CObjIntervention* obj_i=new CObjIntervention(j,i,true);
						Objs::InsertObj(obj_i,OBJ_INTERVENTION,10);
						m_map[i][j].obj_check=false;//�I�u�W�F�N�g�����t���O���I�t�ɂ���
						m_map[i][j].stop_flag=false;//�u���b�N�����ʒu�̃X�g�b�v�t���O���I�t�ɂ���
						m_map[i][j].obj_time=0;//�I�u�W�F�N�g�����^�C�������Z�b�g����
					}
					else if(j>9)
					{
						CObjIntervention* obj_i=new CObjIntervention(j,i,false);
						Objs::InsertObj(obj_i,OBJ_INTERVENTION,10);
						m_map[i][j].obj_check=false;//�I�u�W�F�N�g�����t���O���I�t�ɂ���
						m_map[i][j].stop_flag=false;//�u���b�N�����ʒu�̃X�g�b�v�t���O���I�t�ɂ���
						m_map[i][j].obj_time=0;//�I�u�W�F�N�g�����^�C�������Z�b�g����
					}
				}	
			}

			//--------------------------------------------------------
			//���ŃA�j���[�V�����@98
			//----------------------------------------------
			if(m_map[i][j].num == 98)
			{
				if(m_map[i][j].stop_time >= 5)//�����A���ŏ����̔��肪�A�j���[�V�����̎��Ԃ�蒷���Ƃǂ܂��Ă�����
					m_map[i][j].num==99;//�󔒂ɂ��ǂ�
			}

			//-----------------------------------------------
			//�� 99
			//--------------------------------------
			if(m_map[i][j].num == 99)
			{
				m_map[i][j].process_check=true;//�����σt���O���I���ɂ���
			}

			//�ԍ���ۑ�����
			m_map[i][j].before_num=m_map[i][j].num;
			
			m_map[i][j].obj_time++;//�I�u�W�F�N�g��������̃^�C���ۑ�
			if( m_map[i][j].obj_time > 10000)//����10000�𒴂���Ȃ�
				m_map[i][j].obj_time = 10;//10�ɖ߂� 
		}
	}

	//���s����
	m_vc_l=VictoryCheck(true);//��
	m_vc_r=VictoryCheck(false);//�E
	
	if(flag == false)
	{
		VictoryProcess(vs_CP);//����������݂����Ă��邩���ׁA�������Ă���Ώ���������
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
	if(m_count_time>=270)
	{
		//�X�R�A�\��
		swprintf_s(str, L"%02d:%02d",m_time/60, m_time % 60);
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
				else if(m_map[y][x].num==99)
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
	if(m_count_time<=70)
	{
		if(m_count_time==5)
			Audio::Start(9);//���ʉ�

		font_big_time++;

		//font_big_time��������ɂ�ĕ\������鐔�����傫���Ȃ�
		//�`��ʒu�̐ݒ�
		RectSet(200-font_big_time,420-font_big_time,570+font_big_time,400+font_big_time,dst);
		
		Draw::Draw(11,&src,&dst,c,0.0f);//�`��
		
	}

	//2
	if(m_count_time>70&&m_count_time<=140)
	{
		if(m_count_time==75)
			Audio::Start(9);//���ʉ�

		font_big_time++;

		RectSet(200-font_big_time,420-font_big_time,570+font_big_time,400+font_big_time,dst);

		Draw::Draw(12,&src,&dst,c,0.0f);//�`��
	}

	//1
	if(m_count_time>140&&m_count_time<=210)
	{
		if(m_count_time==145)
			Audio::Start(9);//���ʉ�

		font_big_time++;

		RectSet(200-font_big_time,420-font_big_time,570+font_big_time,400+font_big_time,dst);

		Draw::Draw(13,&src,&dst,c,0.0f);//�`��

	}

	//START
	if(m_count_time>210&&m_count_time<=260)
	{
		if(m_count_time==215)
			Audio::Start(10);//���ʉ�

		RectSet(100.0f,300.0f,700.0f,400.0f,dst);

		Draw::Draw(14,&src,&dst,start,0.0f);//�`��
	}

	//�J�E���g��70�����Ƃ��Ɍ��̃T�C�Y�ɖ߂�
	if(font_big_time==70)
		font_big_time=0;
}

//�Ȃ����Ă���u���b�N�̐��𐔂��Ă�����Ȃ���ŏ���������֐�
//����1 :�v�f�ԍ�X
//����2 :�v�f�ԍ�Y
//����3 :���E�`�F�b�N�i�ǂ��瑤���痈�Ă�u���b�N���j
void CObjMain::CheckMap(int x, int y,bool lr)
{
	int pos[2];
	int number=0;//�Ȃ����Ă���u���b�N�̐��J�E���g
	int ojm_count=0;//���ז��u���b�N�̐��J�E���g
	int color=m_map[y][x].num;//�����Ώۂ̐F��ۑ�

	pos[0]=x;
	pos[1]=x;

	if(lr==true) //������Player��������Block�iBullet�j����~���	
		//�����̂͂��݃`�F�b�N�����
		//�E�[��Block����n�܂��āA����ɉE���̃u���b�N���`�F�b�N�ɂ����Ă���

	{
		// x+1 ---> x ��ύX�@2017-05-26
		for(int i=x; i<20; i++) //�z��I���܂ŒT��
		{ 
			if(m_map[y][i].num==color) //�F���o
			{
				pos[1]=i;//�ꏊ���L�^
				
			}

			if(m_map[y][i].num==99)//�T�����ɋ󔒂ɂ��������炻���ŒT���I��
				break;
		}
			
	}
	else //�E����Player��������Block�iBullet�j����~���
	{
		// x-1 ---> x ��ύX�@2017-06-05
		for(int i=x; i>0; i--) //�z��I���܂ŒT��
		{ 
			if(m_map[y][i].num==color) //�F���o
			{
				pos[1]=i;//�ꏊ���L�^

			}

			if(m_map[y][i].num==99)//�T�����ɋ󔒂ɂ��������炻���ŒT���I��
				break;
		}
	}

	number=abs(pos[1]-pos[0])+1;//�Ȃ����Ă��鐔(���ז��Ɨ��T�C�h����)�����߂�

	if(lr==true)//�����v���[���[
	{
		//��
		// x+1 ---> x ��ύX�@2017-06-05
		for(int i=x; i<pos[1]; i++)//�����͈͓��ɂ��ז��������邩�J�E���g����
		{
			if(m_map[y][i].num==6)//�����A���ז��u���b�N�Ȃ�
				ojm_count++;
		}
	}
	else 
	{
		//�E
		// x-1 ---> x ��ύX�@2017-06-05
		for(int i=x; i>pos[1]; i--)//�����͈͓��ɂ��ז��������邩�J�E���g����
		{
			if(m_map[y][i].num==6)//�����A���ז��u���b�N�Ȃ�
				ojm_count++;
		}
	}
	
	//--------------------------------------------
	// �A���`�F�C���@�������ݏ���
	// �S�ȏ�
	//--------------------------------------------
	int nBlockNum = number - ojm_count;//�F�u���b�N�݂̂̐�(�Ȃ����Ă��鐔 - ���ז��̐��@)
	
	if(nBlockNum >= 4)//�F�u���b�N�݂̂̐���4�ȏ�Ȃ�
	{
		//��
		for(int i=0 ; i<number;i++)
		{
			if(lr==true)//����Player
				m_map[y][x+i].num=98;//�}�b�v�ɔ��������p�̐���(98)�������
			else
				m_map[y][x-i].num=98;//�}�b�v�ɔ��������p�̐���(98)�������
		}
	}

	if(nBlockNum>=5)//���ז��������ď���������5�ȏ�Ȃ�
	{
		//�I�u�W�F�N�g�̌Ăяo��
		CObjHero * obj_h =(CObjHero*)Objs ::GetObj(OBJ_HERO);		//��

		//�e�X�g-----------------------------
		//
		if(lr==true)
		{
			//�����痈���u���b�N
			if(vs_CP == true)//CP��Ȃ�
			{
				CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);//CP
				obj_cp->SetOjmNum(nBlockNum-4);//�������邨�ז��̐���ۑ�
			}
			
			if(vs_CP == false)//2P��Ȃ�
			{
				CObjHero_R * obj_hr =(CObjHero_R*)Objs ::GetObj(OBJ_HERO_R);//�E
				obj_hr->SetOjmNum(nBlockNum-4);//�������邨�ז��̐���ۑ�
			}
		}
		else
		{
			//�E���痈���u���b�N
			obj_h->SetOjmNum(nBlockNum-4);//�������邨�ז��̐���ۑ�
		}	
		//------------------------------------------
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
		
	for(int i = 0; i < number ; i++)//�������邨�ז��̐������܂킷
	{
		do
		{
			if(i==7)//7�Ԗڂ̂��ז��Ȃ�// Iv��15��Max
			{
				Dec=0x0000000;//�������������
				j++;//�����ʒu��������ɂ��炷
			}

			y = rand() % 7;//�����_���ňʒu�����߂�
			Sch = 1 << y;

		}while((Dec & Sch ) != 0x0000000);//�����\��n������ψʒu�Ƃ��Ԃ��Ă��Ȃ���Δ�����
			
		Dec += (1 << y);//���肵���ʒu�ɂ͂P������

		if(lr==true)
		{
			//�����ɍ~�炷��
			Enter(0+j,y,6);//�}�b�v�ɓ����
			FlagOn(0+j,y);//�I�u�W�F�N�g�����t���O���I���ɂ���				
		}
		else
		{
			//�E���ɍ~�炷��
			Enter(19-j,y,6);//�}�b�v�ɓ����
			FlagOn(19-j,y);//�I�u�W�F�N�g�����t���O���I���ɂ���
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
		if( StopCheck(i,lr)==false )//���ʂ�false�Ȃ�
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
	

	if(lr==true)
	{
		//��
		for(int i=0;i<=9;i++)
		{
			//���̈ʒu�ɐF�u���b�N�܂��͂��ז��u���b�N�������Ă����
			if( ( 0<=m_map[y][i].num) && (m_map[y][i].num <= 6 ) )  
			{
				//�X�g�b�v�t���O���I�t�Ȃ�
				if(m_map[y][i].stop_flag==false)	
				{	
					//���̃u���b�N�������Ă�����
					return false;
				}
			}
		}
	}
	else
	{
		//�E
		for(int i=10;i<=19;i++)
		{
			//���̈ʒu�ɐF�u���b�N�܂��͂��ז��u���b�N�������Ă����
			if( ( 0<=m_map[y][i].num) && (m_map[y][i].num <= 6 ) )  
			{
				//�X�g�b�v�t���O���I�t�Ȃ�
				if(m_map[y][i].stop_flag==false)	
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
	int j;
	for(int i=0;i<7;i++)
	{
		if(lr==true)
			j=0;
		else
			j=19;

		//�F�u���b�N�����ז��u���b�N�������Ă���Ȃ�
		if( 0<=m_map[i][j].num && m_map[i][j].num<=6)
		{
			//������50�t���[���ȏ�Ƃǂ܂��Ă���Ȃ�
			if(m_map[i][j].stop_time >= 50)
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
		if(lr==true)//���E�`�F�b�N
		{
			//��
			if(m_map[y][i].num == n)
				count++;
		}
		else
		{
			if(m_map[y][i+10].num == n)
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
	int pos[2];
	int number=0;//�Ȃ����Ă���u���b�N�̐��J�E���g
	int ojm_count=0;//���ז��u���b�N�̐��J�E���g
	int color=m_map[y][x].num;//�����Ώۂ̐F��ۑ�

	pos[0]=x;
	pos[1]=x;

	if(lr==true) //������Player��������Block�iBullet�j����~���	
		//�����̂͂��݃`�F�b�N�����
		//�E�[��Block����n�܂��āA����ɉE���̃u���b�N���`�F�b�N�ɂ����Ă���

	{
		// x+1 ---> x ��ύX�@2017-05-26
		for(int i=x; i<20; i++) //�z��I���܂ŒT��
		{ 
			if(m_map[y][i].num==color) //�F���o
			{
				pos[1]=i;//�ꏊ���L�^
				
			}

			if(m_map[y][i].num==99)//�T�����ɋ󔒂ɂ��������炻���ŒT���I��
				break;
		}
			
	}
	else //�E����Player��������Block�iBullet�j����~���
		
	{
		// x-1 ---> x ��ύX�@2017-06-05
		for(int i=x; i>0; i--) //�z��I���܂ŒT��
		{ 
			if(m_map[y][i].num==color) //�F���o
			{
				pos[1]=i;//�ꏊ���L�^
			}

			if(m_map[y][i].num==99)//�T�����ɋ󔒂ɂ��������炻���ŒT���I��
				break;
		}
	}


	number = abs(pos[1]-pos[0])+1;//�Ȃ����Ă��鐔(���ז��Ɨ��T�C�h����)�����߂�

	if(lr==true)//�����v���[���[
	{
		//��
		// x+1 ---> x ��ύX�@2017-06-05
		for(int i=x; i<pos[1]; i++)//�����͈͓��ɂ��ז��������邩�J�E���g����
		{
			if(m_map[y][i].num==6)//�����A���ז��u���b�N�Ȃ�
				ojm_count++;
		}
	}
	else 
	{
		//�E
		// x-1 ---> x ��ύX�@2017-06-05
		for(int i=x; i>pos[1]; i--)//�����͈͓��ɂ��ז��������邩�J�E���g����
		{
			if(m_map[y][i].num==6)//�����A���ז��u���b�N�Ȃ�
				ojm_count++;
		}
	}

	//--------------------------------------------
	// �A���`�F�C���@�������ݏ���
	// �S�ȏ�
	//--------------------------------------------
	if(number-ojm_count>=4)//�Ȃ����Ă��鐔-���ז��̐���4�ȏ�Ȃ�
	{		
		return number-ojm_count;
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
		for(BlockStopPoint[i]=19;BlockStopPoint[i]>=10;BlockStopPoint[i]--)
		{
			//�󔒂Ȃ�
			if(m_map[i][ BlockStopPoint[i] ].num == 99)
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
		BlockStopPoint[i]++;//BlockStopPoint�̒l������₷
	}
}

//AI�p�u���b�N��������ʒu��T���֐�(�u���b�N�c�o�[�W����)
//�����P�F�F�P(�㑤�z��)
//�����Q�F�F�Q(�����z��)
//�����R�F��]�̏��
void CObjMain::AiDeleteCheck_H(int color1,int color2,int r)
{
	//CP�I�u�W�F�N�g�̌Ăяo��
	CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);
	
	int point_color1 = -1;//�F�P�Ɠ����F�̈ʒu��ۑ�����
	int point_color2 = -1;//�F�Q�Ɠ����F�̈ʒu��ۑ�����
	int delete_num = -1;//�ŏI�I�ȏ����鐔��ۑ�����
	int delete_num_color1[7];//���ꂼ��̒i�ŐF�P�̏����鐔
	int delete_num_color2[7];//���ꂼ��̒i�ŐF�Q�̏����鐔
	int ojm_count[7];//���ז��u���b�N�̃J�E���g

	for(int i=0;i<7;i++)
	{
		//������
		delete_num_color1[i]=-1;
		delete_num_color2[i]=-1;
		ojm_count[i]=0;
	}

	Point delete_point;//������ʒu�̕ۑ��p
	delete_point.x=-1;
	delete_point.y=-1;
	
	//�u���b�N�̎~�܂�ł��낤�ʒu��T��
	StopPointCheck();
	
	//�ォ���i���F1,2�ŏ����邩���𒲂ׂĂ���---------------
	for(int y=0;y<7;y++)
	{
		//�����l�ɖ߂�
		point_color1 = -1;
		point_color2 = -1;

		//�u���b�N���~�܂�ʒu�̈�����珇�Ɍ��Ă���
		for(int i=BlockStopPoint[y]-1;i>0;i--)
		{
			//�󔒂Ȃ�
			if( m_map[y][i].num == 99 )
			{
				break;//����ȏ㌩��K�v���Ȃ��̂Ń��[�v�𔲂���
			}

			//�F�P�Ɠ����F�Ȃ�
			if( m_map[y][i].num == color1)
			{
				point_color1=i;//���̈ʒu��ۑ�����
			}

			//�F�Q�Ɠ����F�Ȃ�
			if( m_map[y][i].num == color2)
			{
				point_color2=i;//���̈ʒu��ۑ�����
			}

			//���ז��u���b�N�Ȃ�
			if(m_map[y][i].num==6)
			{
				ojm_count[y]++;//�J�E���g�𑝂₷
			}
		}

		if(point_color1 != -1)//���̒i�ŐF�P���������Ă����
		{
			delete_num_color1[y] = abs( BlockStopPoint[y] - point_color1) + 1 - 4 - ojm_count[y];//�����鐔���X�V����
			
			//if(delete_num_color1[y] < 0)
			//	delete_num_color1[y]=0;//0�ȉ��ɂȂ�Ȃ��悤�ɂ���
		}

		if(point_color2 != -1)//���̒i�ŐF2���������Ă����
		{
			delete_num_color2[y] = abs( BlockStopPoint[y] - point_color2) + 1 - 4 - ojm_count[y];//�����鐔���X�V����
				
			//if(delete_num_color2[y] < 0)
			//	delete_num_color2[y]=0;//0�ȉ��ɂȂ�Ȃ��悤�ɂ���
		}
	}
	//���ꂼ��̒i�ł̏����鐔�𒲂ׂ�̏I���-------------------------------------------------

	//���ꂼ��̏ڍ׏������߂đ���----------------------------------------

	for(int y=0;y<7;y++)
	{
		if(delete_num_color1[y] >= 0)//�F1�̏����鐔��0�ȏ�Ȃ�
		{
			if(y < 6)//��Ԃ����̒i�ŐF�Q�������邱�Ƃ͂Ȃ��̂ŏȂ�
			{
				if(delete_num_color2[y+1] >= 0)//����̒i�̂ŐF2��������Ȃ�
				{
					//�F�P�������ĐF�Q��������

					//���̒i�ŐF�P�������鐔�{����1���ŐF�Q�������鐔�̍��v��ۑ�
					delete_num = delete_num_color1[y]+delete_num_color2[y+1];
				}
				else
				{
					//�F�P������������ꍇ
					
					//���̒i�ŐF�P�������鐔��ۑ�
					delete_num = delete_num_color1[y];
				}
				
				//������|�C���g��ۑ�����
				delete_point.x=BlockStopPoint[y];
				delete_point.y=y;

				obj_cp->SetDeletePoint(delete_point,delete_num,r);//������|�C���g�A���A��]���𑗂�
			}
		}
		
		if( delete_num_color2[y] >= 0)//�F2�̏����鐔��0�ȏ�Ȃ�
		{
			//�F�P�͏����Ȃ��ĐF2�͏�����ꍇ

			if(y >= 1)//��ԏ�̒i�ŐF2�������邱�Ƃ͂Ȃ��̂ŏȂ�
			{
				//������|�C���g��ۑ�����
				delete_point.x=BlockStopPoint[y-1];
				delete_point.y=y-1;

				//1��̒i�ŐF�P�������邩
				if(delete_num_color2[y-1] >=0 )	//�F�P�������ĐF�Q��������ꍇ
				{
				
					//�F1�ŏ����鐔�{�F2�ŏ����鐔
					delete_num = delete_num_color2[y]+ delete_num_color1[y];
				}
				else//�F�P�͏����Ȃ��ĐF�Q����������ꍇ
				{
					//���̒i�ŐF2�������鐔
					delete_num = delete_num_color2[y];
				}				

				obj_cp->SetDeletePoint(delete_point,delete_num,r);//������|�C���g�A���A��]���𑗂�
			}
		}
	}

	//������Ƃ��̏ڍ׋��߂đ���̏I���---------------------------------------------------------
}

//AI�p�u���b�N��������ʒu��T���֐�(�u���b�N���o�[�W����)
//�����P�F�F�P(�����z��)
//�����Q�F�F�Q(�E���z��)
//�����R�F��]�̏��
void CObjMain::AiDeleteCheck_W(int color1,int color2,int r)
{
	//CP�I�u�W�F�N�g�̌Ăяo��
	CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);
	
	int point_color1 = -1;//�F�P�Ɠ����F�̈ʒu��ۑ�����
	int point_color2 = -1;//�F�Q�Ɠ����F�̈ʒu��ۑ�����
	int delete_num_color1[7];//���ꂼ��̒i�ŐF�P�̏����鐔
	int delete_num_color2[7];//���ꂼ��̒i�ŐF�Q�̏����鐔
	int ojm_count[7];//���ז��u���b�N�̃J�E���g

	for(int i=0;i<7;i++)
	{
		//������
		delete_num_color1[i]=-1;
		delete_num_color2[i]=-1;
		ojm_count[i]=0;
	}

	Point delete_point;//������ʒu�̕ۑ��p
	delete_point.x=-1;
	delete_point.y=-1;
	
	//�u���b�N�̎~�܂�ł��낤�ʒu��T��
	StopPointCheck();
	
	//�ォ���i���F1,2�ŏ����邩���𒲂ׂĂ���---------------
	for(int y=0;y<7;y++)
	{
		//�����l�ɖ߂�
		point_color1 = -1;
		point_color2 = -1;

		//�u���b�N���~�܂�ʒu�̈�����珇�Ɍ��Ă���
		for(int i=BlockStopPoint[y]-1;i>0;i--)
		{
			//�󔒂Ȃ�
			if( m_map[y][i].num == 99 )
			{
				break;//����ȏ㌩��K�v���Ȃ��̂Ń��[�v�𔲂���
			}

			//�F�P�Ɠ����F�Ȃ�
			if( m_map[y][i].num == color1)
			{
				point_color1=i;//���̈ʒu��ۑ�����
			}

			//�F�Q�Ɠ����F�Ȃ�
			if( m_map[y][i].num == color2)
			{
				point_color2=i;//���̈ʒu��ۑ�����
			}

			//���ז��u���b�N�Ȃ�
			if(m_map[y][i].num==6)
			{
				ojm_count[y]++;//�J�E���g�𑝂₷
			}

			if(point_color1 != -1)//���̒i�ŐF�P���������Ă����
			{
				delete_num_color1[y] = abs( BlockStopPoint[y] - point_color1) + 1 - 4 - ojm_count[y];//�����鐔���X�V����
			
				//if(delete_num_color1[y] < 0)
				//	delete_num_color1[y]=0;//0�ȉ��ɂȂ�Ȃ��悤�ɂ���
			}

			if(point_color2 != -1)//���̒i�ŐF2���������Ă����
			{
				delete_num_color2[y] = abs( BlockStopPoint[y]+1 - point_color2) + 1 - 4 - ojm_count[y];//�����鐔���X�V����
				
				//if(delete_num_color2[y] < 0)
				//	delete_num_color2[y]=0;//0�ȉ��ɂȂ�Ȃ��悤�ɂ���
			}
		}
	}
	//���ꂼ��̒i�ł̏����鐔�𒲂ׂ�̏I���-------------------------------------------------

	//���ꂼ��̏ڍ׏������߂đ���----------------------------------------
	
		//�������̏ꍇ�͐F1��2�̂ɂ���Ĉʒu�̕ω��͖����̂ŏ����鐔�������ׂ�΂���
		for(int y=0;y<7;y++)
		{
			if( delete_num_color1[y] >= 0 || delete_num_color2[y] >= 0)//�F1���F2�̏����鐔��0��肨���������
			{
				//������|�C���g��ۑ�����
				delete_point.x=BlockStopPoint[y];
				delete_point.y=y;

				//�F�P�ƂQ�ŏ����鐔�̑傫�����𒲂ׂđ���
				if(delete_num_color1[y] >=delete_num_color2[y])	//�F1�̕�������������ꍇ
				{
					
					obj_cp->SetDeletePoint(delete_point,delete_num_color1[y],r);	//���𑗂�
				
				}
				else	//�F2�̕�������������ꍇ
				{
					obj_cp->SetDeletePoint(delete_point,delete_num_color2[y],r);	//���𑗂�
				}
			}	
		}
	//�ڍ׋��߂đ���̂����------------------------------------------------
}

//�u���b�N���~�܂�ʒu�̂Ȃ����ԏ������ʒu��T���A��������΂��̒����烉���_���łP���߂�֐�
int CObjMain::InSideCheck()
{
	int i;//���[�v�p�i���p�j
	int BlockStopPoint_copy[7];//��r�p�ɃR�s�[���ĕۑ��p
	int npc;//�����_���p
	int count=0;//�ォ�牽�Ԗڂ̍ŏ��l���J�E���g����
	
	srand(time(NULL)); // �����_������������

	//�R�s�[������
	for( i=0;i<7;i++)
	{
		BlockStopPoint_copy[i] = BlockStopPoint[i];
	}

	int n;//�l�L���p
	
	//�R�s�[���\�[�g����
	for( i=0;i<6;i++)
	{
		for(int j=i+1;j<7;j++)
		{
			//�����l���傫����Γ���ւ���
			if(BlockStopPoint_copy[i] >BlockStopPoint_copy[j])
			{
				n =BlockStopPoint_copy[i];
				BlockStopPoint_copy[i] = BlockStopPoint_copy[j];
				BlockStopPoint_copy[j] = n;
			}
		}
	}

	n=BlockStopPoint_copy[0];//�ŏ��l��ۑ�

	for( i=1 ;i < 7 ; i++)
	{
		if( BlockStopPoint_copy[i] != n)//�ŏ��l�������Ȃ�
		{
			break;
		}
	}

	npc = rand() % i;//0~n�ň�l���i��

	for(i=0;i<7;i++)
	{
		if(BlockStopPoint[i]==n)
		{
			if(count==npc)//count�Ɨ�������v�����
				return i;

			count++;//�J�E���g�𑝂₷
		}
	}
}

//�������莞�̃Q�[���I�[�o�[�쐬�Ȃǂ̏���������֐�
//����1: �Qp�킩�����킩���ʂ��邽�߂̃t���O
void CObjMain::VictoryProcess(bool vs_CP)
{
	//�q�[���[�I�u�W�F�N�g�̌Ăяo��
	CObjHero * obj_h =(CObjHero*)Objs ::GetObj(OBJ_HERO);		//��
	CObjHero_R * obj_hr =(CObjHero_R*)Objs ::GetObj(OBJ_HERO_R);//�E
	
	if(m_vc_l==true && m_vc_r==true )//�������s�k�����𖞂����Ă���Ȃ�
	{
		//��������
			
		if(vs_CP==false)
		{
			//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
			CObjGameOver* obj_win_lose = new CObjGameOver(0);//�^�C�g���I�u�W�F�N�g�쐬
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);//�^�C�g���I�u�W�F�N�g�쐬

			//�@�̂��s���s�\�ɂ���------
			obj_h->EndFlag_ON();
			obj_hr->EndFlag_ON();
			//------------------------------
		}
		if(vs_CP==true)
		{
			CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);//CP�I�u�W�F�N�g�̌Ăяo��
	
			//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
			CObjGameOver* obj_win_lose = new CObjGameOver(0);//�^�C�g���I�u�W�F�N�g�쐬
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);//�^�C�g���I�u�W�F�N�g�쐬

			//�@�̂��s���s�\�ɂ���------
			obj_h->EndFlag_ON();
			obj_cp->EndFlag_ON();
			//------------------------------
		}
		flag = true;
	}
	else if(m_vc_r==true)//�E�����s�k�����𖞂����Ă���Ȃ�
	{
		if(vs_CP==false)//�Qp��Ȃ�
		{
			//���̏���(1P)
			CObjGameOver* obj_win_lose = new CObjGameOver(1);//�^�C�g���I�u�W�F�N�g�쐬
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);//�^�C�g���I�u�W�F�N�g�쐬
			//�@�̂��s���s�\�ɂ���------
			obj_h->EndFlag_ON();
			obj_hr->EndFlag_ON();
			//------------------------------
		}
		if(vs_CP==true)//CP��Ȃ�
		{
			CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);//CP�I�u�W�F�N�g�̌Ăяo��
	
			CObjGameOver* obj_win_lose = new CObjGameOver(1);//�^�C�g���I�u�W�F�N�g�쐬
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);//�^�C�g���I�u�W�F�N�g�쐬
			//�@�̂��s���s�\�ɂ���------
			obj_h->EndFlag_ON();
			obj_cp->EndFlag_ON();
			//------------------------------
		}
		flag = true;
	}
	else if(m_vc_l==true)//�������s�k�����𖞂����Ă���Ȃ�
	{
		if(vs_CP==false)//2P��Ȃ�
		{
			//�E�̏���(2P)
			CObjGameOver* obj_win_lose = new CObjGameOver(2);//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
			//�@�̂��s���s�\�ɂ���------
			obj_h->EndFlag_ON();
			obj_hr->EndFlag_ON();
			//------------------------------
		}
		if(vs_CP==true)//CP��Ȃ�
		{
			CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);//CP�I�u�W�F�N�g�̌Ăяo��
	
			CObjGameOver* obj_win_lose = new CObjGameOver(2);//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
			//�@�̂��s���s�\�ɂ���------
			obj_h->EndFlag_ON();
			obj_cp->EndFlag_ON();
			//------------------------------
		}

			flag = true;
	}
}