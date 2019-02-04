//使用するヘッダーファイル
#include <stdlib.h>
#include <time.h>
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"
#include "ObjCP.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjCP::Init()
{
	m_x=WINDOW_SIZE_W-54;
	m_y=WINDOW_SIZE_H/3.5f;
	m_f=true;
	m_vx=0.0f;
	m_vy=0.0f;
	m_move=3;
	m_r=0;
	m_rf=true;
	m_bullet_count=0;
	m_move_f=true;//移動処理のフラグ

	srand(time(NULL)); // ランダム情報を初期化
	
	for(int i=0;i<4;i++)
	{
		m_npc[i]=rand() % 6;  // このように記述するとnpcには０～5までの値が入ります
	}

	//ブロック同士の中間点を決める
	m_senter.x=WINDOW_SIZE_W-(BLOCK_SIZE+(BLOCK_SIZE/2));
	m_senter.y=(WINDOW_SIZE_H-8.0f)-(BLOCK_SIZE*2);

	//m_senterと描画の基準点（左上か右下）との差（絶対値）
	m_drow.x=BLOCK_SIZE/2;
	m_drow.y=BLOCK_SIZE;
	
	//弾を撃つ位置の保存用--------
	m_shot_x[0]=-1;
	m_shot_x[1]=-1;

	m_shot_x[0]=-1;
	m_shot_x[1]=-1;
	//----------------------------

	//移動の制御フラグ初期化
	m_down	= true;
	m_up	= true;

	//スタート制御----
	m_count_time=0;

	//ゲームオーバーオブジェクトの有無チェック
	m_end_flag=false;

	//ゲージ用＆強制発射制御用
	m_gauge_time=360;

	//お邪魔ブロックを降らす数
	ojm_num=0;
	
	//発射制御
	m_shoot_time = 360;

	//AI関連-----------------------------
	d_count=0;

	for(int i=0;i<D_POINT_MAX;i++)
	{
		D_Point[i].Delete.x = -1;
		D_Point[i].Delete.y = -1;
		D_Point[i].num=-1;
		D_Point[i].rad=-1;
	}
	//----------------------------------
}

//アクション
void CObjCP::Action()
{
	m_count_time++;
	
	if(m_count_time>=10000)
		m_count_time=270;

	//AI関連の初期化------
	d_count=0;

	for(int i=0;i<D_POINT_MAX;i++)
	{
		D_Point[i].Delete.x = -1;
		D_Point[i].Delete.y = -1;
		D_Point[i].num=-1;
		D_Point[i].rad=-1;
	}
	//Ai関連の初期化　終わり-----

	//ゲームオーバーがなければ
	if(m_end_flag==true) return;
	
	//マップオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);
	
	//スタートカウントがある場合
	if(m_count_time < 270) return;
			
	//ゲージがmax　かつ　お邪魔生成が必要なら
	if(m_gauge_time==360 && ojm_num != 0)
	{
		if( obj->ShotCheck(false) ==true)//自陣のブロック全てがとまっているか確認する
		{
			//自陣のブロック全てがとまっていればd
			obj->CreateIntervention(ojm_num,false);//お邪魔ブロック生成
			ojm_num=0;//生成が終わったら0にする
			return;
		}
	}
	
	Shot_move();//移動、回転、弾を撃つ処理をする関数
		
}

//移動、回転、弾の発射をする関数
void CObjCP::Shot_move()
{
	//マップオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	if(m_count_time % 5 == 0)//5フレームごとに
	{
		m_rf=true;//回転できるようにする
		m_move_f=true;//移動できるようにする
	}

	d_count=0;
	
	//自分のブロックがとまっている場合
	if( obj->ShotCheck(false) ==true)
	{
		m_shoot_time-=2;

		if(m_shoot_time<0)
			m_shoot_time=0;
	}

	//消せるかどうかのチェックをする
	obj->AiDeleteCheck_H(m_npc[m_bullet_count],m_npc[m_bullet_count+1],0);//縦想定
	obj->AiDeleteCheck_W(m_npc[m_bullet_count],m_npc[m_bullet_count+1],1);//横想定

	//色の配置を入れ替える（2回転した場合で消せるかのチェックをする）
	obj->AiDeleteCheck_H(m_npc[m_bullet_count+1],m_npc[m_bullet_count],2);//縦想定
	obj->AiDeleteCheck_W(m_npc[m_bullet_count+1],m_npc[m_bullet_count],3);//横想定

	//タイムが０　かつ　D_Point[0].Delete.yが初期値(移動先が決まっていない)なら
	 if(m_shoot_time==0 && D_Point[0].Delete.y == -1)
	 {
		D_Point[0].Delete.y = obj->InSideCheck();//一番内側で止まる位置からランダムでとりだす
	 }
				
	//自分のブロックがとまっている場合
	if( obj->ShotCheck(false) ==true)
	{
		//D_Point[0].Delete.yが初期の値じゃない場合(消せる位置があるばあい)
		if(D_Point[0].Delete.y!=-1)
		{
			//同じ場所になった場合
			if(D_Point[0].Delete.y == m_move)
			{
				//ブロックの回転同じなら
				if(m_r != D_Point[0].rad)		
				{
					Shot();//発射
					m_shoot_time = 360; //発射までの時間を初期化	
					m_r=0;//回転情報を初期化
				}
				else
				{
					Revolution();//ブロックを回転させる		
				}
			}
		
			//yより下なら上に移動
			if(D_Point[0].Delete.y < m_move) 
			{
				m_move--;
				m_y += -BLOCK_SIZE;
				m_move_f=false;//移動フラグをオフにする
			}
			//yより上なら下に移動
			else if(D_Point[0].Delete.y > m_move)
			{
				m_move++;
				m_y += BLOCK_SIZE;
				m_move_f=false;//移動フラグをオフにする
			}
		}
	}
}


