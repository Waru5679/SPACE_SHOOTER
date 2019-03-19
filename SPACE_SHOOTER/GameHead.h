#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_HERO,
	OBJ_BLOCK,
	OBJ_HERO_R,
	OBJ_BULLET,
	OBJ_BACK_GROUND,
	OBJ_TITLE,
	OBJ_EXPLANATION,
	OBJ_MAIN,
	OBJ_INTERVENTION,
	OBJ_EXPLANATION2,
	OBJ_GAME_OVER,
	OBJ_EXPLANATION3,
	OBJ_EX_BLOCK,
	OBJ_MODE_CHOICE,
	OBJ_CP,
	OBJ_EXPLANATION4,
	OBJ_NAME_INPUT,
	OBJ_RANKING,
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	char mRankingNameData[11][6];	//名前データ
	int mRankingTimeData[11];		//タイムデータ
};
//------------------------------------------------

//ゲーム内で使用されるグローバル変数・定数・列挙・関数--

//ウィンドウサイズ
#define WINDOW_SIZE_W	(1024)
#define WINDOW_SIZE_H	(768)

//ブロックサイズ
#define BLOCK_SIZE (46)

//ランキング関連の初期値
#define SET_NAME	"+++++"
#define SET_TIME	(9999)

//ゲームクリア後の名前未入力の状態に仮でセットする
#define NO_NAME		"-----"
//------------------------------------------------------

//ゲーム内で使用する構造体------------------------------
//位置構造体
struct Point 
{
	float x;
	float y;
};


//------------------------------------------------

//ゲーム内で使用するクラスヘッダ------------------
#include "ObjTitle.h"
#include "ObjExplanation.h"
#include "CObjBlock.h"
#include "CObjHero.h"
#include "CobjHero_R.h"
#include "ObjBackground.h"
#include "ObjMain.h"
#include "CObjIntervention.h"
#include "ObjExplanation2.h"
#include "ObjGameOver.h"
#include "ObjExplanation3.h"
#include "ObjExBlock.h"
#include "Function.h"
#include "ObjModeChoice.h"
#include "ObjCP.h"
#include "ObjNameInput.h"
#include "ObjExplanation4.h"
#include "ObjRanking.h"
//------------------------------------------------

//ゲームシーンヘッダ------------------
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneVsCP.h"
#include "SceneNameInput.h"
#include "SceneRanking.h"
//------------------------------------------------


//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
#define SET_GAME_START  CSceneTitle
//-----------------------------------------------