#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�b�v���\����
struct MAP
{	int Num;		//�u���b�N�̎�ނ̐���
	int ObjTime;	//�I�u�W�F�N�g����������Ă���̃^�C���𒲂ׂ�
	int BeforeNum;	//�O��̏������̐�����ۊǂ���
	int StopTime;	//���̃u���b�N���Ƃ܂��Ă��鎞�Ԃ�ۑ�����

	bool bStop;		//�I�u�W�F�N�g���~�܂��Ă��邩
	bool bProcess;	//�����ς�
	bool bCreate;	//�I�u�W�F�N�g�������ς݂�

};

//�I�u�W�F�N�g�F���C��
class CObjMain : public CObj
{
public:
	CObjMain(bool tipe) { m_bCpBattle = tipe; }
	~CObjMain() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	void MapUpdate();//�}�b�v�X�V

	//�w�肵���}�b�v�v�f�Ɏw�肵���l�������֐�
	void Enter(int x, int y, int n)	{m_map[y][x].Num = n;}

	//�w�肵���}�b�v�v�f�̒l��Ԃ��֐�
	int ReturnNum(int x, int y) { return m_map[y][x].Num; }

	//�I�u�W�F�N�g��������̎��Ԃ�Ԃ�
	int ReturnObjTime(int x, int y) { return m_map[y][x].ObjTime; }

	//���ז��u���b�N�̐���
	void CreateIntervention(int number, bool m_lr);

	//�w�肵���}�b�v�v�f�̐����t���O���I���ɂ���
	void FlagOn(int x, int y) { m_map[y][x].bCreate = true; }

	//�w�肵���}�b�v�v�f�̃X�g�b�v�t���O��؂�ւ�
	void StopFlagOn(int x, int y) { m_map[y][x].bStop = true; }
	void StopFlagOff(int x, int y) { m_map[y][x].bStop = false; }

	//�w�肵���v�f�Ɏw�肵���X�g�b�v�t���O������֐�
	void EnterStopFlag(int x, int y, bool Stop) { m_map[y][x].bStop = Stop; }

	//�w�肵���}�b�v�v�f�̃X�g�b�v�t���O��Ԃ��֐�
	bool ReturnStopFlag(int x, int y) { return m_map[y][x].bStop; }

	//�w�肵���}�b�v�v�f�̏����t���O���w�肵�����̂ɒu��������
	void Processflag(int x, int y, bool Process) { m_map[y][x].bProcess = Process; }

	//�����`�F�b�N�t���O��Ԃ�
	int ReturnProcess(int x, int y) { return m_map[y][x].bProcess; }

	//�w�肵���i�̉E(�܂��͍�)�����̃X�g�b�v�t���O���I���Ȃ�true:��ł��I�t�Ȃ�false�@��Ԃ��֐�
	bool StopCheck(int y, bool lr);

	//�E�����܂��͍������̃u���b�N���S�Ď~�܂��Ă��邩�ǂ������ׂ�
	bool ShotCheck(bool lr);

	//�Ȃ����Ă���u���b�N�̐��𐔂��ď�����Ȃ���ŏ���������֐�
	void CheckMap(int x, int y, bool check);

	//�Ȃ����Ă���u���b�N�̐��𐔂��Ă��̐���Ԃ��֐�	
	int BlockDeleteCheck(int x, int y, bool lr);

	//�^�C����Ԃ�
	int ReturnTime() { return m_Time; }
	
	//�w�肵���͈͂Ɏw�肵���u���b�N�����邩�ǂ������ׂ�֐�
	int BlockCheck(int y, bool lr, int n);
	
	//���s�̔���p
	bool VictoryCheck(bool lr);
	
	//�Q�[���I�[�o�[�`�F�b�N�̃t���O��Ԃ�
	bool GameOverCheck() { return m_bGameOver; }

	//�������莞�̃Q�[���I�[�o�[�쐬�Ȃǂ̏����������
	void VictoryProcess(bool vs_CP);
	
//VSCP�p-------------------------------
	//AI�p�u���b�N��������ʒu��T���֐�(�u���b�N�c�z��)
	void AiDeleteCheck_H(int color1, int color2, int r);
	
	//AI�p�u���b�N��������ʒu��T���֐�(�u���b�N���z��)
	void AiDeleteCheck_W(int color1, int color2, int r);
	
	//���ꂼ��̒i�̂ǂ��Ńu���b�N���Ƃ܂邩�𒲂ׂ�
	void StopPointCheck();

	//�u���b�N���~�܂�ʒu�̂Ȃ��ň�ԏ������ʒu��T���A��������΂��̒����烉���_���łP���߂�
	int InSideCheck();
//-------------------------------------
	
	//CP�킩�̃t���O��Ԃ��֐�
	bool ReturnCPflag() { return m_bCpBattle; }	

private:
	MAP m_map[7][20];		//�}�b�v���u���b�N��(X=20,Y=7)

	int m_CountTime;		//�X�^�[�g�J�n�O�̃J�E���g�_�E��
	int m_FontBigTime;		//�������傫���Ȃ鎞��
	int m_Time;				//�����L���O�p�̃^�C���v���p
	int m_BlockStopPoint[7];//�u���b�N�̎~�܂�ʒu(AI�p)

	bool m_bGameOver;	//�Q�[���I�[�o�[�Ǘ�
	bool m_bRightWin;	//���s�̃`�F�b�N
	bool m_bLeftWin;	//���s�̃`�F�b�N
	bool m_bCpBattle;	//CP�킩�Q���킩��ʂ���
};
