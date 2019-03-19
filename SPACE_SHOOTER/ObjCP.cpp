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

//初期化
void CObjCP::Init()
{
	//位置
	m_Pos.x = WINDOW_SIZE_W - 54;
	m_Pos.y = WINDOW_SIZE_H / 3.5f;

	//m_f=true;

	//移動
	m_Move.x = 0.0f;
	m_Move.y = 0.0f;

	//移動の制御
	m_MoveCheck = 3;

	//回転
	m_RotNum = 0;

	m_bRot = true;

	//発射回数
	m_BulletCount = 0;

	//移動処理フラグ
	m_bMove = true;

	//ランダム情報を初期化(0-6)
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		m_Npc[i] = rand() % 6;
	}

	//ブロック同士の中間点を決める
	m_Senter.x = WINDOW_SIZE_W - (BLOCK_SIZE + (BLOCK_SIZE / 2));
	m_Senter.y = (WINDOW_SIZE_H - 8.0f) - (BLOCK_SIZE * 2);

	//m_senterと描画の基準点（左上か右下）との差（絶対値）
	m_Drow.x = BLOCK_SIZE / 2;
	m_Drow.y = BLOCK_SIZE;

	//弾を撃つ位置の保存用
	m_Shot[0].x = -1;
	m_Shot[0].y = -1;
	m_Shot[1].x = -1;
	m_Shot[1].y = -1;

	//移動の制御フラグ初期化
	m_bDown = true;
	m_bUp = true;

	//スタート制御
	m_Time = 0;

	//ゲームオーバーオブジェクトの有無チェック
	m_bEnd = false;

	//ゲージ用＆強制発射制御用
	m_GaugeTime = 360;

	//お邪魔ブロックを降らす数
	m_OjmNum = 0;

	//発射制御
	m_ShootTime = 360; 
	
	//AI初期化
	AiInit();

	//描画カラー
	ColorSet(m_fNomalColor, 1.0f, 1.0f, 1.0f, 1.0f);
	ColorSet(m_fPreBlockColor, 1.0f, 1.0f, 1.0f, 0.5f);
	ColorSet(m_fFontColor, 0.0f, 0.0f, 0.0f, 1.0f);

}

//AI関連の情報の初期化
void CObjCP::AiInit()
{
	m_DeleteCount = 0;
	for (int i = 0; i < DELETE_INFO_MAX; i++)
	{
		DeleteInfo[i].Pos.x = -1;
		DeleteInfo[i].Pos.y = -1;
		DeleteInfo[i].Num = -1;
		DeleteInfo[i].Rot = -1;
	}
}


//アクション
void CObjCP::Action()
{
	//カウンタ更新
	m_Time++;
	if(m_Time>=10000)
		m_Time=270;

	//Aiの初期化
	AiInit();
	
	//ゲームオーバーならここで終わり
	if( m_bEnd == true) return;
	
	//マップオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);
	
	//スタートまでのカウント
	if(m_Time < 270) return;
			
	//ゲージがMAXになった時にお邪魔生成が必要なら
	if(m_GaugeTime==360 && m_OjmNum != 0)
	{
		//自陣のブロック全てがとまっているればお邪魔生成
		if( obj->ShotCheck(false) ==true)
		{
			obj->CreateIntervention(m_OjmNum,false);
			m_OjmNum=0;
			
			return;
		}
	}
	
	//移動、回転、弾を撃つ処理をする関数
	ShotMove();
}

//移動、回転、弾の発射をする関数
void CObjCP::ShotMove()
{
	//マップオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);

	//5フレーム毎に回転と移動をできるようにする
	if(m_Time % 5 == 0)
	{
		m_bRot  = true;
		m_bMove = true;
	}

	m_DeleteCount=0;
	
	//自分のブロックがとまっている場合
	if( obj->ShotCheck(false) ==true)
	{
		m_ShootTime-=2;

		if(m_ShootTime <0)
			m_ShootTime =0;
	}

	//全ての向きで消せるかどうかのチェックをする
	obj->AiDeleteCheck_H(m_Npc[m_BulletCount], m_Npc[m_BulletCount+1],0);
	obj->AiDeleteCheck_W(m_Npc[m_BulletCount], m_Npc[m_BulletCount+1],1);
	obj->AiDeleteCheck_H(m_Npc[m_BulletCount], m_Npc[m_BulletCount + 1], 2);
	obj->AiDeleteCheck_W(m_Npc[m_BulletCount], m_Npc[m_BulletCount + 1], 3);

	//発射リミットで位置が決まっていないなら
	//一番内側で止まる位置からランダムでとりだす
	if(m_ShootTime ==0 && DeleteInfo[0].Pos.y == -1)
	{
		DeleteInfo[0].Pos.y = obj->InSideCheck();
	}
				
	//自分のブロックがとまっている場合
	if( obj->ShotCheck(false) ==true)
	{
		//消せる位置があるばあい
		if(DeleteInfo[0].Pos.y!=-1)
		{
			//同じ場所になった場合
			if(DeleteInfo[0].Pos.y == m_MoveCheck)
			{
				//ブロックの回転同じなら
				if(m_RotNum != DeleteInfo[0].Rot)
				{
					Shot();//発射
					
					//発射までの時間を初期化	
					m_ShootTime = 360; 
					
					//回転情報を初期化
					m_RotNum=0;
				}
				else
				{
					Revolution();//ブロックを回転させる		
				}
			}
		
			//yより下なら上に移動
			if(DeleteInfo[0].Pos.y < m_MoveCheck)
			{
				m_MoveCheck--;
				if (m_MoveCheck < 0)
					m_MoveCheck = 0;

				m_Pos.y += -BLOCK_SIZE;
				m_bMove=false;	
			}
			//yより上なら下に移動
			else
			{
				m_MoveCheck++;
				if (m_MoveCheck > 6)
					m_MoveCheck = 6;

				m_Pos.y += BLOCK_SIZE;
				m_bMove =false;
			}
		}
	}
}


