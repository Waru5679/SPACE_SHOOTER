//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjMain.h"

#include <stdlib.h>
#include <time.h>

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMain::Init()
{
	//MAP構造体の初期化
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<20;j++)
		{
			m_map[i][j].Num = 99;
			m_map[i][j].BeforeNum = 99;
			m_map[i][j].StopTime = 0;
			m_map[i][j].ObjTime = 0;
			m_map[i][j].bCreate	= false;
			m_map[i][j].bStop = false;
			m_map[i][j].bProcess = true;
		}
	}

	//勝利判定フラグ初期化
	m_bLeftWin=false;
	m_bRightWin-false;

	//スタートカウントダウン
	m_CountTime=0;

	//文字が大きくなる時間
	m_FontBigTime=0;

	//ランキング用タイムの初期化
	m_Time = 0;

	//ゲームオーバー管理
	m_bGameOver = false;

	//AI用
	for(int i=0;i<7;i++)
	{
		m_BlockStopPoint[i]=19;//ブロックの止まる位置
	}
}

//アクション
void CObjMain::Action()
{
	//勝負が終わっていればなにもしない
	if (m_bGameOver == true) return;

	m_CountTime++;

	//スタートの表示が終わっていれば
	if (m_CountTime > 270)
	{
		//ランキング用のタイム計測
		if ((m_CountTime - 270) % 60 == 0)
			m_Time++;				
	}

	//ヒーローオブジェクトの呼び出し
	CObjHero * obj_h =(CObjHero*)Objs ::GetObj(OBJ_HERO);		
	CObjHero_R * obj_hr =(CObjHero_R*)Objs ::GetObj(OBJ_HERO_R);
	
	//マップ情報更新
	MapUpdate();

	//勝敗判定
	m_bLeftWin=VictoryCheck(true);//左
	m_bRightWin=VictoryCheck(false);//右
	
	if(m_bGameOver == false)
	{
		VictoryProcess(m_bCpBattle);//勝利判定をみたしているか調べ、満たしていれば処理をする
	}
}

//マップ更新
void CObjMain::MapUpdate()
{
	//Map情報更新
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			//前回の処理時と同じ数値が入っていれば
			if (m_map[i][j].Num == m_map[i][j].BeforeNum)
				m_map[i][j].StopTime++;//ストップタイムを増やす
			else
				m_map[i][j].StopTime = 0;//ストップタイムを0に戻す

			//色ブロックが入っていれば
			if (m_map[i][j].Num < 6)
			{
				//オブジェクト生成フラグがオンなら
				if (m_map[i][j].bCreate == true)
				{
					//特殊なケース　右端 横向きのとき
					//18番目で19番目にもブロックが入っている場合（右側で横向きにうったとき
					if (j == 18 && (m_map[i][19].Num < 6))
					{
						//ブロック作成
						CObjBlock* obj_b = new CObjBlock(j, i, m_map[i][j].Num, false, true);
						Objs::InsertObj(obj_b, OBJ_BLOCK, 10);

						m_map[i][j].bCreate = false;	//オブジェクト生成フラグをオフにする
						m_map[i][j].bStop = false;	//ブロック生成位置のストップフラグをオフにする
						m_map[i][j].ObjTime = 0;		//オブジェクト生成タイムをリセットする
					}
					//普通のケース
					else
					{
						//左側用のブロック生成
						if (j <= 9)
						{
							CObjBlock* obj_b = new CObjBlock(j, i, m_map[i][j].Num, true, false);
							Objs::InsertObj(obj_b, OBJ_BLOCK, 10);
						}
						//右側用のブロック生成
						else if (j >= 10)
						{
							CObjBlock* obj_b = new CObjBlock(j, i, m_map[i][j].Num, false, false);
							Objs::InsertObj(obj_b, OBJ_BLOCK, 10);
						}

						m_map[i][j].bCreate = false;//オブジェクト生成フラグをオフにする
						m_map[i][j].bStop = false;	//ブロック生成位置のストップフラグをオフにする
						m_map[i][j].ObjTime = 0;		//オブジェクト生成タイムをリセットする
					}
				}
			}
			//お邪魔ブロック
			if (m_map[i][j].Num == 6)
			{
				//オブジェクト生成フラグがオンなら
				if (m_map[i][j].bCreate == true)
				{
					//左側用のブロック生成
					if (j <= 9)
					{
						CObjIntervention* obj_i = new CObjIntervention(j, i, true);
						Objs::InsertObj(obj_i, OBJ_INTERVENTION, 10);
					}
					//右側用のブロック生成
					else if (j >= 10)
					{
						CObjIntervention* obj_i = new CObjIntervention(j, i, false);
						Objs::InsertObj(obj_i, OBJ_INTERVENTION, 10);
					}

					m_map[i][j].bCreate = false;//オブジェクト生成フラグをオフにする
					m_map[i][j].bStop = false;	//ブロック生成位置のストップフラグをオフにする
					m_map[i][j].ObjTime = 0;	//オブジェクト生成タイムをリセットする
				}
			}
			//消滅アニメーション　
			if (m_map[i][j].Num == 98)
			{
				//消滅処理の判定がアニメーションの時間より長くとどまっていたら//空白にもどす
				if (m_map[i][j].StopTime >= 5)
					m_map[i][j].Num = 99;
			}
			//空白 99
			if (m_map[i][j].Num == 99)
			{
				//処理済フラグをオンにする
				m_map[i][j].bProcess = true;
			}

			//番号を保存する
			m_map[i][j].BeforeNum = m_map[i][j].Num;

			//オブジェクトのタイム更新
			m_map[i][j].ObjTime++;
			if (m_map[i][j].ObjTime > 10000)
				m_map[i][j].ObjTime = 10;
		}
	}
}

