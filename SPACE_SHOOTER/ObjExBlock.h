#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：説明用ブロック
class CObjExBlock:public CObj
{
	public:
		CObjExBlock(int color);//コンストラクタ
		~CObjExBlock(){};//デストラクタ
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//描画
	private:
		//座標関連
		float m_vx;//移動量
		float m_px;//位置X
		float m_py;//位置Y

		int m_color;//色
};