//描画
void CObjCP::Draw()
{
	//スタートまでのカウントが終わっていれば
	if(m_Time>=270)
	{
		//機体の描画
		AircraftDraw();
		
		//お邪魔の数を表示
		OjmNumDraw();

		//ゲージ描画
		GaugeDraw();

		//後のブロック描画
		AfterBloackDraw();
	}
}

//機体の描画
void CObjCP::AircraftDraw()
{
	//切り取り位置の設定
	RectSet(1.0f, 32.0f, 64.0f, 31.0f, m_Src);

	//表示位置の設定
	RectSet(m_Pos.y, 60.0f + m_Pos.x,m_Pos.x, 60.0f + m_Pos.y, m_Dst);

	//描画
	Draw::Draw(10, &m_Src, &m_Dst, m_fNomalColor, 0.0f);
}

//お邪魔の数を描画
void CObjCP::OjmNumDraw()
{
	//切り取り位置をセットする
	RectSet(0.0f, 0.0f, 32.0f, 32.0f, m_Src);

	//描画位置をセットする
	RectSet(20.0f, WINDOW_SIZE_W - (50.0f + BLOCK_SIZE * 4),
		WINDOW_SIZE_W - (50.0f + BLOCK_SIZE * 3), 20.0f + BLOCK_SIZE, m_Dst);

	//お邪魔ブロック描画
	Draw::Draw(6, &m_Src, &m_Dst, m_fNomalColor, 0.0f);

	//文字を用意
	wchar_t str[128];
	swprintf_s(str, L"%d", m_OjmNum);

	//文字描画
	Font::StrDraw((wchar_t*)L"x", WINDOW_SIZE_W - (50.0f + BLOCK_SIZE * 3), 20.0f, BLOCK_SIZE, m_fFontColor);
	Font::StrDraw(str, WINDOW_SIZE_W - (50.0f + BLOCK_SIZE * 3) + 30.0f, 20.0f, BLOCK_SIZE, m_fFontColor);
}

//ゲージ描画
void CObjCP::GaugeDraw()
{
//ゲージ用背景-------------------
	//切り取り位置セット 灰色
	RectSet(0.0f, 401.0f, 402.0f, 99.0f, m_Src);
	
	//描画位置をセット
	RectSet(445.0f, 960.0f, 950.0f - 360, 485.0f, m_Dst);
	
	//描画する
	Draw::Draw(15, &m_Src, &m_Dst,m_fNomalColor, 0.0f);
	
	//切り取り位置セット 黒色
	RectSet(0.0f, 100.0f, 101.0f, 99.0f, m_Src);
	
	//描画位置をセット
	RectSet(450.0f, 955.0f, 955.0f - 360.0f, 480.0f, m_Dst);
	
	//描画する
	Draw::Draw(15, &m_Src, &m_Dst, m_fNomalColor, 0.0f);
//背景おわり----------------------

//ゲージ本体----------------------
	//切り取り位置
	RectSet(0.0f, 1.0f, 2.0f, 99.0f, m_Src);

	//描画位置
	RectSet(450.0f, 955.0f, 955.0f - m_ShootTime, 480.0f, m_Dst);
	
	//描画
	Draw::Draw(15, &m_Src, &m_Dst, m_fNomalColor, 0.0f);
//ゲージおわり-----------------------------------------------------------
}