//ドロー
void CObjMain::Draw()
{
	//描画カラー情報
	float c[4]={1.0f,1.0f,1.0f,1.0f};
	float start[4]={1.0f,1.0f,0.0f,1.0f};

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置
	
	wchar_t str[10];//0:分　1:秒

	//スタートのカウントが終わっていれば
	if(m_CountTime>=270)
	{
		//スコア表示
		swprintf_s(str, L"%02d:%02d",m_Time/60, m_Time % 60);
		Font::StrDraw(str, 430.0f, 20.0f, 60.0f, c);

		//ここからブロック表示-----------
		for(int y=0;y<7;y++)
		{
			for(int x=0;x<20;x++)
			{
				//表示位置の設定
				RectSet(80.0f+y*BLOCK_SIZE,50.0f+x*BLOCK_SIZE,
					50.0f+x*BLOCK_SIZE+BLOCK_SIZE,80.0f+y*BLOCK_SIZE+BLOCK_SIZE,dst);
				
				//枠表示
				if(x==9)
				{
					//青いウィンドウ
					//切り取り位置の設定
					RectSet(46.0f,320.0f,320.0f+64.0f,46.0f+64.0f,src);
					
					Draw::Draw(9,&src,&dst,c,0.0f);//描画
				}
				else if(x==10)
				{
					//青いウィンドウ
					//切り取り位置の設定
					RectSet(46.0f,255.0f,255.0f+64.0f,46.0f+64.0f,src);
					
					Draw::Draw(9,&src,&dst,c,0.0f);//描画
				}
				else if(m_map[y][x].Num==99)
				{
					//白いウィンドウ
					//切り取り位置の設定
					RectSet(111.0f,255.0f,255.0f+64.0f,111.0f+64.0f,src);
					
					Draw::Draw(9,&src,&dst,c,0.0f);//描画
				}
			}
		}
	}

	//切り取り位置の設定
	RectSet(0.0f,0.0f,256.0f,256.0f,src);

	//3
	if(m_CountTime<=70)
	{
		if(m_CountTime ==5)
			Audio::Start(9);//効果音

		m_FontBigTime++;

		//font_big_timeが増えるにつれて表示される数字が大きくなる
		//描画位置の設定
		RectSet(200-m_FontBigTime,420-m_FontBigTime,570+m_FontBigTime,400+ m_FontBigTime,dst);
		
		Draw::Draw(11,&src,&dst,c,0.0f);//描画
		
	}

	//2
	if(m_CountTime>70&&m_CountTime<=140)
	{
		if(m_CountTime ==75)
			Audio::Start(9);//効果音

		m_FontBigTime++;

		RectSet(200- m_FontBigTime,420- m_FontBigTime,570+ m_FontBigTime,400+ m_FontBigTime,dst);

		Draw::Draw(12,&src,&dst,c,0.0f);//描画
	}

	//1
	if(m_CountTime>140&&m_CountTime<=210)
	{
		if(m_CountTime ==145)
			Audio::Start(9);//効果音

		m_FontBigTime++;

		RectSet(200- m_FontBigTime,420- m_FontBigTime,570+ m_FontBigTime,400+ m_FontBigTime,dst);

		Draw::Draw(13,&src,&dst,c,0.0f);//描画

	}

	//START
	if(m_CountTime>210&&m_CountTime<=260)
	{
		if(m_CountTime ==215)
			Audio::Start(10);//効果音

		RectSet(100.0f,300.0f,700.0f,400.0f,dst);

		Draw::Draw(14,&src,&dst,start,0.0f);//描画
	}

	//カウントが70きたときに元のサイズに戻す
	if(m_FontBigTime ==70)
		m_FontBigTime =0;
}

