/*ーーーーーーーーーーーーーーーーーーーーーーーーーーー*/
/*　　　　　　　　　                  　　　　　　　　　*/
/*　　　　　　　　　                  　　　　　　　　　*/
/*　　　　　　　　　ver2開発用エディタ　　　　　　　　　*/
/*　　　　　　　　　                  　　　　　　　　　*/
/*　　　　　　　　　                  　　　　　　　　　*/
/*ーーーーーーーーーーーーーーーーーーーーーーーーーーー*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<conio.h>

#include<locale.h>
#include<windows.h>
//#include<Mmsystem.h>

//#pragma comment (lib, "winmm.lib")
#include"Base.h"


#define ERR	 -1
#define SAFE  0

//キーコード設定
#define ENTER	0x0d
#define UP		0x48
#define RIGHT	0x4d
#define LEFT	0x4b
#define DOWN	0x50

//スコア設定
#define SINGLE (100)
#define DOUBLE (300)
#define TRIPLE (500)
#define TETRIS (800)

#define RANK_MAX 5

//フィールドの大きさ設定
#define FIELD_HEIGHT 23
#define FIELD_WIDTH	 16

//ブロックの大きさ設定
#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH	 4

/*ーーーーーーーーーーーーーーーーーーーーーーーーーーー*/
/*　　　　　　　　　メニュー関連の関数　　　　　　　　　*/
/*ーーーーーーーーーーーーーーーーーーーーーーーーーーー*/

char Command_Name[5][18] = {
		"   ス タ ー ト   ",
		"   操 作 説 明   ",
		" 難 易 度 変 更  ",
		" ゲ ー ム 終 了  " };

char Level_Name[3][18] = {
		"     E A Z Y     ",
		"   N O R M A L   ",
		"     H A R D     " };

void Title();		/*タイトル描写*/
void Menu();		/*メニュー選択*/
void Start();		/*ゲーム開始*/
void Operation();	/*操作確認*/
void LevelChange();	/*難易度設定*/
/*ーーーーーーーーーーーーーーーーーーーーーーーーーーー*/
/*　　　　　　 　　　 PLAY関連の関数 　　 　　　　　　　*/
/*ーーーーーーーーーーーーーーーーーーーーーーーーーーー*/

void Shokika();			//初期化関数
int Ransu(int Number);	//０～Number－１の乱数生成
void Key();				//キー入力の処理
void Locate();			//ブロックを回転させる
void Moving(int, int);	//ブロックを移動させる
void Drawing();			//壁・空白・ブロックの可視化
void SponBlock();		//ブロックのスポーン・初期座標付与
int SponCheck(int);		//引数が格納できるか確認する
int MinoCheck();		//mino_arrayに格納場所あるか確認

/*ーーーーーーーーーーーーーーーーーーーーーーーーーーー*/
/*　　　　　 　　　 ギミック関連の関数 　　 　　　　　　*/
/*ーーーーーーーーーーーーーーーーーーーーーーーーーーー*/

void TrapUp(int R, int col);	/* 下からブロック生えるギミック */

int TrapCheck();				/* TrapUp()できるかのチェック関数 */
								/* ERR or SAFEが戻される */

/*ーーーーーーーーーーーーーーーーーーーーーーーーーーー*/
/*　　　　　　　　BlockDown()関連の関数　　　　	　　　　*/
/*ーーーーーーーーーーーーーーーーーーーーーーーーーーー*/

void MovingDown();
void Score();		/*スコア計算*/
void GameOver();	/*GameOver表示*/
void Line();		/*消せるラインの確認・削除*/

void Fixing();		/*現在のブロック座標にブロックを固定する*/
					/*			Stageを初期化する			*/


void BulkLine();	/*再帰処理であるLine()を一括にまとめる関数*/
					/*				Cheinの維持				　*/


int EndCheck();		/*Sponできるかチェック				*/
					/*できない場合Gameover				*/
					/*戻り値　１＝エラー　０＝正常終了　*/

