#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：説明
class CObjExplanation4 : public CObj
{
public:
	CObjExplanation4() {};
	~CObjExplanation4() {};
	void Init();//イニシャライズ
	void Action();//アクション
	void Draw();//ドロー

private:
	bool m_key_flag;//キーフラグ

};