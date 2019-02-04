//使用するヘッダーファイル
#include <stdlib.h>
#include <time.h>
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"
#include "CObjHero_R.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjHero_R::Init()
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
	
	m_push_f=true;//押し続けるの阻止用のフラグ
}

//アクション
void CObjHero_R::Action()
{
	m_count_time++;
	
	if(m_count_time>=10000)
		m_count_time=270;

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
void CObjHero_R::Shot_move()
{
	//マップオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	//自陣のブロック全てが止まってれば
	if( obj->ShotCheck(false) == true)
		m_f=true;//弾を撃てるようにする
	else
		m_f=false;//ブロックが動いていれば打てないようにする

	if(m_f == true)//弾が撃てる状況なら
	{
		m_gauge_time-=2;//強制発射カウントを進める
						
		if(m_gauge_time < 0)//0未満になるばあい０にする
			m_gauge_time = 0;
	}

	Block_Pos_Save();//弾の生成予定地の保存

	//主人公機の弾丸発射
	if(Input::GetVKey(VK_LEFT)==true )//←が押された時
	{
		//ブロックがとまっていて、長押しされていない場合
		if( m_f == true && m_push_f == true)
		{
			Shot();//弾を撃つ処理の関数を呼びだす
			m_push_f = false;//長押し阻止フラグをオフにする
		}
	}
	else
	{
		m_push_f = true;//長押し阻止フラグをオンにする
	}

	//自動発射システム-----------------------------------
	if(m_f == true)//弾が撃てる状況なら
	{					
		if( m_gauge_time == 0)//カウントが0になれば強制で発射
		{
			Shot();//弾を撃つ処理の関数を呼びだす
		}
	}
	//---------------------------------------------------
				
	//主人公機の移動ベクトルの初期化
	m_vx=0.0f;
	m_vy=0.0f;

	//キーの入力方向にベクトルの速度をいれる
	if(Input::GetVKey(VK_UP)==true)
	{
		if(m_up==true)
		{
			m_up = false;
			m_move--;//移動のカウントを減らす
			m_vy = -BLOCK_SIZE;
		
			//外に生きそうならカウントと位置を維持するようにする
			if( m_move < 0 )
			{
				m_move=0;
				m_vy=0.0f;
			}
		}
	}
	else
	{
		m_up = true;
	}
				
	//連打バグ回避用
	if(Input::GetVKey(VK_UP)!=true)
	{
		if(Input::GetVKey(VK_DOWN)==true)//　→が押されたとき
		{
			if(m_down == true)
			{
				m_down = false;
				m_move++;//移動のカウントを増やす
				m_vy=BLOCK_SIZE;

				//外に生きそうならカウントと位置を維持するようにする
				if(m_move >6)
				{
					m_move=6;
					m_vy=0.0f;
				}
			}
		}
		else //→が離されたとき
		{
			m_down = true;
		}
	}//連打バグ回避　おわり

	if(Input::GetVKey(VK_RIGHT)==true)
	{
		Revolution();//回転処理の関数を呼び出し
		m_rf=false;
	}
	else 
	{
		m_rf=true;
	}
	
	//移動ベクトルを座標に加算する
	m_x+=m_vx;
	m_y+=m_vy;
}


//ドロー
void CObjHero_R::Draw()
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
		RectSet(450.0f,955.0f,955.0f- m_gauge_time,480.0f,dst);

		Draw::Draw(15,&src,&dst,c,0.0f);//描画

//ゲージおわり-----------------------------------------------------------

		//切り取り位置の設定
		RectSet(0.0f,0.0f,64.0f,64.0f,src);
		
//ブロックの生成予定地の表示---------------------------------------------

		for(int i=0;i<2;i++)
		{
			//表示位置の設定
			RectSet(80.0f+m_shot_y[i]*BLOCK_SIZE,50.0f+m_shot_x[i]*BLOCK_SIZE,
				50.0f+m_shot_x[i]*BLOCK_SIZE+BLOCK_SIZE,80.0f+m_shot_y[i]*BLOCK_SIZE+BLOCK_SIZE,dst);
			
			Draw::Draw(m_npc[ (m_bullet_count+i)%4 ],&src,&dst,c1,0.0f);//描画
		}

//ブロックの生成予定地おわり-----------------------------------------------

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

//後のブロック表示----------------------------------------------------------

	}
}

//弾を撃つ関数
void CObjHero_R::Shot()
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
void CObjHero_R::Revolution()
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
void CObjHero_R::Block_Pos_Save()
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
