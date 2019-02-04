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
#include "SceneMain.h"
#include "GameHead.h"

//コンストラクタ
CSceneMain::CSceneMain()
{
}

//デストラクタ
CSceneMain::~CSceneMain()
{

}

//ゲームメインの初期化メソッド
void CSceneMain::InitScene()
{
	//音楽の読み込み宣言
	Audio::LoadAudio(2,(wchar_t*)L"Hit.WAV",EFFECT);	       //ブロックとブロック、ブロックと一番最初の真ん中であたったときの音
	Audio::LoadAudio(3, (wchar_t*)L"bomb.WAV",EFFECT);        //爆発音
	Audio::LoadAudio(4, (wchar_t*)L"Ojama.WAV",EFFECT);       //お邪魔発射音
	Audio::LoadAudio(5, (wchar_t*)L"SetOjama.WAV",EFFECT);    //お邪魔設置音
	Audio::LoadAudio(7, (wchar_t*)L"Win.wav"   ,BACK_MUSIC);  //勝負がついた時に流れる
	Audio::LoadAudio(8, (wchar_t*)L"Fight.wav" , BACK_MUSIC); //戦闘ミュージック
	Audio::LoadAudio(9, (wchar_t*)L"Start1.wav" , EFFECT);     //スタートシグナル(3~1)
	Audio::LoadAudio(10, (wchar_t*)L"Start0.wav" , EFFECT);     //スタートシグナル(start)
	
	//戦闘ミュージック開始
	Audio::Start(8);

	//ボリュームを増やす
	
	//音楽スタート
	float Volume2 = Audio::Volume(-0.4f,2);//設置音
	float Volume3 = Audio::Volume(-0.7f,3);//爆発音
	float Volume4 = Audio::Volume(1.0f,4);//お邪魔発射音
	float Volume5 = Audio::Volume(1.0f,5);//お邪魔設置音
	float Volume7 = Audio::Volume(-0.2f,7);//勝利音
	float Volume8 = Audio::Volume(-0.6f,8);//戦闘BGM
	float Volume9 = Audio::Volume(-0.3f,9);//スタートシグナル
	float Volume10 = Audio::Volume(-0.3f,10);//スタートシグナル
	
	//ブロック 0~5 & 6
	Draw::LoadImage((wchar_t*)L"ColorBlue.png"  ,0,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorRed.png"   ,1,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorGreen.png" ,2,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorYellow.png",3,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorPink.png"  ,4,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"ColorPurple.png" ,5,TEX_SIZE_64);
	Draw::LoadImage((wchar_t*)L"Intervention.png",6,TEX_SIZE_32);//お邪魔ブロック

	//背景 7~8
	Draw::LoadImage((wchar_t*)L"background1.png",7,TEX_SIZE_512);//背景
	Draw::LoadImage((wchar_t*)L"background2.png",8,TEX_SIZE_512);//背景枠有
	Draw::LoadImage((wchar_t*)L"blueback.png",9,TEX_SIZE_512);//マップの枠線

	//主人公&爆発エフェクト 9
	Draw::LoadImage((wchar_t*)L"image.png",10,TEX_SIZE_512);

	//カウントダウン用数字
	Draw::LoadImage((wchar_t*)L"3.png",11,TEX_SIZE_256);
	Draw::LoadImage((wchar_t*)L"2.png",12,TEX_SIZE_256);
	Draw::LoadImage((wchar_t*)L"1.png",13,TEX_SIZE_256);
	Draw::LoadImage((wchar_t*)L"START.png",14,TEX_SIZE_256);
	
	//ゲージ
	Draw::LoadImage((wchar_t*)L"gauge.png",15,TEX_SIZE_600);


	//主人公オブジェクト作成
	CObjHero*obj=new CObjHero();//主人公オブジェクトの作成
	Objs::InsertObj(obj,OBJ_HERO,10);//作った主人公オブジェクトをオブジェクトマネージャーに登録
	
	//主人公（右）オブジェクト作成
	CObjHero_R*obj_r=new CObjHero_R();//主人公オブジェクトの作成
	Objs::InsertObj(obj_r,OBJ_HERO_R,10);//作った主人公オブジェクトをオブジェクトマネージャーに登録
	
	//背景オブジェクト作成
	CObjBackground *obj_b=new CObjBackground();//背景オブジェクトの作成
	Objs::InsertObj(obj_b,OBJ_BACK_GROUND,1);//背景オブジェクトをオブジェクトマネージャーに登録

	//マップオブジェクト
	CObjMain* p=new CObjMain(false);//マップオブジェクトの作成
	Objs::InsertObj(p,OBJ_MAIN,5);//マップオブジェクトをオブジェクトマネージャーに登録
}

//ゲームメインの実行中メソッド
void CSceneMain::Scene()
{
	
}


