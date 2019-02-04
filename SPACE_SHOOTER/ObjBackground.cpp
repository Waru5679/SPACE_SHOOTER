//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBackground.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjBackground::Init()
{
	m_count_time=0;
}

//アクション
void CObjBackground::Action()
{
	m_count_time++;
}

//ドロー
void CObjBackground::Draw()
{
	//描画カラー情報　R=RED G=Green B=Blue A=alpha(透過情報)
	float c[4]={1.0f,1.0f,1.0f,0.8f};
	float c1[4]={1.0f,1.0f,1.0f,1.0f};
	RECT_F src;//描画元の切り取り位置
	RECT_F dst;//描画先の表示位置

	//切り取り位置の設定
	RectSet(0.0f,0.0f,512.0f,512.0f,src);

	//背景の表示位置の設定
	RectSet(0.0f,0.0f,WINDOW_SIZE_W,WINDOW_SIZE_H,dst);

	if(m_count_time<270)//スタートまでのカウント中
	{
		Draw::Draw(7,&src,&dst,c,0.0f);//枠なし背景の描画
	}
	else//カウント終了後
	{			
		Draw::Draw(8,&src,&dst,c,0.0f);//枠有背景の描画
	}


}
