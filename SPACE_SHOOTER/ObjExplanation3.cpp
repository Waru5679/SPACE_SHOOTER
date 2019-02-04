//使用するヘッダー
#include <time.h>
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjExplanation3.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ

//イニシャライズ
void CObjExplanation3::Init()
{
	m_key_flag=false;

	m_gauge_time = 180;

	srand(time(NULL)); // ランダム情報を初期化
	
	m_f=true;//ブロック生成のフラグ

	m_color = rand() % 6;
	
	
}

//アクション
void CObjExplanation3::Action()
{
	//ブロックオブジェクトの呼び出し
	CObjBlock * obj_b =(CObjBlock*)Objs ::GetObj(OBJ_BLOCK);

	m_gauge_time--;

	if(m_gauge_time < 0)//0以下にならないようにする
		m_gauge_time=0;

	//→キーかDキーを押してモードセレクトの説明画面に移行する
	if (Input::GetVKey(VK_RIGHT) == true || Input::GetVKey('D') == true)
	{
		if (m_key_flag == true)
		{
			//説明4に移動
			CObjExplanation4* obj = new CObjExplanation4();
			Objs::InsertObj(obj, OBJ_EXPLANATION4, 10);

			m_key_flag = false;

			this->SetStatus(false);//説明1オブジェクト破棄
		}
	}
	//←キーかAキーを押して前の説明画面に移行する
	else if (Input::GetVKey(VK_LEFT) == true || Input::GetVKey('A') == true)
	{
		if (m_key_flag == true)
		{
			//説明オブジェクト作成
			CObjExplanation* obj = new CObjExplanation();//説明オブジェクト2作成
			Objs::InsertObj(obj, OBJ_EXPLANATION3, 10);

			m_key_flag = false;

			this->SetStatus(false);//説明オブジェクト3破棄
		}
	}
	else
	{
		m_key_flag = true;
	}

	if(m_gauge_time == 0)
	{
		if(m_f == true)
		{
			m_color = rand() % 6;

			//説明ブロックオブジェクト作成
			CObjExBlock* obj = new CObjExBlock(m_color);
			Objs::InsertObj(obj, OBJ_EX_BLOCK, 20);

			m_f=false;

		}
	}

}

//ドロー
void CObjExplanation3::Draw()
{
	float c[4]={1.0f,1.0f,1.0f,1.0f};
	float c2[4]={2.5f,2.5f,2.5f,1.0f};

	RECT_F src;//描画元の切り取り位置
	RECT_F dst;//描画先の表示位置

//文字表示--------------------------------------------------------------------------------------

	//説明3開始
	Font::StrDraw((wchar_t*)L"3/4",950,10,30,c);
	Font::StrDraw((wchar_t*)L"x0", 770, 110, 60, c);

	Font::StrDraw((wchar_t*)L"　・お邪魔ブロック",100,160,40,c);
	Font::StrDraw((wchar_t*)L"    消すことのできないブロック。", 150, 210 , 28, c);
	Font::StrDraw((wchar_t*)L"    横の数字は次に降ってくるお邪魔の数を", 150, 240, 28, c);
	Font::StrDraw((wchar_t*)L"    表示しています。", 150, 270, 28, c);

	//ゲージの説明
	Font::StrDraw((wchar_t*)L"　・ゲージ",100,380,40,c);
	Font::StrDraw((wchar_t*)L"    赤色のゲージがなくなると",150,440,28,c);
	Font::StrDraw((wchar_t*)L"    弾が勝手に発射される。",150,470,28,c);

	////勝利判定の説明
	//Font::StrDraw(L"　・勝敗について", 100, 430, 40, c);
	//Font::StrDraw(L"　  1P・2Pの端のマスが埋まり、消えない状態になると", 150, 490, 28, c);
	//Font::StrDraw(L"　　ゲーム終了。相手の端のマスにブロックを埋めると", 150, 520, 28, c);
	//Font::StrDraw(L"　　勝利となる" , 150 , 550 , 28 , c);

	Font::StrDraw((wchar_t*)L"Next Page   : → / D", 360, 660, 32, c);
	Font::StrDraw((wchar_t*)L"Back Page   : ← / A", 360, 692, 32, c);

//文字表示おわり--------------------------------------------------------------------------------------------

//お邪魔ブロックを表示---------------------------------------

	//切り取り位置の設定
	RectSet(0.0f,0.0f,32.0f,32.0f,src);

	//表示位置の設定
	RectSet(110.0f,700.0f,770.0f,170.0f,dst);

	Draw::Draw(10, &src, &dst, c2, 0.0f);//描画



//お邪魔ブロックを表示おわり------------------------------------------

//ゲージ表示------------------------------------------------------

	//ゲージ用背景----------------------

	//切り取り位置 灰色
	RectSet(0.0f,401.0f,402.0f,99.0f,src);
	//描画位置
	RectSet(395.0f,695.0f,885.0f,425.0f,dst);
	//描画する
	Draw::Draw(23,&src,&dst,c,0.0f);

	//---------------------------

	//切り取り位置 黒色
	RectSet(0.0f,100.0f,101.0f,99.0f,src);
	//描画位置
	RectSet(400.0f,700.0f,880.0f,420.0f,dst);
	//描画する
	Draw::Draw(23,&src,&dst,c,0.0f);

	//背景終おわり----------------------

	//ゲージ本体------------------

	//切り取り位置
	RectSet(0.0f,1.0f,2.0f,99.0f,src);

	//表示位置
	RectSet(400.0f,700.0f,700.0f+m_gauge_time,420.0f,dst);

	Draw::Draw(23,&src,&dst,c,0.0f);//描画

//ゲージ表示おわり--------------------------------------------------------

//機体の表示---------------------------------------------------
	
	//切り取り位置の設定
	RectSet(1.0f,1.0f,32.0f,31.0f,src);

	//描画位置
	RectSet(460.0f,640.0f,690.0f,510.0f,dst);
	
	Draw::Draw(21,&src,&dst,c,0.0f);//描画

//機体表示おわり------------------------------------------------------------
}