//---------------------------------------------
// Color Block Move Check
// Collision Check
// 2017-06-12 Monday Released
// By カラスアゲハ
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

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBlock::CObjBlock(float x,float y,int color,bool lr,bool sk )
{
	m_px=x;
	m_py=y;
	m_color=color;
	m_lr=lr;
	m_skip=sk;
}

//イニシャライズ
void CObjBlock::Init()
{
	if(m_lr==true)
	{
		//左機体から作られたブロック
		m_vx=1.0f;
	}
	else
	{
		//右機体から作られたブロック
		m_vx=-1.0f;
	}

	srand(time(NULL)); // ランダム情報を初期化

	m_time=0;//タイムの初期化
	
	m_stop_flag=false;//ストップフラグ

	m_Processing_flag=false;//未処理状態にする

	//消滅処理関連の初期化------------
	m_eff.m_top	  = 32;
	m_eff.m_left  =  0;
	m_eff.m_right = 32;
	m_eff.m_bottom= 64;
	m_ani=0;
	m_ani_time=0;
	m_del=false;
	//--------------------------------

	m_se=true;//SE用のフラグの初期化
	
	m_gemeover_check=false;//ゲームオーバーチェックフラグの初期化

	//デバッグ用　判定用HitBoxを作成
	Hits::SetHitBox(this,m_px*BLOCK_SIZE+60.0f,m_py*BLOCK_SIZE+80.0f,BLOCK_SIZE/2,BLOCK_SIZE/2,ELEMENT_NULL,OBJ_BLOCK,1);
	
	move_check = true;
}
//アクション
void CObjBlock::Action()
{
	//メインオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	//ゲームオーバーオブジェクトの有無を調べる
	m_gemeover_check = obj->GameOverCheck();

	//ゲームオーバーオブジェクトがあれば
	if(m_gemeover_check == true)	return ;
	
	m_time++;
	
	if(m_time>1000)//1000を超えないようにする
		m_time=0;

	//Blockが停止したとき（1回のみ）--------------------------------
	//移動処理の後からここに移動させた（2017-06-23）
	if(m_stop_flag==true)
	{
		if(m_Processing_flag==false)//処理が実行されていないなら
		{
			Disappear();//消滅処理関数の呼び出しなど、ブロックがとまったときの処理をする関数
		}
	}
	//-----------------------------------------------------------------------
		
	//消滅処理-----------------------------------------
	if(obj->ReturnNum(m_px,m_py)==98)//98が入っていれば
	{
		m_del=true; //消滅処理のフラグを立てる
	}

	if(m_del==true)//消滅処理のフラグがたっていれば
	{
		DeleteAnimetion();//消滅とアニメーションの処理をする
		return;
	}
	//---------------------------------------
		
	Check();//移動できるかチェックする	

	if(move_check == true)//移動可能なら
	{
		//10fに1回処理する-----------------
		if(m_time%10==0)
		{
			Move();//移動処理をする
		}
		//------------------------------------
		m_se=true;//se管理フラグオン

		Check();//次に移動できるか調べる(二重チェック)

		if( move_check == true )//次に移動でれば
		{
			m_stop_flag = false;//ストップフラグをオフにする
		}
		else
		{
			m_stop_flag = true;//自身のストップフラグをオンにする
		}					
	}
	else//移動不可
	{
		if(m_se==true)
		{
			Audio::Start(2);//SEを鳴らす
			m_se=false;//フラグをオフにする
		}
		m_stop_flag = true;
	}			
	
	//マップ構造体の更新-----------------------------
	//消滅処理中でなければ
	if(m_del==false)
		obj->Enter(m_px,m_py,m_color);//移動後の位置に自分の色を入れる
	
	//ストップフラグ更新
	obj->EnterStopFlag(m_px,m_py,m_stop_flag);
	//処理フラグ更新
	obj->Processflag(m_px,m_py,m_Processing_flag);
	//-------------------------------------------------

	//hitboxの更新
	CHitBox* hit=Hits::GetHitBox(this); 
	hit->SetPos(m_px*BLOCK_SIZE+60.0f,m_py*BLOCK_SIZE+80.0f);
}


//ドロー
void CObjBlock::Draw()
{
	//描画カラー情報
	float c[4]={1.0f,1.0f,1.0f,1.0f};

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置をセットする
	RectSet(0.0f,0.0f,64.0f,64.0f,src);
	
	//描画位置をセットする
	RectSet( 80.0f + m_py * BLOCK_SIZE ,50.0f + m_px * BLOCK_SIZE ,
		50.0f + m_px * BLOCK_SIZE + BLOCK_SIZE , 80.0f + m_py * BLOCK_SIZE + BLOCK_SIZE , dst);

	//ブロックの描画
	Draw::Draw(m_color,&src,&dst,c,0.0f);

	if(m_del==true)//爆発処理フラグがオンなら
	{
		//爆破アニメーション処理
		Draw::Draw(10,&m_eff,&dst,c,0.0f);
	}
}

