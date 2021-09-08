#pragma comment(lib, "winmm.lib")
#include "Game.h"
#include "Snack.h"
#include <conio.h>
#include <vector>
#include <iostream>
#include <Windows.h>

int MAP[MAP_X][MAP_Y] = { 0 };
int foodExist = 0;
unsigned int speed = 一般;
std::vector<COORD> CMAP;

// 定位坐标打印字符串
void writeChar(int x, int y, const char* ch) {
	COORD pos = { x * 2,y };
	CONSOLE_CURSOR_INFO set = { 1,0 };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &set);
	SetConsoleCursorPosition(hOut, pos);
	std::cout << ch;
}

//LOGO
void showLogo() {
	writeChar(40, 0, "               o8888888o                  ");
	writeChar(40, 1, "              88\" . \"88                 ");
	writeChar(40, 2, "               (| -_- |)                  ");
	writeChar(40, 3, "              O\\  =  /O                  ");
	writeChar(40, 4, "            ____/`---'\\____              ");
	writeChar(40, 5, "          .'  \\\\|     |//  `.           ");
	writeChar(40, 6, "         /  \\\\|||  :  |||//  \\         ");
	writeChar(40, 7, "        /  _||||| -:- |||||_  \\          ");
	writeChar(40, 8, "        |   | \\\\\\  -  /'| |   |        ");
	writeChar(40, 9, "        | \\_|  `\\`---'//  |_/ |         ");
	writeChar(40, 10, "        \\  .-\\__ `-. -'__/-.  /         ");
	writeChar(40, 11, "      ___`. .'  /--.--\\  `. .'___        ");
	writeChar(40, 12, "   .\"\" '<  `.___\\_<|>_/___.' _> \\\"\".");
	writeChar(40, 13, "  | | :  `- \\`. ;`. _/; .'/ /  .' ; |    ");
	writeChar(40, 14, "  \\  \\ `-.   \\_\\_`. _.'_/_/  -' _.' / ");
	writeChar(40, 15, "===`-.`___`-.__\\ \\___  /__.-'_.'_.-'=== ");
	writeChar(40, 16, "                   `=--=-'                ");
}

// 菜单
void menu() {
	showLogo();
	writeChar(48, 18, "1.新游戏");
	writeChar(48, 19, "2.暂停继续");
	writeChar(48, 20, "3.存档");
	writeChar(48, 21, "4.读档");
	writeChar(48, 22, "5.结束游戏");
	writeChar(47, 24, "当前得分：");
}

// 初始化游戏
void initGame() {
	// 设定控制台
	system("title 一起来玩蛇");
	system("color 9F");
	system("cls");

	// BGM
	PlaySoundA("bg.wav", NULL, SND_ASYNC | SND_NODEFAULT);
}

// 自定义地图
void mouseLoop() {
	// 获取到当前输出缓冲区的标识，有了标识就知道要操作的是谁了
	HANDLE input = GetStdHandle(STD_INPUT_HANDLE);

	// 定义结构体用于保存接收到的事件信息
	DWORD count = 0;
	INPUT_RECORD input_record = { 0 };

	// 设置控制台的模式，允许控制台接收鼠标事件
	DWORD mode = 0;
	GetConsoleMode(input, &mode);            // 先获取原有模式
	SetConsoleMode(input, mode | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);  // 在原有基础上增加鼠标事件

	COORD tempWall;
	// 1. 读取哪一个控制台缓冲区接收到的事件信息
	// 2. 保存输入事件信息的结构体
	// 3. 参数二传入的缓冲区保存了几个结构体
	// 4. 传入给函数，返回当前接收到的事件的个数
	/*writeChar(7, 36, "绘图结束后按任意键开始游戏");
	writeChar(8, 36, "关闭编辑模式重新启动才能绘图");*/
	while (ReadConsoleInput(input, &input_record, 1, &count))
	{
		// 如果接收不到鼠标事件，可能是下面的两个原因
		//  1. 设置控制台的属性: 控制台标题右键设置属性，取消选中的快速选择模式
		//  2. 设置控制台的模式: 允许控制台接收到鼠标的事件信息(点击、移动等)
		if (input_record.EventType == KEY_EVENT)
		{
			KEY_EVENT_RECORD ker = input_record.Event.KeyEvent;
			if (ker.bKeyDown)
				break;
		}
		// 如果接收到了鼠标事件，就输出相应的内容
		if (input_record.EventType == MOUSE_EVENT)
		{
			auto mosue_event = input_record.Event.MouseEvent;

			// 无论是什么鼠标事件，都输出鼠标的坐标
			auto point = mosue_event.dwMousePosition;
			/*char buffer[0x20] = { 0 };
			sprintf_s(buffer, 0x20, "(%02hd, %02hd)", point.X, point.Y);
			Writechar({ 0, 0 }, WHITE_COLOR, buffer);*/

			// 捕获到鼠标的左键点击事件
			if (mosue_event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				// 输出函数的坐标已经经过了转换，但是当前我们得到的坐标是控制台坐标
				writeChar(point.X, point.Y, "■");
				tempWall.X = point.X;
				tempWall.Y = point.Y;
				CMAP.push_back(tempWall);
			}
			// 假设按下了鼠标右键就擦除
			else if (mosue_event.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				writeChar(point.Y, point.X / 2, "  ");
			}
		}
	}
}

