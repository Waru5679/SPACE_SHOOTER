//---------------------------------------------
// Intervention Block Move Check
// Collision Check
// 2017-06-12 Monday Released
// By カラスアゲハ
//---------------------------------------------
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "CObjIntervention.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjIntervention::CObjIntervention(float x,float y,bool lr)
{
	m_px=x;
	m_py=y;
	m_lr=lr;
}

//イニシャライズ
void CObjIntervention::Init()
{
	if(m_lr==true)
	{
		m_vx=1.0f;
	}
	else
	{
		m_vx=-1.0f;
	}
	//判定用HitBoxを作成
	Hits::SetHitBox(this,m_px*BLOCK_SIZE+60.0f,m_py*BLOCK_SIZE+80.0f,BLOCK_SIZE/2,BLOCK_SIZE/2,ELEMENT_NULL,OBJ_BLOCK,1);
	m_time=0;

	m_Processing_flag=false;
	m_se=true;
	m_gameover_check=false;
	m_stop_flag=false; // ==になっていたのを修正(2017-06-28)
	move_check=true;
}
//アクション お邪魔キャラの移動
void CObjIntervention::Action()
{
	//メインオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	//ゲームオーバーオブジェクトの有無を調べる
	m_gameover_check = obj->ReturnFlag();
	
	//ゲームオーバーオブジェクトがあれば
	if(m_gameover_check==true) return;
	
	m_time++;
		
	if(m_time>1000)//1000を超えないようにする
		m_time = 0;

	Check();//移動できるかチェックする

	//移動可能の場合
	if(move_check == true)
	{
		//10fに１回処理する--------------------------------
		if(m_time%10==0)
		{
			Move();//移動のチェックと移動をする
		}
		//------------------------------------------------

		Check();//次のとき移動できるかチェックする(二重チェック)

		if( move_check ==true)
		{
			//移動可能なら
			m_stop_flag = false;//ストップフラグをオフにする	
		}
		else
		{
			//移動不可
			m_stop_flag=true;//ストップフラグをオンにする
		}
	}
	else//移動不可（ブロックがある）
	{
		m_Processing_flag=true;//処理済みフラグを立てる
		m_stop_flag = true;//ストップフラグをオンにする
	}
		
	//マップ構造体の更新
	obj->Enter(m_px,m_py,6);//お邪魔ブロックは6番に設定
	obj->Enter_Stop_flag(m_px,m_py,m_stop_flag);//ストップフラグをマップ構造体に入れる
	obj->Processflag(m_px,m_py,m_Processing_flag);//消滅処理用のフラグをマップに入れる

	//hitboxの更新
	CHitBox* hit = Hits::GetHitBox(this); 
	hit->SetPos( m_px * BLOCK_SIZE + 60.0f , m_py * BLOCK_SIZE + 80.0f );
}

//ドロー
void CObjIntervention::Draw()
{
	//描画カラー情報
	float c[4]={1.0f,1.0f,1.0f,1.0f};

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	RectSet(0.0f,0.0f,32.0f,32.0f,src);

	//表示位置の設定
	RectSet(80.0f+m_py*BLOCK_SIZE,50.0f+m_px*BLOCK_SIZE,
		50.0f+m_px*BLOCK_SIZE+BLOCK_SIZE,80.0f+m_py*BLOCK_SIZE+BLOCK_SIZE,dst);

	Draw::Draw(6,&src,&dst,c,0.0f);//描画
}

//移動処理の関数
void CObjIntervention::Move()
{
	//メインオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	if(m_lr==true)
	{
		//左
		if( m_px+m_vx<=9 )//移動先が中央より左でかつ移動可能なら
		{
			obj->Enter(m_px,m_py,99);//移動前の位置を99にする
			obj->StopFlag_OFF(m_px,m_py);//移動前の位置のストップフラグをオフにする
		
			m_px+=m_vx;//位置を更新
		}
		if(m_se==true)
		{
			Audio::Start(4);//発射音再生
			m_se=false;
		}
	}
	else
	{
		//右
		if( m_px+m_vx>=10 )//移動先が中央より右でかつ移動可能なら
		{
			obj->Enter(m_px,m_py,99);//移動前の位置を99にする
			obj->StopFlag_OFF(m_px,m_py);//移動前の位置のストップフラグをオフにする
			
			m_px+=m_vx;//位置を更新
		}
		if(m_se==true)
		{
			Audio::Start(4);//発射音再生
			m_se=false;
		}
	}
}

//移動できるかどうかのチェック用
void CObjIntervention::Check()
{
	//ブロックオブジェクトの呼び出し
	CObjBlock * obj_b =(CObjBlock*)Objs ::GetObj(OBJ_BLOCK);

	if(m_px<9 || m_px>10)//移動できる可能性がある位置なら
	{			
		move_check = obj_b->MoveCheck(m_px+m_vx,m_py);//移動できるかのチェック関数を呼び出す
	}
	else//すでに中央の位置にある場合
		move_check=false;
}