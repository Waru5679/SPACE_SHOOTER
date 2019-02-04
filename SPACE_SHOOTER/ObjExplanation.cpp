//使用するヘッダー
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjExplanation.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjExplanation::Init()
{
	m_key_flag=false;
}

//アクション
void CObjExplanation::Action()
{

	//→キーかDキーを押して次の説明画面に移行する
	if(Input ::GetVKey(VK_RIGHT)==true || Input::GetVKey('D') == true)
	{
		if(m_key_flag==true)
		{
			//説明オブジェクト3作成
			CObjExplanation3* obj=new CObjExplanation3();//説明オブジェクト2作成
			Objs::InsertObj(obj,OBJ_EXPLANATION3,10);

			m_key_flag = false;

			this->SetStatus(false);//説明1オブジェクト破棄
		}
	}
	//←キーかAキーを押して前の説明画面に移行する
	else if (Input::GetVKey(VK_LEFT) == true || Input::GetVKey('A') == true)
	{
		if (m_key_flag == true)
		{
			//説明オブジェクト2作成
			CObjExplanation2* obj = new CObjExplanation2();//説明オブジェクト2作成
			Objs::InsertObj(obj, OBJ_EXPLANATION3, 10);

			m_key_flag = false;

			this->SetStatus(false);//説明1オブジェクト破棄
		}
	}
	else
	{
		m_key_flag=true;
	}

	
}

//ドロー
void CObjExplanation::Draw()
{
	float key[4]={1.0f,1.0f,1.0f,1.0f};//各キー
	float moji[4]={1.0f,1.0f,1.0f,1.0f};//文字
	float back[4]={0.9f,0.9f,0.9f,0.9f};//背景

	RECT_F src;//描画元の切り取り位置
	RECT_F dst;//描画先の表示位置

//文字表示-------------------------------------

	Font::StrDraw((wchar_t*)L"2/4",950,10,30,moji);
	//左機体説明
	Font::StrDraw((wchar_t*)L"左機体",150,150,30,moji);
	Font::StrDraw((wchar_t*)L"上移動",375,210,25,moji);
	Font::StrDraw((wchar_t*)L"下移動",375,310,25,moji);
	Font::StrDraw((wchar_t*)L"弾発射",375,410,25,moji);
	Font::StrDraw((wchar_t*)L"弾回転(右回転)",375,510,25,moji);

	//右機体説明
	Font::StrDraw((wchar_t*)L"右機体",530,150,30,moji);
	Font::StrDraw((wchar_t*)L"上移動",750,210,25,moji);
	Font::StrDraw((wchar_t*)L"下移動",750,310,25,moji);
	Font::StrDraw((wchar_t*)L"弾発射",750,410,25,moji);
	Font::StrDraw((wchar_t*)L"弾回転(右回転)",750,510,25,moji);

	Font::StrDraw((wchar_t*)L"Next Page   : → / D", 360, 660, 32, moji);
	Font::StrDraw((wchar_t*)L"Back Page   : ← / A", 360, 692, 32, moji);

//文字表示おわり----------------------------------------------------
		
	//切り取り位置の設定
	RectSet(0.0f,0.0f,470.0f,270.0f,src);
	
//機体表示-----------------------------------------------------
	
	//左機体を表示

	//切り取り位置
	RectSet(1.0f,0.0f,32.0f,31.0f,src);

	//表示位置の設定
	RectSet(190.0f,150.0f,220.0f,260.0f,dst);

	Draw::Draw(21,&src,&dst,key,0.0f);//描画

	//右機体を表示
	//切り取り位置の設定
	RectSet(1.0f,32.0f,64.0f,31.0f,src);

	//表示位置の設定
	RectSet(190.0f,530.0f,600.0f,260.0f,dst);

	Draw::Draw(21,&src,&dst,key,0.0f);//描画

//機体表示おわり-----------------------------------------------------------------------

//ここからキー表示-------------------------------------------------------------------------------	

	//切り取り位置の設定
	RectSet(0.0f,0.0f,32.0f,32.0f,src);

	//--------------------------------------------------------------------------------------------------
	
	//Wキー表示

	//表示位置の設定
	RectSet(190.0f,275.0f,340.0f,250.0f,dst);

	Draw::Draw(13,&src,&dst,key,0.0f);//描画
	
	//---------------------------------------------------------------------------------------------------

	//Dキーの表示

	//表示位置の設定
	RectSet(390.0f,275.0f,340.0f,450.0f,dst);
	
	Draw::Draw(14,&src,&dst,key,0.0f);//描画

	//-----------------------------------------------------------------------------------------------------
	
	//Aキーの表示
	
	//表示位置の設定
	RectSet(490.0f,275.0f,340.0f,550.0f,dst);
	
	Draw::Draw(15,&src,&dst,key,0.0f);//描画

	//-----------------------------------------------------------------------------------------------------
	
	//Sキーの表示

	//表示位置の設定
	RectSet(290.0f,275.0f,340.0f,350.0f,dst);

	Draw::Draw(16,&src,&dst,key,0.0f);//描画

	//----------------------------------------------------------------------------------------------

	//↑キーの表示

	//表示位置の設定
	RectSet(190.0f,650.0f,715.0f,256.0f,dst);

	Draw::Draw(17,&src,&dst,key,0.0f);//描画

	//-----------------------------------------------------------------------------------------------------

	//↓キーの表示

	//表示位置の設定
	RectSet(290.0f,650.0f,715.0f,350.0f,dst);

	Draw::Draw(18,&src,&dst,key,0.0f);//描画

	//--------------------------------------------------------------------------------------------------------

	//←キーの表示

	//表示位置の設定
	RectSet(390.0f,650.0f,715.0f,450.0f,dst);

	Draw::Draw(19,&src,&dst,key,0.0f);//描画

	//-----------------------------------------------------------------------------------------------------------

	//→キーの表示

	//表示位置の設定
	RectSet(490.0f,650.0f,715.0f,550.0f,dst);

	Draw::Draw(20,&src,&dst,key,0.0f);//描画

	//--------------------------------------------------------------------------------------------------------
}