/*ーーーーーーーーーーーーーーーーーーーーーーーーーーー*/
/*　　　　　　　　　　確認関連の関数　　　　　　　　　　*/
/*ーーーーーーーーーーーーーーーーーーーーーーーーーーー*/

int Check(int, int);	/*移動先にブロック・壁がないかどうか*/
						/*戻り値　１＝エラー　０＝正常終了　*/

int LocateCheck();		/*回転時にブロック・壁がないかどうか*/
						/*戻り値　１＝エラー　０＝正常終了　*/

/*----------------------------------------------------------------------*/

/* グローバル変数 */
int timer = 0;		//次のブロック落下まで数える
int trapcnt_1 = 0;	//次のTrapUpまで数える
int TrapUp_R = 0;	//TrapUpで生える段数
int TrapUp_col = 0;	//TrapUpでのブロックの空き座標
int Trap_1_flag = 0;
char name[30] = { "\0" };
char kari[30] = { "\0" };
int score = 0;


//int prvRnd = 0;		//前回の乱数
int gamelevel = 40000;	//ブロック落下間隔
int nammido = 1;
int gameover = 0;

/* スコア変数 */
int chein = 0;		//チェインカウント
int lineCnt = 0;	//消せるラインカウント

/* ブロック座標	(stage) */
int x = 6;
int y = 1;

/* ブロック格納配列 */
int tentative[BLOCK_HEIGHT][BLOCK_WIDTH] = { 0 };
int Block[BLOCK_HEIGHT][BLOCK_WIDTH] = { 0 };
int NextBlock[BLOCK_HEIGHT][BLOCK_WIDTH] = { 100 };

