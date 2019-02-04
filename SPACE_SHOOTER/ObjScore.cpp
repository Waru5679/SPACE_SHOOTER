//使用するヘッダーファイル
#include <stdio.h>
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjScore.h"

//使用するネームスペース
using namespace GameL;

//デストラクタ
CObjScore::~CObjScore()
{
}

//イニシャライズ
void CObjScore::Init()
{
	//出力させる文字のグラフィック
	Font::SetStrTex((wchar_t*)L"0123456789");
	Font::SetStrTex((wchar_t*)L"1UP HIGH SCORE");
	m_score_L=0;
	m_score_R=0;
	m_high_score=0;
		
}

//アクション
void CObjScore::Action()
{
}

//ドロー
void CObjScore::Draw()
{
	//描画カラー情報
	float c[4]={1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//切り取り
	RECT_F dst;//表示先

		
	wchar_t score_L[10];
	swprintf_s(score_L,L"%d",m_score_L,4*10);
	Font::StrDraw(score_L,(WINDOW_SIZE_W/6) ,10,60.0f,c);

	wchar_t	score_R[10];
	swprintf_s(score_R,L"%d",m_score_R,4*10);
	Font::StrDraw(score_R,(WINDOW_SIZE_W/6)*4,10,60.0f,c);

	
}

//スコア追加関数
//引数１　bool true:左　false:右
//引数２　int  消したブロックの数
void CObjScore::ScorePlus(bool LorR,int num)
{
	if(LorR==true)
		m_score_L+=100*num;
	else
		m_score_R+=100*num;
}
