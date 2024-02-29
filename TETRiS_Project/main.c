/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/
/*�@�@�@�@�@�@�@�@�@                  �@�@�@�@�@�@�@�@�@*/
/*�@�@�@�@�@�@�@�@�@                  �@�@�@�@�@�@�@�@�@*/
/*�@�@�@�@�@�@�@�@�@ver2�J���p�G�f�B�^�@�@�@�@�@�@�@�@�@*/
/*�@�@�@�@�@�@�@�@�@                  �@�@�@�@�@�@�@�@�@*/
/*�@�@�@�@�@�@�@�@�@                  �@�@�@�@�@�@�@�@�@*/
/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/
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

//�L�[�R�[�h�ݒ�
#define ENTER	0x0d
#define UP		0x48
#define RIGHT	0x4d
#define LEFT	0x4b
#define DOWN	0x50

//�X�R�A�ݒ�
#define SINGLE (100)
#define DOUBLE (300)
#define TRIPLE (500)
#define TETRIS (800)

#define RANK_MAX 5

//�t�B�[���h�̑傫���ݒ�
#define FIELD_HEIGHT 23
#define FIELD_WIDTH	 16

//�u���b�N�̑傫���ݒ�
#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH	 4

/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/
/*�@�@�@�@�@�@�@�@�@���j���[�֘A�̊֐��@�@�@�@�@�@�@�@�@*/
/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/

char Command_Name[5][18] = {
		"   �X �^ �[ �g   ",
		"   �� �� �� ��   ",
		" �� �� �x �� �X  ",
		" �Q �[ �� �I ��  " };

char Level_Name[3][18] = {
		"     E A Z Y     ",
		"   N O R M A L   ",
		"     H A R D     " };

void Title();		/*�^�C�g���`��*/
void Menu();		/*���j���[�I��*/
void Start();		/*�Q�[���J�n*/
void Operation();	/*����m�F*/
void LevelChange();	/*��Փx�ݒ�*/
/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/
/*�@�@�@�@�@�@ �@�@�@ PLAY�֘A�̊֐� �@�@ �@�@�@�@�@�@�@*/
/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/

void Shokika();			//�������֐�
int Ransu(int Number);	//�O�`Number�|�P�̗�������
void Key();				//�L�[���͂̏���
void Locate();			//�u���b�N����]������
void Moving(int, int);	//�u���b�N���ړ�������
void Drawing();			//�ǁE�󔒁E�u���b�N�̉���
void SponBlock();		//�u���b�N�̃X�|�[���E�������W�t�^
int SponCheck(int);		//�������i�[�ł��邩�m�F����
int MinoCheck();		//mino_array�Ɋi�[�ꏊ���邩�m�F

/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/
/*�@�@�@�@�@ �@�@�@ �M�~�b�N�֘A�̊֐� �@�@ �@�@�@�@�@�@*/
/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/

void TrapUp(int R, int col);	/* ������u���b�N������M�~�b�N */

int TrapCheck();				/* TrapUp()�ł��邩�̃`�F�b�N�֐� */
								/* ERR or SAFE���߂���� */

/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/
/*�@�@�@�@�@�@�@�@BlockDown()�֘A�̊֐��@�@�@�@	�@�@�@�@*/
/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/

void MovingDown();
void Score();		/*�X�R�A�v�Z*/
void GameOver();	/*GameOver�\��*/
void Line();		/*�����郉�C���̊m�F�E�폜*/

void Fixing();		/*���݂̃u���b�N���W�Ƀu���b�N���Œ肷��*/
					/*			Stage������������			*/


void BulkLine();	/*�ċA�����ł���Line()���ꊇ�ɂ܂Ƃ߂�֐�*/
					/*				Chein�̈ێ�				�@*/


int EndCheck();		/*Spon�ł��邩�`�F�b�N				*/
					/*�ł��Ȃ��ꍇGameover				*/
					/*�߂�l�@�P���G���[�@�O������I���@*/

/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/
/*�@�@�@�@�@�@�@�@�@�@�m�F�֘A�̊֐��@�@�@�@�@�@�@�@�@�@*/
/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/

int Check(int, int);	/*�ړ���Ƀu���b�N�E�ǂ��Ȃ����ǂ���*/
						/*�߂�l�@�P���G���[�@�O������I���@*/