//後のブロック描画
void CObjCP::AfterBloackDraw()
{
//1つ後の２つ------------------------------------
	//切り取り位置の設定
	RectSet(0.0f, 0.0f, 64.0f, 64.0f, m_Src);

	//表示位置の設定
	RectSet(m_Senter.y - m_Drow.y, m_Senter.x - m_Drow.x - 6,
		m_Senter.x - m_Drow.x - 6 + BLOCK_SIZE, m_Senter.y - m_Drow.y + BLOCK_SIZE, m_Dst);

	//描画
	Draw::Draw(m_Npc[m_BulletCount], &m_Src, &m_Dst, m_fNomalColor, 0.0f);

	//描画位置を設定
	RectSet(m_Senter.y + m_Drow.y - BLOCK_SIZE, m_Senter.x + m_Drow.x - 6 - BLOCK_SIZE,
		m_Senter.x + m_Drow.x - 6, m_Senter.y + m_Drow.y, m_Dst);

	//描画
	Draw::Draw(m_Npc[(m_BulletCount + 1) % 4], &m_Src, &m_Dst, m_fNomalColor, 0.0f);

//2つ後の2つ-----------------------------------------
	
	//描画位置の設定
	RectSet(m_Senter.y, m_Senter.x + 17 - BLOCK_SIZE * 2 - BLOCK_SIZE / 2 - 4,
		m_Senter.x + 17 - BLOCK_SIZE * 2 - BLOCK_SIZE / 2 - 4 + BLOCK_SIZE - 20, m_Senter.y + BLOCK_SIZE - 20, m_Dst);

	//描画
	Draw::Draw(m_Npc[(m_BulletCount + 2) % 4], &m_Src, &m_Dst, m_fNomalColor, 0.0f);

	//描画位置の設定
	RectSet(m_Senter.y + BLOCK_SIZE - 20, m_Senter.x + 17 - BLOCK_SIZE * 2 - BLOCK_SIZE / 2 - 4,
		m_Senter.x + 17 - BLOCK_SIZE * 2 - BLOCK_SIZE / 2 - 4 + BLOCK_SIZE - 20, m_Senter.y + BLOCK_SIZE - 20 + BLOCK_SIZE - 20, m_Dst);

	//描画
	Draw::Draw(m_Npc[(m_BulletCount + 3) % 4], &m_Src, &m_Dst, m_fNomalColor, 0.0f);
}

//弾を撃つ関数
void CObjCP::Shot()
{
	//マップオブジェクトの呼び出し
	CObjMain * obj =(CObjMain*)Objs ::GetObj(OBJ_MAIN);
	
	//弾の生成予定地の保存
	BlockPosSave();

	//ブロックを入れる位置がお邪魔ブロックとの重複しないかのチェック
	bool check,check2;
	check = (obj->Return_Num(m_Shot[0].x,m_Shot[0].y) == 99 );
	check2= (obj->Return_Num(m_Shot[1].x,m_Shot[1].y) == 99 );
	
	//２つのブロックが無事に打てる状況なら
	if(check==true && check2==true)
	{
		//2つのブロック生成
		for(int i=0;i<2;i++)
		{
			//記憶させた配列の位置の要素を変更する
			obj->Enter(m_Shot[i].x,m_Shot[i].y,m_Npc[m_BulletCount]);

			//使用した位置のランダム情報の更新
			m_Npc[(m_BulletCount++)%4]=rand() % 6;

			//オブジェクト生成フラグをオンにする
			obj->FlagOn(m_Shot[i].x,m_Shot[i].y);
		}
	
		//回転情報のリセット--------------------------
		m_RotNum = 0;
		m_Drow.x = BLOCK_SIZE/2;
		m_Drow.y = BLOCK_SIZE;
	
		//カウンタ更新(0-3を繰り返す）
		m_BulletCount %= 4;

		//ゲージの初期化
		m_GaugeTime = 360;
	}		
}

//ブロックを回転させる関数
void CObjCP::Revolution()
{
	if(m_bRot==true)
	{
		//回転
		m_RotNum++;
		if(m_RotNum==4)
			m_RotNum=0;

		//基準点の調整（ｘとｙの入れ替え）
		float num	= m_Drow.x;
		m_Drow.x	= m_Drow.y;
		m_Drow.y	= num;
			
		//回転が偶数回目なら
		if(m_RotNum ==1|| m_RotNum ==3)
		{
			//乱数入れ替え
			int tmp=m_Npc[m_BulletCount];
			m_Npc[m_BulletCount]=m_Npc[(m_BulletCount+1)%4];
			m_Npc[(m_BulletCount+1)%4]=tmp;
		}
	}
}

//弾の生成予定地の保存
void CObjCP::BlockPosSave()
{
	//プレイヤーの中心位置からブロックを入れるべき配列の要素数を求める
	int index = m_MoveCheck;
			
	//ブロックが縦長（偶数回転）なら
	if(m_RotNum%2==0)
	{	
		//一番したの段で打とうとした場合はひとつずつ上にずらす
		if(index==6)
			index--;

		//上側のブロックの位置を記憶
		m_Shot[0].x=19;
		m_Shot[0].y=index;
		//下側のブロックの位置を記憶
		m_Shot[1].x = 19;
		m_Shot[1].y = index+1;
	}
	else 
	{

		//左側のブロックの位置を記憶
		m_Shot[0].x=18;
		m_Shot[0].y=index;
		
		//右側のブロックの位置を記憶
		m_Shot[1].x=19;
		m_Shot[1].y=index;
	}
}

//ブロックの消せるをセットする関数
void CObjCP::SetDeletePoint(Point Pos,int Num,int Rot)
{
	DeleteInfo[m_DeleteCount].Pos = Pos;	//座標を入れる
	DeleteInfo[m_DeleteCount].Num = Num;	//消える数をセット
	DeleteInfo[m_DeleteCount].Rot = Rot;	//回転数をセット
	
	//カウンタ更新
	m_DeleteCount++;
	if(m_DeleteCount >= DELETE_INFO_MAX)
		m_DeleteCount =0;
}
