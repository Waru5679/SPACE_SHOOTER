#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト:主人公
class CObjHero:public CObj
{
public:
	CObjHero(){};//コンストラクタ
	~CObjHero(){};//デストラクタ
	void Init();//イニシャライズ
	void Action();//アクション
	void Draw();//ドロー

	void Shot();		//弾を打つ関数
	void Shot_move();	//移動と回転、弾を撃つ処理をする関数

	void EndFlag_ON(){m_end_flag=true;}//ゲームオブジェクトフラグをオンにする
	
	void Block_Pos_Save();//ブロックを生成する予定位置の保存
	
	void Revolution();//ブロックの回転処理をする関数

	int ReturnMove(){return m_move;}//移動の位置を返す関数
	void SetOjmNum(int n){ ojm_num +=n ;}//お邪魔ブロックの生成数をセットする関数

private:
	float m_x;//主人公のｘ方向移動用変数
	float m_y;//主人公のｙ方向移動用変数
		
	float m_vx;//主人公機のｘ方向移動ベクトル用変数
	float m_vy;//主人公機のｙ方向移動ベクトル用変数

	int m_npc[4];//ランダム記憶
	int m_bullet_count;//玉の発射回数
	int m_r;//玉の回転数(0-3）
	bool m_rf;//回転の制御
	Point m_senter;//待機中のブロック同士の中心点
	Point m_drow;//m_senterと基準点（左上か右下）になる点との差(絶対値

	int m_shot_x[2];//マップに入れるx位置の保存用
	int m_shot_y[2];//マップに入れるy位置の保存用

	int m_move;//移動のチェック用
	bool m_down;//下移動の管理
	bool m_up;//上移動の管理

	int m_count_time;//スタート制御用
	bool m_end_flag;//ゲームオーバーオブジェクトの有無チェック
	float m_shoot_count;//放置時の強制発射までの時間

	int m_gauge_time;//ゲージ用タイム
	int ojm_num;//お邪魔ブロックを降らす数

	//デバッグ用
	bool m_f2;//お邪魔ブロックのテスト用
	
	bool m_f;//動いてるブロックの有無保存用
	bool m_push_f;//押し続けるの阻止用のフラグ

	RECT_F src;//描画元の切り取り位置
	RECT_F dst;//描画先の表示位置


};
