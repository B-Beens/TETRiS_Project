#include <stdio.h>
#include <conio.h>
#include <windows.h>

// 画面消去の定数
#define CLS_SPACE	((WORD)(0x20))
#define CLS_COLOR	((WORD)(0x0F))
/*====================================================================*/
/*	locate	座標設定処理											  */
/*		引数１：Ｘ軸　　引数２：Ｙ軸　　戻り値：なし				  */
/*		座標の原点は左上が（0,0)とする								  */
/*====================================================================*/
void locate(int x, int y)
{
	HANDLE hdt;	/* 標準出力デバイスハンドル */
	COORD pos;	/* 座標(X,Y) */

	hdt = GetStdHandle(STD_OUTPUT_HANDLE);	/* 標準出力デバイスハンドル取得 */

	pos.X = (SHORT)x;	/* Ｘ座標設定 */
	pos.Y = (SHORT)y;	/* Ｙ座標設定 */

	SetConsoleCursorPosition(hdt, pos);	/* 標準出力にカーソル位置設定 */
}