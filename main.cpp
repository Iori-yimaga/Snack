#include "Game.h"
#include "Snack.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>

int main() {
	char choice = 0; // 游戏选项
	unsigned int speed = 0;
	char cm = 0;     // 地图选项
	int flag = 1;
	// 初始化蛇
	initGame();
	system("cls");

	menu();
	writeChar(18, 10, "请选择地图模式：");
	writeChar(18, 12, "1. 默认模式");
	writeChar(18, 14, "2. 自编辑模式");
	// 选择地图
	do {
		cm = _getch();
		switch (cm) {
		case '1': {
			system("cls");
			initMap();
			flag = 0;
			break;
		}
		case '2': {
			system("cls");
			custoMap();
			flag = 0;
			break;
		}
		default:
			writeChar(18, 16, "非法输入");
			Sleep(300);
			writeChar(18, 16, "          ");
			break;
		}
	} while (flag);
	drawMap();
	menu();

	do {
		choice = _getch();
		switch (choice) {
		case 新游戏: {
			speed = choiceDiff();
			startGame(speed);
			break;
		}
				/*case 暂停继续: {}*/
				// case 存档: {}
		case 读档: {

		}
		case 结束游戏: {

			exit(0);
		}
		default:
			break;
		}
	} while (choice != 结束游戏);
	return 0;
}