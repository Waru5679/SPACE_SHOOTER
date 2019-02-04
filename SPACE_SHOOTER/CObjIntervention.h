#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：お邪魔ブロック
class CObjIntervention:public CObj
{
	public:
		CObjIntervention(float x,float y,bool lr);
		~CObjIntervention(){};
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//描画

		void Move();	//移動処理の関数
		void Check();	//移動のチェック用の関数
	
private:
		float m_vx;
		float m_vy;

		float m_px;
		float m_py;
		int m_time;

		bool m_lr;//trueが左 falseが右
		bool m_se;//SE制御用
		bool m_Processing_flag;//処理用のフラグ
		bool m_gameover_check;//ゲームオーバーの有無をしらべる
		bool m_stop_flag;//自身が泊まっているかどうかのフラグ
		bool move_check;//移動できるかどうかのチェック用フラグ
};