//つながっているブロックの数を数えてけせるなら消滅処理をする関数
//引数1 :要素番号X
//引数2 :要素番号Y
//引数3 :左右チェック（どちら側から来てるブロックか）
void CObjMain::CheckMap(int x, int y,bool lr)
{
	int pos[2];
	int number=0;	//つながっているブロックの数カウント
	int OjmCount=0;	//お邪魔ブロックの数カウント
	int Color=m_map[y][x].Num;	//検索対象の色を保存

	pos[0]=x;
	pos[1]=x;

	//左側のPlayerが放った かつ　Block停止状態
	if(lr==true) 	
	{
		//配列終わりまで探索
		for(int i=x; i<20; i++)
		{ 
			//色検出
			if(m_map[y][i].Num==Color)
			{
				pos[1]=i;//場所を記録
				
			}
			//探索中に空白にがあったらそこで探索終了
			if(m_map[y][i].Num==99)
				break;
		}
			
	}
	//右側のPlayerが放った　かつ　Block停止状態
	else
	{
		//配列終わりまで探索
		for(int i=x; i>0; i--)
		{ 
			//色検出
			if(m_map[y][i].Num==Color)
			{
				pos[1]=i;//場所を記録
			}

			//探索中に空白にがあったらそこで探索終了
			if(m_map[y][i].Num==99)
				break;
		}
	}

	//つながっている数(お邪魔と両サイド込み)を求める
	number=abs(pos[1]-pos[0])+1;

	//左側プレーヤー
	if(lr==true)
	{
		//消す範囲内にお邪魔が何個あるかカウントする
		for(int i=x; i<pos[1]; i++)
		{
			if(m_map[y][i].Num==6)
				OjmCount++;
		}
	}
	//右側プレイヤー
	else 
	{
		//消す範囲内にお邪魔が何個あるかカウントする
		for(int i=x; i>pos[1]; i--)
		{
			if(m_map[y][i].Num==6)
				OjmCount++;
		}
	}
	
	//色ブロックのみの数(つながっている数 - お邪魔の数)
	int BlockNum = number - OjmCount;
	
	//色ブロックの数が4以上なら
	if(BlockNum >= 4)
	{
		for(int i=0 ; i<number;i++)
		{
			//マップに爆発処理用の数字(98)をいれる
			if(lr==true)
				m_map[y][x+i].Num=98;
			else
				m_map[y][x-i].Num=98;
		}
	}

	//お邪魔を除いて消した数が5以上なら
	if(BlockNum>=5)
	{
		//プレイヤーの呼び出し
		CObjHero * obj_h =(CObjHero*)Objs ::GetObj(OBJ_HERO);

		//左側Player
		if(lr==true)
		{
			//CP戦
			if(m_bCpBattle == true)
			{
				//お邪魔の生成数を設定
				CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);//CP
				obj_cp->SetOjmNum(BlockNum-4);//生成するお邪魔の数を保存
			}
			//2P戦
			else
			{
				//お邪魔の生成数を設定
				CObjHero_R * obj_hr =(CObjHero_R*)Objs ::GetObj(OBJ_HERO_R);
				obj_hr->SetOjmNum(BlockNum-4);
			}
		}

		//右側Player
		else
		{
			//お邪魔の生成数を設定
			obj_h->SetOjmNum(BlockNum-4);
		}	
	}
}

