#pragma once

//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�l�[������
class CObjNameInput :public CObj
{
public:
	CObjNameInput(int rank);
	~CObjNameInput() {};
	void Init();//�C�j�V�����C�Y
	void Action();//�A�N�V����
	void Draw();//�h���[

	bool KeyInput(int number);	//�l�[�����͂̃L�[�{�[�h���當����ǂݎ��֐�
	bool InputEndCheck();		//��������͂��I����Ă��邩(\0�����邩)���ׂ�֐�
	void NameCpy(char name[]);//������̕������ƊԂɔ��p�󔒂������֐�

private:
	char m_name[6];		//���͂��ꂽ���O�̕ۑ��p
	char m_cpy_name[11];//wchar_t�ɕϊ����鎞�p�̔z��
	bool m_first_flag;	//�ŏ���1�񂾂��������Ȃ��悤�ɂ��邽�߂̃t���O
	bool m_key_flag;	//�L�[�����͉\�ȏ�Ԃ��ǂ�����\���t���O
	bool m_input_flag;	//�L�[���͂��ꂽ���ǂ�����\���t���O
	bool m_end_flag;	//���O�̓��͂��I�����Ă��邩�ǂ����̃t���O
	bool m_noname_flag;	//�������͂�����Enter���������ꍇ�ɒ��ӕ����o�����߂̃t���O
	bool m_time_flag;	//�����̓_�ŗp�t���O�@true:�\����	false:�����Ă鎞
	int m_input_count;	//���͂����񐔂̃J�E���^�[�B
	int m_rank;			//�����L���O�̏���
	int m_time;			//�����̓_�ŗp�^�C��
};