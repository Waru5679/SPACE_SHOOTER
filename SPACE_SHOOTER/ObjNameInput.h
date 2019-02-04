#pragma once

//使用するヘッダー
#include"GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ネーム入力
class CObjNameInput :public CObj
{
public:
	CObjNameInput(int rank);
	~CObjNameInput() {};
	void Init();//イニシャライズ
	void Action();//アクション
	void Draw();//ドロー

	bool KeyInput(int number);	//ネーム入力のキーボードから文字を読み取る関数
	bool InputEndCheck();		//文字列入力が終わっているか(\0があるか)調べる関数
	void NameCpy(char name[]);//文字列の文字ごと間に半角空白をいれる関数

private:
	char m_name[6];		//入力された名前の保存用
	char m_cpy_name[11];//wchar_tに変換する時用の配列
	bool m_first_flag;	//最初の1回だけ処理しないようにするためのフラグ
	bool m_key_flag;	//キーが入力可能な状態かどうかを表すフラグ
	bool m_input_flag;	//キー入力されたかどうかを表すフラグ
	bool m_end_flag;	//名前の入力が終了しているかどうかのフラグ
	bool m_noname_flag;	//何も入力せずにEnterを押した場合に注意分を出すためのフラグ
	bool m_time_flag;	//文字の点滅用フラグ　true:表示時	false:消えてる時
	int m_input_count;	//入力した回数のカウンター。
	int m_rank;			//ランキングの順位
	int m_time;			//文字の点滅用タイム
};