//お邪魔ブロックの量計算と生成
//引数1：生成するお邪魔ブロックの数　　　
//引数2：ブロックを生成する方向
void CObjMain::CreateIntervention(int number,bool lr)
{
	int y;//生成するお邪魔の高さ保存用

    //Debug用　発生済みお邪魔キャラの数
    int SpawnBombCnt=0;

	int Dec=0x0000000;//決定位置
	int Sch=0x0000000;//予定位置　７ビットで管理する
		
	int j=0;//ブロックを入れる要素が端から何番目かカウント
		
	//生成するお邪魔の数だけまわす
	for(int i = 0; i < number ; i++)
	{
		do
		{
			//7番目のお邪魔なら
			if(i==7)
			{
				Dec=0x0000000;//決定を初期化し
				j++;//生成位置を一つ内側にずらす
			}

			y = rand() % 7;//ランダムで位置を決める
			Sch = 1 << y;

		}while((Dec & Sch ) != 0x0000000);//生成予定地が決定済位置とかぶっていなければ抜ける
			
		//決定した位置には１を入れる
		Dec += (1 << y);

		//左側に降らす時
		if(lr==true)
		{
			Enter(0+j,y,6);	//マップに入れる
			FlagOn(0+j,y);	//オブジェクト生成フラグをオンにする				
		}
		//右側に降らす時
		else
		{
			Enter(19-j,y,6);//マップに入れる
			FlagOn(19-j,y);	//オブジェクト生成フラグをオンにする
		}		
	}
}

//右半分または左半分のブロック全てが止まっているか調べる
//引数：どちら側を調べるかをあらわす。tureなら左、falseなら右
//戻り値:範囲の全てが止まっていればtrue:違えばfalseを返す
bool CObjMain::ShotCheck(bool lr)
{
	for(int i=0;i<7;i++)
	{
		//StopCheck関数を用いて一段ずつ調べていく
		if( StopCheck(i,lr)==false )
			return false;
	}
	return true;
}

//指定した段の指定した範囲（右半分または左半分）のオンになっているストップフラグの数を数える関数
//引数１：調べたい段
//引数２：調べたい方向
//戻り値：全てオンならtrue:１つでもオフがあればfalseを返す
bool CObjMain::StopCheck(int y,bool lr)//指定した段の全てのブロックがとまっていれば
{
	int count=0;//ストップフラグのカウント用
	
	//左側
	if(lr==true)
	{
		for(int i=0;i<=9;i++)
		{
			//その位置に色ブロックまたはお邪魔ブロックが入っていれば
			if( ( 0<=m_map[y][i].Num) && (m_map[y][i].Num <= 6 ) )  
			{
				//ストップフラグがオフなら
				if(m_map[y][i].bStop==false)	
				{	
					//そのブロックが動いている状態
					return false;
				}
			}
		}
	}
	//右側
	else
	{	for(int i=10;i<=19;i++)
		{
			//その位置に色ブロックまたはお邪魔ブロックが入っていれば
			if( ( 0<=m_map[y][i].Num) && (m_map[y][i].Num <= 6 ) )  
			{
				//ストップフラグがオフなら
				if(m_map[y][i].bStop==false)	
				{
					//そのブロックが動いている状態
					return false;
				}
			}
		}
	}
	return true;
}

//勝敗の判定用の関数
//引数1:左右を示すフラグ
//一番端にブロックは入っていて、そこに50フレーム以上とどまっていればtrue。それ以外ならfalse
bool CObjMain::VictoryCheck(bool lr)
{
	//一番端のx方向の要素数
	int SideIndex;

	for(int i=0;i<7;i++)
	{
		//左
		if(lr==true)
			SideIndex =0;
		//右
		else
			SideIndex =19;

		//色ブロックかお邪魔ブロックが入っているなら
		if( 0<=m_map[i][SideIndex].Num && m_map[i][SideIndex].Num<=6)
		{
			//そこに50フレーム以上とどまっているなら
			if(m_map[i][SideIndex].StopTime >= 50)
				return true;
		}
	}
	return false;
}

