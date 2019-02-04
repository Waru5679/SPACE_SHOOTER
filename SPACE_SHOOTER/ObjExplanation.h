#pragma once

//使用するヘッダー
#include"GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：説明
class CObjExplanation:public CObj
{
public:
	CObjExplanation(){};
	~CObjExplanation(){};
	void Init();//イニシャライズ
	void Action();//アクション
	void Draw();//ドロー
private:
	bool m_key_flag;//キーフラグ
};