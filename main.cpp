#include "Game.h"
#include "Snack.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>

// 主函数
int main() {

	// 初始化控制台
	initGame();
	system("cls");
	// 欢迎界面
	showFace();
	// 选择模式
	chooseMode();
	// 画地图
	drawMap();
	// 加载logo和菜单
	menu();
	// 选择菜单
	chooseMenu();
	return 0;
}