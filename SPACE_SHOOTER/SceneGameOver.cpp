//ＳＴＬデバッグ機能をＯＦＦにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用するヘッダー
#include "SceneGameOver.h"
#include "GameHead.h"
#include"GameL\DrawTexture.h"
#include "GameL\Audio.h"


//コンストラクタ
CSceneGameOver::CSceneGameOver(int p)
{
	m_pattern=p;
}

//デストラクタ
CSceneGameOver::~CSceneGameOver()
{

}

//ゲームメイン初期化メソッド
void CSceneGameOver::InitScene()
{

	//出力させる文字のグラフィックを作成
	Font::SetStrTex((wchar_t*)L"１P　WIN");
	Font::SetStrTex((wchar_t*)L"２P　WIN");
	Font::SetStrTex((wchar_t*)L"DROW");
	//音楽情報の読み込み


	//バックミュージックスタート
	

	//ゲームオーバーオブジェクト作成
	CObjGameOver* obj=new CObjGameOver(m_pattern);//タイトルオブジェクト作成
	Objs::InsertObj(obj,OBJ_GAME_OVER,10);//タイトルオブジェクト作成
}

//ゲームメイン実行中のメソッド
void CSceneGameOver::Scene()
{

}


