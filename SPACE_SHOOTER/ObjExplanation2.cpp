//使用するヘッダー
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"

#include "GameHead.h"
#include "ObjExplanation2.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjExplanation2::Init()
{
	m_key_flag=false;
}

//アクション
void CObjExplanation2::Action()
{
	//→キーかDキーを押して次の説明画面に移行する
	if (Input::GetVKey(VK_RIGHT) == true || Input::GetVKey('D') == true)
	{
		if (m_key_flag == true)
		{
			//説明オブジェクト作成
			CObjExplanation* obj = new CObjExplanation();//説明オブジェクト2作成
			Objs::InsertObj(obj, OBJ_EXPLANATION, 10);

			m_key_flag = false;

			this->SetStatus(false);//説明1オブジェクト破棄
		}
	}
	//←キーかAキーを押して前の説明画面に移行する
	else if (Input::GetVKey(VK_LEFT) == true || Input::GetVKey('A') == true)
	{
		if (m_key_flag == true)
		{
			CObjModeChoice* obj = new CObjModeChoice();
			Objs::InsertObj(obj, OBJ_MODE_CHOICE, 10);

			m_key_flag = false;

			this->SetStatus(false);//説明オブジェクト3破棄
		}
	}
	else
	{
		m_key_flag = true;
	}
}

//ドロー
void CObjExplanation2::Draw()
{
	float c[4]={1.0f,1.0f,1.0f,1.0f};

	RECT_F src;
	RECT_F dst;
	
	//切り取り位置
	RectSet(0.0f,0.0f,1024.0f,1024.0f,src);

	//表示位置
	RectSet(0.0f,0.0f,1024.0f,768.0f,dst);
	
	Draw::Draw(22,&src,&dst,c,0.0f);//描画


	Font::StrDraw((wchar_t*)L"1/4",950,10,30,c);

	Font::StrDraw((wchar_t*)L"Next Page   : → / D", 360, 660, 32, c);
	Font::StrDraw((wchar_t*)L"Mode Select : ← / A", 360, 692, 32, c);
}