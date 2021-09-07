#include "Snack.h"
#include "Game.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>

Snack snack[100];
int len = 4;
char op = RIGHT;
char opp = RIGHT;
char tDir = RIGHT;
unsigned int score = 0;

// 清除蛇
void clearSnack() {
	for (int i = 0; i < len; i++) {
		writeChar(snack[i].X, snack[i].Y, " ");
	}
}

// 移动蛇
int moveSnack() {
	int tX = snack[0].X;
	int tY = snack[0].Y;

	// 不可回头
	if (_kbhit() && (op = _getch())) {
		if ((op == UP && opp != DOWN) || (op == DOWN && opp != UP) || (op == LEFT && opp != RIGHT) || (op == RIGHT && opp != LEFT) || (op == 暂停继续) || (op == 结束游戏)) {
			opp = op;
			// 保存进入暂停前最后一次的操作（方向）
			if (opp != 暂停继续 && opp != 结束游戏) {
				tDir = opp;
			}
			// 暂停继续操作
			if (opp == 暂停继续) {
				writeChar(18, 7, "游戏暂停");
				while (_getch() != 暂停继续) {
					op = _getch();
				}
				writeChar(18, 7, "游戏继续");
				Sleep(3000);
				writeChar(18, 7, "          ");
				// 退出暂停后蛇按之前的方向移动
				opp = tDir;
			}
			// 结束游戏操作
			if (opp == 结束游戏) {
				writeChar(47, 26, "是否退出游戏？");
				writeChar(47, 27, "(y)es / (n)o ");
				do {
					opp = _getch();
					switch (opp) {
					case 'y': exit(0);
					case 'n': break;
					default:
						writeChar(48, 28, "非法输入");
						Sleep(1000);
						writeChar(48, 28, "          ");
						break;
					}
				} while (opp != 'n');
				writeChar(47, 26, "                ");
				writeChar(47, 27, "                ");
				opp = tDir;
			}
		}
	}

	// 蛇的操作
	switch (opp) {
	case UP: {
		tY--;
		break;
	}
	case DOWN: {
		tY++;
		break;
	}
	case LEFT: {
		tX--;
		break;
	}
	case RIGHT: {
		tX++;
		break;
	}
	default:
		break;
	}

	// 判断蛇头是否撞到东西
	if (MAP[tX][tY] == SPACE) {

	}
	else if (MAP[tX][tY] == FOOD) {
		len++;
		MAP[tX][tY] = SPACE;
		foodExist = 0;
		score += 10;
		writeChar(47, 24, "当前得分：");
		std::cout << score;
	}
	else if (MAP[tX][tY] == OBSTACLE) {
		return 0;
	}
	else if (MAP[tX][tY] == MYSELF) {
		return 0;
	}

	// 清除标记
	for (int i = 1; i < len; i++) {
		MAP[snack[i].X][snack[i].Y] = SPACE;
	}

	for (int i = len - 1; i >= 0; i--) {
		snack[i + 1].X = snack[i].X;
		snack[i + 1].Y = snack[i].Y;
	}
	snack[0].X = tX;
	snack[0].Y = tY;

	return 1;
}

// 画蛇
void drawSnack() {
	writeChar(snack[0].X, snack[0].Y, "■");
	for (int i = 1; i < len; i++) {
		MAP[snack[i].X][snack[i].Y] = MYSELF;     // 标记蛇身
		writeChar(snack[i].X, snack[i].Y, "■");
	}
}