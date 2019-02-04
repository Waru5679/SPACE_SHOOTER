#pragma once

//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ランキング
class CSceneRanking : public CScene
{
public:
	CSceneRanking() { m_rank = -1; };
	CSceneRanking(int rank);
	~CSceneRanking() {};
	void InitScene();//初期化メソッド
	void Scene();//実行中メソッド
private:
	int m_rank;	//ランキング順位
};