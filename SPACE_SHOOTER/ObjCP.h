#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameHead.h"

#define DELETE_INFO_MAX 20

//使用するネームスペース
using namespace GameL;

//ブロックを消せるときの情報を保存するための構造体
struct BlockDelete
{
	Point Pos;	//ブロックが消せるときの上または左に来るブロックの位置
	int Num;	//そのときに消える数を保存
	int Rot;	//そのときの回転数を保存
};

//オブジェクト:CP
class CObjCP:public CObj
{
public:
	void Init();	//初期化
	void Action();	//更新
	void Draw();	//描画
	void ShotMove();//移動、回転、弾の発射をする関数
	void Shot();	//弾を打つ関数

	void BlockPosSave();//ブロックを生成する予定位置の保存
	void Revolution();	//ブロックの回転処理の関数
	
	void EndFlagON(){ m_bEnd = true; }		//ゲームオブジェクトフラグをオンにする
	int ReturnMove(){ return m_MoveCheck; }	//移動の位置を返す関数
	void SetOjmNum(int Num){ m_OjmNum += Num; }	//お邪魔ブロックの生成数をセットする関数

	//AI関連の関数
	void SetDeletePoint(Point Pos, int Num, int Rot);//ブロックの消せるをセットする関数

private:
	//AI関連の情報の初期化
	void AiInit();

	//機体描画
	void AircraftDraw();

	//お邪魔の数描画
	void OjmNumDraw();

	//ゲージ描画
	void GaugeDraw();

	//後のブロック描画
	void AfterBloackDraw();

	Point m_Pos;	//位置
	Point m_Move;	//移動
	Point m_Senter;	//2つのブロック同士の中心点
	Point m_Drow;	//m_senterと基準点（左上か右下）になる点との差(絶対値
	Point m_Shot[2];//マップに入れるときの位置保存用

	BlockDelete DeleteInfo[DELETE_INFO_MAX];	//ブロックを消せるときの情報

	int m_Npc[4];		//ランダム記憶
	int m_BulletCount;	//玉の発射回数
	int m_RotNum;		//ブロックの回転数(0-3）
	int m_MoveCheck;	//移動のチェック用
	int m_Time;			//スタート制御用
	int m_GaugeTime;	//ゲージ用タイム
	int m_OjmNum;		//お邪魔ブロックを降らす数
	int m_ShootTime;	////放置時の強制発射までの時間
	int m_DeleteCount;//ブロックを消す関数の呼び出し回数をカウントする

	bool m_bShot;	//弾丸の発射制御用
	bool m_bRot;	//回転の制御
	bool m_bDis;	//消滅があるか
	bool m_bUp;		//上の移動チェック用
	bool m_bDown;	//下の移動チェック用
	bool m_bEnd;	//ゲームオーバーのチェック
	bool m_bMove;	//移動処理のフラグ

	//描画関連
	RECT_F m_Src;				//描画元の切り取り位置
	RECT_F m_Dst;				//描画先の表示位置
	float m_fNomalColor[4];		//通常の色
	float m_fPreBlockColor[4];	//予測ブロックの色
	float m_fFontColor[4];		//文字表示色の色	
};
