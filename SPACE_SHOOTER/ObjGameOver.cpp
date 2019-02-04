//使用するヘッダー
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include"GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjGameOver.h"
#include "ObjBackground.h"

#include "GameL\UserData.h"

//使用するネームスペース
using namespace GameL;



//コンストラクタ
CObjGameOver::CObjGameOver(int p)
{
	m_pattern=p; //ゲーム勝利パターンをObjMainから持ってきて、m_patternに代入
}

//イニシャライズ
void CObjGameOver::Init()
{
	//位置の初期化
	m_y = 900.0f;
	m_yy = 800.0f;

	count=0;
	ranking = 0;


	//CP戦かどうかしらべる------
	//マップオブジェクトの呼び出し
	CObjMain * obj = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	m_cp_flag=obj->ReturnCPflag();
	//-------------------------

	//Win.wav以外の音楽をとめる------
	//戦闘曲ストップ
	Audio::Stop(8);
	//勝敗ミュージック開始
	Audio::Start(7);
	//--------------------------------
}

//アクション
void CObjGameOver::Action()
{	
	count++;//カウントを増やしていく

	if( count > 300)//300を超えないようにする
		count = 300;

	//エンターキーがおされたら
	if(Input ::GetVKey(VK_RETURN)==true)
	{
		//マスターボリュームを1.0に戻す
		float v =Audio::VolumeMaster( 0 );
		v =Audio::VolumeMaster( (1.0f-v) );

		//CP戦　かつ　左プレイヤーの勝利なら
		if (m_cp_flag == true && m_pattern == 1)
		{
			//マップオブジェクトの呼び出し
			CObjMain * obj_main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
			
			//ランキングの最下位に今回のタイムと名前を保存
			((UserData*)Save::GetData())->mRankingTimeData[10] = obj_main->ReturnTime();
			strcpy_s( ((UserData*)Save::GetData())->mRankingNameData[10],NO_NAME);

			//ランキングをソートして、今回の順位を調べる
			ranking = RankingSort(((UserData*)Save::GetData())->mRankingTimeData, ((UserData*)Save::GetData())->mRankingNameData);

			//ランキングへ移行
			Scene::SetScene(new CSceneRanking(ranking));
		}
		else
		{
			//タイトルへ移行
			Scene::SetScene(new CSceneTitle);
		}
	}
}

//ドロー
void CObjGameOver::Draw()
{
	float c[4]={1.0f,1.0f,1.0f,1.0f};//カラー
		
	Result();//結果を表示する
	Font::StrDraw((wchar_t*)L"EnterKeyでタイトルに戻る",223,m_y - count,50,c);
	
}

//パターンに応じて
void CObjGameOver::Result()
{
	CObjCP* obj_cp = new CObjCP();

	float c[4]={1.0f,1.0f,1.0f,1.0f};//カラー
	
	switch(m_pattern)
	{
		case 0:
		{
			//引き分け表示
			Font::StrDraw((wchar_t*)L"DROW",400,m_yy - count,100,c);
			break;
		}
		case 1:
		{
			if (obj_cp != nullptr)
			{
				//CPU勝利
				Font::StrDraw((wchar_t*)L"YOU WIN", 350, m_yy - count, 100, c);
				break;
			}
			else//2人対戦時
			{
				//1Pwin表示
				Font::StrDraw((wchar_t*)L"1P WIN", 350, m_yy - count, 100, c);
				break;
			}
		}
		case 2:
		{
			if (obj_cp != nullptr)//CPU対戦か否か判定
			{
				//CPU勝利
				Font::StrDraw((wchar_t*)L"YOU LOSE", 350, m_yy - count, 100, c);
				break;
			}
			else//2人対戦時
			{
				//2Pwin表示
				Font::StrDraw((wchar_t*)L"2P WIN", 350, m_yy - count, 100, c);
				break;
			}
		}
	}
}

//低い順でソートを行う
//引数1:タイム配列
//引数2:名前配列
//戻り値：今回の順位
int CObjGameOver::RankingSort(int time[],char name[][6])
{
	int w;		//タイム交換用変数
	int ranking;//今回の順位保存用
	char n[6];	//名前交換用配列

	//ソート
	for (int i = 10; i >= 1; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (time[i] <= time[j])
			{
				//タイムの交換
				w = time[i];
				time[i] = time[j];
				time[j]= w;

				//名前の交換
				strcpy_s(n, name[i]);
				strcpy_s(name[i], name[j]);
				strcpy_s(name[j], n);
			}
		}
	}

	//未入力の名前箇所を探して今回の順位を調べる
	for (int i = 0; i < 11; i++)
	{
		//名前が未入力なら
		if (strcmp(name[i], NO_NAME) == 0)
		{
			ranking = i + 1; //順位保存
			break;
		}
	}

	return ranking;
}
