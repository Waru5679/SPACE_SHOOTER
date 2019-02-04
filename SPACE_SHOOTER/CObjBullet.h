#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト:弾丸
class CObjBullet:public CObj
{
public:
	CObjBullet(float x,float y,bool s,int n);//コンストラクタ
	~CObjBullet(){};
	void Init();//イニシャライズ
	void Action();//アクション
	void Draw();//ドロー

	float GetX(){return m_px;}
	float GetY(){return m_py;}

void  BlockHit(
	float *x,bool* left,bool* right,float* vx,int* bt
	);


private:
	float m_px;//位置
	float m_py;
	float m_x;//弾丸のx方向の位置用変数
	float m_y;//弾丸のy方向の位置用変数
	float m_vx;//弾丸のｘ方向の速度用変数
	int m_ani;//着弾アニメーション用
	int m_ani_time;//着弾アニメーション間隔タイム
	bool m_del;//削除チェック
	RECT_F m_eff;//着弾エフェクト描画用
	
	bool m_check;//移動させるかどうかの判定用
	bool m_s;//左右どちら側の機体か判別用　true 右：false 左
	int npc;
};
