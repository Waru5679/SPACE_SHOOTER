#pragma once 

//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームタイトル
class CSceneGameOver:public CScene
{
public:
	CSceneGameOver(int p);
	~CSceneGameOver();
	void InitScene();//ゲームタイトルの初期化メソッド
	void Scene();//ゲームタイトルの実行中メソッド
private:
	int m_pattern;//パターンわけ
};