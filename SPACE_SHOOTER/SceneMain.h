#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:ゲームメイン
class CSceneMain:public CScene
{
public:
	void InitScene();	//ゲームメインの初期化のメソッド
	void Scene() {};		//ゲームメインの実行中のメソッド
private:
};
