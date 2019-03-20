//使用するヘッダー
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include"ObjExplanation4.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjExplanation4::Init()
{
	m_key_flag = false;

}

//アクション
void CObjExplanation4::Action()
{
	//→かDキーを押すとモードセレクトへ移行
	if (Input::GetVKey(VK_RIGHT) == true || Input::GetVKey('D') == true)
	{
		if (m_key_flag == true)
		{
			CObjModeChoice* obj = new CObjModeChoice();
			Objs::InsertObj(obj, OBJ_MODE_CHOICE, 10);

			m_key_flag = false;

			this->SetStatus(false);

		}
	}
	//←かAキーを押すと説明3に移行する
	else if (Input::GetVKey(VK_LEFT) == true || Input::GetVKey('A') == true)
	{
		if (m_key_flag == true)
		{
			CObjExplanation3* obj = new CObjExplanation3();
			Objs::InsertObj(obj,OBJ_EXPLANATION3, 10);

			m_key_flag = false;

			this->SetStatus(false);
		}
	}

	else
	{
		m_key_flag = true;
	}
}

//ドロー
void CObjExplanation4::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float c2[4] = { 1.0f,1.0f,1.0f,2.0f };
	float moji[4] = { 1.0f,1.0f,1.0f,1.0f};

	Font::StrDraw((wchar_t*)L"4/4", 950, 10, 30, moji);

	//タイム表示
	Font::StrDraw((wchar_t*)L"00:41", 100, 210, 50, moji);

	//タイムの説明文
	Font::StrDraw((wchar_t*)L"･タイムの説明",270,120,40,moji);

	Font::StrDraw((wchar_t*)L"タイムは対戦開始から決着するまでの時間です。", 280, 190, 30, moji);
	Font::StrDraw((wchar_t*)L"タイムの早い上位10人がランキングに", 280, 240, 30, moji);
	Font::StrDraw((wchar_t*)L"表示･記録されます。", 280, 290, 30, moji);

	//勝利判定の説明
	Font::StrDraw((wchar_t*)L"･勝敗について", 270, 390, 40, c);
	Font::StrDraw((wchar_t*)L"相手の端のマスが埋まり、一定時間が経過すると", 280, 460, 28, c);
	Font::StrDraw((wchar_t*)L"勝利となる。", 280, 510, 28, c);
	
	Font::StrDraw((wchar_t*)L"Mode Select : → / D", 360, 660, 32, c);
	Font::StrDraw((wchar_t*)L"Back Page   : ← / A", 360, 692, 32, c);

}