//指定した範囲に指定ブロックがあるか調べる関数
//引数1　y	：段数
//引数2　lr	：右か左かのフラグ
//引数3　n	：調べたい数
//戻り値　見つけた数を返す
int CObjMain::BlockCheck(int y,bool lr,int n)
{
	int count=0;//見つけた個数カウント用

	for(int i=0;i<=9;i++)
	{
		//左
		if(lr==true)
		{
			if(m_map[y][i].Num == n)
				count++;
		}
		//右
		else
		{
			if(m_map[y][i+10].Num == n)
				count++;
		}
	}
	
	return count;
}

//つながっているブロックの数を数えてその数を返す関数
//引数1 :要素番号X
//引数2 :要素番号Y
//引数3 :左右チェック
int CObjMain::BlockDeleteCheck(int x,int y,bool lr)
{
	int Pos[2];
	int Number = 0;		//つながっているブロックの数カウント
	int OjmCount = 0;	//お邪魔ブロックの数カウント
	int Color = m_map[y][x].Num;	//検索対象の色を保存

	Pos[0] = x;
	Pos[1] = x;

	//左側のPlayerが放った かつ　Block停止状態
	if (lr == true)
	{
		//配列終わりまで探索
		for (int i = x; i < 20; i++)
		{
			//色検出
			if (m_map[y][i].Num == Color)
			{
				Pos[1] = i;//場所を記録

			}
			//探索中に空白にがあったらそこで探索終了
			if (m_map[y][i].Num == 99)
				break;
		}

	}
	//右側のPlayerが放った　かつ　Block停止状態
	else
	{
		//配列終わりまで探索
		for (int i = x; i > 0; i--)
		{
			//色検出
			if (m_map[y][i].Num == Color)
			{
				Pos[1] = i;//場所を記録
			}

			//探索中に空白にがあったらそこで探索終了
			if (m_map[y][i].Num == 99)
				break;
		}
	}

	//つながっている数(お邪魔と両サイド込み)を求める
	Number = abs(Pos[1] - Pos[0]) + 1;

	//左側プレーヤー
	if (lr == true)
	{
		//消す範囲内にお邪魔が何個あるかカウントする
		for (int i = x; i < Pos[1]; i++)
		{
			if (m_map[y][i].Num == 6)
				OjmCount++;
		}
	}
	//右側プレイヤー
	else
	{
		//消す範囲内にお邪魔が何個あるかカウントする
		for (int i = x; i > Pos[1]; i--)
		{
			if (m_map[y][i].Num == 6)
				OjmCount++;
		}
	}

	//色ブロックのみの数(つながっている数 - お邪魔の数)
	int BlockNum = Number - OjmCount;
	
	//つながっている数-お邪魔の数が4以上なら
	if(BlockNum >=4)
	{		
		return BlockNum;
	}
	else
		return 0;
}

//それぞれの段のどこでブロックがとまるかを調べる関数
void CObjMain::StopPointCheck()
{
	//右から調べてブロックの止まるであろう位置を探す-----
	for(int i=0;i<7;i++)
	{
		for(m_BlockStopPoint[i]=19;m_BlockStopPoint[i]>=10;m_BlockStopPoint[i]--)
		{
			//空白なら
			if(m_map[i][ m_BlockStopPoint[i] ].Num == 99)
			{
				;//なにもしない
			}
			//それ以外なら
			else
			{
					break;//ループを抜ける
			}
		}

		//このときBlockStopPointは右側からみて初めてブロックが入っている箇所になる
		//ブロックが来るのはこの一つ右隣なのでもう一つ右の値が欲しい
		m_BlockStopPoint[i]++;//BlockStopPointの値を一つ増やす
	}
}

