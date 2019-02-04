#include "UtilityModule.h"

//---UnitVec関数
//引数1　float* vx	:ベクトルｘ成分のポインタ
//引数2　float* yx	:ベクトルｙ成分のポインタ
//戻り値　bool　:true=計算成功

bool UnitVec(float* vx,float* vy)
{
	//ベクトルの長さを求める(3平方の定理)
	float r=0.0f;
	r=(*vx)*(*vx)+(*vy)*(*vy);
	r=sqrt(r);//ｒの√を求める

	//長さが0かどうか調べる
	if(r==0.0f)
	{
		return false;//0なら計算失敗
	}
	else
	{
		//正規化を行い、vxとvyの参照先の値を変更
		(*vx)=1.0f/r*(*vx);
		(*vy)=1.0f/r*(*vy);
	}

	//計算成功
	return true;
}

//checkWindow関数
//引数1　float pos_x:領域外か調べるx位置
//引数2　float pos_y:領域外か調べるy位置
//引数3　float window_x:領域のtop位置
//引数4　float window_y:領域のleft位置
//引数5　float window_w:領域のright位置
//引数6　float window_h:領域のbottom位置
//戻り値　bool :true=領域ない flse=領域外

//領域内かどうか調べる位置pos_(xy)がwindow_(xywh)の内か外かを調べる

bool CheckWindow(float pos_x,float pos_y,
	float window_x,float window_y,float window_w,float window_h)
{
	
	//領域外に出たら破棄する
	if(pos_x<window_x)
	{
		return false;//領域外
	}
	if(pos_x>window_w)
	{
		return false;//領域外
	}
	if(pos_y<window_y)
	{
		return false;//領域外
	}
		if(pos_y>window_h)
	{
		return false;//領域外
	}

	return true;//領域内
}

//----GetAtan2Angle関数
//引数１ float w 幅
//引数２ float h 高さ
//戻り値　float 角度
//内容
//高さと幅から直角三角形があると仮定しその角度を求める
float GetAtan2Angle(float w,float h)
{
	float r=atan2(h,w)*180.0f/3.14f;
		if(r<0)
		{
			r=360-abs(r);
		}
		return r;
}

//GetBulletEffect関数
//引数1 int* ani
//引数2 int* ani_time
//引数3 bool del
//引数4 int timeing
//戻り値　RECT_F eff
//delで弾丸のRECTや着弾effectのRECT(アニメーションのRECT）を返す
RECT_F GetBulletEffec(int* ani,int* ani_time,bool del,int timing)
{
	//返すＲＥＣＴ情報
	RECT_F rect;

	//フラグで通常弾丸か着弾アニメーション分岐
	if(del==true)
	{
		//着弾アニメーション
		//リソース着弾アニメーション位置
		RECT_F ani_src[4]=
		{
			{32,0,32,64},
			{32,32,64,64},
			{32,64,96,64},
			{32,96,128,64},
		};

		//アニメーションのコマ感覚
		if(*ani_time>timing)
		{
			*ani+=1;//アニメーションのコマを一つ進める
			*ani_time=0;
		}
		else
		{
			*ani_time+=1;
		}

		rect=ani_src[*ani];//アニメーションのＲＥＣＴ配列からm_ani番目のRECT情報を渡す
	}
	
	else 
	{
		//弾丸アニメーションなし
		//リソース弾丸位置
		RECT_F bullet={0.0f,126.0f,158.0f,32.0f};
		rect =bullet;
	}
	return rect;
}
