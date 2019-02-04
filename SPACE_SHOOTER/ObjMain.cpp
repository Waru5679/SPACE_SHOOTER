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
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<20;j++)
		{
			//MAP構造体の初期化
			m_map[i][j].num=99;
			m_map[i][j].obj_check=false;
			m_map[i][j].obj_time=0;
			m_map[i][j].stop_flag=false;
			m_map[i][j].process_check=true;
			m_map[i][j].before_num=99;
			m_map[i][j].stop_time=0;
		}
	}

	//勝利判定フラグ初期化
	m_vc_r=false;
	m_vc_l-false;

	//スタートカウントダウン
	m_count_time=0;

	//文字が大きくなる時間
	font_big_time=0.0f;

	//ランキング用タイムの初期化
	m_time = 0;

	//ゲームオーバー管理
	flag = false;

	//AI用
	for(int i=0;i<7;i++)
	{
		BlockStopPoint[i]=19;//ブロックの止まる位置
	}
}

//アクション
void CObjMain::Action()
{
	//勝負が終わっていればなにもしない
	if (flag == true) return;

	m_count_time++;

	if (m_count_time > 270)//スタートの表示が終わっていれば
	{
		if ((m_count_time - 270) % 60 == 0)	//60f毎(1秒ごと)に
			m_time++;				//ランキング用のタイムの更新
	}

	//ヒーローオブジェクトの呼び出し
	CObjHero * obj_h =(CObjHero*)Objs ::GetObj(OBJ_HERO);		//左
	CObjHero_R * obj_hr =(CObjHero_R*)Objs ::GetObj(OBJ_HERO_R);//右
	
	//-----------------------------------------
	//テーブルヒット連鎖チェック
	// ７行２０列
	//-----------------------------------------
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<20;j++)
		{
			//前回の処理時と同じ数値が入っていれば
			if(m_map[i][j].num == m_map[i][j].before_num)
				m_map[i][j].stop_time++;//ストップタイムを増やす
			else
				m_map[i][j].stop_time=0;//ストップタイムを０に戻す
			
			//色ブロックが入っていれば
			if( m_map[i][j].num < 6)
			{
				//オブジェクト生成フラグがオンなら
				if(m_map[i][j].obj_check==true)
				{
					//特殊なケース　右端 横向きのとき
					if(j==18 && ( m_map[i][19].num < 6) )//18番目で19番目にもブロックが入っている場合（右側で横向きにうったとき
					{
						CObjBlock* obj_b=new CObjBlock(j,i,m_map[i][j].num,false,true);
						Objs::InsertObj(obj_b,OBJ_BLOCK,10);
						m_map[i][j].obj_check=false;//オブジェクト生成フラグをオフにする
						m_map[i][j].stop_flag=false;//ブロック生成位置のストップフラグをオフにする
						m_map[i][j].obj_time=0;//オブジェクト生成タイムをリセットする
					}
					else//普通のケース
					{
						if(j<=9) //左側用のブロック生成
						{
							CObjBlock* obj_b=new CObjBlock(j,i,m_map[i][j].num,
										true,false);
							Objs::InsertObj(obj_b,OBJ_BLOCK,10);
						
						}
						else if(j>=10) //右側用のブロック生成　//2017-05-26 発見 > -> >=
						{
							CObjBlock* obj_b=new CObjBlock(j,i,m_map[i][j].num,
										false,false);
							Objs::InsertObj(obj_b,OBJ_BLOCK,10);					
						}
						m_map[i][j].obj_check=false;//オブジェクト生成フラグをオフにする
						m_map[i][j].stop_flag=false;//ブロック生成位置のストップフラグをオフにする
						m_map[i][j].obj_time=0;//オブジェクト生成タイムをリセットする
					}
				}//生成フラッグオン　ENDif	
			}
			//---------------------------------
			//お邪魔ブロック　6
			//---------------------------------
			if(m_map[i][j].num==6)
			{
				//オブジェクト生成フラグがオンなら
				if(m_map[i][j].obj_check==true)
				{
					if(j<10)
					{
						CObjIntervention* obj_i=new CObjIntervention(j,i,true);
						Objs::InsertObj(obj_i,OBJ_INTERVENTION,10);
						m_map[i][j].obj_check=false;//オブジェクト生成フラグをオフにする
						m_map[i][j].stop_flag=false;//ブロック生成位置のストップフラグをオフにする
						m_map[i][j].obj_time=0;//オブジェクト生成タイムをリセットする
					}
					else if(j>9)
					{
						CObjIntervention* obj_i=new CObjIntervention(j,i,false);
						Objs::InsertObj(obj_i,OBJ_INTERVENTION,10);
						m_map[i][j].obj_check=false;//オブジェクト生成フラグをオフにする
						m_map[i][j].stop_flag=false;//ブロック生成位置のストップフラグをオフにする
						m_map[i][j].obj_time=0;//オブジェクト生成タイムをリセットする
					}
				}	
			}

			//--------------------------------------------------------
			//消滅アニメーション　98
			//----------------------------------------------
			if(m_map[i][j].num == 98)
			{
				if(m_map[i][j].stop_time >= 5)//もし、消滅処理の判定がアニメーションの時間より長くとどまっていたら
					m_map[i][j].num==99;//空白にもどす
			}

			//-----------------------------------------------
			//空白 99
			//--------------------------------------
			if(m_map[i][j].num == 99)
			{
				m_map[i][j].process_check=true;//処理済フラグをオンにする
			}

			//番号を保存する
			m_map[i][j].before_num=m_map[i][j].num;
			
			m_map[i][j].obj_time++;//オブジェクト生成からのタイム保存
			if( m_map[i][j].obj_time > 10000)//もし10000を超えるなら
				m_map[i][j].obj_time = 10;//10に戻す 
		}
	}

	//勝敗判定
	m_vc_l=VictoryCheck(true);//左
	m_vc_r=VictoryCheck(false);//右
	
	if(flag == false)
	{
		VictoryProcess(vs_CP);//勝利判定をみたしているか調べ、満たしていれば処理をする
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
	if(m_count_time>=270)
	{
		//スコア表示
		swprintf_s(str, L"%02d:%02d",m_time/60, m_time % 60);
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
				else if(m_map[y][x].num==99)
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
	if(m_count_time<=70)
	{
		if(m_count_time==5)
			Audio::Start(9);//効果音

		font_big_time++;

		//font_big_timeが増えるにつれて表示される数字が大きくなる
		//描画位置の設定
		RectSet(200-font_big_time,420-font_big_time,570+font_big_time,400+font_big_time,dst);
		
		Draw::Draw(11,&src,&dst,c,0.0f);//描画
		
	}

	//2
	if(m_count_time>70&&m_count_time<=140)
	{
		if(m_count_time==75)
			Audio::Start(9);//効果音

		font_big_time++;

		RectSet(200-font_big_time,420-font_big_time,570+font_big_time,400+font_big_time,dst);

		Draw::Draw(12,&src,&dst,c,0.0f);//描画
	}

	//1
	if(m_count_time>140&&m_count_time<=210)
	{
		if(m_count_time==145)
			Audio::Start(9);//効果音

		font_big_time++;

		RectSet(200-font_big_time,420-font_big_time,570+font_big_time,400+font_big_time,dst);

		Draw::Draw(13,&src,&dst,c,0.0f);//描画

	}

	//START
	if(m_count_time>210&&m_count_time<=260)
	{
		if(m_count_time==215)
			Audio::Start(10);//効果音

		RectSet(100.0f,300.0f,700.0f,400.0f,dst);

		Draw::Draw(14,&src,&dst,start,0.0f);//描画
	}

	//カウントが70きたときに元のサイズに戻す
	if(font_big_time==70)
		font_big_time=0;
}

//つながっているブロックの数を数えてけせるなら消滅処理をする関数
//引数1 :要素番号X
//引数2 :要素番号Y
//引数3 :左右チェック（どちら側から来てるブロックか）
void CObjMain::CheckMap(int x, int y,bool lr)
{
	int pos[2];
	int number=0;//つながっているブロックの数カウント
	int ojm_count=0;//お邪魔ブロックの数カウント
	int color=m_map[y][x].num;//検索対象の色を保存

	pos[0]=x;
	pos[1]=x;

	if(lr==true) //左側のPlayerが放ったBlock（Bullet）かつ停止状態	
		//ここのはさみチェックが問題
		//右端のBlockから始まって、さらに右側のブロックをチェックにいっている

	{
		// x+1 ---> x 大変更　2017-05-26
		for(int i=x; i<20; i++) //配列終わりまで探索
		{ 
			if(m_map[y][i].num==color) //色検出
			{
				pos[1]=i;//場所を記録
				
			}

			if(m_map[y][i].num==99)//探索中に空白にがあったらそこで探索終了
				break;
		}
			
	}
	else //右側のPlayerが放ったBlock（Bullet）かつ停止状態
	{
		// x-1 ---> x 大変更　2017-06-05
		for(int i=x; i>0; i--) //配列終わりまで探索
		{ 
			if(m_map[y][i].num==color) //色検出
			{
				pos[1]=i;//場所を記録

			}

			if(m_map[y][i].num==99)//探索中に空白にがあったらそこで探索終了
				break;
		}
	}

	number=abs(pos[1]-pos[0])+1;//つながっている数(お邪魔と両サイド込み)を求める

	if(lr==true)//左側プレーヤー
	{
		//左
		// x+1 ---> x 大変更　2017-06-05
		for(int i=x; i<pos[1]; i++)//消す範囲内にお邪魔が何個あるかカウントする
		{
			if(m_map[y][i].num==6)//もし、お邪魔ブロックなら
				ojm_count++;
		}
	}
	else 
	{
		//右
		// x-1 ---> x 大変更　2017-06-05
		for(int i=x; i>pos[1]; i--)//消す範囲内にお邪魔が何個あるかカウントする
		{
			if(m_map[y][i].num==6)//もし、お邪魔ブロックなら
				ojm_count++;
		}
	}
	
	//--------------------------------------------
	// 連鎖チェイン　消しこみ処理
	// ４つ以上
	//--------------------------------------------
	int nBlockNum = number - ojm_count;//色ブロックのみの数(つながっている数 - お邪魔の数　)
	
	if(nBlockNum >= 4)//色ブロックのみの数が4以上なら
	{
		//左
		for(int i=0 ; i<number;i++)
		{
			if(lr==true)//左側Player
				m_map[y][x+i].num=98;//マップに爆発処理用の数字(98)をいれる
			else
				m_map[y][x-i].num=98;//マップに爆発処理用の数字(98)をいれる
		}
	}

	if(nBlockNum>=5)//お邪魔を除いて消した数が5以上なら
	{
		//オブジェクトの呼び出し
		CObjHero * obj_h =(CObjHero*)Objs ::GetObj(OBJ_HERO);		//左

		//テスト-----------------------------
		//
		if(lr==true)
		{
			//左から来たブロック
			if(vs_CP == true)//CP戦なら
			{
				CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);//CP
				obj_cp->SetOjmNum(nBlockNum-4);//生成するお邪魔の数を保存
			}
			
			if(vs_CP == false)//2P戦なら
			{
				CObjHero_R * obj_hr =(CObjHero_R*)Objs ::GetObj(OBJ_HERO_R);//右
				obj_hr->SetOjmNum(nBlockNum-4);//生成するお邪魔の数を保存
			}
		}
		else
		{
			//右から来たブロック
			obj_h->SetOjmNum(nBlockNum-4);//生成するお邪魔の数を保存
		}	
		//------------------------------------------
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
		
	for(int i = 0; i < number ; i++)//生成するお邪魔の数だけまわす
	{
		do
		{
			if(i==7)//7番目のお邪魔なら// Ivが15がMax
			{
				Dec=0x0000000;//決定を初期化し
				j++;//生成位置を一つ内側にずらす
			}

			y = rand() % 7;//ランダムで位置を決める
			Sch = 1 << y;

		}while((Dec & Sch ) != 0x0000000);//生成予定地が決定済位置とかぶっていなければ抜ける
			
		Dec += (1 << y);//決定した位置には１を入れる

		if(lr==true)
		{
			//左側に降らす時
			Enter(0+j,y,6);//マップに入れる
			FlagOn(0+j,y);//オブジェクト生成フラグをオンにする				
		}
		else
		{
			//右側に降らす時
			Enter(19-j,y,6);//マップに入れる
			FlagOn(19-j,y);//オブジェクト生成フラグをオンにする
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
		if( StopCheck(i,lr)==false )//結果がfalseなら
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
	

	if(lr==true)
	{
		//左
		for(int i=0;i<=9;i++)
		{
			//その位置に色ブロックまたはお邪魔ブロックが入っていれば
			if( ( 0<=m_map[y][i].num) && (m_map[y][i].num <= 6 ) )  
			{
				//ストップフラグがオフなら
				if(m_map[y][i].stop_flag==false)	
				{	
					//そのブロックが動いている状態
					return false;
				}
			}
		}
	}
	else
	{
		//右
		for(int i=10;i<=19;i++)
		{
			//その位置に色ブロックまたはお邪魔ブロックが入っていれば
			if( ( 0<=m_map[y][i].num) && (m_map[y][i].num <= 6 ) )  
			{
				//ストップフラグがオフなら
				if(m_map[y][i].stop_flag==false)	
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
	int j;
	for(int i=0;i<7;i++)
	{
		if(lr==true)
			j=0;
		else
			j=19;

		//色ブロックかお邪魔ブロックが入っているなら
		if( 0<=m_map[i][j].num && m_map[i][j].num<=6)
		{
			//そこに50フレーム以上とどまっているなら
			if(m_map[i][j].stop_time >= 50)
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
		if(lr==true)//左右チェック
		{
			//左
			if(m_map[y][i].num == n)
				count++;
		}
		else
		{
			if(m_map[y][i+10].num == n)
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
	int pos[2];
	int number=0;//つながっているブロックの数カウント
	int ojm_count=0;//お邪魔ブロックの数カウント
	int color=m_map[y][x].num;//検索対象の色を保存

	pos[0]=x;
	pos[1]=x;

	if(lr==true) //左側のPlayerが放ったBlock（Bullet）かつ停止状態	
		//ここのはさみチェックが問題
		//右端のBlockから始まって、さらに右側のブロックをチェックにいっている

	{
		// x+1 ---> x 大変更　2017-05-26
		for(int i=x; i<20; i++) //配列終わりまで探索
		{ 
			if(m_map[y][i].num==color) //色検出
			{
				pos[1]=i;//場所を記録
				
			}

			if(m_map[y][i].num==99)//探索中に空白にがあったらそこで探索終了
				break;
		}
			
	}
	else //右側のPlayerが放ったBlock（Bullet）かつ停止状態
		
	{
		// x-1 ---> x 大変更　2017-06-05
		for(int i=x; i>0; i--) //配列終わりまで探索
		{ 
			if(m_map[y][i].num==color) //色検出
			{
				pos[1]=i;//場所を記録
			}

			if(m_map[y][i].num==99)//探索中に空白にがあったらそこで探索終了
				break;
		}
	}


	number = abs(pos[1]-pos[0])+1;//つながっている数(お邪魔と両サイド込み)を求める

	if(lr==true)//左側プレーヤー
	{
		//左
		// x+1 ---> x 大変更　2017-06-05
		for(int i=x; i<pos[1]; i++)//消す範囲内にお邪魔が何個あるかカウントする
		{
			if(m_map[y][i].num==6)//もし、お邪魔ブロックなら
				ojm_count++;
		}
	}
	else 
	{
		//右
		// x-1 ---> x 大変更　2017-06-05
		for(int i=x; i>pos[1]; i--)//消す範囲内にお邪魔が何個あるかカウントする
		{
			if(m_map[y][i].num==6)//もし、お邪魔ブロックなら
				ojm_count++;
		}
	}

	//--------------------------------------------
	// 連鎖チェイン　消しこみ処理
	// ４つ以上
	//--------------------------------------------
	if(number-ojm_count>=4)//つながっている数-お邪魔の数が4以上なら
	{		
		return number-ojm_count;
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
		for(BlockStopPoint[i]=19;BlockStopPoint[i]>=10;BlockStopPoint[i]--)
		{
			//空白なら
			if(m_map[i][ BlockStopPoint[i] ].num == 99)
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
		BlockStopPoint[i]++;//BlockStopPointの値を一つ増やす
	}
}

//AI用ブロックが消せる位置を探す関数(ブロック縦バージョン)
//引数１：色１(上側想定)
//引数２：色２(下側想定)
//引数３：回転の情報
void CObjMain::AiDeleteCheck_H(int color1,int color2,int r)
{
	//CPオブジェクトの呼び出し
	CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);
	
	int point_color1 = -1;//色１と同じ色の位置を保存する
	int point_color2 = -1;//色２と同じ色の位置を保存する
	int delete_num = -1;//最終的な消せる数を保存する
	int delete_num_color1[7];//それぞれの段で色１の消せる数
	int delete_num_color2[7];//それぞれの段で色２の消せる数
	int ojm_count[7];//お邪魔ブロックのカウント

	for(int i=0;i<7;i++)
	{
		//初期化
		delete_num_color1[i]=-1;
		delete_num_color2[i]=-1;
		ojm_count[i]=0;
	}

	Point delete_point;//消せる位置の保存用
	delete_point.x=-1;
	delete_point.y=-1;
	
	//ブロックの止まるであろう位置を探す
	StopPointCheck();
	
	//上から一段ずつ色1,2で消せるかずを調べていく---------------
	for(int y=0;y<7;y++)
	{
		//初期値に戻す
		point_color1 = -1;
		point_color2 = -1;

		//ブロックが止まる位置の一つ左から順に見ていく
		for(int i=BlockStopPoint[y]-1;i>0;i--)
		{
			//空白なら
			if( m_map[y][i].num == 99 )
			{
				break;//それ以上見る必要がないのでループを抜ける
			}

			//色１と同じ色なら
			if( m_map[y][i].num == color1)
			{
				point_color1=i;//その位置を保存する
			}

			//色２と同じ色なら
			if( m_map[y][i].num == color2)
			{
				point_color2=i;//その位置を保存する
			}

			//お邪魔ブロックなら
			if(m_map[y][i].num==6)
			{
				ojm_count[y]++;//カウントを増やす
			}
		}

		if(point_color1 != -1)//その段で色１が見つかっていれば
		{
			delete_num_color1[y] = abs( BlockStopPoint[y] - point_color1) + 1 - 4 - ojm_count[y];//消せる数を更新する
			
			//if(delete_num_color1[y] < 0)
			//	delete_num_color1[y]=0;//0以下にならないようにする
		}

		if(point_color2 != -1)//その段で色2が見つかっていれば
		{
			delete_num_color2[y] = abs( BlockStopPoint[y] - point_color2) + 1 - 4 - ojm_count[y];//消せる数を更新する
				
			//if(delete_num_color2[y] < 0)
			//	delete_num_color2[y]=0;//0以下にならないようにする
		}
	}
	//それぞれの段での消せる数を調べるの終わり-------------------------------------------------

	//それぞれの詳細情報を求めて送る----------------------------------------

	for(int y=0;y<7;y++)
	{
		if(delete_num_color1[y] >= 0)//色1の消せる数が0以上なら
		{
			if(y < 6)//一番したの段で色２が消せることはないので省く
			{
				if(delete_num_color2[y+1] >= 0)//一つ下の段ので色2が消えるなら
				{
					//色１が消せて色２が消える

					//その段で色１が消せる数＋その1つ下で色２が消せる数の合計を保存
					delete_num = delete_num_color1[y]+delete_num_color2[y+1];
				}
				else
				{
					//色１だけが消せる場合
					
					//その段で色１が消せる数を保存
					delete_num = delete_num_color1[y];
				}
				
				//消せるポイントを保存する
				delete_point.x=BlockStopPoint[y];
				delete_point.y=y;

				obj_cp->SetDeletePoint(delete_point,delete_num,r);//消せるポイント、数、回転情報を送る
			}
		}
		
		if( delete_num_color2[y] >= 0)//色2の消せる数が0以上なら
		{
			//色１は消せなくて色2は消せる場合

			if(y >= 1)//一番上の段で色2が消せることはないので省く
			{
				//消せるポイントを保存する
				delete_point.x=BlockStopPoint[y-1];
				delete_point.y=y-1;

				//1つ上の段で色１が消えるか
				if(delete_num_color2[y-1] >=0 )	//色１も消えて色２も消える場合
				{
				
					//色1で消える数＋色2で消える数
					delete_num = delete_num_color2[y]+ delete_num_color1[y];
				}
				else//色１は消えなくて色２だけ消える場合
				{
					//その段で色2が消せる数
					delete_num = delete_num_color2[y];
				}				

				obj_cp->SetDeletePoint(delete_point,delete_num,r);//消せるポイント、数、回転情報を送る
			}
		}
	}

	//消せるときの詳細求めて送るの終わり---------------------------------------------------------
}

//AI用ブロックが消せる位置を探す関数(ブロック横バージョン)
//引数１：色１(左側想定)
//引数２：色２(右側想定)
//引数３：回転の情報
void CObjMain::AiDeleteCheck_W(int color1,int color2,int r)
{
	//CPオブジェクトの呼び出し
	CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);
	
	int point_color1 = -1;//色１と同じ色の位置を保存する
	int point_color2 = -1;//色２と同じ色の位置を保存する
	int delete_num_color1[7];//それぞれの段で色１の消せる数
	int delete_num_color2[7];//それぞれの段で色２の消せる数
	int ojm_count[7];//お邪魔ブロックのカウント

	for(int i=0;i<7;i++)
	{
		//初期化
		delete_num_color1[i]=-1;
		delete_num_color2[i]=-1;
		ojm_count[i]=0;
	}

	Point delete_point;//消せる位置の保存用
	delete_point.x=-1;
	delete_point.y=-1;
	
	//ブロックの止まるであろう位置を探す
	StopPointCheck();
	
	//上から一段ずつ色1,2で消せるかずを調べていく---------------
	for(int y=0;y<7;y++)
	{
		//初期値に戻す
		point_color1 = -1;
		point_color2 = -1;

		//ブロックが止まる位置の一つ左から順に見ていく
		for(int i=BlockStopPoint[y]-1;i>0;i--)
		{
			//空白なら
			if( m_map[y][i].num == 99 )
			{
				break;//それ以上見る必要がないのでループを抜ける
			}

			//色１と同じ色なら
			if( m_map[y][i].num == color1)
			{
				point_color1=i;//その位置を保存する
			}

			//色２と同じ色なら
			if( m_map[y][i].num == color2)
			{
				point_color2=i;//その位置を保存する
			}

			//お邪魔ブロックなら
			if(m_map[y][i].num==6)
			{
				ojm_count[y]++;//カウントを増やす
			}

			if(point_color1 != -1)//その段で色１が見つかっていれば
			{
				delete_num_color1[y] = abs( BlockStopPoint[y] - point_color1) + 1 - 4 - ojm_count[y];//消せる数を更新する
			
				//if(delete_num_color1[y] < 0)
				//	delete_num_color1[y]=0;//0以下にならないようにする
			}

			if(point_color2 != -1)//その段で色2が見つかっていれば
			{
				delete_num_color2[y] = abs( BlockStopPoint[y]+1 - point_color2) + 1 - 4 - ojm_count[y];//消せる数を更新する
				
				//if(delete_num_color2[y] < 0)
				//	delete_num_color2[y]=0;//0以下にならないようにする
			}
		}
	}
	//それぞれの段での消せる数を調べるの終わり-------------------------------------------------

	//それぞれの詳細情報を求めて送る----------------------------------------
	
		//横向きの場合は色1と2のによって位置の変化は無いので消せる数だけ調べればいい
		for(int y=0;y<7;y++)
		{
			if( delete_num_color1[y] >= 0 || delete_num_color2[y] >= 0)//色1か色2の消せる数が0よりおおきければ
			{
				//消せるポイントを保存する
				delete_point.x=BlockStopPoint[y];
				delete_point.y=y;

				//色１と２で消せる数の大きい方を調べて送る
				if(delete_num_color1[y] >=delete_num_color2[y])	//色1の方が多く消せる場合
				{
					
					obj_cp->SetDeletePoint(delete_point,delete_num_color1[y],r);	//情報を送る
				
				}
				else	//色2の方が多く消せる場合
				{
					obj_cp->SetDeletePoint(delete_point,delete_num_color2[y],r);	//情報を送る
				}
			}	
		}
	//詳細求めて送るのおわり------------------------------------------------
}

//ブロックが止まる位置のなかれ一番小さい位置を探し、複数あればその中からランダムで１つ決める関数
int CObjMain::InSideCheck()
{
	int i;//ループ用（乱用）
	int BlockStopPoint_copy[7];//比較用にコピーして保存用
	int npc;//ランダム用
	int count=0;//上から何番目の最小値かカウントする
	
	srand(time(NULL)); // ランダム情報を初期化

	//コピーをつくる
	for( i=0;i<7;i++)
	{
		BlockStopPoint_copy[i] = BlockStopPoint[i];
	}

	int n;//値記憶用
	
	//コピーをソートする
	for( i=0;i<6;i++)
	{
		for(int j=i+1;j<7;j++)
		{
			//もし値が大きければ入れ替える
			if(BlockStopPoint_copy[i] >BlockStopPoint_copy[j])
			{
				n =BlockStopPoint_copy[i];
				BlockStopPoint_copy[i] = BlockStopPoint_copy[j];
				BlockStopPoint_copy[j] = n;
			}
		}
	}

	n=BlockStopPoint_copy[0];//最小値を保存

	for( i=1 ;i < 7 ; i++)
	{
		if( BlockStopPoint_copy[i] != n)//最小値いがいなら
		{
			break;
		}
	}

	npc = rand() % i;//0~nで一つ値を絞る

	for(i=0;i<7;i++)
	{
		if(BlockStopPoint[i]==n)
		{
			if(count==npc)//countと乱数が一致すれば
				return i;

			count++;//カウントを増やす
		}
	}
}

//勝利判定時のゲームオーバー作成などの処理をする関数
//引数1: ２p戦かｃｐ戦か判別するためのフラグ
void CObjMain::VictoryProcess(bool vs_CP)
{
	//ヒーローオブジェクトの呼び出し
	CObjHero * obj_h =(CObjHero*)Objs ::GetObj(OBJ_HERO);		//左
	CObjHero_R * obj_hr =(CObjHero_R*)Objs ::GetObj(OBJ_HERO_R);//右
	
	if(m_vc_l==true && m_vc_r==true )//両方が敗北条件を満たしているなら
	{
		//引き分け
			
		if(vs_CP==false)
		{
			//ゲームオーバーオブジェクト作成
			CObjGameOver* obj_win_lose = new CObjGameOver(0);//タイトルオブジェクト作成
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);//タイトルオブジェクト作成

			//機体を行動不能にする------
			obj_h->EndFlag_ON();
			obj_hr->EndFlag_ON();
			//------------------------------
		}
		if(vs_CP==true)
		{
			CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);//CPオブジェクトの呼び出し
	
			//ゲームオーバーオブジェクト作成
			CObjGameOver* obj_win_lose = new CObjGameOver(0);//タイトルオブジェクト作成
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);//タイトルオブジェクト作成

			//機体を行動不能にする------
			obj_h->EndFlag_ON();
			obj_cp->EndFlag_ON();
			//------------------------------
		}
		flag = true;
	}
	else if(m_vc_r==true)//右だけ敗北条件を満たしているなら
	{
		if(vs_CP==false)//２p戦なら
		{
			//左の勝ち(1P)
			CObjGameOver* obj_win_lose = new CObjGameOver(1);//タイトルオブジェクト作成
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);//タイトルオブジェクト作成
			//機体を行動不能にする------
			obj_h->EndFlag_ON();
			obj_hr->EndFlag_ON();
			//------------------------------
		}
		if(vs_CP==true)//CP戦なら
		{
			CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);//CPオブジェクトの呼び出し
	
			CObjGameOver* obj_win_lose = new CObjGameOver(1);//タイトルオブジェクト作成
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);//タイトルオブジェクト作成
			//機体を行動不能にする------
			obj_h->EndFlag_ON();
			obj_cp->EndFlag_ON();
			//------------------------------
		}
		flag = true;
	}
	else if(m_vc_l==true)//左だけ敗北条件を満たしているなら
	{
		if(vs_CP==false)//2P戦なら
		{
			//右の勝ち(2P)
			CObjGameOver* obj_win_lose = new CObjGameOver(2);//ゲームオーバーオブジェクト作成
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);//ゲームオーバーオブジェクト作成
			//機体を行動不能にする------
			obj_h->EndFlag_ON();
			obj_hr->EndFlag_ON();
			//------------------------------
		}
		if(vs_CP==true)//CP戦なら
		{
			CObjCP * obj_cp =(CObjCP*)Objs ::GetObj(OBJ_CP);//CPオブジェクトの呼び出し
	
			CObjGameOver* obj_win_lose = new CObjGameOver(2);//ゲームオーバーオブジェクト作成
			Objs::InsertObj(obj_win_lose,OBJ_GAME_OVER,10);//ゲームオーバーオブジェクト作成
			//機体を行動不能にする------
			obj_h->EndFlag_ON();
			obj_cp->EndFlag_ON();
			//------------------------------
		}

			flag = true;
	}
}