//移動処理の関数
void CObjBlock::Move()
{
	//メインオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	if(m_lr==true)
	{
		//左

		obj->Enter(m_px,m_py,99);//移動前の位置を99にする
		obj->StopFlagOff(m_px,m_py);//移動前の位置のストップフラグをオフにする
				
		m_px+=m_vx;//位置の更新
	}
	else
	{
		//右

		if(m_skip!=true )//スキップブロック(右側で横向きに打った場合の左側に来るブロック）でなければ
		{	
			obj->Enter(m_px,m_py,99);//移動前の位置を99にする
		}
		obj->StopFlagOff(m_px,m_py);//移動前の位置のストップフラグをオフにする
				
		m_px+=m_vx;//位置の更新
	}
}

//移動できるかのチェック
void CObjBlock::Check()
{
	if(m_px<9||m_px>10)//中央ラインのすぐ隣ではないなら
	{
		move_check=MoveCheck(m_px+m_vx,m_py);//移動先の確認
	}
	else//すでに中央の位置にいる場合
	{
		move_check = false;//移動不可
	}
}

//移動先のチェック関数
//引数1：調べる位置のx座標（m_px+m_vx）
//引数2：調べる位置のy座標
//移動可能ならtrueを、無理ならfalseを返す
bool CObjBlock::MoveCheck(int x,int y)
{
	int  num_check;//数値の確認
	bool stop_check;//ストップフラグの確認
			
	//メインオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	num_check  = obj->ReturnNum(x,y);//一つ先の数を持ってくる
	stop_check = obj->ReturnStopFlag(x,y);//一つ先のストップフラグを持ってくる

	//もし一つ先がカラーブロックなら（おじゃま6含む）
	if( (0 <= num_check ) && ( num_check <= 6 ) )
	{
		if( stop_check == false )//ストップフラグがオフなら
		{
			return true;//移動可能
		}
		else
		{
			return false;//移動不可
		}
	}
	else 
	{
		if( num_check == 98 )//消滅処理中
		{
			return false;
		}
		else if( num_check == 99 )//空白
		{
			return true;
		}
	}
}

//消滅処理関数の呼び出しなど、ブロックがとまったときの処理をする関数
void CObjBlock::Disappear()
{			
	//メインオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	bool stop_check_flag = obj->StopCheck(m_py,m_lr);//自陣のその段が全てとまっているか調べ保存する
	
	//その段の自陣が全て止まっているなら
	if( stop_check_flag == true)// ; ->  2017-06-26
	{
		switch(m_lr)
		{
			case true://左側プレーヤー
			{
				Left_Dis();//左側の消滅処理を呼び出す前の調整をする関数
			}
			break;

			case false://右側プレーヤー
			{
				Right_Dis();//右側の消滅処理を呼び出す前の調整をする関数
			}
			break;
		}
	}
}


//左側の消滅処理を呼び出す前の調整をする関数
void CObjBlock::Left_Dis()
{
	//メインオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	int n=obj->ReturnNum(m_px-1,m_py);//一つ左のマスの数値を保存する
	
	static int lplayerblockcheck=0;
	bool m_wh;//ブロックの向きを保存　true:横　false:縦
	
	m_wh = CheckWH(n,lplayerblockcheck);//ブロックの向きを調べる
	
	//向きに応じて処理をする---------------------------------------------------
	if(m_wh == false)
	{
		//縦向き
		obj->CheckMap(m_px,m_py,m_lr);//消滅処理関数を呼び出す	
		//処理済みフラグを立てる
		m_Processing_flag=true;
	}
	else 
	{
		//横向き
		//横2連ブロックのチェック 2017-05-26
		switch(lplayerblockcheck)
		{
			case 0://内側
			{
				m_delete_check[0] = obj->BlockDeleteCheck( m_px		, m_py ,m_lr );//内側の消す数
				m_delete_check[1] = obj->BlockDeleteCheck( m_px - 1	, m_py ,m_lr );//外側の消す数

				//内側の消す数の方が多い 
				if( m_delete_check[0]>m_delete_check[1] )
					obj->CheckMap( m_px , m_py , m_lr );//消滅処理関数を呼び出す				
							
				lplayerblockcheck=1;//static変数を更新

				//処理済みフラグを立てる
				m_Processing_flag=true;								
			}
			break;
			case 1://外側
			{
				m_delete_check[0] = obj->BlockDeleteCheck( m_px + 1 , m_py , m_lr );//内側の消す数
				m_delete_check[1] = obj->BlockDeleteCheck( m_px		, m_py , m_lr );//外側の消す数

				//外側の消す数の方が多い場合 または　外側と内側の消す数が同じ(0以外)の場合
				if( ( m_delete_check[0] < m_delete_check[1] ) || ( m_delete_check[0] == m_delete_check[1] ) && m_delete_check[0] != 0 )
					obj->CheckMap( m_px , m_py , m_lr );//滅処理関数を呼び出す
				
				lplayerblockcheck=0;//static変数を更新

				//処理済みフラグを立てる
				m_Processing_flag=true;																
			}
			break;
		}
	}
	//-----------------------------------------------------------------------
}

