#pragma once

//使用するヘッダー
#include"GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：説明
class CObjExplanation3:public CObj
{
public:
	CObjExplanation3(){};
	~CObjExplanation3(){};
	void Init();//イニシャライズ
	void Action();//アクション
	void Draw();//ドロー

	void Updata(){ m_gauge_time = 180; m_f=true;}//ゲージタイムを更新する関数

private:
	float m_x;
	float m_y;
	bool m_key_flag;//キーフラグ

	float m_gauge_time;//ゲージ用タイム
	bool m_f;//ブロック生成のフラグ
	bool flag;

	int m_color;//色管理用
};