//使用するヘッダー
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle::Init()
{
	m_key_flag=false;
}

//アクション
void CObjTitle::Action()
{
	//エンターキーを押してシーン：ゲームメインに移行する
	if(Input ::GetVKey(VK_RETURN)==true)
	{
		if(m_key_flag==true)
		{
			//説明オブジェクト作成
			CObjExplanation* obj=new CObjExplanation();//説明オブジェクト作成
			Objs::InsertObj(obj,OBJ_EXPLANATION,10);//タイトルオブジェクト作成

			this->SetStatus(false);//タイトルオブジェクト削除

			m_key_flag=false;
		}
	}
	else
	{
		m_key_flag=true;
	}

}

//ドロー
void CObjTitle::Draw()
{
	float c[4]={1.0f,1.0f,1.0f,1.0f};
	Font::StrDraw((wchar_t*)L"タイトル",130,100,80,c);
	Font::StrDraw((wchar_t*)L"GameStart : PushEnterKey",200,400,32,c);
}