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
#include "SceneTitle.h"
#include "GameHead.h"
#include"GameL\DrawTexture.h"
#include "GameL\Audio.h"


//コンストラクタ
CSceneTitle::CSceneTitle()
{
	
}
//デストラクタ
CSceneTitle::~CSceneTitle()
{

}

//ゲームメイン初期化メソッド
void CSceneTitle::InitScene()
{
	//出力させる文字のグラフィックを作成
	Font::SetStrTex((wchar_t*)L"GameStart : PushEnterKey");
	Font::SetStrTex((wchar_t*)L"タイトル");
	//Font::SetStrTex(L"説明");

	Draw::LoadImage((wchar_t*)L"TitleBackground.png",6,TEX_SIZE_512);//タイトル背景
	Draw::LoadImage((wchar_t*)L"Title.png",7,TEX_SIZE_512);//タイトルロゴ
	Draw::LoadImage((wchar_t*)L"Intervention.png", 10, TEX_SIZE_32);//お邪魔ブロック
	Draw::LoadImage((wchar_t*)L"W_key.png" , 13 , TEX_SIZE_32);//Wキー
	Draw::LoadImage((wchar_t*)L"D_key.png" , 14 , TEX_SIZE_32);//Dキー
	Draw::LoadImage((wchar_t*)L"A_key.png" , 15 , TEX_SIZE_32);//Aキー
	Draw::LoadImage((wchar_t*)L"S_key.png" , 16 , TEX_SIZE_32);//Sキー
	Draw::LoadImage((wchar_t*)L"UP_key.png" , 17 , TEX_SIZE_32);//↑キー
	Draw::LoadImage((wchar_t*)L"DOWN_key.png" , 18 , TEX_SIZE_32);//↓キー
	Draw::LoadImage((wchar_t*)L"LEFT_key.png" , 19 , TEX_SIZE_32);//←キー
	Draw::LoadImage((wchar_t*)L"RIGHT_key.png" , 20 , TEX_SIZE_32);//→キー
	Draw::LoadImage((wchar_t*)L"image.png",21,TEX_SIZE_512);//機体と爆発のエフェクト
	Draw::LoadImage((wchar_t*)L"slide.png",22,TEX_SIZE_1024);//スライド
	Draw::LoadImage((wchar_t*)L"gauge.png",23,TEX_SIZE_600);//ゲージ

	 //タイム説明とお邪魔説明
	Draw::LoadImage((wchar_t*)L"time.png", 24, TEX_SIZE_512);
	Draw::LoadImage((wchar_t*)L"bomb.png", 25, TEX_SIZE_512);

	
	Audio::LoadAudio(9, (wchar_t*)L"Title.wav" , BACK_MUSIC);//タイトルミュージック
	Audio::LoadAudio(10, (wchar_t*)L"Exp.wav" , BACK_MUSIC);//説明画面時のミュージック

	//ブロック 0~5 & 6
	Draw::LoadImage((wchar_t*)L"ColorBlue.png"  ,0,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorRed.png"   ,1,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorGreen.png" ,2,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorYellow.png",3,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorPink.png"  ,4,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorPurple.png" ,5,TEX_SIZE_64);

	//バックミュージックスタート
	float Volume = Audio::VolumeMaster(-0.8f);
	Audio::Start(9);

	//タイトルオブジェクト作成
	CObjTitle* obj=new CObjTitle();//タイトルオブジェクト作成
	Objs::InsertObj(obj,OBJ_TITLE,10);//タイトルオブジェクト作成
}

//ゲームメイン実行中のメソッド
void CSceneTitle::Scene()
{

}