//AI用ブロックが消せる位置を探す関数(ブロック縦バージョン)
//引数１：色１(上側想定)
//引数２：色２(下側想定)
//引数３：回転の情報
void CObjMain::AiDeleteCheck_H(int color1,int color2,int r)
{
	//CPオブジェクトの呼び出し
	CObjCP * ObjCp =(CObjCP*)Objs ::GetObj(OBJ_CP);
	
	//色1,2同じ色の位置を保存する
	int PointColor[2];	
	
	int DeleteNum = -1;	//最終的な消せる数

	int DeleteNumColor1[7];	//それぞれの段で色１の消せる数
	int DeleteNumColor2[7];	//それぞれの段で色２の消せる数
	
	int OjmCount[7];//お邪魔ブロックのカウント

	//初期化
	for(int i=0;i<7;i++)
	{
		DeleteNumColor1[i]=-1;
		DeleteNumColor2[i]=-1;
		OjmCount[i]=0;
	}

	//消せる位置の保存用
	Point DeletePoint;
	DeletePoint.x=-1;
	DeletePoint.y=-1;
	
	//ブロックの止まるであろう位置を探す
	StopPointCheck();
	
	//上から一段ずつ色1,2で消せる数を調べていく
	for(int y=0;y<7;y++)
	{
		//初期値に戻す
		PointColor[0] = -1;
		PointColor[1] = -1;

		//ブロックが止まる位置の一つ左から順に見ていく
		for(int i=m_BlockStopPoint[y]-1;i>0;i--)
		{
			//空白ならそれ以上見る必要がないのでループを抜ける
			if( m_map[y][i].Num == 99 )
			{
				break;
			}

			//色1と同じ色ならその位置を保存する
			if( m_map[y][i].Num == color1)
			{
				PointColor[0]=i;
			}

			//色2と同じ色ならその位置を保存する
			if( m_map[y][i].Num == color2)
			{
				PointColor[1] = i;
			}

			//お邪魔ブロックならお邪魔のカウントを増やす
			if(m_map[y][i].Num==6)
			{
				OjmCount[y]++;
			}
		}

		//その段で色１が見つかっていれば消せる数を更新する
		if(PointColor[0] != -1)
		{
			DeleteNumColor1[y] = abs( m_BlockStopPoint[y] - PointColor[0]) + 1 - 4 - OjmCount[y];
		}

		if(PointColor[1] != -1)//その段で色2が見つかっていれば消せる数を更新する
		{
			DeleteNumColor2[y] = abs( m_BlockStopPoint[y] - PointColor[1]) + 1 - 4 - OjmCount[y];
		}
	}
	
	//それぞれの詳細情報を求めて送る
	for(int y=0;y<7;y++)
	{	
		//色1の消せる数が0以上なら
		if(DeleteNumColor1[y] >= 0)
		{
			if(y < 6)//一番したの段で色２が消せることはないので省く
			{
				//一つ下の段ので色2が消える
				if(DeleteNumColor2[y+1] >= 0)
				{
					//その段で色１が消せる数＋その1つ下で色２が消せる数の合計を保存
					DeleteNum = DeleteNumColor1[y]+DeleteNumColor2[y+1];
				}
				//色１だけが消せる場合
				else
				{
					//その段で色１が消せる数を保存
					DeleteNum = DeleteNumColor1[y];
				}
				
				//消せるポイントを保存する
				DeletePoint.x=m_BlockStopPoint[y];
				DeletePoint.y=y;

				//消せるポイント、数、回転情報を送る
				ObjCp->SetDeletePoint(DeletePoint,DeleteNum,r);
			}
		}
		
		//色2の消せる数が0以上なら
		if( DeleteNumColor2[y] >= 0)
		{
			if(y >= 1)//一番上の段で色2が消せることはないので省く
			{
				//色1も消えて色2も消える場合
				if(DeleteNumColor2[y-1] >=0 )
				{
				
					//色1で消える数＋色2で消える数
					DeleteNum = DeleteNumColor2[y]+ DeleteNumColor1[y];
				}
				//色１は消えなくて色２だけ消える場合
				else
				{
					//その段で色2が消せる数
					DeleteNum = DeleteNumColor2[y];
				}

				//消せるポイントを保存する
				DeletePoint.x = m_BlockStopPoint[y - 1];
				DeletePoint.y = y - 1;
				
				//消せるポイント、数、回転情報を送る
				ObjCp->SetDeletePoint(DeletePoint,DeleteNum,r);	
			}
		}
	}
}