int LocateCheck();		/*��]���Ƀu���b�N�E�ǂ��Ȃ����ǂ���*/
						/*�߂�l�@�P���G���[�@�O������I���@*/

/*----------------------------------------------------------------------*/

/* �O���[�o���ϐ� */
int timer = 0;		//���̃u���b�N�����܂Ő�����
int trapcnt_1 = 0;	//����TrapUp�܂Ő�����
int TrapUp_R = 0;	//TrapUp�Ő�����i��
int TrapUp_col = 0;	//TrapUp�ł̃u���b�N�̋󂫍��W
int Trap_1_flag = 0;
char name[30] = { "\0" };
char kari[30] = { "\0" };
int score = 0;


//int prvRnd = 0;		//�O��̗���
int gamelevel = 40000;	//�u���b�N�����Ԋu
int nammido = 1;
int gameover = 0;

/* �X�R�A�ϐ� */
int chein = 0;		//�`�F�C���J�E���g
int lineCnt = 0;	//�����郉�C���J�E���g

/* �u���b�N���W	(stage) */
int x = 6;
int y = 1;

/* �u���b�N�i�[�z�� */
int tentative[BLOCK_HEIGHT][BLOCK_WIDTH] = { 0 };
int Block[BLOCK_HEIGHT][BLOCK_WIDTH] = { 0 };
int NextBlock[BLOCK_HEIGHT][BLOCK_WIDTH] = { 100 };

