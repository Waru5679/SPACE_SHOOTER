#pragma once 

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：マップ
class CObjScore:public CObj
{
public:
	CObjScore(){};
	~CObjScore();

	void ScorePlus(bool LorR,int num );//スコア追加関数
	void Init();//イニシャライズ
	void Action();//アクション
	void Draw();//ドロー
private:
	int m_score_L;//左のプレイヤーのスコア
	int m_score_R;//右のプレイヤーのスコア
	int m_high_score;
};
