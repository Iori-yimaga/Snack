#pragma once

// 蛇的结构体
typedef struct _SNACK {
	int X;
	int Y;
}Snack, * PSnack;

// 声明蛇的数组
extern Snack snack[100];
// 蛇的长度
extern int len;
// 按键操作
extern char op;
extern char opp;
extern char tDir;
// 分数
extern unsigned int score;

void initSnack();      // 初始化蛇
void clearSnack();      // 清除蛇
void drawSnack();       // 画蛇
int moveSnack();        // 移动蛇