#pragma once

//使用するヘッダー
#include"GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjRanking :public CObj
{
public:
	CObjRanking(int rank);
	~CObjRanking() {};
	void Init();//イニシャライズ
	void Action();//アクション
	void Draw();//ドロー
private:
	int	 m_rank;	//ランキングの順位
	bool m_key_flag;//キーフラグ
	bool time_set_flag[11];//タイムセットフラグ
						  //初期値が入ってるかどうか調べる用
};