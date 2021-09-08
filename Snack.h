#pragma once
#pragma once

typedef struct _SNACK {
	int X;
	int Y;
}Snack, * PSnack;

extern Snack snack[100];
extern int len;
extern char op;
extern char opp;
extern char tDir;
extern unsigned int score;

void initSnack();      // 初始化蛇
void clearSnack();      // 清除蛇
void drawSnack();       // 画蛇
int moveSnack();        // 移动蛇