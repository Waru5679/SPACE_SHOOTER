//使用するヘッダー
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "ObjNameInput.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjNameInput::CObjNameInput(int rank)
{
	m_rank = rank;	//ランキング
}

//イニシャライズ
void CObjNameInput::Init()
{
	//フラグの初期化
	m_first_flag = true;
	m_key_flag = false;		
	m_input_flag = false;
	m_end_flag = false;
	m_noname_flag = false;
	m_time_flag = true;
	

	//名前用配列の初期化
	for (int i = 0; i <= 6; i++)
		m_name[i] = ' ';//半角空白で初期化
	
	//コピー用配列の初期化
	for (int i = 0; i <= 10; i++)
		m_cpy_name[i] = ' ';//半角空白で初期化

	m_time=0;//点滅用のタイムの初期化
	m_input_count = 0;//名前保存用配列の要素番号初期化

	//出力させる文字のグラフィックを作成
	Font::SetStrTex((wchar_t*)L"名前を入力してください(英字5文字以内)");
	Font::SetStrTex((wchar_t*)L"最低1文字は入力してください");
	Font::SetStrTex((wchar_t*)L"Enterで入力終了");
	Font::SetStrTex((wchar_t*)L"BackSpaceでやり直し");
	Font::SetStrTex((wchar_t*)L"_");
}

//アクション
void CObjNameInput::Action()
{
	m_time++;//点滅用にタイムを増やす

	if (m_time >= 10000)//10000をこえそうになったら0に戻す
		m_time = 0;

	if (m_time % 60 == 0)//60fごとにフラグを入れ替える
		m_time_flag = !(m_time_flag);

	//初めの2回目以降
	if (m_first_flag == false)	
	{
		if(m_end_flag == false)	//入力が終了していなければ
		{
			if (m_key_flag == true)	//キーフラグがオンなら
			{
				m_input_flag = KeyInput(m_input_count);//名前の入力をさせる
				
				if (m_input_flag == true)//対応ボタンのどこかが押されたら
				{
					NameCpy(m_name);//描画用のコピーをとる
					m_end_flag = InputEndCheck();//文字列の入力が終えているかどうかを調べる
					m_key_flag = false;	//キーフラグをオフにする
				}
			}
			else //キーフラグがオフなら
			{
				//1つ前の文字と同じ文字が押されていなければ
				if (Input::GetVKey(m_name[m_input_count - 1]) == false)
					m_key_flag = true;	//キーフラグをオンにする
			}
		}
		else		//入力が完了したら
		{
			//名前をユーザーデータにコピー
			strcpy_s(((UserData*)Save::GetData())->mRankingNameData[m_rank - 1], m_name);		//名前			

			Save::Seve();//UserDataの作成（セーブ）する。
		
			//タイトルシーンに移動
			Scene::SetScene(new CSceneTitle());
		}
	}

	m_first_flag = false;

}

//ドロー
void CObjNameInput::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//通常時のカラー（白）
	float c_red[4]{ 1.0f,0.0f,0.0f,1.0f };	//注意文のカラー（赤）

	//文字の描画
	Font::StrDraw((wchar_t*)L"名前を入力してください(英字5文字以内)", 50.0f, 150.0f, 50.0f, c);
	Font::StrDraw((wchar_t*)L"BackSpaceで入力のやり直し", 100.0f, WINDOW_SIZE_H - 50.0f, 30.0f, c);
	Font::StrDraw((wchar_t*)L"Enterで入力終了",WINDOW_SIZE_W - 300.0f,WINDOW_SIZE_H - 50.0f,30.0f,c);

	wchar_t str_name[50];
	
	//char からwchar_t　に　指定したサイズ分コピー
	size_t* size = nullptr;
	mbstowcs_s(size, str_name, 50, m_cpy_name, 50);
	
	Font::StrDraw(str_name, 350.0f, 400.0f, 50.0f, c);// 入力した文字を表示

	//_の表示
	for (int i = 0; i < 5; i++)
	{
		if(i == m_input_count && m_time_flag == false)//次の入力箇所 かつ　フラグオフなら
			Font::StrDraw((wchar_t*)L" ", 350.0f + 50.0f*i, 400.0f, 50.0f, c);// ' 'を表示
		else
			Font::StrDraw((wchar_t*)L"_", 350.0f + 50.0f*i, 400.0f, 50.0f, c);// '_'を表示
	}

	if(m_noname_flag == true)
		Font::StrDraw((wchar_t*)L"最低1文字は入力してください", 170.0f, 300.0f, 50.0f, c_red);

}

//ネーム入力のキーボードから文字を読み取る関数
//引数:入力された文字を入れる配列の要素数
//戻り値：対応しているkeyが押されたら:true 何処も押されていなければ:false
bool CObjNameInput::KeyInput(int number)
{
	//EnterKeyが押されたとき
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_name[0] == ' ')//未入力の状態なら
			m_noname_flag = true;//入力を促す文章の追加用にフラグをオンにする
		else
			m_name[number] = '\0';	//\0を入れる
		return true;
	}
	
	//バックスペースが押されたとき
	if (Input::GetVKey(VK_BACK) == true)
	{		
		for(int i=0;i<6;i++)
			m_name[i]=' ';//配列の初期化

		m_input_count = 0;

		return true;		
	}

	//keyの状態を調べる
	for (char key = 'A'; key <= 'Z'; key++)
	{
		if (Input::GetVKey(key) == true)
		{
			m_name[number] = key;	//押されたkeyを配列に保存
			
			if( m_input_count < 5)	//5文字目までなら
				m_input_count++;		//保存位置を一文字進める

			return true;
		}
	}
	return false;
}

//文字列入力が終わっているか(\0があるか)調べる関数
//戻り値：\0があれば:true なければ:false 
bool CObjNameInput::InputEndCheck()
{
	//配列の中身を確認していく
	for (int i = 0; i < 6;i++)
	{
		//\0があれば
		if (m_name[i] == '\0')
			return true;
	}

	return false;
}

//文字列の文字ごと間に半角空白をいれる関数
void CObjNameInput::NameCpy(char name[])
{
	int i;
	//文字列の配列サイズになるまでループ
	for (i= 0; i < sizeof(name) * 2 + 1 ; i++)
	{
		if (i % 2 == 0)	//要素数が偶数なら
			m_cpy_name[i] = m_name[i / 2];	//配列に入っている文字をいれる
		else
			m_cpy_name[i] = ' ';			//半角空白をいれる
	}

	m_cpy_name[i] = '\0';//末尾に\0をいれる
}
