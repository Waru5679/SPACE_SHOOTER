#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：メイン
class CObjMain : public CObj
{
public:
	CObjMain(bool tipe) { vs_CP = tipe; }
	~CObjMain() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	//2017-06-19　大改造-------------------

	//指定したマップ要素に指定した値をいれる関数
	void Enter(int x, int y, int n)
	{
		m_map[y][x].num = n;
	}
	//------------------------------------------------------

	//値を返す
	int Return_Num(int x, int y) { return m_map[y][x].num; }//指定したマップ要素の値を返す関数
	int Return_obj_time(int x, int y) { return m_map[y][x].obj_time; }//オブジェクト生成からの時間を返す

	//ブロックの生成関連
	void CreateIntervention(int number, bool m_lr);//お邪魔ブロックの生成
	void FlagOn(int x, int y) { m_map[y][x].obj_check = true; }//指定したマップ要素のオブジェクト生成フラグをオンにする関数

	//stopフラグ関連
	void StopFlag_ON(int x, int y) { m_map[y][x].stop_flag = true; }//指定したマップ要素のストップフラグをオンにする関数
	void StopFlag_OFF(int x, int y) { m_map[y][x].stop_flag = false; }//指定したマップ要素のストップフラグをオフにする関数
	void Enter_Stop_flag(int x, int y, bool stop_flag) { m_map[y][x].stop_flag = stop_flag; }//指定した要素に指定したストップフラグを入れる関数
	bool Return_Stop_Flag(int x, int y) { return m_map[y][x].stop_flag; }//指定したマップ要素のストップフラグを返す関数

	//処理フラグ関連
	void Processflag(int x, int y, bool check) { m_map[y][x].process_check = check; }//指定したマップ要素の処理フラグを指定したものに置き換える
	int ReturnProcess_flag(int x, int y) { return m_map[y][x].process_check; }//処理チェックフラグを返す

	//範囲チェック関連
	bool StopCheck(int y, bool lr);//指定した段の右(または左)半分のストップフラグがオンならtrue:一つでもオフならfalse　を返す関数
	bool ShotCheck(bool lr);//右半分または左半分のブロックが全て止まっているかどうか調べる

	//消滅の処理関連
	void CheckMap(int x, int y, bool check);//つながっているブロックの数を数えて消せるなら消滅処理をする関数
	int BlockDeleteCheck(int x, int y, bool lr);//つながっているブロックの数を数えてその数を返す関数	

	//勝敗関連				
	int BlockCheck(int y, bool lr, int n);//指定した範囲に指定したブロックがあるかどうか調べる関数
	bool VictoryCheck(bool lr);//勝敗の判定用
	bool ReturnFlag() { return flag; }//ゲームオーバーチェックのフラグを返す関数
	void VictoryProcess(bool vs_CP);//勝利判定時のゲームオーバー作成などの処理をする関数
	
	//VSCP用
	void AiDeleteCheck_H(int color1, int color2, int r);//AI用ブロックが消せる位置を探す関数(ブロック縦想定)
	void AiDeleteCheck_W(int color1, int color2, int r);//AI用ブロックが消せる位置を探す関数(ブロック横想定)
	void StopPointCheck();//それぞれの段のどこでブロックがとまるかを調べる関数
	int InSideCheck();//ブロックが止まる位置のなかれ一番小さい位置を探し、複数あればその中からランダムで１つ決める関数
	bool ReturnCPflag() { return vs_CP; }	//CP戦かのフラグを返す関数

	//ランキングシステム用
	int ReturnTime(){return m_time;}

	private:
		bool m_f;
		bool vs_CP;//CP戦か２ｐ戦か区別するフラグ true：CP戦　false:2P戦

		//オブジェクトチェック用のフラグを持ったマップ
		struct MAP
		{
			int num;//ブロックの種類の数字
			bool obj_check;//オブジェクトがすでに生成済みかどうかしらべる
			int obj_time;//オブジェクトが生成されてからのタイムを調べる
			bool stop_flag;//オブジェクトが止まっているか調べるためのフラグ
			bool process_check;//処理済か調べるフラグ
			int before_num;//前回の処理時の数字を保管する
			int stop_time;//そのブロックがとまっている時間を保存する
		};

		MAP m_map[7][20];	//マップ情報ブロック数(X=20,Y=7)	

		bool m_vc_r;//勝敗のチェックフラグ（右）
		bool m_vc_l;//勝敗のチェックフラグ（左）

		int m_count_time;//スタート開始前のカウントダウン
		float font_big_time;//文字が大きくなる時間
		bool flag;//ゲームオーバー管理

		//デバッグ用
		int ojm_num;//お邪魔の数を保存
		int del_num;//最終的に消す数を保存
		int sum_num;//お邪魔ふくめた数を保存	

		//AI用の変数
		int BlockStopPoint[7];

		//ランキング用のタイム計測用
		int m_time;
};
