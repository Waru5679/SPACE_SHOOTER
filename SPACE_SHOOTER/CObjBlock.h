#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック
class CObjBlock:public CObj
{
	public:
		CObjBlock(float x,float y,int color,bool lr,bool sk);//コンストラクタ
		~CObjBlock(){};//デストラクタ
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//描画

		void Move();//移動

		//ブロック停止時の処理関連
		void Disappear();//ブロックがとまったときの処理をする関数
		void Left_Dis();//ブロックがとまったときの左側
		void Right_Dis();//ブロックがとまったときの右側
		
		//チェック関連
		bool CheckWH(int n,int staticnum );//ブロックの向きを調べて返す関数
		void Check();//移動できるかのチェック
		bool MoveCheck(int x,int y);//移動先のチェック関数
		
		void DeleteAnimetion();//消滅＆アニメーションの処理をする関数
	private:
		//座標関連
		float m_vx;//移動量
		float m_px;//位置X
		float m_py;//位置Y

		//自身の状態の管理関連
		bool m_stop_flag;//ブロックが動いてるかとまっているかの管理

		int m_color;//色
		int m_time;//時間の管理用
		bool m_lr;//どちら側から打たれたブロックかの管理　true：左 false：右
		bool m_skip;//trueのときのみ移動時に空白を入れる処理を飛ばす
		bool m_Processing_flag;//処理の実行済みかの管理　true：済　false：未
		
		//ブロックの処理用
		int m_delete_check[2];//削除個数保存

		bool m_se;//SE制御用
		bool m_gemeover_check;//ゲームオーバーオブジェクトの有無を調べる
		
		//爆発と消滅関連
		int    m_ani;		//爆破アニメーション用
		int	   m_ani_time;	//爆破アニメーション間隔
		bool   m_del;		//削除チェック
		RECT_F m_eff;		//削除エフェクト描画用

		bool move_check;//最終的な移動できるかの判定用
};