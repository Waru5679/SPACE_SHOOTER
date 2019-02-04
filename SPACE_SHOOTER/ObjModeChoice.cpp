//使用するヘッダー
#include <time.h>
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjModeChoice.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjModeChoice::Init()
{
	m_key_flag = false;
	select = 1;

	//モードセレクト画面に移動時11位のみ初期化
	((UserData*)Save::GetData())->mRankingTimeData[10] = SET_TIME;

}

//アクション
void CObjModeChoice::Action()
{
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if(m_key_flag == true)
		{
			//説明が選択されたならなら
			if(select == 1)
			{
				//説明オブジェクト1作成
				CObjExplanation2* obj=new CObjExplanation2();//説明オブジェクト2作成
				Objs::InsertObj(obj,OBJ_EXPLANATION2,10);

				this->SetStatus(false);
				m_key_flag = false;

			}
			//COM対戦が選択されたなら
			if(select == 2)
			{
				//COM対戦メイン移行
				Scene::SetScene(new CSceneVsCP());
				m_key_flag = false;
			}
			//対戦(オフライン)が選択されたなら
			if(select == 3)
			{
				//対戦(オフライン)に移行
				Scene::SetScene(new CSceneMain());
				m_key_flag = false;
			}
			//ランキングが選択されたなら
			if(select == 4)
			{
				//ランキングへ移行
				Scene::SetScene(new CSceneRanking(99));

				m_key_flag = false;
			}
		}
	}

	else
	{
		m_key_flag = true;;
	}

	
	//→キー又はDキーを押すと対戦モード(オフライン)・対戦モード(オンライン)に移動
	if (Input::GetVKey('D') == true || Input::GetVKey(VK_RIGHT) == true)
	{
		//説明画面が選択されているとき
		if (select == 1)
		{
			//COM対戦に移動
			select += 1;
		}
		//対戦(オフライン)が選択されているとき
		if (select == 3)
		{
			//対戦(オンライン)に移動
			select += 1;
		}
			
	}

	//←キー又は左を押すとCOM対戦モード・説明画面に移動
	if(Input::GetVKey('A') == true || Input::GetVKey(VK_LEFT) == true)
	{
		//COM対戦が選択されているとき
		if(select == 2)
		{
			//説明に移動
			select -= 1;
		}
		//対戦(オンライン)が選ばれているとき
		if(select == 4)
		{
			//対戦(オフライン)に移動
			select -=1;
		}
	}

	//↓キー又はSキーを押すと説明・対戦モード(オンライン)に移動
	if(Input::GetVKey('S') == true || Input::GetVKey(VK_DOWN) == true)
	{
		//説明が選択されているとき
		if(select == 1)
		{
			//対戦(オフライン)に移動
			select += 2;
		}
		//COM対戦)が選ばれているとき
		if(select == 2)
		{
			//対戦(オンライン)に移動する
			select += 2;
		}
	}

	//↑キー又はWキーを押すとCOM対戦モード・対戦モード(オフライン)に移動
	if(Input::GetVKey('W') == true || Input::GetVKey(VK_UP) == true)
	{
		//対戦(オフライン)が選択されているとき
		if(select == 3)
		{
			//説明に移動する
			select -= 2;
		}
		//対戦(オンライン)が選択されているとき
		if(select == 4)
		{
			//COM対戦に移動する。
			select -= 2;
		}
	}

}
//ドロー
void CObjModeChoice::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float red[4] = { 0.0f , 0.5f , 1.0f , 1.0f };

	Font::StrDraw((wchar_t*)L"矢印キーでモードを選択してEnterキーを押してください", 50, 200, 35,c);
	if(select == 1)
	{
		Font::StrDraw((wchar_t*)L"説明画面", 200, 400, 50, red);
	}
	else
	{
		Font::StrDraw((wchar_t*)L"説明画面", 200, 400, 30, c);
	}

	if(select == 2)
	{
		Font::StrDraw((wchar_t*)L"COM対戦", 600, 400, 50, red);
	}
	else
	{
		Font::StrDraw((wchar_t*)L"COM対戦", 600, 400, 30, c);
	}

	if(select == 3)
	{
		Font::StrDraw((wchar_t*)L"対戦",200,550,50,red);
		Font::StrDraw((wchar_t*)L"(オフライン)",300,560,30,red);
	}
	else
	{
		Font::StrDraw((wchar_t*)L"対戦(オフライン)",200,550,30,c);
	}

	if(select == 4)
	{
		Font::StrDraw((wchar_t*)L"ランキング", 600, 550, 50, red);
	}
	else
	{
		Font::StrDraw((wchar_t*)L"ランキング", 600, 550, 30, c);
	}

}