#include <stdio.h>
#include <conio.h>
#include <windows.h>

// ��ʏ����̒萔
#define CLS_SPACE	((WORD)(0x20))
#define CLS_COLOR	((WORD)(0x0F))
/*====================================================================*/
/*	locate	���W�ݒ菈��											  */
/*		�����P�F�w���@�@�����Q�F�x���@�@�߂�l�F�Ȃ�				  */
/*		���W�̌��_�͍��オ�i0,0)�Ƃ���								  */
/*====================================================================*/
void locate(int x, int y)
{
	HANDLE hdt;	/* �W���o�̓f�o�C�X�n���h�� */
	COORD pos;	/* ���W(X,Y) */

	hdt = GetStdHandle(STD_OUTPUT_HANDLE);	/* �W���o�̓f�o�C�X�n���h���擾 */

	pos.X = (SHORT)x;	/* �w���W�ݒ� */
	pos.Y = (SHORT)y;	/* �x���W�ݒ� */

	SetConsoleCursorPosition(hdt, pos);	/* �W���o�͂ɃJ�[�\���ʒu�ݒ� */
}