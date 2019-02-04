#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���C��
class CObjMain : public CObj
{
public:
	CObjMain(bool tipe) { vs_CP = tipe; }
	~CObjMain() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	//2017-06-19�@�����-------------------

	//�w�肵���}�b�v�v�f�Ɏw�肵���l�������֐�
	void Enter(int x, int y, int n)
	{
		m_map[y][x].num = n;
	}
	//------------------------------------------------------

	//�l��Ԃ�
	int Return_Num(int x, int y) { return m_map[y][x].num; }//�w�肵���}�b�v�v�f�̒l��Ԃ��֐�
	int Return_obj_time(int x, int y) { return m_map[y][x].obj_time; }//�I�u�W�F�N�g��������̎��Ԃ�Ԃ�

	//�u���b�N�̐����֘A
	void CreateIntervention(int number, bool m_lr);//���ז��u���b�N�̐���
	void FlagOn(int x, int y) { m_map[y][x].obj_check = true; }//�w�肵���}�b�v�v�f�̃I�u�W�F�N�g�����t���O���I���ɂ���֐�

	//stop�t���O�֘A
	void StopFlag_ON(int x, int y) { m_map[y][x].stop_flag = true; }//�w�肵���}�b�v�v�f�̃X�g�b�v�t���O���I���ɂ���֐�
	void StopFlag_OFF(int x, int y) { m_map[y][x].stop_flag = false; }//�w�肵���}�b�v�v�f�̃X�g�b�v�t���O���I�t�ɂ���֐�
	void Enter_Stop_flag(int x, int y, bool stop_flag) { m_map[y][x].stop_flag = stop_flag; }//�w�肵���v�f�Ɏw�肵���X�g�b�v�t���O������֐�
	bool Return_Stop_Flag(int x, int y) { return m_map[y][x].stop_flag; }//�w�肵���}�b�v�v�f�̃X�g�b�v�t���O��Ԃ��֐�

	//�����t���O�֘A
	void Processflag(int x, int y, bool check) { m_map[y][x].process_check = check; }//�w�肵���}�b�v�v�f�̏����t���O���w�肵�����̂ɒu��������
	int ReturnProcess_flag(int x, int y) { return m_map[y][x].process_check; }//�����`�F�b�N�t���O��Ԃ�

	//�͈̓`�F�b�N�֘A
	bool StopCheck(int y, bool lr);//�w�肵���i�̉E(�܂��͍�)�����̃X�g�b�v�t���O���I���Ȃ�true:��ł��I�t�Ȃ�false�@��Ԃ��֐�
	bool ShotCheck(bool lr);//�E�����܂��͍������̃u���b�N���S�Ď~�܂��Ă��邩�ǂ������ׂ�

	//���ł̏����֘A
	void CheckMap(int x, int y, bool check);//�Ȃ����Ă���u���b�N�̐��𐔂��ď�����Ȃ���ŏ���������֐�
	int BlockDeleteCheck(int x, int y, bool lr);//�Ȃ����Ă���u���b�N�̐��𐔂��Ă��̐���Ԃ��֐�	

	//���s�֘A				
	int BlockCheck(int y, bool lr, int n);//�w�肵���͈͂Ɏw�肵���u���b�N�����邩�ǂ������ׂ�֐�
	bool VictoryCheck(bool lr);//���s�̔���p
	bool ReturnFlag() { return flag; }//�Q�[���I�[�o�[�`�F�b�N�̃t���O��Ԃ��֐�
	void VictoryProcess(bool vs_CP);//�������莞�̃Q�[���I�[�o�[�쐬�Ȃǂ̏���������֐�
	
	//VSCP�p
	void AiDeleteCheck_H(int color1, int color2, int r);//AI�p�u���b�N��������ʒu��T���֐�(�u���b�N�c�z��)
	void AiDeleteCheck_W(int color1, int color2, int r);//AI�p�u���b�N��������ʒu��T���֐�(�u���b�N���z��)
	void StopPointCheck();//���ꂼ��̒i�̂ǂ��Ńu���b�N���Ƃ܂邩�𒲂ׂ�֐�
	int InSideCheck();//�u���b�N���~�܂�ʒu�̂Ȃ����ԏ������ʒu��T���A��������΂��̒����烉���_���łP���߂�֐�
	bool ReturnCPflag() { return vs_CP; }	//CP�킩�̃t���O��Ԃ��֐�

	//�����L���O�V�X�e���p
	int ReturnTime(){return m_time;}

	private:
		bool m_f;
		bool vs_CP;//CP�킩�Q���킩��ʂ���t���O true�FCP��@false:2P��

		//�I�u�W�F�N�g�`�F�b�N�p�̃t���O���������}�b�v
		struct MAP
		{
			int num;//�u���b�N�̎�ނ̐���
			bool obj_check;//�I�u�W�F�N�g�����łɐ����ς݂��ǂ�������ׂ�
			int obj_time;//�I�u�W�F�N�g����������Ă���̃^�C���𒲂ׂ�
			bool stop_flag;//�I�u�W�F�N�g���~�܂��Ă��邩���ׂ邽�߂̃t���O
			bool process_check;//�����ς����ׂ�t���O
			int before_num;//�O��̏������̐�����ۊǂ���
			int stop_time;//���̃u���b�N���Ƃ܂��Ă��鎞�Ԃ�ۑ�����
		};

		MAP m_map[7][20];	//�}�b�v���u���b�N��(X=20,Y=7)	

		bool m_vc_r;//���s�̃`�F�b�N�t���O�i�E�j
		bool m_vc_l;//���s�̃`�F�b�N�t���O�i���j

		int m_count_time;//�X�^�[�g�J�n�O�̃J�E���g�_�E��
		float font_big_time;//�������傫���Ȃ鎞��
		bool flag;//�Q�[���I�[�o�[�Ǘ�

		//�f�o�b�O�p
		int ojm_num;//���ז��̐���ۑ�
		int del_num;//�ŏI�I�ɏ�������ۑ�
		int sum_num;//���ז��ӂ��߂�����ۑ�	

		//AI�p�̕ϐ�
		int BlockStopPoint[7];

		//�����L���O�p�̃^�C���v���p
		int m_time;
};