//AI用ブロックが消せる位置を探す関数(ブロック横バージョン)
//引数１：色１(左側想定)
//引数２：色２(右側想定)
//引数３：回転の情報
void CObjMain::AiDeleteCheck_W(int color1,int color2,int r)
{
	//CPオブジェクトの呼び出し
	CObjCP * ObjCp =(CObjCP*)Objs ::GetObj(OBJ_CP);
	
	//色1,2同じ色の位置を保存する
	int PointColor[2];

	int DeleteNum = -1;	//最終的な消せる数

	int DeleteNumColor1[7];	//それぞれの段で色１の消せる数
	int DeleteNumColor2[7];	//それぞれの段で色２の消せる数

	int OjmCount[7];//お邪魔ブロックのカウント

	//初期化
	for(int i=0;i<7;i++)
	{
		DeleteNumColor1[i]=-1;
		DeleteNumColor2[i]=-1;
		OjmCount[i]=0;
	}

	//消せる位置の保存用
	Point DeletePoint;
	DeletePoint.x=-1;
	DeletePoint.y=-1;
	
	//ブロックの止まるであろう位置を探す
	StopPointCheck();
	
	//上から一段ずつ色1,2で消せるかずを調べていく
	for(int y=0;y<7;y++)
	{
		//初期値に戻す
		PointColor[0] = -1;
		PointColor[1] = -1;

		//ブロックが止まる位置の一つ左から順に見ていく
		for(int i=m_BlockStopPoint[y]-1;i>0;i--)
		{
			//空白ならそれ以上見る必要がないのでループを抜ける
			if( m_map[y][i].Num == 99 )
			{
				break;
			}

			//色1と同じ色ならその位置を保存する
			if( m_map[y][i].Num == color1)
			{
				PointColor[0]=i;
			}

			//色2と同じ色ならその位置を保存する
			if( m_map[y][i].Num == color2)
			{
				PointColor[1] = i;
			}

			//お邪魔ブロックならお邪魔カウントを増やす
			if(m_map[y][i].Num==6)
			{
				OjmCount[y]++;
			}

			//その段で色1が見つかっていれば消せる数を更新する
			if(PointColor[0] != -1)
			{
				DeleteNumColor1[y] = abs( m_BlockStopPoint[y] - PointColor[0]) + 1 - 4 - OjmCount[y];		
			}

			//その段で色2が見つかっていれば消せる数を更新する
			if (PointColor[1] != -1)
			{
				DeleteNumColor2[y] = abs(m_BlockStopPoint[y] - PointColor[1]) + 1 - 4 - OjmCount[y];
			}
		}
	}
	
	//それぞれの詳細情報を求めて送る
	//横向きの場合は色1と2のによって位置の変化は無いので消せる数だけ調べればいい
	for(int y=0;y<7;y++)
	{
		//色1か色2の消せる数が0よりおおきければ
		if( DeleteNumColor1[y] >= 0 || DeleteNumColor2[y] >= 0)
		{
			//消せるポイントを保存する
			DeletePoint.x=m_BlockStopPoint[y];
			DeletePoint.y=y;

			//色１と２で消せる数の大きい方を調べて送る

			//色1の方が多く消せる場合
			if(DeleteNumColor1[y] >=DeleteNumColor2[y])	
			{
				ObjCp->SetDeletePoint(DeletePoint,DeleteNumColor1[y],r);				
			}
			//色2の方が多く消せる場合
			else
			{
				ObjCp->SetDeletePoint(DeletePoint,DeleteNumColor2[y],r);
			}
		}	
	}
}

