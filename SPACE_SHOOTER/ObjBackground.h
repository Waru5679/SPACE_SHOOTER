#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

class CObjBackground:public CObj
{
public:
	CObjBackground(){};
	~CObjBackground(){};
	void Init();//イニシャライズ
	void Action();//アクション
	void Draw();//ドロー
private:
	int m_count_time;
	
};
