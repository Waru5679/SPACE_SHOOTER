#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//マップ情報構造体
struct MAP
{	int Num;		//ブロックの種類の数字
	int ObjTime;	//オブジェクトが生成されてからのタイムを調べる
	int BeforeNum;	//前回の処理時の数字を保管する
	int StopTime;	//そのブロックがとまっている時間を保存する

	bool bStop;		//オブジェクトが止まっているか
	bool bProcess;	//処理済か
	bool bCreate;	//オブジェクトが生成済みか

};

//オブジェクト：メイン
class CObjMain : public CObj
{
public:
	CObjMain(bool tipe) { m_bCpBattle = tipe; }
	~CObjMain() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	void MapUpdate();//マップ更新

	//指定したマップ要素に指定した値をいれる関数
	void Enter(int x, int y, int n)	{m_map[y][x].Num = n;}

	//指定したマップ要素の値を返す関数
	int ReturnNum(int x, int y) { return m_map[y][x].Num; }

	//オブジェクト生成からの時間を返す
	int ReturnObjTime(int x, int y) { return m_map[y][x].ObjTime; }

	//お邪魔ブロックの生成
	void CreateIntervention(int number, bool m_lr);

	//指定したマップ要素の生成フラグをオンにする
	void FlagOn(int x, int y) { m_map[y][x].bCreate = true; }

	//指定したマップ要素のストップフラグを切り替え
	void StopFlagOn(int x, int y) { m_map[y][x].bStop = true; }
	void StopFlagOff(int x, int y) { m_map[y][x].bStop = false; }

	//指定した要素に指定したストップフラグを入れる関数
	void EnterStopFlag(int x, int y, bool Stop) { m_map[y][x].bStop = Stop; }

	//指定したマップ要素のストップフラグを返す関数
	bool ReturnStopFlag(int x, int y) { return m_map[y][x].bStop; }

	//指定したマップ要素の処理フラグを指定したものに置き換える
	void Processflag(int x, int y, bool Process) { m_map[y][x].bProcess = Process; }

	//処理チェックフラグを返す
	int ReturnProcess(int x, int y) { return m_map[y][x].bProcess; }

	//指定した段の右(または左)半分のストップフラグがオンならtrue:一つでもオフならfalse　を返す関数
	bool StopCheck(int y, bool lr);

	//右半分または左半分のブロックが全て止まっているかどうか調べる
	bool ShotCheck(bool lr);

	//つながっているブロックの数を数えて消せるなら消滅処理をする関数
	void CheckMap(int x, int y, bool check);

	//つながっているブロックの数を数えてその数を返す関数	
	int BlockDeleteCheck(int x, int y, bool lr);

	//タイムを返す
	int ReturnTime() { return m_Time; }
	
	//指定した範囲に指定したブロックがあるかどうか調べる関数
	int BlockCheck(int y, bool lr, int n);
	
	//勝敗の判定用
	bool VictoryCheck(bool lr);
	
	//ゲームオーバーチェックのフラグを返す
	bool GameOverCheck() { return m_bGameOver; }

	//勝利判定時のゲームオーバー作成などの処理をする関
	void VictoryProcess(bool vs_CP);
	
//VSCP用-------------------------------
	//AI用ブロックが消せる位置を探す関数(ブロック縦想定)
	void AiDeleteCheck_H(int color1, int color2, int r);
	
	//AI用ブロックが消せる位置を探す関数(ブロック横想定)
	void AiDeleteCheck_W(int color1, int color2, int r);
	
	//それぞれの段のどこでブロックがとまるかを調べる
	void StopPointCheck();

	//ブロックが止まる位置のなかで一番小さい位置を探し、複数あればその中からランダムで１つ決める
	int InSideCheck();
//-------------------------------------
	
	//CP戦かのフラグを返す関数
	bool ReturnCPflag() { return m_bCpBattle; }	

private:
	MAP m_map[7][20];		//マップ情報ブロック数(X=20,Y=7)

	int m_CountTime;		//スタート開始前のカウントダウン
	int m_FontBigTime;		//文字が大きくなる時間
	int m_Time;				//ランキング用のタイム計測用
	int m_BlockStopPoint[7];//ブロックの止まる位置(AI用)

	bool m_bGameOver;	//ゲームオーバー管理
	bool m_bRightWin;	//勝敗のチェック
	bool m_bLeftWin;	//勝敗のチェック
	bool m_bCpBattle;	//CP戦か２ｐ戦か区別する
};