//ブロックが止まる位置のなかれ一番小さい位置を探し、複数あればその中からランダムで１つ決める関数
int CObjMain::InSideCheck()
{
	int i = 0;		//ループ用（乱用）
	int npc;	//ランダム用
	int count=0;//上から何番目の最小値かカウントする
	
	int BlockStopPointCopy[7];//比較用にコピーして保存用

	//ランダム情報を初期化
	srand(time(NULL)); 

	//コピーをつくる
	for( i=0;i<7;i++)
	{
		BlockStopPointCopy[i] = m_BlockStopPoint[i];
	}

	//値記憶用
	int num;
	
	//コピーをソートする
	for( i=0;i<6;i++)
	{
		for(int j=i+1;j<7;j++)
		{
			//もし値が大きければ入れ替える
			if(BlockStopPointCopy[i] >BlockStopPointCopy[j])
			{
				num =BlockStopPointCopy[i];
				BlockStopPointCopy[i] = BlockStopPointCopy[j];
				BlockStopPointCopy[j] = num;
			}
		}
	}

	//最小値を保存
	num=BlockStopPointCopy[0];

	for( i=1 ;i < 7 ; i++)
	{
		//最小値いがいなら
		if( BlockStopPointCopy[i] != num)
		{
			break;
		}
	}

	//0-numで一つ値を絞る
	npc = rand() % i;

	for(i=0;i<7;i++)
	{
		if(m_BlockStopPoint[i]==num)
		{
			//countと乱数が一致すれば
			if(count==npc)
				return i;

			//カウントを増やす
			count++;
		}
	}
	return 0;
}

//勝利判定時のゲームオーバー作成などの処理をする関数
//引数1: ２p戦かｃｐ戦か判別するためのフラグ
void CObjMain::VictoryProcess(bool vs_CP)
{
	//ヒーローオブジェクトの呼び出し
	CObjHero * obj_h =(CObjHero*)Objs ::GetObj(OBJ_HERO);		
	CObjHero_R * obj_hr =(CObjHero_R*)Objs ::GetObj(OBJ_HERO_R);
	
	// 両方が敗北条件を満たしているなら引き分け
	if(m_bLeftWin==true && m_bRightWin==true )
	{ 
		if(vs_CP==false)
		{
			//ゲームオーバーオブジェクト作成
			CObjGameOver* obj_win_lose = new CObjGameOver(0);
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);

			//機体を行動不能にする
			obj_h->EndFlagON();
			obj_hr->EndFlagON();
		}
		if(vs_CP==true)
		{
			CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);//CPオブジェクトの呼び出し
	
			//ゲームオーバーオブジェクト作成
			CObjGameOver* obj_win_lose = new CObjGameOver(0);
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);

			//機体を行動不能にする
			obj_h->EndFlagON();
			obj_cp->EndFlagON();
		}
		m_bGameOver = true;
	}
	//右だけ敗北条件を満たしているなら左の勝ち(1P)
	else if(m_bRightWin==true)
	{
		//２p戦なら
		if(vs_CP==false)
		{
			//ゲームオーバーオブジェクト作成
			CObjGameOver* obj_win_lose = new CObjGameOver(1);
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);
			
			//機体を行動不能にする
			obj_h->EndFlagON();
			obj_hr->EndFlagON();
		}
		if(vs_CP==true)//CP戦
		{
			//CPオブジェクトの呼び出し
			CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);
	
			//ゲームオーバーオブジェクト作成
			CObjGameOver* obj_win_lose = new CObjGameOver(1);
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);
	
			//機体を行動不能にする
			obj_h->EndFlagON();
			obj_cp->EndFlagON();
		}
		m_bGameOver = true;
	}
	//左だけ敗北条件を満たしているなら右の勝ち
	else if(m_bLeftWin==true)
	{
		//2P戦
		if(vs_CP==false)
		{
			//ゲームオーバーオブジェクト作成
			CObjGameOver* obj_win_lose = new CObjGameOver(2);
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);

			//機体を行動不能にする
			obj_h->EndFlagON();
			obj_hr->EndFlagON();
		}
		//CP戦
		if(vs_CP==true)
		{
			//CPオブジェクトの呼び出し
			CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);
	
			//ゲームオーバーオブジェクト作成
			CObjGameOver* obj_win_lose = new CObjGameOver(2);
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);
			
			//機体を行動不能にする
			obj_h->EndFlagON();
			obj_cp->EndFlagON();
		}
		m_bGameOver = true;
	}
}