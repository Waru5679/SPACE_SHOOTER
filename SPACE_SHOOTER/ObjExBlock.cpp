//---------------------------------------------
// Color Block Move Check
// Collision Check
// 2017-06-12 Monday Released
// By カラスアゲハ
//---------------------------------------------
#include <time.h>

#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjExBlock.h"


//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjExBlock::CObjExBlock(int color)
{
	m_color = color;
}

//イニシャライズ
void CObjExBlock::Init()
{
	srand(time(NULL)); // ランダム情報を初期化
	m_color= rand()%6; // ランダムに色を決める

	m_vx = 2.0f;
	m_px= 700.0f;
	m_py= 470.0f;
}

//アクション
void CObjExBlock::Action()
{
	//メインオブジェクトの呼び出し
	CObjExplanation3 * obj_e3 = (CObjExplanation3*)Objs ::GetObj(OBJ_EXPLANATION3);

	m_px += m_vx;

	if(m_px >= 850.0f || Input::GetVKey('D') == true || Input::GetVKey('A') == true
		|| Input::GetVKey(VK_LEFT) == true || Input::GetVKey(VK_RIGHT) == true)//270まで移動かAまたはDキーを押すと消える。
	{
		obj_e3->Updata();//ゲージを初期化する
		this->SetStatus(false);//自身を削除する
	}

}


//ドロー
void CObjExBlock::Draw()
{
	//描画カラー情報
	float c[4]={1.0f,1.0f,1.0f,1.0f};

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	RectSet(0.0f,0.0f,64.0f,64.0f,src);

	//表示位置の設定
	RectSet(m_py,m_px,m_px+30.0f,m_py+30.0f,dst);

	//ブロックの描画
	Draw::Draw(m_color,&src,&dst,c,0.0f);
}
