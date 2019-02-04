//使用するヘッダー
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include"GameL\DrawTexture.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjRanking.h"
#include"ObjBackground.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRanking::CObjRanking(int rank)
{
	m_rank = rank; //持ってきた順位を保存
}

//イニシャライズ
void CObjRanking::Init()
{
	m_key_flag = false;//キーフラグ

	for (int i = 0; i <= 10; i++)
	{
		//時間に初期値9999が入っていた場合true
		if (((UserData*)Save::GetData())->mRankingTimeData[i] == SET_TIME)
		{
			time_set_flag[i] = true;
		}
	}
}

//アクション
void CObjRanking::Action()
{
	//エンターキーが押されたら
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			if (m_rank <= 10)	//10位以内なら
			{
				//名前入力シーンへ移動
				Scene::SetScene(new CSceneNameInput(m_rank));
			}
			else//ランキング外なら
			{
				//モードセレクトへ
				CObjModeChoice* obj = new CObjModeChoice();
				Objs::InsertObj(obj, OBJ_MODE_CHOICE, 10);

				m_key_flag = false;

				this->SetStatus(false);//ランキング破棄
			}
		}
	}
	else
	{
		m_key_flag = true;
	}
}

//ドロー
void CObjRanking::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float yellow[4] = { 1.0f,1.0f,0.0f,1.0f };
	wchar_t str_time[256];

	//ランキング
	Font::StrDraw((wchar_t*)L"ランキング",350,30,60,c);

	int j;

	//ランク取得で10位以上なら11位表示させない
	if (m_rank > 10)
		j = 10;
	else
		j = 9;

	for (int i = 0; i <= j; i++)
	{
		//タイム表示-----------------------------------------------
		//初期値9999が入っている場合
		if (time_set_flag[i] == true)
		{
			if (j == 9)
			{
				swprintf_s(str_time, L"%2d位     --:--", i + 1);
				Font::StrDraw(str_time, 250, 130 + 55 * i, 40, c);				
			}
			else if (j == 10 && i < 10)
			{
				swprintf_s(str_time, L"%2d位     --:--", i + 1);
				Font::StrDraw(str_time, 250, 130 + 55 * i, 40, c);
			}
		}
		//初期値9999が入っていない場合
		else
		{
			//10位以上なら11位表示しない
			if (j == 9 && ((UserData*)Save::GetData())->mRankingTimeData[0] == SET_TIME)
			{
				swprintf_s(str_time, L"%2d位     %02d:%02d", i + 1, ((UserData*)Save::GetData())->mRankingTimeData[i] / 60, ((UserData*)Save::GetData())->mRankingTimeData[i] % 60);
				Font::StrDraw(str_time, 250, 130 + 55 * i, 40, c);
			}
			//データの0番目に初期値が入ってない場合
			else if (j == 9 && ((UserData*)Save::GetData())->mRankingTimeData[0] != SET_TIME)
			{
				swprintf_s(str_time, L"%2d位     %02d:%02d", i + 1, ((UserData*)Save::GetData())->mRankingTimeData[i] / 60, ((UserData*)Save::GetData())->mRankingTimeData[i] % 60);
				Font::StrDraw(str_time, 135, 110 + 55 * i, 60, yellow);
			}
			//入っている場合
			else if (((UserData*)Save::GetData())->mRankingTimeData[0] != SET_TIME && i == 0)
			{
				swprintf_s(str_time, L"%2d位     %02d:%02d", i + 1, ((UserData*)Save::GetData())->mRankingTimeData[i] / 60, ((UserData*)Save::GetData())->mRankingTimeData[i] % 60);
				Font::StrDraw(str_time, 135, 110 + 55 * i, 60, yellow);
			}
			//10位以下なら11位表示
			else if (j == 10 && i == 10)
			{
				swprintf_s(str_time, L"         %02d:%02d",((UserData*)Save::GetData())->mRankingTimeData[i] / 60, ((UserData*)Save::GetData())->mRankingTimeData[i] % 60);
				Font::StrDraw(str_time, 225, 140 + 55 * i, 45, c);
			}
			//1～10位表示
			else if (j == 10 && i < 10 && i > 0)
			{
				swprintf_s(str_time, L"%2d位     %02d:%02d", i + 1, ((UserData*)Save::GetData())->mRankingTimeData[i] / 60, ((UserData*)Save::GetData())->mRankingTimeData[i] % 60);
				Font::StrDraw(str_time, 250, 130 + 55 * i, 40, c);
			}
			
		}
	}
	//-----------------------------------------------------------------------------

	//名前表示----------------------------------------
	for (int i = 0; i < 10; i++)
	{
		wchar_t str_name[256];
		char name[6];
		strcpy_s(name, ((UserData*)Save::GetData())->mRankingNameData[i]);

		//char からwchar_t　に　指定したサイズ分コピー
		size_t* size = nullptr;
		mbstowcs_s(size, str_name, 12, name, 12);
			   
		if(((UserData*)Save::GetData())->mRankingNameData[0] == SET_NAME && i == 0)//ネームに初期文字が入っている場合の1位
			Font::StrDraw(str_name, 660, 130 + 55 * i, 40, c);
		else if (i == 0 && ((UserData*)Save::GetData())->mRankingTimeData[0] != SET_TIME)//入っていない場合の1位
			Font::StrDraw(str_name, 700, 110 + 55 * i, 60, yellow);
		else
			Font::StrDraw(str_name, 660, 130 + 55 * i, 40, c);//それ以外の順位
	}
	//-------------------------------------------------
}