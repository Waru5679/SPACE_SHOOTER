//使用するヘッダーファイル
#include <stdlib.h>
#include <time.h>
#include"GameHead.h"
#include"GameL\HitBoxManager.h"
#include"CObjBullet.h"
#include"GameL\DrawTexture.h"
#include"UtilityModule.h"
#include"GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBullet::CObjBullet(float x,float y,bool s,int n)
{
	m_x=x;
	m_y=y;
	m_s=s;
	npc=n;

}

//イニシャライズ
void CObjBullet::Init()
{
	m_eff.m_top=32;
	m_eff.m_left=0;
	m_eff.m_right=32;
	m_eff.m_bottom=64;
	m_ani=0;
	m_ani_time=0;
	m_del=false;
	m_check=true;



	if(m_s==true)
		m_vx=-3.0f;
	else
		m_vx=+3.0f;

	
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this,m_x,m_y,45,45,ELEMENT_NULL,OBJ_BULLET,1);



}

//アクション
void CObjBullet::Action()
{
	////主人公の位置を取得
	//CObjHero* hero = (CObjHero*) Objs::GetObj(OBJ_HERO);
	//float hx = hero->GetX();
	//float hy = hero->GetY();

	//Resorcesの描画物のRECT
	m_eff =GetBulletEffec(&m_ani,&m_ani_time,m_del,2);

	//弾丸消滅処理
	if(m_del==true)
	{
			//着弾アニメーション終了で本当にオブジェクト破棄
			if(m_ani==4)
			{
				this->SetStatus(false);
				Hits::DeleteHitBox(this);
			}

		return;//消滅し処理はココでアクションメソッドを終了させる
	}
		
	//弾丸のHitBox行進用ポインター取得
	CHitBox*hit=Hits::GetHitBox(this);
	hit->SetPos(m_x,m_y);//HitBoxの位置を弾丸の位置に更新

	//領域の判定
	if(m_s==true)//右機体
		m_check=CheckWindow(m_x,m_y,WINDOW_SIZE_W/2,0.0f,WINDOW_SIZE_W,WINDOW_SIZE_H);
	else//左機体
		m_check=CheckWindow(m_x+32.0f,m_y,0.0f,0.0f,WINDOW_SIZE_W/2,WINDOW_SIZE_H);

	if(m_check==true)
	{
		//移動
		m_x+=m_vx;
	}


	if(hit->CheckObjNameHit(OBJ_BULLET) != nullptr&&m_vx!=0.0f)
	{

		//自身のHitBoxを持ってくる
		CHitBox* hit=Hits::GetHitBox(this);
		//敵と当たっているか確認
		if(hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
		{
			//主人公が敵とどの角度で当たっているか確認
			HIT_DATA** hit_data;								//当たった時の細かな情報をいれるための構造体
			hit_data=hit->SearchObjNameHit(OBJ_BULLET);			//hit_data主人公と当たっている他全てのHitBoxとの情報を入れる

			for(int i=0; i<hit->GetCount(); i++)
			{

				//敵の左右に当たったら
				float r=hit_data[0]->r;
				if((r<45 && r>=0) || r>315)
				{
					m_x -=1.0f;//左に移動させる

				}

				if(r>135 && r<225)
				{
					m_x+=1.0f;//右に移動させる
				}
			}

		}

		m_vx = 0.0f;
			
	}
		
}

//ドロー
void CObjBullet::Draw()
{
	//描画カラー情報　R=RED G=Green B=Blue A=alpha(透過情報)
	float c[4]={1.0f,1.0f,1.0f,1.0f};
	RECT_F dst;//描画先の表示位置
	RECT_F src;


	
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = npc * 100.0f;
	src.m_right  = src.m_left + 100.0f;
	src.m_bottom = 32.0f;

	if(m_s==false)
	{
		//表示位置の設定
		dst.m_top    = 0.0f+m_y;
		dst.m_left   = 0.0f+m_x;
		dst.m_right  = 45.0f+m_x;
		dst.m_bottom = 45.0f+m_y;
	}
	else 
	{
		//表示位置の設定
		dst.m_top    = 0.0f+m_y;
		dst.m_left   = 45.0f+m_x;
		dst.m_right  = 0.0f+m_x;
		dst.m_bottom = 45.0f+m_y;
	}
	if(m_del==true)
	{
		////2番目に登録したグラフィックのをsrc.dst.cの情報を元に描画
		//Draw::Draw(2,&m_eff,&dst,c,0.0f);	
	}
	else
	{
		////2番目に登録したグラフィックのをsrc.dst.cの情報を元に描画
		//Draw::Draw(2,&src,&dst,c,0.0f);	
	}

}


////BlockHit関数
////引数1		float* x			:判定を行うobjectのX位置
////引数2		float* y			:判定を行うobjectのY位置
////引数3		bool	scroll_on	:判定を行うobjectはスクロールの影響与えるかどうか(true=与える　false=与えない)
////引数4		bool*   up			:上下左右判定の上部分に当たっているかどうかを返す
////引数5		bool*	down		:上下左右判定の下部分に当たっているかどうかを返す
////引数6		bool*	left		:上下左右判定の左部分に当たっているかどうかを返す
////引数7		bool*	right		:上下左右判定の右部分に当たっているかどうかを返す
////引数8		float*	vx			:左右判定時の反発による移動方向・力の値変えて返す
////引数9		float*	vy			:上下判定時による自由落下運動の移動方向・力の値変えて返す
////引数10	int*	bt			:下部分判定時、特殊なブロックのタイプを返す
////判定を行うobjectとブロック64X64限定で、当たり判定と上下左右判定を行う
////その結果は引数は4～10に返す
//void  CObjBullet ::BlockHit(
//	float *x,bool* left,bool* right,float* vx,int* bt
//	)
//{
//	//主人公の衝突状態確認用フラグの初期化
//	*left	= false;
//	*right	= false;
//
//					//上下左右判定
//
//					//vectorの作成
//					float rvx = *x - bx;
//
//					//長さを求める
//					float len = sqrt( rvx*rvx);
//
//					//角度を求める
//					float r=atan2(rvx);
//					r = r * 180.0f / 3.14f;
//
//					if(r <= 0.0f)
//						r = abs(r);
//					else
//						r = 360.0f-abs(r);
//
//					//lenがある一定の長さのより短い場合判定に入る
//					if(len<88.0f)
//					{
//
//					//角度で上下左右を判定
//
//
//					if((r<45 && r>0) || r>315)
//					{
//						//右
//						*right = true;//主人公の左部分が衝突している
//						*x = bx + 64.0f;//ブロックの位置+主人公の幅
//						*vx = -(*vx) * 0.1f;;//-VX*反発係数
//					}
//
//					if(r>135 && r<225)
//					{
//						//左
//						*left = true;//主人公の右の部分が衝突している。
//						*x = bx - 64.0f;//ブロックの位置-主人公の幅
//						*vx = -(*vx) * 0.1f;;//-VX*反発係数
//					}
//
//					}
//
//				}
//
//			}
//		}
//	}
//
//	
//}