//ドロー
void CObjCP::Draw()
{
	//描画カラー情報　R=RED G=Green B=Blue A=alpha(透過情報)
	float c[4]={1.0f,1.0f,1.0f,1.0f};//通常
	float c1[4]={1.0f,1.0f,1.0f,0.5f};//ブロック位置予測用
	float str_c[4]={0.0f,0.0f,0.0f,1.0f};//文字表示用

	RECT_F src;//描画元の切り取り位置
	RECT_F dst;//描画先の表示位置

	//スタートまでのカウントが終わっていれば
	if(m_count_time>=270)
	{

//機体の表示---------------------------------------------------
		
		//切り取り位置の設定
		RectSet(1.0f,32.0f,64.0f,31.0f,src);
		
		//表示位置の設定
		RectSet(0.0f+m_y,60.0f+m_x,0.0f+m_x,60.0f+m_y,dst);

		//10番目に登録したグラフィックのをsrc.dst.cの情報を元に描画
		Draw::Draw(10,&src,&dst,c,0.0f);
//----------------------------------------------------------------

//お邪魔の数を表示------------------------------------------
	
	//切り取り位置をセットする
	RectSet(0.0f,0.0f,32.0f,32.0f,src);
		
	//描画位置をセットする
	RectSet( 20.0f ,WINDOW_SIZE_W-(50.0f + BLOCK_SIZE*4) ,
		WINDOW_SIZE_W-(50.0f + BLOCK_SIZE*3) , 20.0f + BLOCK_SIZE , dst);

	//10番目に登録したグラフィックのをsrc.dst.cの情報を元に描画
	Draw::Draw(6,&src,&dst,c,0.0f);
	
	//文字を用意して表示する
	wchar_t str[128];
	swprintf_s(str,L"%d",ojm_num);

	Font::StrDraw((wchar_t*)L"x",WINDOW_SIZE_W-(50.0f + BLOCK_SIZE*3),20.0f,BLOCK_SIZE,str_c);
	Font::StrDraw(str,WINDOW_SIZE_W-(50.0f + BLOCK_SIZE*3)+30.0f,20.0f,BLOCK_SIZE,str_c);

//----------------------------------------------------------

//ゲージ----------------------------------------------------

		//ゲージ用背景-------------------

		//切り取り位置セット 灰色
		RectSet(0.0f,401.0f,402.0f,99.0f,src);
		//描画位置をセット
		RectSet(445.0f,960.0f,950.0f-360,485.0f,dst);
		//描画する
		Draw::Draw(15,&src,&dst,c,0.0f);
		//-------------------------

		//切り取り位置セット 黒色
		RectSet(0.0f,100.0f,101.0f,99.0f,src);
		//描画位置をセット
		RectSet(450.0f,955.0f,955.0f-360.0f,480.0f,dst);
		//描画する
		Draw::Draw(15,&src,&dst,c,0.0f);

		//背景おわり----------------------

		//ゲージ本体----------------------

		//切り取り位置
		RectSet(0.0f,1.0f,2.0f,99.0f,src);

		//描画位置
		RectSet(450.0f,955.0f,955.0f- m_shoot_time,480.0f,dst);

		Draw::Draw(15,&src,&dst,c,0.0f);//描画

//ゲージおわり-----------------------------------------------------------

		//切り取り位置の設定
		RectSet(0.0f,0.0f,64.0f,64.0f,src);
		
//後のブロック表示----------------------------------------------------------
		
	//1つ後の２つ------------------------------------
	
		//表示位置の設定
		RectSet(m_senter.y-m_drow.y,m_senter.x-m_drow.x-6,
			m_senter.x-m_drow.x-6+BLOCK_SIZE,m_senter.y-m_drow.y+BLOCK_SIZE,dst);//描画

		Draw::Draw(m_npc[m_bullet_count],&src,&dst,c,0.0f);//描画
	
		//描画位置を設定
		RectSet(m_senter.y+m_drow.y-BLOCK_SIZE,m_senter.x+m_drow.x-6-BLOCK_SIZE,
			m_senter.x+m_drow.x-6,m_senter.y+m_drow.y,dst);
	
		Draw::Draw(m_npc[(m_bullet_count+1)%4],&src,&dst,c,0.0f);//描画
	
	//2つ後の2つ-----------------------------------------
		//切り取り位置の設定

		//描画位置の設定
		RectSet(m_senter.y,m_senter.x+17-BLOCK_SIZE*2-BLOCK_SIZE/2-4,
			m_senter.x+17-BLOCK_SIZE*2-BLOCK_SIZE/2-4+BLOCK_SIZE-20,m_senter.y+BLOCK_SIZE-20,dst);
	
		Draw::Draw(m_npc[(m_bullet_count+2)%4],&src,&dst,c,0.0f);//描画
	
		//表示
		//描画位置
		RectSet(m_senter.y+BLOCK_SIZE-20 ,m_senter.x+17-BLOCK_SIZE*2-BLOCK_SIZE/2-4,
			m_senter.x+17-BLOCK_SIZE*2-BLOCK_SIZE/2-4+BLOCK_SIZE-20,m_senter.y+BLOCK_SIZE-20+BLOCK_SIZE-20,dst);

		Draw::Draw(m_npc[(m_bullet_count+3)%4],&src,&dst,c,0.0f);//描画

	//後のブロック表示  終わり----------------------------------------------------------
	}
}