/* フィールド用配列 */
int Stage[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };
int Field[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

/* ブロックの種類 */
int mino_youso = 0;
int mino_array[7] = { 100 };
int tetoromino[7][BLOCK_HEIGHT][BLOCK_WIDTH] = {
	/* I型 */
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,

	/* O型 */
	0,0,0,0,
	0,1,1,0,
	0,1,1,0,
	0,0,0,0,

	/* S型 */
	0,0,0,0,
	0,1,1,0,
	1,1,0,0,
	0,0,0,0,

	/* Z型 */
	0,0,0,0,
	1,1,0,0,
	0,1,1,0,
	0,0,0,0,

	/* J型 */
	0,0,1,0,
	0,0,1,0,
	0,1,1,0,
	0,0,0,0,

	/* L型 */
	0,1,0,0,
	0,1,0,0,
	0,1,1,0,
	0,0,0,0,

	/* T型 */
	0,0,0,0,
	0,1,0,0,
	1,1,1,0,
	0,0,0,0, };
/*----------------------------------------------------------------------*/
int main() {

	system("cls");
	locate(30, 19);
	printf_s("┏━━━━━━━━━━━━━━━━━━┓");
	locate(30, 20);
	printf_s("┃ ※推奨：反画面　　　　　　　　　　 ┃");
	locate(30, 21);
	printf_s("┃ ※一部BGMが流れます。 　　　　　　 ┃");
	locate(30, 22);
	printf_s("┃ ゲームをするときは部屋を明るくして ┃");
	locate(30, 23);
	printf_s("┃ 近づきすぎないようにしましょう。   ┃");
	locate(30, 24);
	printf_s("┗━━━━━━━━━━━━━━━━━━┛");
	locate(54, 25);
	printf_s("Enter を押す...");
	_getch();
	system("cls");

	Menu();

	return 0;
}
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void Title() {
	locate(8, 6);
	printf_s("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	locate(8, 7);
	printf_s("■                                                                        ■\n");
	locate(8, 8);
	printf_s("■ ■■■■■■ ■■■■■ ■■■■■■ ■■■■■　   ■■    ■■■■   ■\n");
	locate(8, 9);
	printf_s("■     ■■      ■■          ■■　　  ■■　　■■  ■■  ■■ 　 ■■ ■\n");
	locate(8, 10);
	printf_s("■     ■■  　  ■■    　    ■■　　  ■■　　■■        ■■ 　      ■\n");
	locate(8, 11);
	printf_s("■     ■■ 　   ■■■■      ■■ 　   ■■■■■　  ■■    ■■■■   ■\n");
	locate(8, 12);
	printf_s("■     ■■      ■■    　    ■■      ■■ ■■　 　■■　        ■■ ■\n");
	locate(8, 13);
	printf_s("■     ■■      ■■          ■■      ■■　■■　　■■　■■　  ■■ ■\n");
	locate(8, 14);
	printf_s("■    ■■■    ■■■■■    ■■■    ■■■   ■■  ■■    ■■■■   ■\n");
	locate(8, 15);
	printf_s("■  　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　          ■\n");
	locate(8, 16);
	printf_s("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
}

void Menu() {

	int i;
	int keycode;
	int command = 0;
	int end = 0;

	while (end == 0) {

		Title();

		locate(30, 19);
		printf_s("□□□□□□□□□□□□□□□□\n");

		for (i = 0; i < 4; i++) {

			locate(30, 19 + ((i + 1) * 2) - 1);
			printf_s("□　　　　　　　　　　　　　　□\n");

			locate(30, 19 + (i + 1) * 2);
			printf_s("□  %s　%s　  %s □\n"
				, (command == i) ? ">" : "　"
				, Command_Name[i]
				, (command == i) ? " " : "");
		}

		locate(30, 28);
		printf_s("□　　　　　　　　　　　　　　□\n");
		locate(30, 29);
		printf_s("□□□□□□□□□□□□□□□□\n");
		keycode = _getch();

		//Enterが押された時
		if (keycode == ENTER) {
			switch (command) {
			case 0:		//STARTコマンド
				Start();
				break;
			case 1:		//OPERATIONコマンド
				Operation();
				break;
			case 2:		//RANKINGコマンド
				LevelChange();
				break;
			case 3:		//GAMEENDコマンド
				end = 1;
				break;
			}
		}
		//Enterが押されなかった時
		else {
			switch (keycode) {
			case UP:	//上キー
				if (command != 0) {
					command--;
				}
				else if (command == 0) {
					command = 3;
				}
				break;
			case DOWN:	//下キー
				if (command < 3) {
					command++;
				}
				else if (command == 3) {
					command = 0;
				}
				break;
			default:
				break;
			}
		}
	}
}

void Start() {

	int flag;
	int i, R;

	srand((unsigned)time(NULL));

	//名前の入力------------------
	while (kari[0] == '\0') {
		system("cls");
		locate(22, 20);
		printf_s("名前を入力してください...(10バイト以内)\n");
		locate(22, 22);
		printf_s("￣￣￣￣￣￣￣￣\n");
		locate(22, 21);
		printf_s("→");
		locate(24, 21);
		scanf_s(" %s", &kari, 30);

		if (strlen(kari) < 11) {
			locate(22, 24);
			printf_s("『%s』でよろしいですか？\n", kari);
			locate(22, 26);
			printf_s("YESなら『1』NOなら『2』を押してください(半角)>>");
			scanf_s("%d", &flag);

			if (flag == 1) {
				for (i = 0; i < 11; i++) {
					name[i] = kari[i];
				}
				break;
			}
			else {
				for (i = 0; i < 30; i++) {
					kari[i] = '\0';
				}
			}
		}
		else {
			for (i = 0; i < 30; i++) {
				kari[i] = '\0';
			}
			locate(22, 24);
			printf_s("文字数オーバーしています...");
			Sleep(1000);
		}
	}

	//本処理
	system("cls");
	Shokika();
	SponBlock();

	//PlaySound((" "),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC);

	while (gameover == 0) {
		/* キー入力時の処理 */
		if (_kbhit()) {
			Key();
		}
		/* 一定時間後の落下処理 */
		if (timer <= gamelevel) {
			timer++;
		}
		else {
			MovingDown();
			timer = 0;
		}
		if (trapcnt_1 <= gamelevel * 20) {
			trapcnt_1++;
		}
		else {
			Trap_1_flag = 1;
		}
	}
}

void Operation() {

	system("cls");

	locate(7, 7);
	printf_s("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	locate(7, 8);
	printf_s("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	locate(7, 9);
	printf_s("■【操作方法】　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	locate(7, 10);
	printf_s("■　　　　　　　　　                                  　　　　　　　　　　　■\n");
	locate(7, 11);
	printf_s("■↑キー：ブロックを９０度回転させる　　　　　　　　　　　　　　　　　　　　■\n");
	locate(7, 12);
	printf_s("■　　　                                　　　　　　　　　　　　　　　　　　■\n");
	locate(7, 13);
	printf_s("■←キー：ブロックを左に移動させる　　　　　　　　　　　　　　　　　　　　　■\n");
	locate(7, 14);
	printf_s("■　　　　　　　　　　　　　　　　                                  　　　　■\n");
	locate(7, 15);
	printf_s("■↓キー：ブロックの落下速度を上げる　　　　　　　　　＋ー＋　　　　　　　　■\n");
	locate(7, 16);
	printf_s("■　　　　　　　　　                                　｜↑｜　　　　　　　　■\n");
	locate(7, 17);
	printf_s("■→キー：ブロックを右に移動させる　　　　　　　　＋ー＋ー＋ー＋　　　　　　■\n");
	locate(7, 18);
	printf_s("■                                 　　　　 　　　｜←｜↓｜→｜　　　　　　■\n");
	locate(7, 19);
	printf_s("■                                  　　　　　　　＋ー＋ー＋ー＋　　　　　　■\n");
	locate(7, 20);
	printf_s("■　　　　　　　　　　　　　　　　　　　　　                    　　　　　　■\n");
	locate(7, 21);
	printf_s("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

	_getch();
	system("cls");
}

void LevelChange() {

	int i;
	int keycode;
	int command = 0;
	int end = 0;

	system("cls");

	while (end == 0) {

		Title();

		locate(30, 19);
		printf_s("□□□□□□□□□□□□□□□□\n");

		for (i = 0; i < 3; i++) {

			locate(30, 19 + ((i + 1) * 2) - 1);
			printf_s("□　　　　　　　　　　　　　　□\n");

			locate(30, 19 + (i + 1) * 2);
			printf_s("□　%s　%s　%s　 □\n"
				, (command == i) ? ">" : "  "
				, Level_Name[i]
				, (command == i) ? " " : "");
		}

		locate(30, 26);
		printf_s("□　　　　　　　　　　　　　　□\n");
		locate(30, 27);
		printf_s("□□□□□□□□□□□□□□□□\n");
		keycode = _getch();

		//Enterが押された時
		if (keycode == 0x0d) {
			switch (command) {
			case 0:		//イージーコマンド
				gamelevel = 30000;
				nammido = 1;
				end = 1;
				break;
			case 1:		//ノーマルコマンド
				gamelevel = 20000;
				nammido = 2;
				end = 1;
				break;
			case 2:		//ハードコマンド
				gamelevel = 11000;
				nammido = 3;
				end = 1;
				break;
			}
		}
		//Enterが押されなかった時
		else {
			switch (keycode) {
			case UP:	//上キー
				if (command != 0) {
					command--;
				}
				else if (command == 0) {
					command = 2;
				}
				break;
			case DOWN:	//下キー
				if (command < 2) {
					command++;
				}
				else if (command == 2) {
					command = 0;
				}
				break;
			default:
				break;
			}
		}
	}
	system("cls");
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

void Shokika() {

	int i, j;

	//グローバル変数の初期化
	x = 6;
	y = 1;
	score = 0;
	timer = 0;
	trapcnt_1 = 0;
	gameover = 0;
	chein = 0;
	lineCnt = 0;
	mino_youso = 0;
	Trap_1_flag = 0;
	NextBlock[0][0] = 100;

	for (i = 0; i < 7; i++) {
		mino_array[i] = 100;
	}

	//フィールド用の配列の初期化
	for (i = 0; i < FIELD_HEIGHT; i++) {
		for (j = 0; j < FIELD_WIDTH; j++) {
			if (i == 0 || i > 20) {
				Field[i][j] = Stage[i][j] = 9;
			}
			else if (j >= 0 && j < 3) {
				Field[i][j] = Stage[i][j] = 9;
			}
			else if (j >= FIELD_WIDTH - 3 && j < FIELD_WIDTH) {
				Field[i][j] = Stage[i][j] = 9;
			}
			else {
				Field[i][j] = Stage[i][j] = 0;
			}
		}
	}
}
/* 乱数生成 */
int Ransu(int Number) {

	int r;

	r = rand() % Number;

	return r;
}

void Key() {

	int keycode = _getch();

	switch (keycode) {
	case UP:	//上キー
		Locate();
		break;
	case LEFT:	//左キー
		Moving(x - 1, y);
		break;
	case DOWN:	//下キー
		MovingDown();
		break;
	case RIGHT:	//右キー
		Moving(x + 1, y);
		break;
	}
}

int SponCheck(int YOUSO) {	//mino_arrayの中を確認

	int i;

	for (i = 0; i <= mino_youso; i++) {
		if (mino_array[i] == YOUSO) {
			return ERR;
		}
	}
	return SAFE;
}

int MinoCheck() {	//mino_arrayに格納場所あるか確認

	int i;

	for (i = 0; i < 7; i++) {
		if (mino_array[i] == 100) {
			mino_youso = i;
			return SAFE;
		}
	}
	return ERR;
}

void SponBlock() {

	int i, j;
	int R;
	int flag = ERR;	//次のミノが決まったか

	x = 6;
	y = 1;

	//ブロックをStageに配置
	//最初のブロック選択の時							
	if (NextBlock[0][0] == 100) {
		//ブロック選択									
		R = Ransu(7);
		mino_array[mino_youso] = R;
		mino_youso++;

		//ブロックをStageに初期配置						
		for (i = 0; i < BLOCK_HEIGHT; i++) {
			for (j = 0; j < BLOCK_WIDTH; j++) {
				Block[i][j] = tetoromino[R][i][j];
				Stage[y + i][x + j] = Block[i][j];
			}
		}
	}
	else {
		for (i = 0; i < BLOCK_HEIGHT; i++) {
			for (j = 0; j < BLOCK_WIDTH; j++) {
				Block[i][j] = NextBlock[i][j];
				Stage[y + i][x + j] = Block[i][j];
			}
		}
	}

	//mino_arrayに格納場所の確保
	//mino_arrayが満杯時								
	if (MinoCheck() == ERR)
	{
		//mino_array初期化								
		for (i = 0; i < 7; i++) {
			mino_array[i] = 100;
		}
		mino_youso = 0;
	}

	//NextBlockを選択
	while (flag == ERR) {
		R = Ransu(7);
		//次のブロックの種類が決まる						
		if (SponCheck(R) == SAFE) {
			mino_array[mino_youso] = R;	//確認配列に格納	
			mino_youso++;

			for (i = 0; i < BLOCK_HEIGHT; i++) {
				for (j = 0; j < BLOCK_WIDTH; j++) {
					//次のブロックに格納					
					NextBlock[i][j] = tetoromino[R][i][j];
				}
			}
			flag = SAFE;
		}
	}
	Drawing();
}

void Drawing() {

	int i, j;

	system("cls");

	for (i = 0; i < FIELD_HEIGHT; i++) {
		for (j = 0; j < FIELD_WIDTH; j++) {

			if (Field[i][j] == 9) {
				printf_s("■");
			}
			else if (Field[i][j] == 1 || Stage[i][j] == 1) {
				printf_s("□");
			}
			else if (Field[i][j] == 0 && Stage[i][j] == 0) {
				printf_s("　");
			}
			else {
				printf_s("？");
			}
		}
		printf_s("\n");
	}


	printf_s("\n");
	printf_s("■■NEXT■■");
	printf_s("\n");
	for (i = 0; i < BLOCK_HEIGHT; i++) {
		printf_s("■");
		for (j = 0; j < BLOCK_WIDTH; j++) {
			if (NextBlock[i][j] == 1) {
				printf_s("□");
			}
			else if (NextBlock[i][j] == 0) {
				printf_s("　");
			}
			else {
				printf_s("？");
			}
		}
		printf_s("■\n");
	}
	printf_s("■■■■■■\n");

	printf_s(" SCORE: %6d\n", score);
	printf_s(" CHEIN: %6d\n", chein);
}

int LocateCheck() {

	int i, j;

	for (i = 0; i < BLOCK_HEIGHT; i++) {
		for (j = 0; j < BLOCK_WIDTH; j++) {
			tentative[BLOCK_WIDTH - 1 - j][i] = Block[i][j];
		}
	}

	for (i = 0; i < BLOCK_HEIGHT; i++) {
		for (j = 0; j < BLOCK_WIDTH; j++) {
			if (tentative[i][j] == 1) {
				if (Field[y + i][x + j] > 0) {
					return ERR;	//異常終了
				}
			}
		}
	}
	return SAFE;	//正常終了
}

int Check(int X, int Y) {

	int i, j;

	for (i = 0; i < BLOCK_HEIGHT; i++) {
		for (j = 0; j < BLOCK_WIDTH; j++) {
			if (Block[i][j] == 1) {
				if (Field[Y + i][X + j] > 0) {
					return ERR;	//異常終了
				}
			}
		}
	}
	return SAFE;	//正常終了
}

void Locate() {

	int i, j;

	if (LocateCheck() == SAFE) {	//回転できる時
		for (i = 0; i < BLOCK_HEIGHT; i++) {
			for (j = 0; j < BLOCK_WIDTH; j++) {
				Block[i][j] = tentative[i][j];
				Stage[y + i][x + j] = Block[i][j];
			}
		}

		for (i = 0; i < BLOCK_HEIGHT; i++) {	//tentativeの初期化
			for (j = 0; j < BLOCK_WIDTH; j++) {
				tentative[i][j] = 0;
			}
		}
		Drawing();
	}
}

void Moving(int X, int Y) {

	int i, j;

	if (Check(X, Y) == SAFE)	//移動方向に移動できる時
	{
		//移動前のブロック位置を初期化
		for (i = 0; i < BLOCK_HEIGHT; i++) {
			for (j = 0; j < BLOCK_WIDTH; j++) {
				Stage[y + i][x + j] = 0;
			}
		}

		//移動後のブロック位置の書き込み
		for (i = 0; i < BLOCK_HEIGHT; i++) {
			for (j = 0; j < BLOCK_WIDTH; j++) {
				Stage[Y + i][X + j] = Block[i][j];
			}
		}
		Drawing();
		x = X;
		y = Y;
	}
}

void MovingDown() {

	if (Check(x, y + 1) == SAFE) {	//下に移動できた時
		Moving(x, y + 1);
	}
	else {						//もう下に移動できない時

		Fixing();

		BulkLine();

		EndCheck();

		if (EndCheck() == ERR) {
			gameover = 1;
			GameOver();
		}
		else {
			if (Trap_1_flag == 1) {
				TrapUp_R = Ransu(3);	//ランダムブロック行数生成　０～３
				TrapUp_col = Ransu(10);	//ランダムブロック列数生成　０～９
				TrapUp(TrapUp_R, TrapUp_col);
				Drawing();
				trapcnt_1 = 0;
				Trap_1_flag = 0;
			}
			SponBlock();
		}
	}
}

void Fixing() {

	int i, j;

	for (i = 0; i < BLOCK_HEIGHT; i++) {
		for (j = 0; j < BLOCK_WIDTH; j++) {
			if (Stage[y + i][x + j] == 1) {
				//StageをFieldにコピー・Stageを初期化する
				Field[y + i][x + j] = Stage[y + i][x + j];
				Stage[y + i][x + j] = 0;
			}
		}
	}
}

void Line() {

	int i, j;
	int n, m;
	int b;
	char exitFlag = 'f';

	for (i = FIELD_HEIGHT - 3; i > 0; i--) {
		for (j = 3; j < FIELD_WIDTH - 3; j++) {
			if (Field[i][j] == 0) {
				break;
			}
			//消せる行が見つかった時
			if (j == FIELD_WIDTH - 4) {
				//１→０行目の９をコピーしてしまう
				for (n = i; n > 1; n--) {
					//上の行をコピーする
					for (m = 3; m < FIELD_WIDTH - 3; m++) {
						Field[n][m] = Field[n - 1][m];
					}
				}
				//１行目に新たな空白行を作る
				for (b = 3; b < FIELD_WIDTH - 3; b++) {
					Field[1][b] = 0;
				}
				lineCnt++;
				Line();
				exitFlag = 't';
				break;
			}
		}
		if (exitFlag == 't') break;
	}
}

void BulkLine() {

	Line();

	if (lineCnt == 0) {
		chein = 0;
	}
	if (lineCnt > 0) {
		Score();
		chein++;
	}
	Drawing();
}

void Score() {

	//難易度 イージー　score * 1
	//	     ノーマル　score * 2
	//	     ハード　　score * 3

	switch (lineCnt) {
	case 1:
		score += (SINGLE * (1 + (chein * 0.2))) * nammido;
		break;
	case 2:
		score += (DOUBLE * (1 + (chein * 0.2))) * nammido;
		break;
	case 3:
		score += (TRIPLE * (1 + (chein * 0.2))) * nammido;
		break;
	case 4:
		score += (TETRIS * (1 + (chein * 0.2))) * nammido;
		break;
	}
	lineCnt = 0;
}

int EndCheck() {

	int i, j;

	for (i = 0; i < BLOCK_HEIGHT; i++) {
		for (j = 0; j < BLOCK_WIDTH; j++) {
			if (NextBlock[i][j] == 1) {
				if (Field[i + 1][j + 6] == 1) {
					return ERR;
				}
			}
		}
	}
	return SAFE;
}

void GameOver() {

	char c[30];
	int CHK = ERR;

	system("cls");

	locate(30, 20);
	printf_s("＋ーーーーーーーーーー＋\n");
	locate(30, 21);
	printf_s("｜　G a m e  O v e r　｜\n");
	locate(30, 22);
	printf_s("｜　SCORE: %6d   　｜\n", score);
	locate(30, 23);
	printf_s("＋ーーーーーーーーーー＋\n");

	Sleep(3000);
	getchar();

	system("cls");
}

void TrapUp(int R, int col) {

	int i, j;
	char buff;

	//下から一段上にあげてfieldに書き込む
//                     ↓上にずらしてもいいかの確認
	if (R >= 0 && TrapCheck() == SAFE) {
		for (i = 1; i < FIELD_HEIGHT - 1; i++) {
			for (j = 3; j < FIELD_WIDTH - 3; j++) {
				if (i < FIELD_HEIGHT - 3) {
					Field[i][j] = Field[i + 1][j];
				}
				else if (i == FIELD_HEIGHT - 3) {
					if (j != col + 3) {
						Field[i][j] = 1;
					}
					else {
						Field[i][j] = 0;
					}
				}
			}
		}
		Drawing();
		TrapUp(R - 1, col);
	}
}

int TrapCheck() {

	int i, j;

	//上にずらしてもいいかの確認
	for (j = 3; j < FIELD_WIDTH - 3; j++) {
		for (i = 1; i < FIELD_HEIGHT - 1; i++) {
			if (Field[i][j] == 1) {
				if (Stage[i - 1][j] == 1) {
					return ERR;	//移動不可
				}
				break;
			}
		}
	}
	return SAFE;//移動可
}