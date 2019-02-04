#include "UtilityModule.h"

//---UnitVec�֐�
//����1�@float* vx	:�x�N�g���������̃|�C���^
//����2�@float* yx	:�x�N�g���������̃|�C���^
//�߂�l�@bool�@:true=�v�Z����

bool UnitVec(float* vx,float* vy)
{
	//�x�N�g���̒��������߂�(3�����̒藝)
	float r=0.0f;
	r=(*vx)*(*vx)+(*vy)*(*vy);
	r=sqrt(r);//���́�����߂�

	//������0���ǂ������ׂ�
	if(r==0.0f)
	{
		return false;//0�Ȃ�v�Z���s
	}
	else
	{
		//���K�����s���Avx��vy�̎Q�Ɛ�̒l��ύX
		(*vx)=1.0f/r*(*vx);
		(*vy)=1.0f/r*(*vy);
	}

	//�v�Z����
	return true;
}

//checkWindow�֐�
//����1�@float pos_x:�̈�O�����ׂ�x�ʒu
//����2�@float pos_y:�̈�O�����ׂ�y�ʒu
//����3�@float window_x:�̈��top�ʒu
//����4�@float window_y:�̈��left�ʒu
//����5�@float window_w:�̈��right�ʒu
//����6�@float window_h:�̈��bottom�ʒu
//�߂�l�@bool :true=�̈�Ȃ� flse=�̈�O

//�̈�����ǂ������ׂ�ʒupos_(xy)��window_(xywh)�̓����O���𒲂ׂ�

bool CheckWindow(float pos_x,float pos_y,
	float window_x,float window_y,float window_w,float window_h)
{
	
	//�̈�O�ɏo����j������
	if(pos_x<window_x)
	{
		return false;//�̈�O
	}
	if(pos_x>window_w)
	{
		return false;//�̈�O
	}
	if(pos_y<window_y)
	{
		return false;//�̈�O
	}
		if(pos_y>window_h)
	{
		return false;//�̈�O
	}

	return true;//�̈��
}

//----GetAtan2Angle�֐�
//�����P float w ��
//�����Q float h ����
//�߂�l�@float �p�x
//���e
//�����ƕ����璼�p�O�p�`������Ɖ��肵���̊p�x�����߂�
float GetAtan2Angle(float w,float h)
{
	float r=atan2(h,w)*180.0f/3.14f;
		if(r<0)
		{
			r=360-abs(r);
		}
		return r;
}

//GetBulletEffect�֐�
//����1 int* ani
//����2 int* ani_time
//����3 bool del
//����4 int timeing
//�߂�l�@RECT_F eff
//del�Œe�ۂ�RECT�⒅�eeffect��RECT(�A�j���[�V������RECT�j��Ԃ�
RECT_F GetBulletEffec(int* ani,int* ani_time,bool del,int timing)
{
	//�Ԃ��q�d�b�s���
	RECT_F rect;

	//�t���O�Œʏ�e�ۂ����e�A�j���[�V��������
	if(del==true)
	{
		//���e�A�j���[�V����
		//���\�[�X���e�A�j���[�V�����ʒu
		RECT_F ani_src[4]=
		{
			{32,0,32,64},
			{32,32,64,64},
			{32,64,96,64},
			{32,96,128,64},
		};

		//�A�j���[�V�����̃R�}���o
		if(*ani_time>timing)
		{
			*ani+=1;//�A�j���[�V�����̃R�}����i�߂�
			*ani_time=0;
		}
		else
		{
			*ani_time+=1;
		}

		rect=ani_src[*ani];//�A�j���[�V�����̂q�d�b�s�z�񂩂�m_ani�Ԗڂ�RECT����n��
	}
	
	else 
	{
		//�e�ۃA�j���[�V�����Ȃ�
		//���\�[�X�e�ۈʒu
		RECT_F bullet={0.0f,126.0f,158.0f,32.0f};
		rect =bullet;
	}
	return rect;
}
