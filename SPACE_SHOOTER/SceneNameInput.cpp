//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneNameInput.h"
#include "GameHead.h"

//コンストラクタ
CSceneNameInput::CSceneNameInput(int rank)
{
	m_rank = rank;	//ランキングを保存
}

//ゲームメインの初期化メソッド
void CSceneNameInput::InitScene()
{
	//ネーム入力オブジェクトの作成
	CObjNameInput* p = new CObjNameInput(m_rank);
	Objs::InsertObj(p, OBJ_NAME_INPUT, 5);
}

//ゲームメインの実行中メソッド
void CSceneNameInput::Scene()
{

}