// 默认地图标记
void initMap() {
	// 初始化默认地图
	for (int i = 0; i < MAP_X; i++) {
		for (int j = 0; j < MAP_Y; j++) {
			if (i == 0 || j == 0 || i == MAP_X - 1 || j == MAP_Y - 1) {
				MAP[i][j] = OBSTACLE;
			}
			else {
				MAP[i][j] = SPACE;
			}
		}
	}
	// 设置障碍物
	for (int i = 0; i < 7; i++) {
		MAP[17 + i][15] = OBSTACLE;
	}
	for (int i = 0; i < 7; i++) {
		MAP[20][12 + i] = OBSTACLE;
	}
	for (int i = 1; i <= 3; i++) {
		MAP[17][15 + i] = OBSTACLE;
	}
	for (int i = 1; i <= 3; i++) {
		MAP[23][15 - i] = OBSTACLE;
	}
	for (int i = 1; i <= 3; i++) {
		MAP[20 - i][12] = OBSTACLE;
	}
	for (int i = 1; i <= 3; i++) {
		MAP[20 + i][18] = OBSTACLE;
	}
}

// 自编辑地图
void custoMap() {
	mouseLoop();
	int len = size(CMAP);
	int tx = 0, ty = 0;
	for (int i = 0; i < len; i++) {
		tx = CMAP[i].X;
		ty = CMAP[i].Y;
		MAP[tx][ty] = OBSTACLE;
	}
}

// 根据标记生成地图
void drawMap() {

	for (int i = 0; i < MAP_X; i++) {
		for (int j = 0; j < MAP_Y; j++) {
			if (MAP[i][j] == OBSTACLE) {
				writeChar(i, j, "#");
			}
		}
	}
}

// 生成食物
void createFood() {
	while (true) {
		int food_X = rand() % 38 + 1;
		int food_Y = rand() % 28 + 1;
		if (MAP[food_X][food_Y] == SPACE) {
			MAP[food_X][food_Y] = FOOD;
			writeChar(food_X, food_Y, "$");
			foodExist = 1;
			return;
		}
	}
}

// 选择难度
unsigned int choiceDiff() {
	int flag = 1;
	do {
		char co = 0;
		writeChar(18, 5, "请选择难度");
		writeChar(18, 6, "  1.简单  ");
		writeChar(18, 7, "  2.一般  ");
		writeChar(18, 8, "  3.困难  ");
		co = _getch();
		switch (co) {
			case '1': {speed = 简单; flag = 0; break; }
			case '2': {speed = 一般; flag = 0; break; }
			case '3': {speed = 困难; flag = 0; break; }
			default: {
				writeChar(19, 10, "非法输入");
				Sleep(300);
				writeChar(19, 10, "        ");
				break;
			}
		}
	} while (flag);
	writeChar(18, 5, "          ");
	writeChar(18, 6, "          ");
	writeChar(18, 7, "          ");
	writeChar(18, 8, "          ");
	return speed;
}

// 开始游戏
void startGame(unsigned int speed) {
	while (true) {
		// 清除蛇
		clearSnack();
		// 移动蛇
		if (!moveSnack()) {
			writeChar(15, 15, "GAME OVER!");
			system("pause");
		}
		// 画蛇
		drawSnack();
		// 生成食物
		if (foodExist == 0) {
			createFood();
		}
		// 速度随着分数增加而变快（越来越难）
		speed -= (score % 10);
		Sleep(speed);
	}
}

// 存档
void doArchives() {
	// 打开文件
	FILE* fp = NULL;
	fopen_s(&fp, "archives.txt", "w");
	// 记录当前速度、蛇的方向、分数、长度
	fprintf(fp, "%d\t%c\t%d\t%d", speed, tDir, score, len);
	// 回车分割
	fprintf(fp, "\n");
	// 获取蛇当前坐标
	int sx = 0, sy = 0;
	for (int i = 0; i < len; i++) {
		sx = snack[i].X;
		sy = snack[i].Y;
		fprintf(fp, "(%d,%d)\t", sx, sy);
	}
	// 回车分割
	fprintf(fp, "\n");
	// 获取障碍物当前坐标
	for (int i = 0; i < MAP_X;  i++) {
		for (int j = 0; j < MAP_Y; j++) {
			if (MAP[i][j] == OBSTACLE) {
				fprintf(fp, "(%d,%d)\t", i, j);
			}
		}
	}
	// 回车分割
	fprintf(fp, "\n");
	// 获取食物当前坐标
	for (int i = 0; i < MAP_X; i++) {
		for (int j = 0; j < MAP_Y; j++) {
			if (MAP[i][j] == FOOD) {
				fprintf(fp, "(%d,%d)\t", i, j);
			}
		}
	}
	// 关闭文件
	fclose(fp);
	fp = NULL;
}

// 读取存档
void loadArchives() {
	FILE* fp = NULL;
	fopen_s(&fp, "archives.txt", "r");

	// 读取当前速度、蛇的方向、分数、长度
	fscanf_s(fp, "%d\t%c\t%d\t%d", &speed, &tDir, 1, &score, &len);
	opp = tDir;
	// 分割回车
	fscanf_s(fp, "\n");

	// 读取蛇的坐标
	int sx = 0, sy = 0;
	for (int i = 0; i < len; i++) {
		fscanf_s(fp, "(%d,%d)\t", &sx, &sy);
		snack[i].X = sx;
		snack[i].Y = sy;
	}
	// 分割回车
	fscanf_s(fp, "\n");

	// 读取障碍物当前坐标
	for (int i = 0; i < MAP_X; i++) {
		for (int j = 0; j < MAP_Y; j++) {
			fscanf_s(fp, "(%d,%d)\t", &i, &j);
			MAP[i][j] = OBSTACLE;
		}
	}
	// 分割回车
	fscanf_s(fp, "\n");

	// 读取食物当前坐标
	for (int i = 0; i < MAP_X; i++) {
		for (int j = 0; j < MAP_Y; j++) {
			fscanf_s(fp, "(%d,%d)", &i, &j);
			MAP[i][j] = FOOD;
		}
	}
	// 关闭文件
	fclose(fp);
	fp = NULL;
}