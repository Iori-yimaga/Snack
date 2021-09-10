#pragma once
#include <vector>
#include <Windows.h>
#include <iostream>

#define UP       'w'
#define DOWN     's'
#define LEFT     'a'
#define RIGHT    'd'
#define MAP_X     40
#define MAP_Y     30
#define SPACE     0
#define FOOD      1
#define OBSTACLE  2
#define MYSELF    3
#define 新游戏       '1'
#define 暂停继续     '2'
#define 存档         '3'
#define 读档         '4'
#define 结束游戏     '5'
#define 简单         200
#define 一般         150
#define 困难         100

extern int MAP[MAP_X][MAP_Y];                 // 地图
extern int food_X;
extern int food_Y;                            // 食物
extern int foodExist;                         // 食物是否存在
extern unsigned int speed;                    // 速度
extern std::vector<COORD> CMAP;               // 自定义地图

void showFace();                              // 欢迎界面
void menu();                                  // 菜单
void doAgain();                               // 是否回到主菜单
void showLogo();                              // 欢迎图
unsigned int choiceDiff();                    // 选择难度
void chooseMode();                            // 选择模式
void chooseMenu();                            // 选择菜单
void startGame(unsigned int speed);           // 开始游戏
void initGame();                              // 初始化控制台
void drawMap();                               // 生成地图
void initMap();                               // 默认地图
void initObstacle();                          // 默认障碍物
void custoMap();                              // 自编辑地图
void createFood();                            // 生成食物
void mouseLoop();                             // 获取鼠标事件
void doArchives();                            // 存档
void loadArchives();                          // 读档
void writeChar(int x, int y, const char* ch); // 画操作