/* �t�B�[���h�p�z�� */
int Stage[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };
int Field[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

/* �u���b�N�̎�� */
int mino_youso = 0;
int mino_array[7] = { 100 };
int tetoromino[7][BLOCK_HEIGHT][BLOCK_WIDTH] = {
	/* I�^ */
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,

	/* O�^ */
	0,0,0,0,
	0,1,1,0,
	0,1,1,0,
	0,0,0,0,

	/* S�^ */
	0,0,0,0,
	0,1,1,0,
	1,1,0,0,
	0,0,0,0,

	/* Z�^ */
	0,0,0,0,
	1,1,0,0,
	0,1,1,0,
	0,0,0,0,

	/* J�^ */
	0,0,1,0,
	0,0,1,0,
	0,1,1,0,
	0,0,0,0,

	/* L�^ */
	0,1,0,0,
	0,1,0,0,
	0,1,1,0,
	0,0,0,0,

	/* T�^ */
	0,0,0,0,
	0,1,0,0,
	1,1,1,0,
	0,0,0,0, };
/*----------------------------------------------------------------------*/
int main() {

	system("cls");
	locate(30, 19);
	printf_s("����������������������������������������");
	locate(30, 20);
	printf_s("�� �������F����ʁ@�@�@�@�@�@�@�@�@�@ ��");
	locate(30, 21);
	printf_s("�� ���ꕔBGM������܂��B �@�@�@�@�@�@ ��");
	locate(30, 22);
	printf_s("�� �Q�[��������Ƃ��͕����𖾂邭���� ��");
	locate(30, 23);
	printf_s("�� �߂Â������Ȃ��悤�ɂ��܂��傤�B   ��");
	locate(30, 24);
	printf_s("����������������������������������������");
	locate(54, 25);
	printf_s("Enter ������...");
	_getch();
	system("cls");

	Menu();

	return 0;
}
//������������������������������������������������������������������������������������
void Title() {
	locate(8, 6);
	printf_s("����������������������������������������������������������������������������\n");
	locate(8, 7);
	printf_s("��                                                                        ��\n");
	locate(8, 8);
	printf_s("�� ������������ ���������� ������������ �����������@   ����    ��������   ��\n");
	locate(8, 9);
	printf_s("��     ����      ����          �����@�@  �����@�@����  ����  ���� �@ ���� ��\n");
	locate(8, 10);
	printf_s("��     ����  �@  ����    �@    �����@�@  �����@�@����        ���� �@      ��\n");
	locate(8, 11);
	printf_s("��     ���� �@   ��������      ���� �@   �����������@  ����    ��������   ��\n");
	locate(8, 12);
	printf_s("��     ����      ����    �@    ����      ���� �����@ �@�����@        ���� ��\n");
	locate(8, 13);
	printf_s("��     ����      ����          ����      �����@�����@�@�����@�����@  ���� ��\n");
	locate(8, 14);
	printf_s("��    ������    ����������    ������    ������   ����  ����    ��������   ��\n");
	locate(8, 15);
	printf_s("��  �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@          ��\n");
	locate(8, 16);
	printf_s("����������������������������������������������������������������������������\n\n\n");
}

void Menu() {

	int i;
	int keycode;
	int command = 0;
	int end = 0;

	while (end == 0) {

		Title();

		locate(30, 19);
		printf_s("��������������������������������\n");

		for (i = 0; i < 4; i++) {

			locate(30, 19 + ((i + 1) * 2) - 1);
			printf_s("���@�@�@�@�@�@�@�@�@�@�@�@�@�@��\n");

			locate(30, 19 + (i + 1) * 2);
			printf_s("��  %s�@%s�@  %s ��\n"
				, (command == i) ? ">" : "�@"
				, Command_Name[i]
				, (command == i) ? " " : "");
		}

		locate(30, 28);
		printf_s("���@�@�@�@�@�@�@�@�@�@�@�@�@�@��\n");
		locate(30, 29);
		printf_s("��������������������������������\n");
		keycode = _getch();

		//Enter�������ꂽ��
		if (keycode == ENTER) {
			switch (command) {
			case 0:		//START�R�}���h
				Start();
				break;
			case 1:		//OPERATION�R�}���h
				Operation();
				break;
			case 2:		//RANKING�R�}���h
				LevelChange();
				break;
			case 3:		//GAMEEND�R�}���h
				end = 1;
				break;
			}
		}
		//Enter��������Ȃ�������
		else {
			switch (keycode) {
			case UP:	//��L�[
				if (command != 0) {
					command--;
				}
				else if (command == 0) {
					command = 3;
				}
				break;
			case DOWN:	//���L�[
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

	//���O�̓���------------------
	while (kari[0] == '\0') {
		system("cls");
		locate(22, 20);
		printf_s("���O����͂��Ă�������...(10�o�C�g�ȓ�)\n");
		locate(22, 22);
		printf_s("�P�P�P�P�P�P�P�P\n");
		locate(22, 21);
		printf_s("��");
		locate(24, 21);
		scanf_s(" %s", &kari, 30);

		if (strlen(kari) < 11) {
			locate(22, 24);
			printf_s("�w%s�x�ł�낵���ł����H\n", kari);
			locate(22, 26);
			printf_s("YES�Ȃ�w1�xNO�Ȃ�w2�x�������Ă�������(���p)>>");
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
			printf_s("�������I�[�o�[���Ă��܂�...");
			Sleep(1000);
		}
	}

	//�{����
	system("cls");
	Shokika();
	SponBlock();

	//PlaySound((" "),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC);

	while (gameover == 0) {
		/* �L�[���͎��̏��� */
		if (_kbhit()) {
			Key();
		}
		/* ��莞�Ԍ�̗������� */
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
	printf_s("������������������������������������������������������������������������������\n");
	locate(7, 8);
	printf_s("���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��\n");
	locate(7, 9);
	printf_s("���y������@�z�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��\n");
	locate(7, 10);
	printf_s("���@�@�@�@�@�@�@�@�@                                  �@�@�@�@�@�@�@�@�@�@�@��\n");
	locate(7, 11);
	printf_s("�����L�[�F�u���b�N���X�O�x��]������@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��\n");
	locate(7, 12);
	printf_s("���@�@�@                                �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��\n");
	locate(7, 13);
	printf_s("�����L�[�F�u���b�N�����Ɉړ�������@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��\n");
	locate(7, 14);
	printf_s("���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@                                  �@�@�@�@��\n");
	locate(7, 15);
	printf_s("�����L�[�F�u���b�N�̗������x���グ��@�@�@�@�@�@�@�@�@�{�[�{�@�@�@�@�@�@�@�@��\n");
	locate(7, 16);
	printf_s("���@�@�@�@�@�@�@�@�@                                �@�b���b�@�@�@�@�@�@�@�@��\n");
	locate(7, 17);
	printf_s("�����L�[�F�u���b�N���E�Ɉړ�������@�@�@�@�@�@�@�@�{�[�{�[�{�[�{�@�@�@�@�@�@��\n");
	locate(7, 18);
	printf_s("��                                 �@�@�@�@ �@�@�@�b���b���b���b�@�@�@�@�@�@��\n");
	locate(7, 19);
	printf_s("��                                  �@�@�@�@�@�@�@�{�[�{�[�{�[�{�@�@�@�@�@�@��\n");
	locate(7, 20);
	printf_s("���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@                    �@�@�@�@�@�@��\n");
	locate(7, 21);
	printf_s("������������������������������������������������������������������������������\n");

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
		printf_s("��������������������������������\n");

		for (i = 0; i < 3; i++) {

			locate(30, 19 + ((i + 1) * 2) - 1);
			printf_s("���@�@�@�@�@�@�@�@�@�@�@�@�@�@��\n");

			locate(30, 19 + (i + 1) * 2);
			printf_s("���@%s�@%s�@%s�@ ��\n"
				, (command == i) ? ">" : "  "
				, Level_Name[i]
				, (command == i) ? " " : "");
		}

		locate(30, 26);
		printf_s("���@�@�@�@�@�@�@�@�@�@�@�@�@�@��\n");
		locate(30, 27);
		printf_s("��������������������������������\n");
		keycode = _getch();

		//Enter�������ꂽ��
		if (keycode == 0x0d) {
			switch (command) {
			case 0:		//�C�[�W�[�R�}���h
				gamelevel = 30000;
				nammido = 1;
				end = 1;
				break;
			case 1:		//�m�[�}���R�}���h
				gamelevel = 20000;
				nammido = 2;
				end = 1;
				break;
			case 2:		//�n�[�h�R�}���h
				gamelevel = 11000;
				nammido = 3;
				end = 1;
				break;
			}
		}
		//Enter��������Ȃ�������
		else {
			switch (keycode) {
			case UP:	//��L�[
				if (command != 0) {
					command--;
				}
				else if (command == 0) {
					command = 2;
				}
				break;
			case DOWN:	//���L�[
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

//������������������������������������������������������������������������������������

void Shokika() {

	int i, j;

	//�O���[�o���ϐ��̏�����
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

	//�t�B�[���h�p�̔z��̏�����
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
/* �������� */
int Ransu(int Number) {

	int r;

	r = rand() % Number;

	return r;
}

void Key() {

	int keycode = _getch();

	switch (keycode) {
	case UP:	//��L�[
		Locate();
		break;
	case LEFT:	//���L�[
		Moving(x - 1, y);
		break;
	case DOWN:	//���L�[
		MovingDown();
		break;
	case RIGHT:	//�E�L�[
		Moving(x + 1, y);
		break;
	}
}

int SponCheck(int YOUSO) {	//mino_array�̒����m�F

	int i;

	for (i = 0; i <= mino_youso; i++) {
		if (mino_array[i] == YOUSO) {
			return ERR;
		}
	}
	return SAFE;
}

int MinoCheck() {	//mino_array�Ɋi�[�ꏊ���邩�m�F

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
	int flag = ERR;	//���̃~�m�����܂�����

	x = 6;
	y = 1;

	//�u���b�N��Stage�ɔz�u
	//�ŏ��̃u���b�N�I���̎�							
	if (NextBlock[0][0] == 100) {
		//�u���b�N�I��									
		R = Ransu(7);
		mino_array[mino_youso] = R;
		mino_youso++;

		//�u���b�N��Stage�ɏ����z�u						
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

	//mino_array�Ɋi�[�ꏊ�̊m��
	//mino_array�����t��								
	if (MinoCheck() == ERR)
	{
		//mino_array������								
		for (i = 0; i < 7; i++) {
			mino_array[i] = 100;
		}
		mino_youso = 0;
	}

	//NextBlock��I��
	while (flag == ERR) {
		R = Ransu(7);
		//���̃u���b�N�̎�ނ����܂�						
		if (SponCheck(R) == SAFE) {
			mino_array[mino_youso] = R;	//�m�F�z��Ɋi�[	
			mino_youso++;

			for (i = 0; i < BLOCK_HEIGHT; i++) {
				for (j = 0; j < BLOCK_WIDTH; j++) {
					//���̃u���b�N�Ɋi�[					
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
				printf_s("��");
			}
			else if (Field[i][j] == 1 || Stage[i][j] == 1) {
				printf_s("��");
			}
			else if (Field[i][j] == 0 && Stage[i][j] == 0) {
				printf_s("�@");
			}
			else {
				printf_s("�H");
			}
		}
		printf_s("\n");
	}


	printf_s("\n");
	printf_s("����NEXT����");
	printf_s("\n");
	for (i = 0; i < BLOCK_HEIGHT; i++) {
		printf_s("��");
		for (j = 0; j < BLOCK_WIDTH; j++) {
			if (NextBlock[i][j] == 1) {
				printf_s("��");
			}
			else if (NextBlock[i][j] == 0) {
				printf_s("�@");
			}
			else {
				printf_s("�H");
			}
		}
		printf_s("��\n");
	}
	printf_s("������������\n");

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
					return ERR;	//�ُ�I��
				}
			}
		}
	}
	return SAFE;	//����I��
}

int Check(int X, int Y) {

	int i, j;

	for (i = 0; i < BLOCK_HEIGHT; i++) {
		for (j = 0; j < BLOCK_WIDTH; j++) {
			if (Block[i][j] == 1) {
				if (Field[Y + i][X + j] > 0) {
					return ERR;	//�ُ�I��
				}
			}
		}
	}
	return SAFE;	//����I��
}

void Locate() {

	int i, j;

	if (LocateCheck() == SAFE) {	//��]�ł��鎞
		for (i = 0; i < BLOCK_HEIGHT; i++) {
			for (j = 0; j < BLOCK_WIDTH; j++) {
				Block[i][j] = tentative[i][j];
				Stage[y + i][x + j] = Block[i][j];
			}
		}

		for (i = 0; i < BLOCK_HEIGHT; i++) {	//tentative�̏�����
			for (j = 0; j < BLOCK_WIDTH; j++) {
				tentative[i][j] = 0;
			}
		}
		Drawing();
	}
}

void Moving(int X, int Y) {

	int i, j;

	if (Check(X, Y) == SAFE)	//�ړ������Ɉړ��ł��鎞
	{
		//�ړ��O�̃u���b�N�ʒu��������
		for (i = 0; i < BLOCK_HEIGHT; i++) {
			for (j = 0; j < BLOCK_WIDTH; j++) {
				Stage[y + i][x + j] = 0;
			}
		}

		//�ړ���̃u���b�N�ʒu�̏�������
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

	if (Check(x, y + 1) == SAFE) {	//���Ɉړ��ł�����
		Moving(x, y + 1);
	}
	else {						//�������Ɉړ��ł��Ȃ���

		Fixing();

		BulkLine();

		EndCheck();

		if (EndCheck() == ERR) {
			gameover = 1;
			GameOver();
		}
		else {
			if (Trap_1_flag == 1) {
				TrapUp_R = Ransu(3);	//�����_���u���b�N�s�������@�O�`�R
				TrapUp_col = Ransu(10);	//�����_���u���b�N�񐔐����@�O�`�X
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
				//Stage��Field�ɃR�s�[�EStage������������
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
			//������s������������
			if (j == FIELD_WIDTH - 4) {
				//�P���O�s�ڂ̂X���R�s�[���Ă��܂�
				for (n = i; n > 1; n--) {
					//��̍s���R�s�[����
					for (m = 3; m < FIELD_WIDTH - 3; m++) {
						Field[n][m] = Field[n - 1][m];
					}
				}
				//�P�s�ڂɐV���ȋ󔒍s�����
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

	//��Փx �C�[�W�[�@score * 1
	//	     �m�[�}���@score * 2
	//	     �n�[�h�@�@score * 3

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
	printf_s("�{�[�[�[�[�[�[�[�[�[�[�{\n");
	locate(30, 21);
	printf_s("�b�@G a m e  O v e r�@�b\n");
	locate(30, 22);
	printf_s("�b�@SCORE: %6d   �@�b\n", score);
	locate(30, 23);
	printf_s("�{�[�[�[�[�[�[�[�[�[�[�{\n");

	Sleep(3000);
	getchar();

	system("cls");
}

void TrapUp(int R, int col) {

	int i, j;
	char buff;

	//�������i��ɂ�����field�ɏ�������
//                     ����ɂ��炵�Ă��������̊m�F
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

	//��ɂ��炵�Ă��������̊m�F
	for (j = 3; j < FIELD_WIDTH - 3; j++) {
		for (i = 1; i < FIELD_HEIGHT - 1; i++) {
			if (Field[i][j] == 1) {
				if (Stage[i - 1][j] == 1) {
					return ERR;	//�ړ��s��
				}
				break;
			}
		}
	}
	return SAFE;//�ړ���
}