//弾を撃つ関数
void CObjCP::Shot()
{
	//マップオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);
		
	Block_Pos_Save();//弾の生成予定地の保存

	//お邪魔ブロックとの重複を避けるためのチェック-----------------------------------------------------------------
	bool check,check2;
	check = (obj->Return_Num(m_shot_x[0],m_shot_y[0]) == 99 );//1つ目のブロックを入れる予定の位置が空白かどうか調べる
	check2= (obj->Return_Num(m_shot_x[1],m_shot_y[1]) == 99 );//2つ目のブロックを入れる予定の位置が空白かどうか調べる
	//------------------------------------------------------------------------------------------------------------
			
	if(check==true && check2==true)//２つのブロックが無事に打てる状況なら
	{
		//二つのブロック生成の処理--------------
		for(int i=0;i<2;i++)
		{
			obj->Enter(m_shot_x[i],m_shot_y[i],m_npc[m_bullet_count]);//記憶させた配列の位置の要素を変更する
			m_npc[(m_bullet_count++)%4]=rand() % 6;//使用した位置のランダム情報の更新
			obj->FlagOn(m_shot_x[i],m_shot_y[i]);//オブジェクト生成フラグをオンにする
		}
		//---------------------------------------
		//回転情報のリセット--------------------------
		m_r=0;

		m_drow.x=BLOCK_SIZE/2;
		m_drow.y=BLOCK_SIZE;
		//------------------------------------------
		m_bullet_count%=4;//bullet_countは0-3を繰り返すようにする

		//ゲージの初期化
		m_gauge_time=360;
	}		
}

//ブロックを回転させる関数
void CObjCP::Revolution()
{
	if(m_rf==true)
	{
		m_r++;

		if(m_r==4)
			m_r=0;

		//基準点の調整（ｘとｙの入れ替え）
		float num	= m_drow.x;
		m_drow.x	= m_drow.y;
		m_drow.y	= num;
			
		//回転が偶数回目なら
		if(m_r==1||m_r==3)
		{
			//乱数入れ替え
			int tmp=m_npc[m_bullet_count];
			m_npc[m_bullet_count]=m_npc[(m_bullet_count+1)%4];
			m_npc[(m_bullet_count+1)%4]=tmp;
		}
	}
}

//弾の生成予定地の保存
void CObjCP::Block_Pos_Save()
{
	//プレイヤーの中心位置からブロックを入れるべき配列の要素数を求める
	int t = m_move;
			
	//ブロックが縦長（偶数回転）なら
	if(m_r%2==0)
	{	
		//一番したの段で打とうとした場合はひとつずつ上にずらす
		if(t==6)
			t--;

		//上側のブロックの位置を記憶
		m_shot_x[0]=19;
		m_shot_y[0]=t;
		//下側のブロックの位置を記憶
		m_shot_x[1]=19;
		m_shot_y[1]=t+1;
	}
	else 
	{

		//左側のブロックの位置を記憶
		m_shot_x[0]=18;
		m_shot_y[0]=t;
		//右側のブロックの位置を記憶
		m_shot_x[1]=19;
		m_shot_y[1]=t;
	}
}

//ブロックの消せるをセットする関数
void CObjCP::SetDeletePoint(Point d,int n,int r)
{
	D_Point[d_count].Delete = d;	//座標を入れる
	D_Point[d_count].num = n;		//消える数をセット
	D_Point[d_count++].rad = r;		//回転数をセット
	
	if(d_count >= D_POINT_MAX)
		d_count=0;
}
