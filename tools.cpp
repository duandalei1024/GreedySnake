/**
 * @file tools.cpp
 * @brief Windows控制台工具函数实现文件
 * @details 封装了Windows
 * API中常用的控制台操作函数，包括窗口大小设置、光标定位、颜色控制等
 */

#include "tools.h"
#include <stdio.h>
#include <windows.h>


/**
 * @brief 设置控制台窗口大小和标题
 * @param cols 窗口列数（逻辑单位，一个图形字符占2个物理字符宽度）
 * @param lines 窗口行数
 * @details 通过system命令调用Windows的mode命令来设置控制台窗口大小
 *          注意：由于图形字符"■"、"●"等占2个字符宽度，所以实际列数需要乘以2
 */
void SetWindowSize(int cols, int lines) {
  system("title 贪吃蛇"); // 设置控制台窗口标题为"贪吃蛇"

  char cmd[30]; // 用于存储系统命令的字符数组
  // 构建mode命令字符串，设置窗口列数和行数
  // 注意：cols需要乘以2，因为每个图形字符占2个字符宽度
  sprintf(cmd, "mode con cols=%d lines=%d", cols * 2, lines);
  system(cmd); // 执行命令设置窗口大小
}

/**
 * @brief 设置控制台光标位置
 * @param x 目标位置的x坐标（逻辑坐标）
 * @param y 目标位置的y坐标（逻辑坐标）
 * @details 使用Windows
 * API设置控制台光标位置，由于图形字符占2个字符宽度，x坐标需要乘以2
 */
void SetCursorPosition(const int x, const int y) {
  COORD position;     // Windows API中的坐标结构体
  position.X = x * 2; // 设置x坐标（乘以2因为图形字符占2个字符宽度）
  position.Y = y;     // 设置y坐标（行号不需要调整）

  // 调用Windows API设置控制台光标位置
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

/**
 * @brief 设置控制台文本颜色
 * @param colorID 颜色ID值（Windows控制台颜色码）
 * @details 使用Windows API设置后续输出的文本颜色
 *          常见颜色值：0-黑，1-蓝，2-绿，3-青，4-红，5-紫，6-黄，7-白等
 */
void SetColor(int colorID) {
  // 调用Windows API设置控制台文本属性（颜色）
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

/**
 * @brief 设置文本背景高亮颜色
 * @details
 * 设置文本为蓝色前景，白色背景（RGB全为1），形成高亮效果，用于菜单选项选中状态
 */
void SetBackColor() {
  // 设置控制台文本属性：
  // FOREGROUND_BLUE - 蓝色前景
  // BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED - 白色背景（RGB全为1）
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          FOREGROUND_BLUE |      // 蓝色前景
                              BACKGROUND_BLUE |  // 蓝色背景分量
                              BACKGROUND_GREEN | // 绿色背景分量
                              BACKGROUND_RED); // 红色背景分量（组合成白色背景）
}