//右側の消滅処理を呼び出す前の調整をする関数
void CObjBlock::Right_Dis()
{
	//メインオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);
	
	int n=obj->ReturnNum(m_px+1,m_py);//一つ右のマスの数値を記憶する

	bool m_wh;//true：横　false：縦
	static int rplayerblockcheck=0;
	
	m_wh = CheckWH(n,rplayerblockcheck);//ブロックの状態が縦か横かどうか調べる	
		
	//向きに応じて処理をする---------------------------------------------------------------------
	if(m_wh == false)
	{
		//縦向き
		obj->CheckMap(m_px,m_py,m_lr);//消滅処理関数を呼び出す
		//処理済みフラグを立てる
		m_Processing_flag=true;
	}
	else 
	{
		//横向き
		//横2連ブロックのチェック 2017-05-26
		switch(rplayerblockcheck)
		{
			case 0://内側
			{
				m_delete_check[0] = obj->BlockDeleteCheck( m_px		, m_py , m_lr );//内側の消す数
				m_delete_check[1] = obj->BlockDeleteCheck( m_px + 1 , m_py , m_lr );//外側の消す数

				//内側の消す数の方が外側の消す数より多い　
				if( m_delete_check[0] > m_delete_check[1] )
					obj->CheckMap( m_px , m_py , m_lr );//消滅処理関数を呼び出す				
				
				//処理済みフラグを立てる
				m_Processing_flag=true;					

				rplayerblockcheck=1;//static変数を更新する
			}
			break;
			case 1://外側
			{
				m_delete_check[0] = obj->BlockDeleteCheck( m_px - 1 , m_py , m_lr );//内側の消す数
				m_delete_check[1] = obj->BlockDeleteCheck( m_px		, m_py , m_lr );//外側の消す数

				//外側の消す数の方が多い または　消す数が同じ(0以外)なら
				if( ( m_delete_check[0] < m_delete_check[1] ) || ( m_delete_check[0] == m_delete_check[1] ) && m_delete_check[0] != 0 )
					obj->CheckMap( m_px , m_py , m_lr );//消滅処理関数を呼び出す
				
				//処理済みフラグを立てる
				m_Processing_flag=true;
				
				rplayerblockcheck=0;//static変数を更新する
			}
			break;
		}
	}
	//-------------------------------------------------------------------------
}

//ブロックの向きを調べて返す関数
//引数1：static変数をもってくる
//引数2：１つ外側のｘ座標をもってくる
//戻り値：　true：横　false：縦　
bool CObjBlock::CheckWH(int n,int staticnum )
{
	//ブロックのstatic変数が１なら
	if( staticnum ==1)
	{
		return true;//横
	}
	else if( n >= 0 && n <=5 )//１つ外側にブロックがあれば
	{
		return true;//横
	}
	else //それ以外
	{
		return false;//縦
	}
}

//消滅＆アニメーションをする関数
void CObjBlock::DeleteAnimetion()
{
	//メインオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	//アニメーションRECT情報
	RECT_F ani_src[4] = 
	{
		{ 32,  0, 32, 64},
		{ 32, 32, 64, 64},
		{ 32, 64, 96, 64},
		{ 32, 96,128, 64},
	};
	//　05/26 14:04-------------------------------------
	m_ani_time++;
	//アニメーションのコマ間隔制御
	if(m_ani_time>2)
	{
		m_ani_time=0;
		m_ani++;			//アニメーションのコマを１つ進める
				
		//爆破アニメーション終了でオブジェクト破棄
		if(m_ani==4)
		{
			m_ani=0;
			Audio::Start(3);//爆発音再生
			m_del=false;
			obj->Enter(m_px,m_py,99);//消滅アニメが終われば空白にする
										//ただし、セルの表示は、残っているので要注意
										//このあとの、処理でブロックは移動させないこと
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
		else
		{		
			m_eff=ani_src[m_ani];//アニメーションのRECT配列からm_ani番目のRECT情報を取得
		}
	}
}